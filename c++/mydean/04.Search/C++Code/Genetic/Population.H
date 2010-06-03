/* Population.H
 *
 * The population of individuals which are mutated and tested.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

const int MAX_CHROMOSOMES = 1024; // Can't have more chromosomos than this many

class Chromosome;
class Population {
friend ostream& operator<<(ostream &o, Population &p);  // Print a population
  int num_chromosomes;          // The number of chromosomes in the population
  Chromosome *chromosomes;      // A linked list of chromosomes
  Chromosome *next_generation;  // A linked list: next chromosome generation

  void reproduce();             // Make a new generation from the current
  Chromosome *select();         // Randomly select a new chromosome by fitness
  void make_distribution();     // Build the distribution used in select()

public:
  Population(int num_individuals, int num_alleles);  // Construct a population
  ~Population();                // Destroy a population
  void evolve();                // Evolve one generation
  void add_new_chromosome(Chromosome *c);  // Add a next generation chromosome
                                // make the fitness values for all chromosomes
  void make_fitness(double (*function)(Chromosome *chromosome));
};

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

