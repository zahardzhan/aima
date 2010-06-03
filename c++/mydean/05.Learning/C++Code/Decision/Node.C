/* Node.C
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

#include <iostream.h>
#include <math.h>
#include "Example.H"
#include "Node.H"
#include "Decision.H"
#include "Dimension.H"

// Construct a node. This means setting up some initial values
Node::Node()
{
   num_children = 0;
   num_examples = 0;
   examples = NULL;

   num_attrs = 0;     // LBH 3/96
   for (int a = 0; a < MAX_ATTRS; a++)
      attributes[a] = -1;
}

// Destroy a node. This means deleting all the dynamically allocated memory
Node::~Node()
{
   // Delete the linked list of examples
   Example *example = examples;
   Example *temp;
   while(example) {
      temp = example->next;
      delete example;
      example = temp;
   }

   // Delete all the children nodes
   for(int x = 0; x < num_children; x++)
      delete children[x];
}

// Add an example to this node. A specific example can only inhabit
// one node at any one time.
void Node::add_example(Example *example)
{
   example->next = examples;
   examples = example;

   num_examples++;
}

// Add an attribute's index to this node.  Attributes may inhabit morei
// than one node at a time. (LBH 3/96)
void Node::add_attribute(int attr)
{
  attributes[num_attrs++] = attr;
}

// Build the decision subtree starting at this node. If this node is the root
// node, then this means building the entire tree! First we see if
// the examples at this node have more than one class. If not, then there
// is no splitting required. If so, then we check all the dimensions
// using a special metric in evaluate() and choose one dimension to split
// on. This split generates new children nodes, and we run the build_tree()
// algorithm on all the children, creating decision subtrees.
//
// default_class is the majority class of the node's parent
void Node::build_tree(int default_class)
{
   int x, max_class_count, class_count[MAX_CLASSES];  // LBH 3/96

   if (num_examples == 0) {
      major_class = default_class;   // (LBH 3/96)
      return;
   }

   for (x = 0; x < Decision::num_classes; x++) class_count[x] = 0; // LBH 3/96

//   print_distribution();   // Print the class distribution of this node

   // We do not want to split this node if the examples all have the
   // same class. Further differentiation is not required, because all
   // the "answers" are the same.
   int first_class = examples->get_class();
   int different_classes = 0;    // Assume not different classes
   for(Example *example = examples->next; example; example = example->next) {
      class_count[example->get_class()]++; // LBH 3/96
      if(example->get_class() != first_class)
         different_classes = 1;
   }

   // Return if no different class
   if(!different_classes) {
//      cout << "Terminal node" << endl;
      major_class = first_class;        // LBH 3/96
      return;
   }

   // Determine majority class in examples at this node. (LBH 3/96)
   major_class = 0;
   max_class_count = class_count[0];
   for (x = 1; x < Decision::num_classes; x++)
      if (class_count[x] > max_class_count) {
         major_class = x;
         max_class_count = class_count[x];
      }

   if (num_attrs == 0) return;  // LBH 3/96

   // Find the attribute that maximizes a particular evaluation function
   // implemented by evaluate(). Which dimension is best to split on?
   attribute = splitter();

//   cout << "Dimension chosen: " 
//        << Decision::dimensions[attribute]->get_attribute() << endl;

   partition(); // Break up the node. Allocate all examples to kids

   for(x = 0; x < num_children; x++)  // Now do it on all the subtrees
      children[x]->build_tree(major_class);
}

// This node has many examples. We build children from this node by creating
// new nodes, one each for a value of the attribute specified in "attribute"
void Node::partition()
{
   int x, y; // LBH 3/96

   for(int val = 0; val < Decision::dimensions[attribute]->num_values; val++)
      children[num_children++] = new Node;

   Example *temp;
   Example *example = examples;
   while(example) {
      temp = example->next;
      children[example->get_value(attribute)]->add_example(example);
      example = temp;
   }
   examples = NULL;

   // pass along all unused attributes (LBH 3/96)
   for (x = 0; x < num_attrs; x++)
      if (attributes[x] != attribute)
         for (y = 0; y < num_children; y++)
            children[y]->add_attribute(attributes[x]);
}

// Print out the class distribution of this node
void Node::print_distribution()
{
  cout << "Class distribution is ";
  int class_totals[MAX_CLASSES];   // How many are in each class?
  for(int x = 0; x < Decision::num_classes; x++)
    class_totals[x] = 0;

  for(Example *example = examples; example; example = example->next)
      class_totals[example->get_class()]++;

  for(x = 0; x < Decision::num_classes; x++)
    cout << Decision::classes[x] << ": " << class_totals[x] << " ";

  cout << endl;
}

// There are many dimensions that we could split on at this node.
// Decide which one is most appropriate. Returns the number index.
int Node::splitter()
{
   // Go through unused (LBH 3/96) dimensions and find the one with the lowest
   // disorder value. We get this from the evaluation function.
   double min_value = evaluate(attributes[0]); // lowest evaluation seen so far
   int min_dim = attributes[0];                // Dimension of lowest evaluation
   double value;

   for(int x = 1; x < num_attrs; x++) {
      value = evaluate(attributes[x]);
      if(value < min_value) {
         min_value = value;
         min_dim = attributes[x];
      }
   }

   return min_dim;
}

// Assuming that we split this node along the given dimension, there
// will be a number of subtrees. Each of these subtrees will have a certain
// disorder. Add up the total disorder of the subtrees and return it.
double Node::evaluate(int dim)
{
   // Find the numerical distribution of examples along this dimension
   int dim_totals[MAX_VALUES];
   for(int value = 0; value < Decision::dimensions[dim]->num_values; value++)
      dim_totals[value] = 0;

   for(Example *example = examples; example; example = example->next)
         dim_totals[example->get_value(dim)]++;

   // Tally up the overall total
   double total = 0;
   for(value = 0; value < Decision::dimensions[dim]->num_values; value++)
      total += dim_totals[value];

   double sum = 0;
   for(value = 0; value < Decision::dimensions[dim]->num_values; value++)
      sum += disorder(dim, value) * dim_totals[value] / total;

   return sum;
}

// Given a dimension to split on, and a particular class, how disordered
// would this subtree be, starting from this node?
double Node::disorder(int dim, int value)
{
   int class_totals[MAX_CLASSES];   // How many are in each class?
   for(int x = 0; x < Decision::num_classes; x++)
      class_totals[x] = 0;

   for(Example *example = examples; example; example = example->next)
      if(example->get_value(dim) == value)
         class_totals[example->get_class()]++;

   double total = 0;
   for(x = 0; x < Decision::num_classes; x++)
      total += class_totals[x];    // Should be same as num_examples. Duh.

   if(total < 0.1)  // basically total == 0
      return 0;

   double sum = 0;
   for(x = 0; x < Decision::num_classes; x++)
      if(class_totals[x] > 0)
         sum += (class_totals[x] / total) * log(class_totals[x]);

   // Use base e intead of base 2 in LISP.
   return log(total) - sum;
}

// Print this node with "depth" amount of indentation
void Node::print(int depth)
{
   int x, y;
   if(num_children == 0) {
      for (x = 0; x < depth; x++) cout << "   ";
      cout << "  Class: " << Decision::classes[major_class] << endl;
      for (x = 0; x < depth; x++) cout << "   ";
      cout << "  Examples:" << endl;
      for(Example *example = examples; example; example = example->next) {
         for(x = 0; x < depth; x++)
            cout << "   ";
         cout << "    " << *example << endl;
      }
   } else {
      for(x = 0; x < depth; x++)
         cout << "   ";
      cout << "Split on " << Decision::dimensions[attribute]->get_attribute()
            << ":" << endl;
      for(y = 0; y < num_children; y++) { 
         for(x = 0; x < depth; x++)
            cout << "   ";
         cout << "---"
              << Decision::dimensions[attribute]->values[y] << ": " << endl;
         children[y]->print(depth+1);
      }
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

