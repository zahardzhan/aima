/* Example.C
 *
 * An example is an assignment of values to each possible attribute.
 * An example has a name, and also a classification value.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include "Decision.H"
#include "Example.H"
#include "Dimension.H"


// Construct an example, given the name of the example and an input stream.
// This input stream is the input from the examples file.
Example::Example(char *_name, istream& in)
{
  strncpy(name, _name, MAX_STRING);
  char word[MAX_STRING];
  in >> word;   // Should be the class value
  my_class = Decision::lookup_class(word);

  values = new int[Decision::num_dimensions];
  for(int x = 0; x < Decision::num_dimensions; x++) {
    in >> word;
    values[x] = Decision::lookup_attribute(x, word);
  }
}

// Destroy this example. That means destroying the dynamically allocated memory
Example::~Example()
{
   delete [] values;
}

// Get the index of the class this example goes with
int Example::get_class()
{
   return my_class;
}

// Get the value for a certain dimension.
int Example::get_value(int dim)
{
   return values[dim];
}

// Print out the example
ostream& operator<<(ostream &o, Example &e)
{
   o << e.name << " [" << Decision::classes[e.my_class] << "] ";

   for(int x = 0; x < Decision::num_dimensions; x++) {
      o << "(";
      o << Decision::dimensions[x]->get_attribute() << ", ";
      o << Decision::dimensions[x]->values[e.values[x]] << ") ";
   }

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

