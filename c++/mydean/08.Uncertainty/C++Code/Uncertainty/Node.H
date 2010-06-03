/* Node.H
 *
 * A node represents one variable in the network, with dependencies to both
 * parents and children.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#ifndef _NODE_H_
#define _NODE_H_

#include <iostream.h>
#include "Support.H"

const int MAX_PARENTS = 100;        // Cannot have more than this many parents
const int MAX_CHILDREN = 100;       // Cannot have more than this many children
const int MAX_NAME_LENGTH = 100;    // Name of node cannot be longer than this

enum EvidenceType {
   NEGATIVE,
   POSITIVE,
   NO_VALUE
};

class Node {
   /********************  Overloaded Operators *********************/
friend istream& operator>>(istream &i, Node &n);   // Read in a node
friend ostream& operator<<(ostream &o, Node &n);   // Print out a node

   /********************  Approximation Algorithm *********************/
private:
   Support scores;                    // Scores for stochastic simulation
public:
   int simulate();                    // Simulate propagating values
   void update_scores(double weight); // Update scores with likelihood weighting
   void estimate();         // Estimate posterior probabilty for node = FALSE
   double probability(EvidenceType val);  // Compute probability of node = val

   /********************  Exact Algorithm *********************/
private:
   Support causal_support;
   Support diagnostic_support[MAX_CHILDREN];

   void up(Node *sender, Support support);   // Propagate support up to parent
   void down(Node *sender, Support support); // Propagate support down to child
   Support causal(Node *child);              // Causal support I have for child
   Support diagnostic(Node *parent);         // Diagnostic support I have for p
   Support get_causal_support();             // Get causal support for this node
   Support get_distribution(int parent_value);
public:
   void initialize_priors();    // Assign diagnostic support and propagate down
   void propagate();   // Propagate evidence down from roots, up from terminals
   void posterior();   // Compute probability that node is false given evidence
   int get_num_parents();  // Return the number of parents this node has

   /********************  General Stuff *********************/
private:
   int num_parents;              // The number of parents this node has
   Node *parents[MAX_PARENTS];   // pointers to all the parents this node has

   int num_children;             // The number of children this node has
   Node *children[MAX_CHILDREN]; // pointers to all the children this node has

   char name[MAX_NAME_LENGTH];   // The name of this node as read in from file

   // If the node has a parent, then prior_distribution[y] is the
   // support for the node, given that the parent has the value y.
   // If the node has no parent, then prior_distribution[0] is
   // the support for the node. The program assumes that no node will ever
   // have more than one parent, greatly simplifying this data structure.
   Support prior_distribution[2];

   double prob_given_the_evidence;   // Calculated probability of node = FALSE
   EvidenceType value;               // Value for this node if evidence given

public:
   Node(char *_name);                // Construct a node given name
   ~Node();                          // Destructor

   void add_child(Node *child);      // Add a child to this node
   void set_value(EvidenceType _value);   // Set the value of this node
   int match(char *_name);           // Does this node's name match given name?
};

#endif

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

