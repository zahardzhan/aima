/* Key.C
 *
 * A Key is a single element of a predicate calculus formula. It can
 * be a word, a variable, or a begin-end sequence.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include <stdlib.h>
#include "Key.H"
#include "String.H"

// Construct a key given its name. The type of the key is apparent from the name
Key::Key(char _name[])
{
   next = NULL;

   strncpy(name, _name, MAX_STRING);   // Copy the string
   switch(name[0]) {
   case '?':      // A variable
      type = VARIABLE;
      break;
   case '(':      // The begin symbol
      type = BEGIN;
      break;
   case ')':      // The end symbol
      type = END;
      break;
   default:       // a symbol
      type = SYMBOL;
      break;
   }
}

// Construct a copy of the given key.
Key::Key(Key& key)
{
  type = key.type;
  strncpy(name, key.name, MAX_STRING);

  next = NULL;
}

// Destroy this key, which means destroying the next key in the linked list
Key::~Key()
{
   delete next;
}

// Do these two keys match exactly? Simple matching is not sufficient.
int operator==(const Key& k1, const Key& k2)
{
   switch(k1.type) {
   case BEGIN:
   case END:
      return k1.type == k2.type;
      break;
   case VARIABLE:
   case SYMBOL:
      return (k1.type == k2.type) && (strcmp(k1.name, k2.name) == 0);
      break;
   }
}

// In a search for a match, we might want to match a subexpression in
// the keylist with a variable key at a node. To do this, we have to
// skip everything in the keylist's subexpression (since it matches
// the variable) and continue trying to match after the subexpression.
// This function performs the skipping. Of course, since there may be
// intervening nested subexpressions, we have to skip those also and
// keep track of the depth.
Key *Key::skip_subexpr(int depth)
{
  switch(type) {
  case BEGIN:     // Marks the start of an intervening subexpression
    return next->skip_subexpr(depth + 1);
  case END:       // The end of a subexpression. But is it nested?
    if(depth == 0)
      return next;  // Not nested, done skipping
    else
      return next->skip_subexpr(depth - 1);  // Else continue skipping
  case VARIABLE:
  case SYMBOL:
    return next->skip_subexpr(depth);
  }
}

// Print out the key
ostream& operator<<(ostream &o, Key &k)
{
   o << k.name;

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

