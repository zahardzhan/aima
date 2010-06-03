/* Labeling.H
 *
 * A labeling for a vertex is an assignment of +, -, RIGHT, or LEFT
 * to the lines coming together at the vertex. These assignments form
 * a kind of description of the real-world scene.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>

// The types of labels
enum Label {
   PLUS,
   MINUS,
   RIGHT,
   LEFT,
   NUM_LABELS
};

class Labeling {
friend ostream& operator<<(ostream &o, Labeling &labeling);
   Label labels[3];    // May use two or three depending on vertex type.

   int num_labels;     // How many labels are in this labeling
   int valid;          // Is this labeling valid for the vertex owning it?

public:
   Labeling();         // The dummy constructor. Must initialize after using!
   Labeling(Label a, Label b);          // Construct a labeling given 2 labels
   Labeling(Label a, Label b, Label c); // Construct a labeling given 3 labels
   ~Labeling();        // Destroy this labeling

   void set_valid(int _valid);  // Set this labeling valid or invalid
   int isvalid();               // Is this labeling valid?
   int consistent_label(int index, Label label);
   Label get_label(int n);      // Get one of the labels of this labeling
   void force_ground(int n);  // Make this label invalid if not a convex line
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

