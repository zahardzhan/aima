/* Node.H
 *
 * The Node class represents one node in the decision tree. A node is
 * associated with a bunch of formulas. If a search through the decision
 * tree for a match arrives at this node, then the formulas at this node
 * are matching formulas.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

// MAX_CHILDERN is large because if you have a lot of symbols, you
// may want a lot of children. You may even want to re-implement this
// using linked lists so that it can be as big as needed. However, for
// demonstrating the algorithm this versatility is not required.
const int MAX_CHILDREN = 1024;
const int MAX_FORMULAS = 1024;

class Formula;
class Key;
class Node {
   int num_children;
   Node *children[MAX_CHILDREN];      // The children of this node
   Key *children_keys[MAX_CHILDREN];  // The keys matching each child

   int num_formulas;                  // The number of formulas at this node
   Formula *formulas[MAX_FORMULAS];   // Formulas stored at this node

   // To match a variable with a begin-end clause, we have to do a
   // depth-first search to find all of the matching "end" parentheses
   // in the children of this node. Of course, there may be intervening
   // begin-end clauses, so the depth variable is used to keep track of
   // the nesting level.
   void strip_off_subexp_keys_extract(Key *keys, int depth);

public:
   Node();                         // Construct a new node
   ~Node();                        // Destroy the node
   Node *index(Key *keys);         // Get the node exactly matching the keys
   void extract(Key *keys);        // Find all formulas matching the keys
   int member(Formula *formula);   // Does this node hold the given formula?
   void add(Formula *formula);     // Add the formula to this node
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

