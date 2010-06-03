/* Population.C
 *
 * The population of individuals which are mutated and tested.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream.h>
#include "Population.H"
#include "Chromosome.H"

// Print a message saying how to use this program. Exit with error number.
void usage()
{
   cerr << "Usage: genetic <-multiple> <-single> <-a num> <-i num> <-g num>"
        << endl;
   cerr << "     -multiple   Evolve to maximize the multiple function" << endl;
   cerr << "     -single     Evolve to maximize the single function" << endl;
   cerr << "     -a num      Use num many alleles in each individual" << endl;
   cerr << "     -i num      Use num many individuals in the population"
        << endl;
   cerr << "     -g num      Use num many generations of evolution" << endl;
   exit(1);
}

// This function is used in the multiple() function below.
double gaussian(double x, double c, double w)
{
  return exp(- ((x - c) * (x - c)) / (2 * w));
}

// A function for determining fitness that our population can evolve towards
double multiple_func(Chromosome *chromosome)
{
  if(chromosome->get_num_alleles() != 30) {
    cerr << "The multiple() function requires 30 allele chromosomes" << endl;
    exit(1);
  }

  double x = chromosome->decimal() / (pow(2, 30) - 1);

  return    (0.50 * gaussian(x, 0.125, 0.003125))
	  + (0.25 * gaussian(x, 0.375, 0.003125))
	  + (1.00 * gaussian(x, 0.625, 0.003125))
	  + (0.25 * gaussian(x, 0.875, 0.003125));
}

// A function for determining fitness that our population can evolve towards
double single_func(Chromosome *chromosome)
{
  if(chromosome->get_num_alleles() != 30) {
    cerr << "The single() function requires 30 allele chromosomes" << endl;
    exit(1);
  }

  return pow(chromosome->decimal() / (pow(2, 30) - 1), 10);
}

// The main() function is the first function called in the program.
// It reads in the command line options, starts up the population,
// and runs the evolution algorithm.
int main(int argc, char *argv[])
{
// Seed the random number generator, if we aren't debugging this program.
#ifndef DEBUG
   srand((unsigned int) time(0));
#endif

   int num_alleles = 30;
   int num_individuals = 30;
   int num_generations = 10;
   double (*function)(Chromosome *chromosome) = NULL;
   
   for(int x = 1; x < argc; x++)   // Cycle through all command line words
      if(argv[x][0] == '-')        // If it starts with dash
         switch(argv[x][1]) {      //     handle the -a  or  -e
         case 'a':      // Set the number of alleles per individual
            if(++x < argc)
               num_alleles = atoi(argv[x]);
            else
               usage();      // Error. Print usage message.
            break;
         case 'i':      // Set the number of individuals (i.e. chromosomes)
            if(++x < argc)
               num_individuals = atoi(argv[x]);
            else
               usage();      // Error. Print usage message.
            break;
         case 'g':      // Set the number of generations to evolve
            if(++x < argc)
               num_generations = atoi(argv[x]);
            else
               usage();      // Error. Print usage message.
            break;
         case 'm':      // Use the multiple() function for fitness measurement
            if(function)
               usage();
            else
               function = multiple_func;
            break;
         case 's':      // Use the single() function for fitness measurement
            if(function)
               usage();
            else
               function = single_func;
            break;
         default:
            usage();
         }

   if(!function)
       usage();

   // Make a population with the given number of chromosomes, each with its
   // own given number of alleles.
   Population population(num_individuals, num_alleles);

   // Precompute the fitness for each chromosome
   population.make_fitness(function);
   cout << population << endl;
   for(x = 0; x < num_generations; x++) {    // Evolve this many times
     population.evolve();
     population.make_fitness(function);      // Evolve
     cout << population << endl;             // print max and average fitness
   }

   return 0;
}

// Construct a population with the given number of chromosomes, each
// having the given number of alleles. Each chromosome's alleles are
// randomly initialized.
Population::Population(int num_individuals, int num_alleles)
{
  chromosomes = NULL;
  next_generation = NULL;
  num_chromosomes = num_individuals;
  Chromosome *c;

  // Build a linked list of all the randomly initialized chromosomes
  for(int x = 0; x < num_chromosomes; x++) {
    c = new Chromosome(num_alleles);
    c->next = chromosomes;
    chromosomes = c;
  }
}

// Destroy a population, which means destroying all dynamically allocated data
Population::~Population()
{
  delete chromosomes;
}

// Precompute the fitness values for all chromosomes in this population
void Population::make_fitness(double (*function)(Chromosome *chromosome))
{
  for(Chromosome *c = chromosomes; c; c = c->next)
     c->make_fitness(function);
}

// Evolve the population by evaluating the fitness of each individual
// and reproducing a new generation based on the distribution of fitness
// of the old generation
void Population::evolve()
{
  next_generation = NULL;
  reproduce();
  delete chromosomes;
  chromosomes = next_generation;
}

// Reproduce the current population by crossover() and mutation()
void Population::reproduce()
{
   make_distribution();
   for(int i = 0; i < num_chromosomes / 2; i++) {
      Chromosome *x = select();  // Grab random chromosome by fitness, mutated
      Chromosome *y = select();  // Grab random chromosome by fitness, mutated
      x->crossover(y);           // Perform crossover on the two chromosomes

      add_new_chromosome(x);     // Add x to the new generation of chromosomes
      add_new_chromosome(y);     // Add y to the new generation of chromosomes
   }
}

// Make the distribution of chromosomes in the population. Here's how this
// works. Each chromosome in the population has a fitness generated
// by the current measuring function. We want to maximize this fitness
// function. We add together all the chromosome fitness values, and tell
// each chromosome what portion of the total fitness it has. This is the
// distribution. Chromosomes with a higher fitness value have a larger
// portion of the distribution, and thus are more likely than their
// brethren to be chosen randomly for the next generation.
void Population::make_distribution()
{
   double sum = 0;
   for(Chromosome *c = chromosomes; c; c = c->next)
      sum += c->get_fitness();

   for(c = chromosomes; c; c = c->next)
      c->set_distribution(sum);
}

// Return a dynamically allocated mutatation of a chromosome randomly
// selected from the population by distribution. Because chromosomes with
// a higher fitness "stick out" in the distribution by having a larger
// portion of the distribution, they are more likely to be chosen.
Chromosome *Population::select()
{
   double random = rand() % 20000 / 20000.0;
   double prob = 0;

   for(Chromosome *c = chromosomes; c; c = c->next) {
      prob += c->get_distribution();
      if(prob > random)
         break;
   }

   return new Chromosome(c);
}

// Add a new chromosome to the next generation of chromosomes being born
void Population::add_new_chromosome(Chromosome *c)
{
   c->next = next_generation;
   next_generation = c;
}

// Print a population
ostream& operator<<(ostream &o, Population &p)
{
  double max = p.chromosomes->get_fitness();
  double sum = 0;
  double fitness;
  for(Chromosome *c = p.chromosomes; c; c = c->next) {
    fitness = c->get_fitness();
    sum += fitness;
    if(max < fitness)
      max = fitness;
  }

  o << "Fittest " << max << " Average " << sum / p.num_chromosomes << endl;

  return o;
}

/*
 * Copyright 1994, Brown University, Providence, RI
 *
 * Permission to use and modify this software and its documentation for
 * any purpose other than its incorporation into a commercial product is
 * hereby granted without fee.  Permission to copy and distribute this
 * software and its documentation only for non-commercial use is also
 * granted without fee, provided, however, that the above copyright notice
 * appear in all copies, that both that copyright notice and this permission
 * notice appear in supporting documentation, that the name of Brown
 * University not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission,
 * and that the person doing the distribution notify Brown University of
 * such distributions outside of his or her organization. Brown University
 * makes no representations about the suitability of this software for
 * any purpose.  It is provided "as is" without express or implied warranty.
 * Brown University requests notification of any modifications to this
 * software or its documentation.
 *
 * Send the following redistribution information:
 *
 *	Name:
 *	Organization:
 *	Address (postal and/or electronic):
 *
 * To:
 *	Software Librarian
 *	Computer Science Department, Box 1910
 *	Brown University
 *	Providence, RI 02912
 *
 *		or
 *
 *	brusd@cs.brown.edu
 *
 * We will acknowledge all electronic notifications.
 */

