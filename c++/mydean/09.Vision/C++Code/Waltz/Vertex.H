/* Vertex.H
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

#include <iostream.h>
#include "Labeling.H"
#include "String.H"

class Vertex {
friend istream& operator>>(istream &i, Vertex &v);
friend ostream& operator<<(ostream &o, Vertex &v);
public:
   enum VertexType {
      ELL,
      FORK,
      TEE,
      ARROW
   };

   static char VertexNames[][6];  // The names of the vertex types
   char name[MAX_STRING];         // The name of this node

private:

   VertexType type;        // Is this node an ELL, FORK, ARROW, or TEE?

   Vertex *neighbors[3];   // The vertices this vertex is connected to.
   int num_neighbors;      // How many neigbors this vertex has.

   int num_labelings;
   Labeling labelings[6];  // At most, one vertex can have 6 possible labelings

   void possible_labelings(); // Set up the possible labelings
   int consistent_labeling(Vertex *vertex, Label label);
   int impossible_vertex();   // Does this vertex have NO possible labelings?

public:
   void ground(Vertex *vertex);  // Grounds this to given vertex index.
   int waltz();                  // Run the waltz filter on this node
   int match(char *_name);       // Does this vertex's name match given name?

   Vertex(char *_name);          // Construct a vertex given its name
   ~Vertex();                    // Destroy this vertex
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

