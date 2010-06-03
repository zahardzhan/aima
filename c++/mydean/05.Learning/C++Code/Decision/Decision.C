/* Decision.C
 *
 * This class is a container class for some globally available values,
 * such as the valid dimensions and classes for this problem.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

#include "Decision.H"
#include "Node.H"
#include "Example.H"
#include "Dimension.H"

int Decision::num_classes;             // The number of classes for this run
char Decision::classes[MAX_CLASSES][MAX_STRING];   // Names for all classes

int Decision::num_dimensions;          // The number of dimensions for this run
Dimension **Decision::dimensions;      // Array of dimensions
int Decision::majority_class;          // LBH 3/96

// The main() function is the first function called in this program. It
// reads the command line to get the filename of the file with the input
// data. It then creates a Decision object and runs the build_tree() method.
// Finally, it prints the completed decision tree.
int main(int argc, char *argv[])
{
   if(argc != 2) {
      cerr << "Usage:  decision myfile.example" << endl;
      exit(1);
   }

   Decision decision(argv[1]);
   decision.build_tree();
   cout << decision << endl;

   return 0;
}

// Construct a decision given the filename for the info file
Decision::Decision(char *filename)
{
   int x, majority_class_count;  // (LBH 3/96)
   int class_count[MAX_CLASSES]; // (LBH 3/96)

   ifstream in(filename);

   if(in.fail()) {
      cerr << "Could not open file " << filename << endl;
      exit(1);
   }

   char word[MAX_STRING];    // Some scratch space for reading in words
   in >> word;   // Should be "classes"
   if(strcmp(word, "classes") != 0) {
      cerr << "Expected keyword \"classes\" at beginning of example file"
           << endl;
      exit(1);
   }
   in >> num_classes;   // Read in the number of classes
   for(x = 0; x < num_classes; x++) { // Read in each class name
      in >> classes[x];
      class_count[x] = 0;   // (LBH 3/96)
   }

   in >> word;   // Should be "dimensions"
   if(strcmp(word, "dimensions") != 0) {
      cerr << "Expected keyword \"dimensions\", got " << word << endl;
      exit(1);
   }
   in >> num_dimensions;  // Read in the number of dimensions for this run
   // Dynamically allocate an array of pointers to Dimension
   dimensions = new Dimension *[num_dimensions];
   for(x = 0; x < num_dimensions; x++) {
     dimensions[x] = new Dimension();
     in >> *dimensions[x];  // Read in each dimension
   }

   root = new Node;    // Create the top of the decision tree

   // Add all attributes as possible split attributes in root node (LBH 3/96)
   for (x = 0; x < num_dimensions; x++) root->add_attribute(x);

   // Construct a linked list of all examples.
   in >> word;   // Should be "examples"
   if(strcmp(word, "examples") != 0) {
      cerr << "Expected keyword \"examples\", got " << word << endl;
      exit(1);
   }

   // Read in all the examples and give them to the root node
   char cword[MAX_STRING];
   while(!in.eof()) {
      in >> word;
      if(!word[0] || in.eof() || in.fail())   // End of file?
         break;
      Example *example = new Example(word, in);
      class_count[example->get_class()]++;
      root->add_example(example);
   }

   // Find majority class (LBH 3/96)
   majority_class = 0;
   majority_class_count = class_count[0];
   for (x = 1; x < num_classes; x++)
     if (class_count[x] > majority_class_count) {
        majority_class = x;
        majority_class_count = class_count[x];
     }
}

// Destroy the decision, which means destroying all the dynamically
// allocated data
Decision::~Decision()
{
   delete [] classes;
   for(int x = 0; x < num_dimensions; x++)
     delete dimensions[x];
   delete [] dimensions;
   delete root;      // Deleting the root will delete the entire tree
}

// Given a name, look up which attribute this is, and return the index
int Decision::lookup_attribute(int x, char temp[])
{
   return dimensions[x]->lookup(temp);
}

// Given a name, look up which class this is, and return the index
int Decision::lookup_class(char temp[])
{
   for(int x = 0; x < num_classes; x++)
      if(strcmp(classes[x], temp) == 0)
         return x;
}

// Run the build_tree() algorithm to create the decision tree
void Decision::build_tree()
{
   root->build_tree(majority_class);
}

// Print out the tree
ostream& operator<<(ostream &o, Decision &d)
{
   d.root->print(0);

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

