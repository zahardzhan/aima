/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Conflict.C                                          */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:22:43 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Conflict.H"
#include <Plan.H>
#include <Link.H>
#include <SLBag.H>
#include <Step.H>
Conflict::Conflict(Link* link, Step* clobberer)
{
   link_ = new Link(*link);
   clobberer_ = new Step(*clobberer);
}

Conflict::~Conflict()
{
   delete link_;
   delete clobberer_;
}

/****************************************************************/
/*                                                              */
/* Function Name:resolve                                        */
/* Parameters: Plan* : the current plan                         */
/* Returns: A bag of new plans                                  */
/* Effects: Constrains the clobberer to occur before the        */
/*          consumer of the link returning the resulting plan   */
/* if that can be done, otherwise returning an empty bag. It    */
/* also tries to constrain the producer of the link to occure   */
/* before the clobberer.                                        */
/*                                                              */
/****************************************************************/


SLBag<Plan,PlanComp>* Conflict::resolve(Plan* plan) 
{
   SLBag<Plan,PlanComp>* ret_val = new SLBag<Plan,PlanComp>;
   Plan* new_plan = clobberer_->constrain(link_->producer(), plan);
   if(new_plan != 0)
      ret_val->addMember(new_plan);
   new_plan = link_->consumer()->constrain(clobberer_, plan);
   if(new_plan != 0)
      ret_val->addMember(new_plan);
   return ret_val;             // returns a the new plans
}




int ConflictComp::equal(Conflict* conflict, Conflict* to)
{
   LinkComp link_comp;
   StepComp step_comp;
   if((link_comp.equal(conflict->link_, to->link_)) && (step_comp.equal(conflict->clobberer_, to->clobberer_)))
      return 1;
   return 0;
}


int ConflictComp::compare(Conflict* conflict, Conflict* to)
{
   StepComp step_comp;
   return step_comp.compare(conflict->clobberer_, to->clobberer_);
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

