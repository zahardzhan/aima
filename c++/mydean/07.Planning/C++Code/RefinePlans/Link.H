/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Link.H                                              */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 01:36:10 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef LINK_HEADER
#define LINK_HEADER
#include <Compare.H>
#include <SLBag.H>
#include <SLBagIterator.H>

class XDString;

/****************************************************************/
/* CLASS NAME : Link                                            */
/*  A link involves two steps and a condition. One step, called */
/* the producer has the condition in the list of additions      */
/* for its associated operator. The producer makse the          */
/* condition true. The other step, called the consumer,         */
/* has the condition in the list of preconditions for its       */
/* associated operator. The consumer requires that the condition*/
/* be true. Links are created to satisfy requirements.          */
/*  A link can generate conflicts if they exist with a given    */
/* plan. The conflicts method is identical in purpose and       */
/* functionality as the function in the Lisp code.              */
/*                                                              */
/****************************************************************/
class Link 
{
   Step* producer_;
   Step* consumer_;
   XDString* conditions_;
   Link();
public:
friend class LinkComp;
   Link(Step* producer, Step* consumer, XDString* conditions);
   Link(Link& link);
   Link& operator=(Link& link);
   ~Link();
   // When a step is adde, this function finds all the links that might
   // conflict with it
   SLBag<Conflict,ConflictComp>* conflicts(Plan* plan);

   Step* producer()
      {
         return producer_;
      }
   Step* consumer()
      {
         return consumer_;
      }
   XDString* conditions()
      {
         return conditions_;
      }
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

