/* Vertex.C
 *
 * The purpose of this program is to take an image reduced to a line-drawing
 * and convert it to a representation of the real world. Each pair of lines
 * that meet form a vertex. Our real world representation is a labelling of
 * each vertex. From the way the lines join up, we can tell whether
 * the vertex is an ELL, FORK, ARROW, or TEE. Each of these vertex types
 * has various possible labellings. This class represents the vertices.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <stdlib.h>
#include "Diagram.H"
#include "Vertex.H"
#include "String.H"

// The names of all the vertex types
char Vertex::VertexNames[][6] = {
   "ELL",
   "FORK",
   "TEE",
   "ARROW"
};

// Construct a vertex given the name
Vertex::Vertex(char *_name)
{
  strncpy(name, _name, MAX_STRING);   // Copy over the string. See String.C.
}

// Destroy a vertex
Vertex::~Vertex()
{
}

// Depending on the type of the vertex, set up the possible labelings.
// These are the maximum possible. As the waltz filter runs, we'll cull
// out labelings that actually don't work.
void Vertex::possible_labelings()
{
   switch(type) {
   case ELL:    // There are 6 different possible labelings for an ELL type
      labelings[0] = Labeling(RIGHT, LEFT);
      labelings[1] = Labeling(LEFT, RIGHT);
      labelings[2] = Labeling(PLUS, RIGHT);
      labelings[3] = Labeling(LEFT, PLUS);
      labelings[4] = Labeling(MINUS, LEFT);
      labelings[5] = Labeling(RIGHT, MINUS);
      num_labelings = 6;
      break;
   case FORK:   // There are 5 different possible labelings for a FORK type
      labelings[0] = Labeling(PLUS, PLUS, PLUS);
      labelings[1] = Labeling(MINUS, MINUS, MINUS);
      labelings[2] = Labeling(LEFT, RIGHT, MINUS);
      labelings[3] = Labeling(MINUS, LEFT, RIGHT);
      labelings[4] = Labeling(RIGHT, MINUS, LEFT);
      num_labelings = 5;
      break;
   case TEE:   // There are 4 different possible labelings for a TEE type
      labelings[0] = Labeling(RIGHT, LEFT, PLUS);
      labelings[1] = Labeling(RIGHT, LEFT, MINUS);
      labelings[2] = Labeling(RIGHT, LEFT, LEFT);
      labelings[3] = Labeling(RIGHT, LEFT, RIGHT);
      num_labelings = 4;
      break;
   case ARROW:   // There are 3 different possible labelings for an ARROW type
      labelings[0] = Labeling(LEFT, RIGHT, PLUS);
      labelings[1] = Labeling(MINUS, MINUS, PLUS);
      labelings[2] = Labeling(PLUS, PLUS, MINUS);
      num_labelings = 3;
      break;
   }
}

// This function is used to indicate that the line between two vertices
// is adjacent to the ground (floor) by labeling the line '-', thereby
// indicating that the line is concave.
void Vertex::ground(Vertex *vertex)
{
   // Which number neighbor is the given vertex
   for(int x = 0; x < num_neighbors; x++)
      if(neighbors[x] == vertex)
	break;

   // Set all labelings invalid if they don't have the '-' in the right place
   for(int y = 0; y < num_labelings; y++)
     labelings[y].force_ground(x);
}

// Invoke the waltz filter on a vertex. This reduces the labelings on the
// vertex by considering the labeling of its neigbors. If it reduces the
// number of labelings at a vertex, then it applies itself recursively.
// Returns 1 if successful, but if the vertex becomes impossible,
// because it has no labelings, it returns 0.
int Vertex::waltz()
{
   int changed_labeling = 0;

   int n;
   for(int labeling = 0; labeling < num_labelings; labeling++)
      if(labelings[labeling].isvalid())
	for(n = 0; n < num_neighbors; n++)
         if(!neighbors[n]->consistent_labeling(this,
                                         labelings[labeling].get_label(n))) {
            labelings[labeling].set_valid(0);  // Invalid
            changed_labeling = 1;
         }

   if(impossible_vertex())   // Does this vertex have no possible labelings?
     return 0;

   if(changed_labeling)
      for(n = 0; n < num_neighbors; n++)
         if(!neighbors[n]->waltz())
	   return 0;

   return 1;
}

// This node is a neighbor the given vertex, and the given label
// is being checked out. Do any of this vertex's labels (in the slot
// for the given vertex) match the given label?
int Vertex::consistent_labeling(Vertex *vertex, Label label)
{
   // First, figure out which of my neighbors the given vertex is.
   for(int n = 0; n < num_neighbors; n++)
      if(neighbors[n] == vertex)
         break;

   for(int labeling = 0; labeling < num_labelings; labeling++)
       if(labelings[labeling].isvalid()
          && labelings[labeling].consistent_label(n, label))
          return 1;

   return 0;
}

// Is this vortex impossible? If it has no possible labelings, it is impossible
int Vertex::impossible_vertex()
{
   int count = 0;

   for(int labeling = 0; labeling < num_labelings; labeling++)
      if(labelings[labeling].isvalid())
         count++;

   return count == 0;   // No consistent labels?
}

// Does the given name match the name of this vertex?
int Vertex::match(char *_name)
{
  return strcmp(name, _name) == 0;
}

// Read in the vertex from a file
istream& operator>>(istream &i, Vertex &v)
{
   char word[MAX_STRING];

   i >> word;   // Should be the name of this vertex
   if(strcmp(word, v.name) != 0) {
     cerr << "Expected name for vertex " << v.name
          << " but got " << word << endl;
     exit(1);
   }

   i >> word;  // Should be the type of vertex
   for(int x = 0; x < 4; x++)
     if(strcmp(word, Vertex::VertexNames[x]) == 0) {
       v.type = (Vertex::VertexType) x;
       break;
     }

   if(x >= 4) {  // If no match was found
     cerr << "Expected vertex type, got " << word << endl;
     exit(1);
   }

   // Read in the neighbors for this vertex. ELLs have 2, others have 3
   switch(v.type) {
   case Vertex::ELL:           // An ELL
      v.num_neighbors = 2;
      i >> word;
      v.neighbors[0] = Diagram::lookup(word);
      i >> word;
      v.neighbors[1] = Diagram::lookup(word);
      break;
   case Vertex::ARROW:         // An ARROW
   case Vertex::FORK:          // A FORK
   case Vertex::TEE:           // A TEE
      v.num_neighbors = 3;
      i >> word;
      v.neighbors[0] = Diagram::lookup(word);
      i >> word;
      v.neighbors[1] = Diagram::lookup(word);
      i >> word;
      v.neighbors[2] = Diagram::lookup(word);
      break;
   }

   // Initialize the possible labelings for this vertex given its type
   v.possible_labelings();

   return i;
}

// Print out the vertex
ostream& operator<<(ostream &o, Vertex &v)
{
   o << "Vertex " << v.name
     << " " << Vertex::VertexNames[v.type] << ":" << endl;

   if(v.impossible_vertex())
      o << "      No consistent labels" << endl;
   else
     for(int labeling = 0; labeling < v.num_labelings; labeling++)
       if(v.labelings[labeling].isvalid())  // Only print valid labels
         o << "      " << v.labelings[labeling] << endl;
   
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

