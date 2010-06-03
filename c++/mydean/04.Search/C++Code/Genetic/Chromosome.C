/* Chromosome.C
 *
 * The Chromosome class contains the genotype for one individual,
 * which is a bunch of boolean-valued alleles.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include <math.h>
#include "Chromosome.H"

// Construct a chromosome and initialize it randomly with the given number
// of alleles.
Chromosome::Chromosome(int _num_alleles)
{
  num_alleles = _num_alleles;
  alleles = new int[num_alleles];
  for(int x = 0; x < num_alleles; x++)
    alleles[x] = rand() % 2;

  next = 0;
}

// Construct a chromosome to be a copy of the given chromosome, but mutated
Chromosome::Chromosome(Chromosome *c)
{
   num_alleles = c->num_alleles;
   alleles = new int[num_alleles];
   for(int x = 0; x < num_alleles; x++)
      alleles[x] = c->alleles[x];

   mutate();
   next = 0;
}

Chromosome::~Chromosome()
{
  delete [] alleles;
}

// Invert the bits 3% of the time
void Chromosome::mutate()
{
   for(int x = 0; x < num_alleles; x++)
      if(rand() % 100 < 3)
         alleles[x] = !alleles[x];
}

// Precompute the fitness value so it dosen't have to be computed over
// and over again later on. The fitness value is a result of whatever
// function we are trying to maximize.
void Chromosome::make_fitness(double (*function)(Chromosome *chromosome))
{
  fitness_value = (*function)(this);
}

// Get my fitness value.
double Chromosome::get_fitness()
{
  return fitness_value;
}

// Get the number of alleles I have
int Chromosome::get_num_alleles()
{
  return num_alleles;
}

// Get a particular allele from my array of alleles.
int Chromosome::get_allele(int index)
{
  return alleles[index];
}

// Return the decimal representation of this number. Actually, it is
// the representation were this chromosome a base 2 number.
double Chromosome::decimal()
{
  double sum = 0;
  for(int i = 0; i < num_alleles; i++)
    sum += alleles[i] * pow(2, i);

  return sum;
}

// Set my portion of my population's distribution. The size of my portion
// will be larger if I have a higher fitness value. The "sum" here is
// the sum of all the fitnesses in the entire population.
void Chromosome::set_distribution(double sum)
{
   distribution = fitness_value / sum;
}

// Get my portion of the distribution
double Chromosome::get_distribution()
{
   return distribution;
}

// Crossover at a random site 60% of time
void Chromosome::crossover(Chromosome *c)
{
   if(rand() % 100 > 60)
      return;

   int position = rand() % num_alleles;
   int x,y;
   for(x = position; x < num_alleles; x++) {
      y = alleles[x];
      alleles[x] = c->alleles[x];
      c->alleles[x] = y;
   }
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

