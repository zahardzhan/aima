/* Network.H
 *
 * The uncertainty program computes probabilities given a network
 * of dependencies and some examples. The Network class contains the
 * network, which is read in from a file. It also contains the examples
 * and some scratch variables needed for computation.
 *
 * Most of the below methods are associated with either the exact
 * algorithm, or the approximation algorithm. Some are used in both.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include "Node.H"

class Network {
   /********************  Overloaded Operators *********************/
friend ostream& operator<<(ostream &o, Network &d);   // Print out the network

   /********************  Approximation Algorithm *********************/
   void initialize_values();   // Set up evidence in root nodes
   void simulate();            // Simulate propagating values
   void update_scores();       // Update scores with likelihood weighting
   double sample_weight();     // Compute likelihood weighting of evidence
   void set_evidence();        // Set evidence for nodes that have it

   /********************  Exact Algorithm *********************/
   void initialize_priors();   // Propagate the priors down the root nodes
   void propagate();           // Propagate evidence up and down

   /********************  General Stuff *********************/
   int lookup_num(char *name); // Get the number of a node given its name

public:
   static Node **nodes;        // All the nodes in the network
   static int num_nodes;       // The number of nodes in the network
   static int do_approximate;  // Run the approximation algorithm? (If not,
                               // then the user wants the exact algorithm)
   static Node *lookup(char *name);  // Get a pointer to node given its name
   EvidenceType *evidence;     // The evidence, which is an array indexed
                               // by node number.
   Network(istream& in);       // Construct a network from a file input
   ~Network();                 // Destructor
   void exact();               // Run the exact algorithm
   void approximate(int iterations);  // Run the approximation algorithm
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

