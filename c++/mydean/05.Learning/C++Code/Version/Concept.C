/* Concept.C
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

#include "Concept.H"
#include "Example.H"
#include "Version.H"
#include "Dimension.H"
#include "String.H"

// Construct an empty concept. No features.
Concept::Concept()
{
  for(int x = 0; x < Version::num_dimensions; x++)
    features[x] = NO_VALUE;    // means no value for this concept

   next = NULL;
   prev = NULL;
}

// Bulid a new concept based on the given concept, and add it to the
// linked list. Copy all the features of the given concept.
Concept::Concept(Concept *concept)
{
   for(int x = 0; x < Version::num_dimensions; x++)
      features[x] = concept->features[x];

   next = concept->next;
   prev = concept;
   concept->next = this;
   next->prev = this;
}

// Construct a concept that has the same features as the given example
Concept::Concept(Example *example)
{
   for(int x = 0; x < Version::num_dimensions; x++)
      features[x] = example->get_value(x);

   next = NULL;
   prev = NULL;
}

// Delete dynamically allocated features array, and correct doubly-linked list.
Concept::~Concept()
{
    next->prev = prev;
    prev->next = next;
}

// Set one of the values of one of the attributes.
void Concept::set_feature(int dim, int value)
{
   features[dim] = value;
}

// A concept is consistent with an example if for each feature (conjunct) in
// the concept, either the attribute of the feature is not mentioned in
// the list of features describing the example, or, if it is mentioned,
// the corresponding feature has the same attribute value. For instance,
// if an example corresponds to an office on the third floor, then any
// concept consistent with that example must either not mention a floor or
// indicate the third floor.
ConsistentType Concept::consistent(Example *example)
{
   for(int x = 0; x < Version::num_dimensions; x++)
      if(features[x] != NO_VALUE && example->get_value(x) != features[x])
         return INCONSISTENT;

   return CONSISTENT;
}

// For the restricted hypothesis space consisting of conjunctions of positive
// literals, generalization corresponds to removing features from a concept
// represented as a conjunction of features.
void Concept::generalize()
{
   Concept *concept;
   for(int x = 0; x < Version::num_dimensions; x++)
      if(features[x] != NO_VALUE) {
         concept = new Concept(this);  // Adds it to the linked list
         concept->set_feature(x, NO_VALUE);
      }
}

// Minimally specialize this concept. Add new concepts to the boundary.
void Concept::specialize()
{
   Concept *temp;
   for(int dim = 0; dim < Version::num_dimensions; dim++)
	if(features[dim] == NO_VALUE)   // Only if consistent
	  for(int v = 0; v < Version::dimensions[dim].num_values; v++) {
	    temp = new Concept(this);   // Adds it to the linked list
	    temp->set_feature(dim, v);  // Adds the new feature
	  }
}

// Is this class a generalization of the given class? If so, return TRUE.
int Concept::is_generalization_of(Concept *concept)
{
   for(int x = 0; x < Version::num_dimensions; x++)
      if(features[x] != NO_VALUE && concept->features[x] != features[x])
         return 0;

   return 1;
}

// Print this concept
ostream& operator<<(ostream &o, Concept &c)
{
  o << "( ";
  for(int x = 0; x < Version::num_dimensions; x++)
    if(c.features[x] != NO_VALUE)
      o << Version::dimensions[x].values[c.features[x]] << " ";
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

