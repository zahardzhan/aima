/* Key.H
 *
 * A Key is a single element of a predicate calculus formula. It can
 * be a word, a variable, or a begin-end sequence.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include "String.H"

// A key can have various types. A symbol is any word, except those that
// begin with a '?'. A variable is any word that begins with a '?'.
// BEGIN corresponds to the open paren. END corresponds to the close paren.
enum KeyType {
  VARIABLE,
  BEGIN,
  END,
  SYMBOL
};

class Key {
friend istream& operator>>(istream &i, Key &k);  // Read in a key
friend ostream& operator<<(ostream &o, Key &k);  // Print out the key
friend int operator==(const Key& k1, const Key& k2);  // Do keys match exactly?

   char name[MAX_STRING];   // The name of this key
public:
   Key(char _name[]);       // Construct a key given its name
   Key(Key& key);           // Make a copy of the given key
   ~Key();                  // Destroy this key
   Key *skip_subexpr(int depth);  // Skip to the end of the current subexpr
   Key *next;               // The next key in a linked list of keys
   KeyType type;            // The type of this key
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

