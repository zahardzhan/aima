/* Example.C
 *
 * An example is an assignment of values to each possible attribute.
 * An example has a name, and also a classification value.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include <stdlib.h>
#include "Example.H"
#include "Version.H"
#include "Dimension.H"

Example::Example(char *_name, istream &in)
{
   strncpy(name, _name, MAX_STRING);

   char word[MAX_STRING];
   in >> word;

   switch(word[0]) {
   case 'y':
      my_class = POSITIVE;
      break;
   case 'n':
      my_class = NEGATIVE;
      break;
   default:
      cerr << "Invalid class for example " << name << "." << endl;
      exit(1);
   }

   for(int x = 0; x < Version::num_dimensions; x++) {
      in >> word;
      values[x] = Version::lookup_value(x, word);
   }
}

Example::~Example()
{
}

int Example::is_positive()
{
   return my_class == POSITIVE;
}

// Get the value for a certain dimension.
int Example::get_value(int dim)
{
   return values[dim];
}

// Print out this example
ostream& operator<<(ostream &o, Example &e)
{
  o << e.name;
  if(e.my_class)
    o << " [yes] ";
  else
    o << " [no] ";

  for(int x = 0; x < Version::num_dimensions; x++)
    o << "(" << Version::dimensions[x].get_attribute() << " "
      << Version::dimensions[x].values[e.values[x]] << ") ";

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

