/* Example.H
 *
 * An example is an assignment of values to each possible attribute.
 * An example has a name, and also a classification value.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include "String.H"

class Example {
friend ostream& operator<<(ostream &o, Example &e);  // Print out the example
   char name[MAX_STRING];   // The name of this example
   int *values;  // Array of values. We use numbers to index
                 // into the symbols in the dimensions.

   int my_class; // Which of the valid classifications this is.

public:
   Example(char *_name, istream& in);   // Construct given a name and in file
   ~Example();                          // Destroy this example
   int get_class();             // Get the class index of this example
   int get_value(int dim);      // Get the value for a certain dimension.

   Example *next;               // The next example in a linked list.
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

