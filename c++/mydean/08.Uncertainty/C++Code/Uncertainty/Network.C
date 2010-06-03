/* Network.C
 *
 * The uncertainty program computes probabilities given a network
 * of dependencies and some examples. The Network class contains the
 * network, which is read in from a file. It also contains the examples
 * and some scratch variables needed for computation.
 *
 * To get an overview of the class, read the Network.H file. This
 * file holds the actual implementation of the class.
 *
 * Each of the below methods is associated with either the exact
 * algorithm, or the approximation algorithm.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include "Network.H"
#include "Node.H"
#include "String.H"

Node **Network::nodes;
int Network::num_nodes;
int Network::do_approximate;

// Print a message saying how to use this program. Exit with error number.
void usage()
{
   cerr << "Usage: uncertainty <-a num> <-e> filename.net" << endl;
   cerr << "     -a num   approximate with num iterations" << endl;
   cerr << "     -e       exact" << endl;
   exit(1);
}

// The main() function is the first function called in the program.
// It reads in the command line options, starts up the network,
// an runs either the exact or approximate algorithm.
int main(int argc, char *argv[])
{
   char *filename = NULL;          // No filename given (yet)
   Network::do_approximate = -1;   // Neither exact nor approximate chosen
   int iterations = 0;
   for(int x = 1; x < argc; x++)   // Cycle through all command line words
      if(argv[x][0] == '-')        // If it starts with dash
         switch(argv[x][1]) {      //     handle the -a  or  -e
         case 'a':
            Network::do_approximate = 1;    // Use approximate algorithm
            if(++x < argc)
               iterations = atoi(argv[x]);
            else
               usage();      // Error. Print usage message.
            break;
         case 'e':
            Network::do_approximate = 0;    // Use exact algorithm
            break;
         default:
            usage();
         }
      else
         if(filename)         // Print error if filename already specified
            usage();
         else
            filename = argv[x];

   if(!filename || Network::do_approximate == -1)
       usage();   // Error if no filename or no exact/approximate choice

   ifstream in(filename);   // Open the network file for reading

   if(in.fail()) {
      cerr << "Could not open file " << filename << endl;
      exit(1);
   }

   Network network(in);     // Create a network object

// Seed the random number generator, if we aren't debugging this program.
#ifndef DEBUG
   srand((unsigned int) time(0));
#endif

   if(Network::do_approximate)
     network.approximate(iterations);   // Run approximation algorithm
   else
     network.exact();                   // Run exact algorithm

   cout << network;                     // Print the resulting network

   return 0;
}

   /****************************************************************/
   /********************  Overloaded Operators *********************/
   /****************************************************************/

// Print this network, by printing each node.
ostream& operator<<(ostream &o, Network &d)
{
   for(int x = 0; x < d.num_nodes; x++)
     o << *d.nodes[x] << endl;

   return o;
}

   /*******************************************************************/
   /********************  Approximation Algorithm *********************/
   /*******************************************************************/

// The value of each node is initialized to NO_VALUE unless the node
// is assigned a value by the evidence and the node has no parents.
// Evidence nodes with parents are assigned values by stochastic
// simulation but the resulting assignments are weighted.
void Network::initialize_values()
{
   for(int x = 0; x < num_nodes; x++)
      if(evidence[x] != NO_VALUE && nodes[x]->get_num_parents() == 0)
         nodes[x]->set_value(evidence[x]);
      else
         nodes[x]->set_value(NO_VALUE);
}

// Simulate by propagating values forward through the network.
// We run through all the nodes, simulating each one. Each node
// simulation either changes the node, or does not. We keep doing
// runs until we get a run in which none of the nodes changes. This
// is a little suboptimal, but sufficient for our purposes.
void Network::simulate()
{
   int num_changed;
   do {
      num_changed = 0;
      for(int x = 0; x < num_nodes; x++)
         if(nodes[x]->simulate())
            num_changed++;
   } while(num_changed > 0);
}

// Update the scores of each node using likelihood weighting
void Network::update_scores()
{
   // Compute the likelihood weighting assigned to the evidence given the
   // sample.
   double weight = sample_weight();

   for(int x = 0; x < num_nodes; x++)
      nodes[x]->update_scores(weight);
}

// Compute the likelihood weighting assigned to the evidence given the sample.
double Network::sample_weight()
{
   double product = 1;
   for(int x = 0; x < num_nodes; x++)
      if(evidence[x] != NO_VALUE)
         product *= nodes[x]->probability(evidence[x]);

   return product;
}

