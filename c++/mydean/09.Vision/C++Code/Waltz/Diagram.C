/* Diagram.C
 *
 * A diagram is the entire representation (in vertices and lines) of
 * the image.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include "Diagram.H"
#include "Vertex.H"
#include "String.H"

Vertex **Diagram::vertices;          // The vertices in the diagram
int Diagram::num_vertices;           // The number of vertices in the diagram

// The main() function is the first function called. It gets the filename
// of the diagram from the command line arguments, sets up a Diagram,
// and runs the waltz filter. Finally, it prints the diagram.
int main(int argc, char *argv[])
{
   if(argc != 2) {
      cerr << "Usage:   waltz filename.diagram" << endl;
      exit(1);
   }

   Diagram diagram(argv[1]);
   cout << "The initial diagram is:" << endl;
   cout << diagram;
   if(diagram.filter()) {   // If successful
     cout << "After filtering, the diagram is:" << endl;
     cout << diagram;
   } else
     cout << "No possible labelings." << endl;
     
   return 0;
}

// Read a Diagram description from an input file.
Diagram::Diagram(char *filename)
{
   ifstream in(filename);

   if(in.fail()) {
      cerr << "Could not open file " << filename << endl;
      exit(1);
   }

   char word[MAX_STRING];    // A generic string used to read in from file
   in >> word;               // Should read "vertices"
   if(strcmp(word, "vertices") != 0) {
     cerr << "Expected keyword \"vertices\" at beginning of file" << endl;
     exit(1);
   }

   in >> num_vertices;       // Read in the number of vertices
   // Dynamically allocate array of pointers to Vertex
   vertices = new Vertex *[num_vertices];
   for(int x = 0; x < num_vertices; x++) {
     in >> word;
     vertices[x] = new Vertex(word);  // Read in the names of all vertices
   }

   for(x = 0; x < num_vertices; x++)  // Read in the type and neighbor info
      in >> *vertices[x];

   // Read in which vertices are grounded.
   Vertex *v1;
   Vertex *v2;
   while(!in.eof()) {    // Keep looping until the end of the file
      in >> word;
      if(!word[0] || in.eof() || in.fail())   // End of file?
         break;
      if(strcmp(word, "ground") != 0) {
         cerr << "Expected ground, got " << word << endl;
         exit(1);
      }
      in >> word;
      v1 = lookup(word);   // Find the vertex by name
      in >> word;
      v2 = lookup(word);   // Find the vertex by name
      v1->ground(v2);
   }
}

// Destroy the Diagram, which means deleting the dynamically allocated stuff
Diagram::~Diagram()
{
   for(int x = 0; x < num_vertices; x++)
     delete vertices[x];
   delete [] vertices;
}

// Return a pointer to the nodes with the given name.
Vertex *Diagram::lookup(char *name)
{
   for(int x = 0; x < num_vertices; x++)
      if(vertices[x]->match(name))
         return vertices[x];

   cerr << "Could not find vertex with name " << name << endl;
   exit(1);
   return NULL;
}

// Invoke the waltz filter on every vertex. Returns 1 if successful.
// Returns 0 if some vertex has no labelings possible, and is
// therefore an impossible vertex.
int Diagram::filter()
{
   for(int vertex = 0; vertex < num_vertices; vertex++)
      if(!vertices[vertex]->waltz())
	return 0;  // failure, found an impossible vertex1

   return 1;   // success
}

// Print out the diagram, by printing every vertex
ostream& operator<<(ostream &o, Diagram &d)
{
   for(int vertex = 0; vertex < d.num_vertices; vertex++)
      o << *d.vertices[vertex] << endl;

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

