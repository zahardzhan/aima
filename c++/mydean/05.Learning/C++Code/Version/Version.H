/* Version.H
 *
 * This class serves as a wrapper for the entire version space algorithm.
 * It reads in dimensions and training examples from a file, and
 * refines the boundaries by processing each training example in turn.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include "Boundary.H"

class Example;
class Dimension;
class Concept;
class Version {
   Example *examples;       // A linked list of examples read in from the file
   Example *tail;           // The end of the examples linked list
   Boundary general_boundary;
   Boundary specific_boundary;

   void print_boundaries();    // Print both general and specific boundaries

public:
   static int num_dimensions;     // The number of dimensions for this run
   static Dimension dimensions[MAX_DIMENSIONS]; // Array of dimension objects
   Version(char *filename);       // Construct a Version given input file
   ~Version();                    // Destroy a version

   // Given a dimension index and a value name, get the associated value index
   static int lookup_value(int dim, char temp[]);

   void versions();                   // Refine the boundaries on all examples
   void refine(Example *example);     // Refine the boundaries on one example
   void generalize_specific(Example *example);  // Generalize specific boundary
   void specialize_general(Example *example);   // Specialize general boundary
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

