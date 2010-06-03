/* Node.C
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

#include "Node.H"
#include "Formula.H"
#include "Key.H"
#include "DTree.H"

// Construct a node
Node::Node()
{
  num_children = 0;
  num_formulas = 0;
}

// Destroy a node, which means destroying all the dynamically allocated memory.
Node::~Node()
{
  for(int x = 0; x < num_formulas; x++)
    delete formulas[x];

  for(x = 0; x < num_children; x++) {
    delete children_keys[x];
    delete children[x];
  }
}

// Add a formula to this node
void Node::add(Formula *formula)
{
   formulas[num_formulas++] = formula;
}

// Given a pattern (a list of keys), index returns a terminal descrimination
// tree corresponding to the given pattern exactly (not a match, which
// might return several terminal nodes). If no matching terminal is found,
// then a new terminal is created, and the new terminal is returned.
Node *Node::index(Key *keys)
{
   if(!keys)
      return this;

   for(int x = 0; x < num_children; x++)
      if(*keys == *children_keys[x])
         return children[x]->index(keys->next);

   children[num_children] = new Node;
   children_keys[num_children] = new Key(*keys);

   return children[num_children++]->index(keys->next);
}

// Is there an exact match for this formula in this node?
int Node::member(Formula *formula)
{
  for(int x = 0; x < num_formulas; x++)
      if(*formulas[x] == *formula)
         return 1;

   return 0;
}

// Given the list of keys, find all the children nodes that match it
// and add all the formulas from those matching nodes to the DTree's
// linked list of results.
//
// We know we're done matching if the keys linked list is empty. So add
// the current node's formulas to the DTree's linked list of results.
//
// Otherwise, a symbol matches a symbol with the same name, or
// a variable. A variable matches a symbol, or a nested expression,
// or another variable! The only really hard case is matching a key's variable
// against a child's nested expression. To do this, we have to do a depth
// first search starting at the child (with an open paren) to find
// the matching close paren for any node in that child's subtree. Of course
// we have to ignore intervening subexpressions, so we need a variable
// to keep track of the depth.
void Node::extract(Key *keys)
{
  int x;
   if(!keys)       // No keys to match means we've succeeded! A match!
      for(x = 0; x < num_formulas; x++)    // So dump all my formulas
         DTree::add_result(formulas[x]);   // onto the DTree's list of results
   else
     for(x = 0; x < num_children; x++)     // Check out all the children
       switch(keys->type) {
       case VARIABLE:     // A variable matches a variable, symbol, or subexpr
          switch(children_keys[x]->type) {
          case BEGIN:
             children[x]->strip_off_subexp_keys_extract(keys->next, 0);
             break;
          case VARIABLE:
          case SYMBOL:
             children[x]->extract(keys->next);
             break;
          case END:    // No match
             break;
          }
          break;
       case BEGIN:        // A subexpr starts with begin, and
                          // matches a variable or another subexpr
          switch(children_keys[x]->type) {
          case BEGIN:
             children[x]->extract(keys->next);
             break;
          case VARIABLE:   // May match keys starting from end
             children[x]->extract(keys->skip_subexpr(0));
             break;
          case END:    // No match
          case SYMBOL: // No match
             break;
          }
          break;
       case SYMBOL:       // A symbol can match a variable
          if(children_keys[x]->type == VARIABLE)
             children[x]->extract(keys->next);
       case END:          // A symbol (fall through) or END matches itself
          if(*children_keys[x] == *keys)
             children[x]->extract(keys->next);
          break;
       }
}

// When we want to match a variable key with a subexpression, we need
// to do a depth-first search through the child's subtree to find the
// closing paren that marks the end of the subexpression. Of course,
// there may be intervening subexpressions, so keep track of the depth
// so those can be handled.
void Node::strip_off_subexp_keys_extract(Key *keys, int depth)
{
  for(int x = 0; x < num_children; x++)
    switch(children_keys[x]->type) {
    case BEGIN:    // An intervening subexpression
      children[x]->strip_off_subexp_keys_extract(keys, depth + 1);
      break;
    case VARIABLE: // part of a subexpression, ignore
    case SYMBOL:
      children[x]->strip_off_subexp_keys_extract(keys, depth);
      break;
    case END:      // The end of a subexpression, but is it a nested one?
      if(depth == 0)
	children[x]->extract(keys);   // If not nested, continue the extraction
      else
	children[x]->strip_off_subexp_keys_extract(keys, depth - 1);
      break;
    }
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

