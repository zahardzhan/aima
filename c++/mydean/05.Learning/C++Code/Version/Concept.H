/* Concept.H
 *
 * A concept is a boolean combination of features. A feature is an attribute
 * together with a value for that attribute. "feature" is just another
 * word for "value". For this program, we assume that all concepts are
 * purely conjunctive.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#ifndef _CONCEPT_H_
#define _CONCEPT_H_

#include <iostream.h>
#include "Dimension.H"

// Things can either be consistent or inconsistent. A lot clearer
// than using 0 and 1.
enum ConsistentType {
   INCONSISTENT,
   CONSISTENT
};

const int NO_VALUE = -1;    // A concept can have no value for a dimension

class Example;
class Boundary;
class Concept {
friend ostream& operator<<(ostream &o, Concept &c);  // Print a concept
   int features[MAX_DIMENSIONS];  // The values of this concept, by dimension

public:
   Concept();                     // Construct an empty concept. No values.
   Concept(Concept *concept);     // Construct a new copy of given concept
   Concept(Example *example);     // Construct with same features as example
   ~Concept();                    // Destroy this construct, repair linked list

   Concept *next;    // The next concept in a linked list
   Concept *prev;    // The previous concept in a linked list
   void set_feature(int dim, int value);   // Set a value in this concept

   ConsistentType consistent(Example *example);  // Consistent with example?
   void generalize();     // Minimally generalize this concept
   void specialize();     // Minimally specialize this concept

   // Is this concept a generalization of the given concept?
   int is_generalization_of(Concept *concept);
};

#endif

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

