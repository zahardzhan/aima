/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Step.H                                              */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:30:51 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef STEP_HEADER
#define STEP_HEADER

#include <Compare.H>
#include <SLBag.H>

/****************************************************************/
/* CLASS NAME :  Step                                           */
/*    A step is the abstraction for a step in least commitment  */
/* planning, similar in purpose to the Step described in the    */
/* text book. A step can constrain itself with another step     */
/* given a plan,determine if it precedes another step           */
/* and determine wether a given step, and requirement are       */
/* linkable so as to produce a new step.                        */
/*    A step has an id and an operator associated to it.        */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/

class Step 
{
   int label_;
   int id_;
   Operator* operator_;
   static int S_id_;
   Step();
public:
   friend class StepComp;
   // creates an operator with a particular id and operator
   Step(Operator* operators);
   Step(Step& step);
   Step& operator=(Step& step);
   ~Step();
   // Creates a new plan with one step to occure before another
   // if the two steps are not already constrained to occur in the oposite
   // order
   Plan* constrain(Step* step, Plan* plan);
   // determines wether this object precedes step given contraints
   int precedes(Step* step, SLBag<Constrain, ConstComp>* constraints);
   // are the steps equal?
   int operator==(Step& step);
   // tries to conficts with the links in the plan.
   SLBag<Conflict, ConflictComp>* conflicts(Plan* plan);
   // Given a link this object it determines wether a conflict
   // exists and if one does, then a conflict is returned
   // otherwise a null is returned. 
   Conflict* conflictp(Link* link);
   // Given a requirement, and a plan, and the current step, this method
   // determins whether a step is linkable, thus generating a new plan and
   // returning it or otherwise returning 0
   Plan* linkable(Requirement* req, Plan* plan);
   Operator* operators()
      {
         return operator_;
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

