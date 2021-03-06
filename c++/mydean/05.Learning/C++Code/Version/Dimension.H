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

#ifndef _DIMENSION_H_
#define _DIMENSION_H_

#include <iostream.h>
#include "String.H"

const int MAX_VALUES = 40;    // Same as MAX_CHILDREN for a node.
const int MAX_DIMENSIONS = 100;  // Cannot have more than this many dimensions

class Concept;
class Example;
class Boundary;
class Dimension {
friend istream& operator>>(istream &i, Dimension &d); // Read in this dimension
   char attribute[MAX_STRING];   // The names of the dimension's attributes

public:
   int num_values;               // The possible values for this dimension
   char values[MAX_VALUES][MAX_STRING];   // The names of all possible values
   char *get_attribute();        // Get the attribute name of this dimension
   int lookup(char temp[]);      // Give a value name, get the associated index
};

#endif

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

