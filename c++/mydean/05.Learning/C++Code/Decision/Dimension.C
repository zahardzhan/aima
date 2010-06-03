/* Dimension.C
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

#include "String.H"
#include "Dimension.H"
#include "Example.H"
#include "Node.H"

// Build a dimension
Dimension::Dimension()
{
  next = NULL;  // (LBH 3/96)
}

// Destroy a dimension
Dimension::~Dimension()
{
}

// Given a name, lookup the index of the corresponding value
int Dimension::lookup(char temp[])
{
   for(int x = 0; x < num_values; x++)
      if(strcmp(temp, values[x]) == 0)
         return x;
}

// Return the name of the attribute for this dimension
char *Dimension::get_attribute()
{
   return attribute;
}

// Read in a dimension from a file
istream& operator>>(istream &i, Dimension &d)
{
   i >> d.attribute;

   i >> d.num_values;
   for(int x = 0; x < d.num_values; x++)
      i >> d.values[x];

   return i;
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

