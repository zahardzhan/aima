/* Formula.H
 *
 * A predicate calculus formula, which can be stored in the decision tree.
 * Formulas can also be used to match against other formulas.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>

class Key;
class Formula {
friend istream& operator>>(istream &i, Formula &f);  // Read in a formula
friend ostream& operator<<(ostream &o, Formula &f);  // Print out the formula
friend int operator==(const Formula& f1, const Formula& f2);
   Key *keys;         // A linked list of keys for this formula
   Key *keys_tail;    // The end of the linked list of keys
public:
   Formula *next;     // The next formula in a linked list of matching formulas
                      // This is used solely to string together a bunch of
                      // formulas that happens to match a fetch() request.

   Formula();         // Construct a formula (it must be filled in with data)
   ~Formula();        // Destroy a formula
   Key *get_keys();   // Get the key list for this formula
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

