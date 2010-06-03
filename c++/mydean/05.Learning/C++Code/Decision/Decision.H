/* Decision.H
 *
 * This class is a container class for some globally available values,
 * such as the valid dimensions and classes for this problem.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include "String.H"

const int MAX_CLASSES = 20;  // The maximum number of classes allowed

class Dimension;
class Node;
class Decision {
friend ostream& operator<<(ostream &o, Decision &d);  // Print out the tree
public:
   static int num_classes;          // The number of classes for this run
   static char classes[MAX_CLASSES][MAX_STRING];   // Names for all classes
   static int lookup_class(char temp[]);  // Get the class index given the name
   static int majority_class;      // majority class in examples (LBH 3/96)

   static int num_dimensions;          // The number of dimensions for this run
   static Dimension **dimensions;      // Array of dimensions
   static int lookup_attribute(int x, char temp[]); // Get the dimension index

   Node *root;                     // The top of the decision tree

   Decision(char *filename);       // Construct a Decision given an info file
   ~Decision();                    // Destroy the decision tree

   void build_tree();              // Build the decision tree
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

