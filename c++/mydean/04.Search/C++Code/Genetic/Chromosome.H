/* Chromosome.H
 *
 * The Chromosome class contains the genotype for one individual,
 * which is a bunch of boolean-valued alleles.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

class Chromosome {
  double fitness_value;               // The fitness metric of this chromosome
  int num_alleles;                    // How many alleles this has
  int *alleles;                       // the array of alleles, boolean values
  double distribution;                // My part in the fitness distribution
  void mutate();                      // mutate me!

public:
  Chromosome *next;                   // The next chromosome in the linked list

  Chromosome(int _num_alleles);       // Construct a randomly init'd chromosome
  Chromosome(Chromosome *c);          // Construct a copy of given chromosome
  ~Chromosome();                      // Destroy this chromosome

  // Precompute the fitness metric, so it dosen't have to be recomputed a lot
  void make_fitness(double (*function)(Chromosome *chromosome));
  double get_fitness();               // Get my fitness value
  int get_num_alleles();              // Get how many alleles I have
  int get_allele(int index);          // Get a specific allele
  double decimal();                   // The decimal equivalent of my alleles
  void set_distribution(double sum);  // Set my portion of the distribution
  double get_distribution();          // Get my portion of the distribution
  void crossover(Chromosome *c);      // Perform crossover on me and given
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

