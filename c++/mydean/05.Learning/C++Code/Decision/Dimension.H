/* Dimension.H
 *
 * Each example that we want to place in the decision tree has a value for
 * each attribute. An attribute together with all the possible values for
 * the attribute we call a dimension. The dimension class stores an
 * attribute and its possible values, which is handy for various reasons.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include "String.H"

const int MAX_VALUES = 40;    // Same as MAX_CHILDREN for a node.

class Node;
class Example;
class Dimension {
friend istream& operator>>(istream &i, Dimension &d);
   char attribute[MAX_STRING];

public:
   int num_values;            // How many values this dimension has
   char values[MAX_VALUES][MAX_STRING];  // The names of all values

   int lookup(char temp[]);   // Lookup the index of a given value
   char *get_attribute();     // Return the name of the attribute
   Dimension();               // Construct a Dimension object
   ~Dimension();              // Destroy this dimension

   Dimension *next;           // List of unused attributes (LBH 3/96)
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

