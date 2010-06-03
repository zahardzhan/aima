/* Formula.C
 *
 * A predicate calculus formula, which can be stored in the decision tree.
 * Formulas can also be used to match against other formulas.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include "Formula.H"
#include "Key.H"

// Construct a formula with no keys. The data for the formula must be
// installed right away.
Formula::Formula()
{
   next = NULL;
   keys = NULL;
   keys_tail = NULL;
}

// Destroy a formula, which means destroying any dynamically allocated memory.
Formula::~Formula()
{
   delete keys;
   delete next;
}

// Compare two formulas for an exact match. A simple match is not enough.
int operator==(const Formula& f1, const Formula& f2)
{
  Key *key1 = f1.keys;
  Key *key2 = f2.keys;
  while(key2 && key1 && *key1 == *key2) {
    key2 = key2->next;
    key1 = key1->next;
  }

  if(key1 || key2)
    return 0;
  else
    return 1;
}

// Read in a formula from a stream
istream& operator>>(istream &i, Formula &f)
{
   Key *key;
   char word[MAX_STRING];
   int depth = 0;
   while(!i.fail()) {
      i >> word;
      key = new Key(word);
      if(f.keys)
         f.keys_tail->next = key;
      else
         f.keys = key;
      f.keys_tail = key;
      if(word[0] == '(')
	depth++;
      if(word[0] == ')' && --depth == 0)
	  break;
   }

   return i;
}

// Return the keylist for this formula
Key *Formula::get_keys()
{
   return keys;
}

// Print out the formula
ostream& operator<<(ostream &o, Formula &f)
{
   for(Key *key = f.keys; key; key = key->next)
      o << *key << " ";

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

