/* Diagram.H
 *
 * A diagram is the entire representation (in vertices and lines) of
 * the image.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>

class Vertex;
class Diagram {
friend ostream& operator<<(ostream &o, Diagram &d);  // Print out the diagram

public:
   static Vertex **vertices;           // The vertices in the diagram
   static int num_vertices;            // The number of vertices in the diagram
   static Vertex *lookup(char *name);  // Get pointer to vertex given its name

   Diagram(char *filename);            // Construct a diagram given a filename
   ~Diagram();                         // Destroy the diagram

   int filter();                       // Do the Waltz filter on every vertex
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

