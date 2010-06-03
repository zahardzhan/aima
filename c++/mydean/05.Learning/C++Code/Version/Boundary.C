/* Boundary.C
 *
 * A boundary is just a list of concepts.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include "Boundary.H"
#include "Example.H"
#include "Concept.H"
#include "Version.H"
#include "Dimension.H"

// Create the stub concept, which holds no data, but just serves as the
// head of the doubly-linked list.
Boundary::Boundary()
{
   head.next = &head;
   head.prev = &head;
}

// Delete all the concepts in this boundary.
Boundary::~Boundary()
{
   while(head.next != &head)
      delete head.next;
}

// Place this new concept at the end of the doubly-linked list.
void Boundary::add_concept(Concept *concept)
{
   concept->prev = head.prev;
   concept->next = &head;
   head.prev->next = concept;
   head.prev = concept;
}

// (b) Minimally specialize all concepts in the general boundary until they
//     are not consistent with the example,         
void Boundary::specialize(Example *example)
{
   Concept *concept = &head;
   while(concept->next != &head)
      if(concept->next->consistent(example) == CONSISTENT) {
         concept->next->specialize();
         delete concept->next;        // Don't need this anymore
      } else
	concept = concept->next;      // Keep going through loop if no delete
}

// (b) Minimally generalize all concepts in the specific boundary until
//     they are consistent with the example.
void Boundary::generalize(Example *example)
{
  Concept *concept = &head;
  while(concept->next != &head)
    if(concept->next->consistent(example) != CONSISTENT) {
      concept->next->generalize();
      delete concept->next;        // Don't need this anymore
    } else 
      concept = concept->next;     // Keep going through loop if no delete
}

// Eliminate all concepts in this boundary that either are or are not
// consistent with the given example.
void Boundary::eliminate(ConsistentType consistent, Example *example)
{
   Concept *concept = &head;
   while(concept->next != &head)
     if(concept->next->consistent(example) == consistent)
       delete concept->next;
     else
       concept = concept->next;    // Keep going through loop if no delete
}

// Check each concept of this boundary to make sure it is a generalization
// of some concept in the given boundary. The flag indicates
// whether we want only generalizations, or only not generalizations.
void Boundary::enforce_generalization_of(Boundary &boundary, int flag)
{
   Concept *concept = &head;
   while(concept->next != &head)
      if(boundary.has_element_concept_is_generalization_of(concept->next)
	 != flag)
         delete concept->next;      // Don't need this anymore
      else
	 concept = concept->next;   // Keep going through loop if no delete
}

// Check each concept of this boundary to make sure it is a specialization
// of some concept in the given boundary. The flag indicates
// whether we want only specializations, or only not specializations.
void Boundary::enforce_specialization_of(Boundary &boundary, int flag)
{
   Concept *concept = &head;
   while(concept->next != &head)
      if(boundary.has_element_concept_is_specialization_of(concept->next)
	 != flag)
         delete concept->next;     // Don't need this anymore
      else
	concept = concept->next;   // Keep going through loop if no delete
}

// Check to see if the given concept is a generalization of any concept
// in the boundary. This is the same as asking if the boundary has a
// specialization of the given concept.
int Boundary::has_element_concept_is_generalization_of(Concept *general)
{
   for(Concept *concept = &head; concept->next != &head; concept=concept->next)
      if(concept->next != general &&
	 general->is_generalization_of(concept->next))
         return 1;

   return 0;
}

// Check to see if the given concept is a specialization of any concept
// in the boundary. This is the same as asking if the boundary has a
// generalization of the given concept.
int Boundary::has_element_concept_is_specialization_of(Concept *specific)
{
   for(Concept *concept = &head; concept->next != &head; concept=concept->next)
      if(concept->next != specific
	 && concept->next->is_generalization_of(specific))
         return 1;

   return 0;
}

// Print the boundary, which basically means printing all the concepts.
ostream& operator<<(ostream &o, Boundary &b)
{
   for(Concept *con = &b.head; con->next != &b.head; con=con->next) {
    if(con != &b.head)     // Don't indent the very first concept
	o << "          ";
     o << *con->next << endl;
   }
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