// Clean up the values of the nodes after stochastic simulation. Only
// evidence nodes should have values after the cleanup.
void Network::set_evidence()
{
   for(int x = 0; x < num_nodes; x++)
      nodes[x]->set_value(evidence[x]);   // Either set a value or set NO_VALUE
}

   /***********************************************************/
   /********************  Exact Algorithm *********************/
   /***********************************************************/

// Propagate priors down from the root nodes. In the case of
// tree-structured networks there will be exactly one root node.
void Network::initialize_priors()
{
   for(int x = 0; x < num_nodes; x++)
      nodes[x]->initialize_priors();
}

// Propagate evidence down from root nodes and up from terminal nodes.
// Only boundary nodes (root and terminal) are allowed to be assigned
// values as evidence.
void Network::propagate()
{
   for(int x = 0; x < num_nodes; x++)        // For each node,
      if(evidence[x] != NO_VALUE) {
         nodes[x]->set_value(evidence[x]);   // initialize evidence...
         nodes[x]->propagate();              // ... and propagate it.
      }
}

   /*********************************************************/
   /********************  General Stuff *********************/
   /*********************************************************/

// Return the number of the node with the given name.
int Network::lookup_num(char *name)
{
   for(int x = 0; x < num_nodes; x++)
      if(nodes[x]->match(name))
         return x;

   cerr << "Could not find node with name " << name << endl;
   exit(1);
   return -1;
}

// Return a pointer to the nodes with the given name.
Node *Network::lookup(char *name)
{
   for(int x = 0; x < num_nodes; x++)
      if(nodes[x]->match(name))
         return nodes[x];

   cerr << "Could not find node with name " << name << endl;
   exit(1);
   return NULL;
}

// Construct a new network object. Our program will have only one
// of these. The Network description is read from an input file.
Network::Network(istream& in)
{
   char word[25];
   in >> word;       // Should be "nodes"
   in >> num_nodes;  // The number of nodes in this network
   nodes = new Node *[num_nodes];   // Allocate memory for the node pointers

   // Read in the node names
   for(int x = 0; x < num_nodes; x++) {
      in >> word;
      nodes[x] = new Node(word);
   }

   // Read in the node distributions
   for(x = 0; x < num_nodes; x++)
      in >> *nodes[x];

   // Allocate memory for the evidence. The evidence is an array of
   // "EvidenceType" values, which can be NEGATIVE, POSITIVE, or NO_VALUE.
   evidence = new EvidenceType[num_nodes];
   for(x = 0; x < num_nodes; x++)
      evidence[x] = NO_VALUE;       // Unless specified, no evidence for nodes

   // Until the end of the file, read in all evidence.
   while(!in.eof()) {
      in >> word;   // Should say "evidence"
      if(!word[0] || in.eof() || in.fail())   // End of file?
         break;
      if(strcmp(word, "evidence") != 0) {
         cerr << "Expected \"evidence\", got " << word << endl;
         exit(1);
      }
            
      in >> word;   // Name of node with evidence.
      in >> x;      // 0 is NEGATIVE, 1 is POSITIVE
      evidence[lookup_num(word)] = (EvidenceType) x;
   }
}

// Run the exact algorithm. This top-level function computes the posterior
// distributions for all the nodes in a tree-structured network, given
// evidence.
void Network::exact()
{
   initialize_priors();    // Propagate diagnostic support from roots down
   propagate();       // Propagate evidence down from roots, up from terminals
   for(int x = 0; x < num_nodes; x++)   // For each node,
     nodes[x]->posterior();    // compute probability it's false given evidence
}

// Run the approximation algorithm. Estimate the posterior probabilities
// using likelihood weighting, given the evidence.
void Network::approximate(int iterations)
{
   for(int i = 0; i < iterations; i++) {   // Do this # iterations many times
      initialize_values();    // Initialize non-root nodes to NO_VALUE
      simulate();             // Simulate by propagating values forward
      update_scores();        // Update node scores with likelihood weighting
   }

   set_evidence();   // Set values for nodes whose value is given by evidence

   for(int x = 0; x < num_nodes; x++)   // For all nodes,
      nodes[x]->estimate();             //   estimate posterior probability
                                        //   that node is False.
}

// Destroy the network, which means cleaning up all dynamically
// allocated memory.
Network::~Network()
{
   for(int x = 0; x < num_nodes; x++)
      delete nodes[x];

   delete [] evidence;
   delete [] nodes;
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

