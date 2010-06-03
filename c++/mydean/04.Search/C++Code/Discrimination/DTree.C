/* DTree.C
 *
 * The DTree class holds the entire decision tree. You can
 * add items to the tree, and fetch matching elements.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include <fstream.h>
#include <strstream.h>
#include <stdlib.h>
#include "DTree.H"
#include "String.H"
#include "Node.H"
#include "Formula.H"

Formula *DTree::results;  // A list of formulas that match the fetch formula

// The main() function is the first function called in this program.
// It parses the command line arguments to find the filename for the
// example file, and starts up a DTree to process the commands in the file.
int main(int argc, char *argv[])
{
   if(argc != 2) {
      cerr << "Usage:  dtree myfile.example" << endl;
      exit(1);
   }
 
   DTree dtree(argv[1]);   // Create a new DTree and process commands in file

   return 0;
}

// Construct a tree, given a filename with add and fetch commands
DTree::DTree(char filename[])
{
   ifstream in(filename);
 
   if(in.fail()) {
      cerr << "Could not open file " << filename << endl;
      exit(1);
   }

   char line[MAX_STRING];
   char command[MAX_STRING];

   Formula *formula;
   root = new Node;

   while(!in.eof()) {    // Process all the commands
      in >> command;
      if(!command[0] || in.fail() || in.eof())     // At end of file?
         break;
      in.getline(line, MAX_STRING);
      istrstream formula_line(line, MAX_STRING);
      formula = new Formula;
      formula_line >> *formula;
      switch(command[0]) {
      case 'a':  // Add a formula. The formula must begin and end with parens
         cout << "Adding formula " << *formula << endl;
         add(formula);
         break;
      case 'f':  // Match a formula. The formula must begin and end with parens
         cout << "Matching formula " << *formula << endl;
         fetch(formula);     // Makes linked list of results in "results"
         delete formula;
         if(!results)
            cout << "No matches." << endl;
         else
            for(Formula *f = results; f; f = f->next)
               cout << *f << endl;
         break;
      default:
         cerr << "Invalid command \"" << command << "\". Skipping it." << endl;
      }
   }
}

// Destroy a DTree, which means destroying the root node
DTree::~DTree()
{
   delete root;
}

// Given a formula, fetch all matching formulas from the DTree
void DTree::fetch(Formula *formula)
{
   results = NULL;

   root->extract(formula->get_keys());
}

// Add a formula to the DTree, creating new nodes if necessary
void DTree::add(Formula *formula)
{
   Node *node = root->index(formula->get_keys());
   if(!node->member(formula))
      node->add(formula);
}

// This function is used when a search for matching formulas is underway.
// Whenever a new matching formula is found, it is added to a linked
// list of "results". These results are printed out later, after all
// the matching is done.
void DTree::add_result(Formula *formula)
{
   formula->next = results;
   results = formula;
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

