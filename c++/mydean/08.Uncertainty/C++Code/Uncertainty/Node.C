/* Node.C
 *
 * A node represents one variable in the network, with dependencies to both
 * parents and children.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include "String.H"
#include "Network.H"
#include "Node.H"

   /****************************************************************/
   /********************  Overloaded Operators *********************/
   /****************************************************************/

// Read in a node from a file. This means read in optional parent line
// and mandatory distribution line. The distribution line must come last.
istream& operator>>(istream &i, Node &n)
{
   char word[25];
   char cmd[25];
   int x, y;

   do {   // Cycle until distribution command given
      i >> cmd;          // Must be "parent" or "distribution"
      i >> word;         // Should be name of this node
      if(strcmp(word, n.name) != 0) {
         cerr << "Expecting node " << n.name << " got node " << word
            << endl;
         exit(1);
      }
      switch(cmd[0]) {
      case 'p':                // Parents command
         i >> n.num_parents;
         if(n.num_parents > 1) {
            cerr << "This program cannot handles cases of more" << endl;
            cerr << "than one parent." << endl;
            exit(1);
         }
         for(x = 0; x < n.num_parents; x++) {
            i >> word;
            n.parents[x] = Network::lookup(word);
            n.parents[x]->add_child(&n);
         }
         break;
      case 'd':                // Distribution command
         i >> n.prior_distribution[0];
         if(n.num_parents == 1)         // Assume no more than one parent.
            i >> n.prior_distribution[1];
         break;
      }
   } while(cmd[0] != 'd');  // Cycle until distribution command given

   return i;
}

// Print a node out. This means printing the name and the probability
// given the evidence.
ostream& operator<<(ostream &o, Node &n)
{
   o << "Node " << n.name << " has distribution ("
     << n.prob_given_the_evidence << ", "
     << 1 - n.prob_given_the_evidence << ")";

   return o;
}

   /*******************************************************************/
   /********************  Approximation Algorithm *********************/
   /*******************************************************************/

// Simulate this node by propagating values forward through the network.
// Return a 1 if this node was changed, otherwise 0. Whether a node
// changes is important information, because we cycle through all nodes
// repeatedly until no node changes.
int Node::simulate()
{
   if(value != NO_VALUE)    // Ignore a node if it already has a value
      return 0;      // This node was not changed

   for(int x = 0; x < num_parents; x++)    // Ignore if it has one or more
      if(parents[x]->value == NO_VALUE)  // parents with no value
         return 0;   // This node was not changed

   // Choose a random number from 0 to 1. If it's below the probability
   // threshhold, then call this node negative.
    if((rand() % 10000) / 10000.0 < probability(NEGATIVE))
      value = NEGATIVE;
   else
      value = POSITIVE;

   return 1;         // This node was changed
}

// Update the scores of this node using likelihood weighting
void Node::update_scores(double weight)
{
   switch(value) {
   case NEGATIVE:
      scores += Support(weight, 0);
      break;
   case POSITIVE:
      scores += Support(0, weight);
      break;
   case NO_VALUE:         // Should never get here.
      break;
   }
}

// Estimate the posterior probability that the node is False. The probability
// for the node being True is just one minus the probability that it is False.
void Node::estimate()
{
   switch(value) {
   case NEGATIVE:   // No sense in estimating evidence nodes
      prob_given_the_evidence = 1;
      break;
   case POSITIVE:   // No sense in estimating evidence nodes
      prob_given_the_evidence = 0;
      break;
   case NO_VALUE:
      prob_given_the_evidence = scores.normalize().sup[0];
      break;
   }
}

// Return the probability of this node being the given value
// This can be estimated from the parents' values and the distribution.
// We assume at most one parent, which simplifies the distribution greatly.
// This method is never called unless the parents all have values.
double Node::probability(EvidenceType val)
{
   if(num_parents == 0)
      return prior_distribution[0].sup[val];
   else   // must be 1 parent
      return prior_distribution[parents[0]->value].sup[val];
}

   /***********************************************************/
   /********************  Exact Algorithm *********************/
   /***********************************************************/

// The following propagation code applies to any singly-connected network.
// However, the code for computing causal and diagnostic support applies
// only to tree-structured networks. As an exercise, you are asked to
// extend the code to handle the sinlge-connected case.

// Propagate diagnostic support up from a sender node to its parent
// receiver. If the diagnostic support from the sender is unchanged or
// the receiver is an instantiated root node, then quit, otherwise
// update the diagnostic support from the sender, propagate diagnostic
// support up to the parents, and propagate causal support down to
// each child except the sender.
void Node::up(Node *sender, Support support)
{
  // What child is this?
  for(int child_num = 0; child_num < num_children; child_num++)
    if(children[child_num] == sender)
      break;

  // Don't propagate support if it has not changed, or the recipient
  // is an instantiated root node.
  if(diagnostic_support[child_num] == support
     || (num_parents == 0 && value != NO_VALUE))
      return;

  diagnostic_support[child_num] = support;
  // Propagate support up to each parent
  for(int x = 0; x < num_parents; x++)
    parents[x]->up(this, diagnostic(parents[x]));

  // Propagate support down to each child but sender
  for(x = 0; x < num_children; x++)
    if(children[x] != sender)
      children[x]->down(this, causal(children[x]));
}

