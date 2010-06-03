/* Labeling.C
 *
 * A labeling for a vertex is an assignment of +, -, RIGHT, or LEFT
 * to the lines coming together at the vertex. These assignments form
 * a kind of description of the real-world scene.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include "Labeling.H"

// The dummy constructor. When this is used, the labeling must be initialized
// with real data right away.
Labeling::Labeling()
{
}

// Construct a labeling with two labels
Labeling::Labeling(Label a, Label b)
{
   num_labels = 2;
   labels[0] = a;
   labels[1] = b;

   valid = 1;   // Assume it is valid
}

// Construct a labeling with three labels
Labeling::Labeling(Label a, Label b, Label c)
{
   num_labels = 3;
   labels[0] = a;
   labels[1] = b;
   labels[2] = c;

   valid = 1;   // Assume it is valid
}

// Destroy the labeling
Labeling::~Labeling()
{
}

// Set the labeling either valid or invalid
void Labeling::set_valid(int _valid)
{
   valid = _valid;
}

// Is this labeling valid?
int Labeling::isvalid()
{
   return valid;
}

// Is the indexed label in this Labeling consistent with the given label?
int Labeling::consistent_label(int index, Label label)
{
   switch(labels[index]) {
   case PLUS:
      return label == PLUS;
   case MINUS:
      return label == MINUS;
   case RIGHT:
      return label == LEFT;
   case LEFT:
      return label == RIGHT;
   }
}

// Return the indexed label
Label Labeling::get_label(int n)
{
   return labels[n];
}

// Make this label invalid if not a convex line. If the label
// has a '-' in the nth position, then it is OK.
void Labeling::force_ground(int n)
{
  if(labels[n] != MINUS)
    valid = 0;               // Make invalid
}

// Print out this labeling
ostream& operator<<(ostream &o, Labeling &labeling)
{
   o << "( ";
   for(int label = 0; label < labeling.num_labels; label++)
      switch(labeling.labels[label]) {
      case PLUS:
         o << "+ ";
         break;
      case MINUS:
         o << "- ";
         break;
      case RIGHT:
         o << "RIGHT ";
         break;
      case LEFT:
         o << "LEFT ";
         break;
      }
   o << ")";

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

