/* Node.H
 *
 * The decision tree is built from nodes.
 *
 * To classify an example, we start at the node of the decision tree
 * and work our way down until we reach a yes or no answer. Each
 * node has some question to ask, and depending on the answer to that
 * question, we choose one of the children. This "question" is called
 * an attribute. We store a dimension with the node, because this lets
 * us know the name of the attribute as well as all the possible values.
 * Each different value as an "answer" to the attribute question would
 * direct the search to a different child.
 *
 * Each node is also associated with one or more examples, if it is
 * a leaf node. These examples are previous data that helped to build
 * the tree.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

const int MAX_CHILDREN = 40;  // Cannot be more than MAX_VALUES for a dimension
const int MAX_ATTRS = 40;     // (LBH 3/96)

class Example;
class Dimension;
class Node {
   Example *examples;               // Start of a linked list of examples.
   int num_examples;                // The number of examples

   int num_attrs;                    // Number of such attributes (LBH 3/96)
   int attributes[MAX_ATTRS];        // Attributes remaining for this subtree

   int attribute;                   // The "question" for this node.
   int major_class;                 // This node's class (LBH 3/96)

   int num_children;
   Node *children[MAX_CHILDREN];    // The children under this node

   int splitter();                  // Which dimension will node be split on?
   double evaluate(int dim);        // Metric for deciding splitting dimension
   double disorder(int dim, int value);  // Another metric, used by evaluate
   void print_distribution();       // Print out the class distribution here
   void partition();                // Break up the node given the split

public:
   Node();                          // Construct a node
   ~Node();                         // Destroy a node
   void add_example(Example *example);   // Add an example to this node's set
   void add_attribute(int attr);    // Add attr to node's set (LBH 3/96)
   void build_tree(int default_class); // Build decision subtree from this node
   double disorder(int value);      // Calculate a metric for disorder
   void print(int depth);           // Print the node with "depth" indentation
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

