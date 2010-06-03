/* Boundary.H
 *
 * A boundary is just a list of concepts.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#ifndef _BOUNDARY_H_
#define _BOUNDARY_H_

#include <iostream.h>
#include "Concept.H"

class Example;
class Boundary {
friend ostream& operator<<(ostream &o, Boundary &b);    // Print a boundary
   Concept head;       // Head of a linked list is a stub with no info in it.

public:
   Boundary();         // Construct a new boundary
   ~Boundary();        // Destroy the boundary

   void add_concept(Concept *concept);   // Add a new concept to the boundary
   void specialize(Example *example);    // Specialize this boundary
   void generalize(Example *example);    // Generalize this boundary

   // Eliminate all concepts that are/aren't consistent with given example
   void eliminate(ConsistentType consistent, Example *example);

   // Every concept in this boundary must/mustn't be a
   // generalization/specialization of some concept in the given boundary
   void enforce_generalization_of(Boundary &boundary, int flag);
   void enforce_specialization_of(Boundary &boundary, int flag);

   // Does this boundary have some element which the given concept is a
   // specialization/generalization of?
   int has_element_concept_is_specialization_of(Concept *concept);
   int has_element_concept_is_generalization_of(Concept *concept);
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