// Propagate causal support down from sender to receiver. If the
// causal support from the sneder is unchanged, then quit,
// otherwise update the causal support from the sender. If the receiver
// is an uninstantiated terminal node, then quit, otherwise propagate
// diagnostic support up to each parent except the sender and
// propagate causal support down to each child. Note that using
// the path-based definition of independence, we could implement
// further optimizations terminating propagation.
void Node::down(Node *sender, Support support)
{
  if(causal_support == support)
    return;

  causal_support = support;
  // Don't propagate through an uninstantiated terminal node
  if(num_children == 0 && value == NO_VALUE)
    return;

  // Propagate support up to each parent except sender
  for(int x = 0; x < num_parents; x++)
    if(parents[x] != sender)
      parents[x]->up(this, diagnostic(parents[x]));

  // Propagate support down to each child
  for(x = 0; x < num_children; x++)
      children[x]->down(this, causal(children[x]));
}

// Compute the causal support originating in this node for the
// given child. The child is the recipient. This node is the sender.
Support Node::causal(Node *child)
{
  // Handle root nodes specially.
  Support terms;
  
  if(num_parents == 0 && value != NO_VALUE)
    return child->get_distribution(value);
  else {
     terms = get_causal_support();
     for(int kid = 0; kid < num_children; kid++)
        if(children[kid] != child)
           terms *= diagnostic_support[kid];
     
     Support distribution = terms.normalize();

     Support support;
     for(int u = 0; u < 2; u++)
        support += child->get_distribution(u) * distribution.sup[u];
     
     return support;
  }
}

// Compute the diagnostic support originating in this node for the parent.
// We don't have to know the recipient for the tree-structured case,
// since the recipient is always the node's single parent.
Support Node::diagnostic(Node *parent)
{
   // If this node is terminal, then treat it specially
   if(num_children == 0)
      if(value == NO_VALUE)
         return Support(1, 1);
      else
         return Support(prior_distribution[0].sup[value],
                        prior_distribution[1].sup[value]);
   else {
      Support support;
      for(int v = 0; v < 2; v++)
         for(int u = 0; u < 2; u++) {
            double prod = get_distribution(v).sup[u];
            for(int x = 0; x < num_children; x++)
               prod *= diagnostic_support[x].sup[u];
            support.sup[v] += prod;
         }
      return support;
   }
}

// Return the causal support for this node being the given value.
Support Node::get_causal_support()
{
   if(num_parents > 0)   // We assume no more than one parent.
      return causal_support;
   else
      return prior_distribution[0];
}

// Return the distribution of this node, given that the parent has the given
// value. Of course, this only works for nodes with only one parent,
// which is the assumption of this program.
Support Node::get_distribution(int parent_value)
{
  return prior_distribution[parent_value];
}

// Initialize support for each node in the network by assigning diagnostic
// support to each node and then propagating the priors from the root nodes
// down. In the case of tree-structured networks, there will be exactly
// one root node.
void Node::initialize_priors()
{
   if(num_parents == 0)  // Only do this if I am a root node.
      for(int x = 0; x < num_children; x++)
         children[x]->down(this, causal(children[x]));
}

// Propagate evidence down from root nodes and up from terminal nodes. Only
// boundary nodes are allowed to be assigned values as evidence.
void Node::propagate()
{
   int x;
   if(num_parents == 0)
      for(x = 0; x < num_children; x++)   // Propagate support down to children
         children[x]->down(this, causal(children[x]));
   else if(num_children == 0)
      for(x = 0; x < num_parents; x++)    // Propagate support up to parents
         parents[x]->up(this, diagnostic(parents[x]));
   else {
      cerr << "Illegal evidence node " << name << endl;
      exit(1);
   }
}

// Compute the probability that the associated random variable is False
// given the evidence. The probability that the variable is True is just
// one minus the probability it is False. The function posterior is called
// on each node when propagation is complete.
void Node::posterior()
{
  switch(value) {
  case POSITIVE:
    prob_given_the_evidence = 0;
    break;
  case NEGATIVE:
    prob_given_the_evidence = 1;
    break;
  case NO_VALUE:
    Support terms;
    terms = get_causal_support();
    for(int x = 0; x < num_children; x++)
      terms *= diagnostic_support[x];
    prob_given_the_evidence = terms.normalize().sup[0];
    break;
  }
}

// Return the number of parents this node has
int Node::get_num_parents()
{
   return num_parents;
}

   /*********************************************************/
   /********************  General Stuff *********************/
   /*********************************************************/

// Create a node
Node::Node(char *_name)
{
   num_parents = 0;                         // It has no parents (yet)
   num_children = 0;                        // It has no children (yet)
   strncpy(name, _name, MAX_NAME_LENGTH);   // copy over the name
   value = NO_VALUE;                        // No evidence gives a value (yet)
}

// Destroy a node
Node::~Node()
{
}

// Add a chlid to a node. Increase the num_children counter and add
// diagnostic support for the child.
void Node::add_child(Node *child)
{
   diagnostic_support[num_children] = Support(1,1);
   children[num_children++] = child;
}

// Set the value of this node.
void Node::set_value(EvidenceType _value)
{
   value = _value;
}

// Does this node's name match the given name? strcmp will compare the strings
int Node::match(char *_name)
{
   return strcmp(name, _name) == 0;
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

