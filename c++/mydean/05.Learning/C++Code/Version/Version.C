/* Version.C
 *
 * This class serves as a wrapper for the entire version space algorithm.
 * It reads in dimensions and training examples from a file, and
 * refines the boundaries by processing each training example in turn.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

#include "Version.H"
#include "Example.H"
#include "Dimension.H"

int Version::num_dimensions;         // The number of dimensions for this run
Dimension Version::dimensions[MAX_DIMENSIONS];      // Array of dimensions

// The main() function is the first function called in this program.
// It gets the input filename from the command line, starts up a
// Version object, and runs the versions algorithm.
int main(int argc, char *argv[])
{
   if(argc != 2) {
      cerr << "Usage:  version myfile.example" << endl;
      exit(1);
   }

   Version version(argv[1]);    // Load dimensions and examples from files
   version.versions();          // Refine the boundaries on all examples

   return 0;
}

// Construct a Version object given the input filename
Version::Version(char *filename)
{
   ifstream in(filename);

   if(in.fail()) {
      cerr << "Could not open file " << filename << endl;
      exit(1);
   }

   char word[MAX_STRING];   // Scratch space for reading in words
   in >> word;              // Should be "dimensions"
   if(strcmp(word, "dimensions") != 0) {
     cerr << "Expecting \"dimensions\" at start of file" << endl;
     exit(1);
   }
   in >> num_dimensions;   // Read in the number of dimensions
   for(int x = 0; x < num_dimensions; x++)
      in >> dimensions[x];

   in >> word;              // Should be "examples"
   if(strcmp(word, "examples") != 0) {
     cerr << "Expecting \"examples\", got " << word << endl;
     exit(1);
   }

   examples = NULL;
   tail = NULL;
   Example *temp;
   // Construct a linked list of all examples.
   while(!in.eof()) {
     in >> word;
     if(!word[0] || in.eof() || in.fail())  // Empty word means end of file
       break;
     temp = new Example(word, in);
     if(tail)    // Add example onto the end of the list
       tail->next = temp;
     else
       examples = temp;
     tail = temp;
   }

   // The General boundary is a single concept with no features.
   general_boundary.add_concept(new Concept);

   // The specific boundary consists of one concept for each example.
   // Each concept has the same features as the example.
   for(Example *example = examples; example; example = example->next)
     specific_boundary.add_concept(new Concept(example));
}

// Destroy the version object, which means destroying all the
// dynamically allocated Examples.
Version::~Version()
{
   Example *temp;    // Placekeeper so we deletion doesn't erase "next" ptr
   Example *example = examples;
   while(example) {  // Go through the linked list and delete all the examples
      temp = example;
      example = example->next;
      delete temp;
   }
}

// Given a dimension index and a value name, get the associated value index
int Version::lookup_value(int dim, char temp[])
{
   return dimensions[dim].lookup(temp); // Ask the appropriate dimension for it
}

// Print both the general and the specific boundaries.
void Version::print_boundaries()
{
  cout << "General:  " << general_boundary;
  cout << "Specific: " << specific_boundary;
  cout << endl;
}

// Perform the version space algorithm, which means refining the
// boundaries for each example.
void Version::versions()
{
  print_boundaries();
  for(Example *example = examples; example; example = example->next) {
    refine(example);
    cout << "Example: " << *example << endl;
    print_boundaries();
  }
}

// Refine boundaries for each exmaple. See section 5.3 for this
// somewhat hairy algorithm.
void Version::refine(Example *example)
{
   if(example->is_positive())         // If the example is classified YES
      generalize_specific(example);   //    then generalize specific boundary
   else                               // otherwise
      specialize_general(example);    //    specialize the general boundary
}

// Generalize the specific boundary, given this example
void Version::generalize_specific(Example *example)
{
   // From section 5.3, if the example is positive, then perform the following
   // steps:
   //
   // (a) Eliminate all concepts in the general boundary that aren't consistent
   //     with the example.
   general_boundary.eliminate(INCONSISTENT, example);

   // (b) Minimally generalize all concepts in the specific boundary until
   //     they are consistent with the example
   specific_boundary.generalize(example);

   // eliminate those that
   //     fail to satisfy the following requirements:
   //     i. Each concept is a specialization of some concept in the general
   //        boundary.
   specific_boundary.enforce_specialization_of(general_boundary, 1);

   //    ii. Each concept is not a generalization of some other concept in
   //        the specific boundary.
   specific_boundary.enforce_generalization_of(specific_boundary, 0);
}

// Specialize the general boundary, given the example
void Version::specialize_general(Example *example)
{
   // From section 5.3, if the example is negative, then perform the following
   // steps:
   // 
   // (a) Eliminate all concepts in the specific boundary that are consistent
   //     with the example.
   specific_boundary.eliminate(CONSISTENT, example);

   // (b) Minimally specialize all concepts in the general boundary until they
   //     are not consistent with the example,
   general_boundary.specialize(example);

   // eliminate those that fail to
   //     satisfy the following requirements:
   //     i. Each concept is a generalization of some concept in the specific
   //        boundary.
   general_boundary.enforce_generalization_of(specific_boundary, 1);

   //    ii. Each concept is not a specialization of some other concept in the
   //        general boundary.
   general_boundary.enforce_specialization_of(general_boundary, 0);
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

