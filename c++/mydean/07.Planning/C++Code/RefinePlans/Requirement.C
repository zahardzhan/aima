/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Requirement.C                                       */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:57:26 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Requirement.H"
#include <SLBag.H>
#include <SLBagIterator.H>
#include <Plan.H>
#include <Conflict.H>
#include <SLBagIterator.H>
#include <Operator.H>
#include <XDString.H>
#include <Step.H>
#include <Constrain.H>
#include <Link.H>

Requirement::Requirement(Step* step, XDString* condition)
{
   step_ = new Step(*step);
   condition_ = new XDString(*condition);
}

Requirement::~Requirement()
{
   delete step_;
   delete condition_;
}




/****************************************************************/
/*                                                              */
/* Function Name:new_step                                       */
/* Parameters:                                                  */
/* SLBag<Operator, OperatorComp>* operators : the operators     */
/* Plan* plan : the current plan                                */
/* Returns: A new bag of plans                                  */
/* Effects: Identical in functionality to the Lisp function     */
/*    resolve-req-new-step. This function eliminates a          */
/* requirement by adding a new step, and create a new plan      */
/* for each applicable operator                                 */
/****************************************************************/


SLBag<Plan, PlanComp>*
 Requirement::new_step(SLBag<Operator, OperatorComp>* operators,
                            Plan* plan)
{
   SLBag<Plan,PlanComp>* ret_val = new SLBag<Plan, PlanComp>;
   SLBagIterator<Operator, OperatorComp>* iterator = new SLBagIterator<Operator, OperatorComp>(operators);
   // iterate throught the operators to determine which are applicable
   for(iterator->start(); iterator->end(); iterator->next())
      {
        Plan* new_plan =applicable(iterator->current()->getElement(), plan);
        if(new_plan != 0)
           ret_val->addMember(new_plan);
      }
   return ret_val;
}



/****************************************************************/
/*                                                              */
/* Function Name:applicable                                     */
/* Parameters:                                                  */
/* Operator* opertor: the operator being considered             */
/* Plan* plan : the current plan                                */
/* Returns: A new plan, or 0, indicating the operator was       */
/* not applicable with the given requirement                    */
/* Effects: Identical to the applicablep function in the Lisp   */
/* text. An operator is applicable just in case the condition   */
/* of the requirement is added by the operator. If applicable,  */
/* create a new plan from the old one by adding a new           */
/* requirement, constraining the new step to precede the        */
/* step of the resolved requirement, eliminating this           */
/* requirement, adding a link resolving the requirement with    */
/* the new step as producer, adding a new set of requirements   */
/* corresponding to the preconditions of the operator, and      */
/* updating the set of conflicts.                               */
/* The implementation follows that of the book.                 */
/****************************************************************/


Plan* Requirement::applicable(Operator* opertor, Plan* plan)
{
    if(!(opertor->additions()->memberOf(condition_)))
      {
         return 0;
      }
   Step* step = new Step(opertor);

   SLBag<Constrain, ConstComp>* constraint = new SLBag<Constrain, ConstComp>;
   constraint->addMember(new  Constrain(step, step_));
   Link* link = new Link(step , step_ , condition_);
   SLBag<Step, StepComp>* new_step = new SLBag<Step, StepComp>(*plan->steps());
   new_step->addMember(step);
   SLBag<Link, LinkComp>* new_link = new SLBag<Link, LinkComp>(*plan->links());
   new_link->addMember(link);
   Plan* ret_plan = new Plan(new_step,
                             link->conflicts(plan)->append(step->conflicts(plan)->append(plan->conflicts())),
                             plan->constraints()->adjoin(constraint),
                             new_link,
                             generateRequirements(opertor, step)->append(plan->requirements()->rest()),
                             plan->operators());
   return ret_plan;
   
}
   

/****************************************************************/
/*                                                              */
/* Function Name: generateRequirements                          */
/* Parameters: Operator* operator : the current operator        */
/* Step* step : the condition for the generated requirements    */
/* Returns: A bag of requirements                               */
/* Effects: Generates a requirement for every precondition      */
/* of the operator with the step being the condition of the     */
/* requirement                                                  */
/*                                                              */
/****************************************************************/


SLBag<Requirement,ReqComp>* 
Requirement::generateRequirements(Operator* opertor, Step* step)
{
   SLBagIterator<XDString, StringComp>* iterator = new SLBagIterator<XDString, StringComp>(opertor->preconditions());
   SLBag<Requirement, ReqComp>* ret_val = new SLBag<Requirement, ReqComp>;
   for(iterator->start(); iterator->end(); iterator->next())
      {
         ret_val->addMember(new Requirement(step, iterator->current()->getElement()));
      };
   return ret_val;
}



/****************************************************************/
/*                                                              */
/* Function Name: existing_step                                 */
/* Parameters: Requirement*                                     */
/* Plan* the current plan being operated on                     */
/* Returns: A bag of new plans                                  */
/* Effects: works exactly like the resolve-req-existing-step    */
/* It eliminates a requirement using an existing step, creating */
/* a new plan for each existing step that can be linked to      */
/* satisfy the requirement.                                     */
/*                                                              */
/****************************************************************/



SLBag<Plan, PlanComp>*
Requirement::existing_step(Requirement* req, Plan* plan)
{
   SLBagIterator<Step,StepComp>* iterator = new SLBagIterator<Step, StepComp>(plan->steps());
   SLBag<Plan, PlanComp>* ret_val = new SLBag<Plan, PlanComp>;
   for(iterator->start(); iterator->end(); iterator->next())
      {
         Plan* new_plan = iterator->current()->getElement()->linkable(req, plan);
         if(new_plan != 0) 
            {
               ret_val->addMember(new_plan); 
            }
      }
   return ret_val;
}


int ReqComp::compare(Requirement* req, Requirement* to)
{
   StepComp step_comp;
   return step_comp.compare(req->step_, to->step_);
}

int ReqComp::equal(Requirement* req, Requirement* to)
{
   StepComp step_comp;
   StringComp string_comp;
   if(step_comp.equal(req->step_, to->step_) 
      && string_comp.equal(to->condition_, req->condition_))
      {
         return 1;
      }
   else 
      {
         return 0;
      }
}
void ReqComp::display(Requirement* rw)
{
   cout << "Displaying requirement condition " << *rw->condition_ << endl;
   cout << "Displaying requirement steps " << endl;
   StepComp disp;
   disp.display(rw->step_);
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

