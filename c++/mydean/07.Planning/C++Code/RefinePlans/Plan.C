/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Plan.C                                              */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:05:27 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <Plan.H>
#include <Conflict.H>
#include <SLBag.H>
#include <Queue.H>
#include <SLBagIterator.H>
#include <Step.H>
#include <Conflict.H>
#include <Requirement.H>
#include <Constrain.H>
#include <Operator.H>
#include <Link.H>

/****************************************************************/
/*                                                              */
/* Function Name: Plan                                          */
/* Parameters: <none>                                           */
/* Returns: <none>                                              */
/* Effects: Initializes all the variables to an empty state     */
/*                                                              */
/****************************************************************/


Plan::Plan()
{
   steps_ = new SLBag<Step,StepComp>;
   conflicts_ = new SLBag<Conflict, ConflictComp>;
   constraints_ = new SLBag<Constrain, ConstComp>;
   link_ = new SLBag<Link, LinkComp>;
   requirements_ = new SLBag<Requirement, ReqComp>;
   operators_ = new SLBag<Operator, OperatorComp>;
   next_plans_ = new Queue<Plan, PlanComp>;
   refinements_made_ = 0;
}

/****************************************************************/
/*                                                              */
/* Function Name: Plan(Plan& plan)                              */
/* Parameters: Plan& plan: the plan to copy from                */
/* Returns: <none>                                              */
/* Effects: Copies the data from plan to this                   */
/*                                                              */
/****************************************************************/

Plan::Plan(Plan& plan)
{
   steps_ = new SLBag<Step,StepComp>(*plan.steps_);
   conflicts_ = new SLBag<Conflict, ConflictComp>(*plan.conflicts_);
   constraints_ = new SLBag<Constrain, ConstComp>(*plan.constraints_);
   link_ = new SLBag<Link, LinkComp>(*plan.link_);
   requirements_ = new SLBag<Requirement, ReqComp>(*plan.requirements_);
   operators_ = new SLBag<Operator, OperatorComp>(*plan.operators_);
   next_plans_ = new Queue<Plan, PlanComp>(*plan.next_plans_);
   refinements_made_ = plan.refinements_made_;
}


/****************************************************************/
/*                                                              */
/* Function Name:operator=                                      */
/* Parameters: Plan&                                            */
/* Returns: Plan& this pointer                                  */
/* Effects: overwrites the data currently in this with the data */
/* in plan                                                      */
/*                                                              */
/****************************************************************/


Plan& Plan::operator=(Plan& plan)
{
   delete steps_;
   delete operators_;
   delete conflicts_;
   delete constraints_;
   delete link_;
   delete requirements_;
   delete next_plans_;
   steps_ = new SLBag<Step,StepComp>(*plan.steps_);
   conflicts_ = new SLBag<Conflict, ConflictComp>(*plan.conflicts_);
   constraints_ = new SLBag<Constrain, ConstComp>(*plan.constraints_);
   link_ = new SLBag<Link, LinkComp>(*plan.link_);
   requirements_ = new SLBag<Requirement, ReqComp>(*plan.requirements_);
   operators_ = new SLBag<Operator, OperatorComp>(*plan.operators_);
   next_plans_ = new Queue<Plan, PlanComp>(*plan.next_plans_);
   refinements_made_ = plan.refinements_made_;
   return *this;

}


/****************************************************************/
/*                                                              */
/* Function Name: Plan                                          */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*    Creates a new plan using the data passed to it            */
/****************************************************************/


Plan::Plan(SLBag<Step, StepComp>* steps,
           SLBag<Conflict, ConflictComp>* conflicts,
           SLBag<Constrain, ConstComp>* constraints,
           SLBag<Link, LinkComp>* links,
           SLBag<Requirement, ReqComp>* requirements,
           SLBag<Operator, OperatorComp>* operators)
{
   steps_ = new SLBag<Step,StepComp>(*steps);
   conflicts_ = new SLBag<Conflict, ConflictComp>(*conflicts);
   constraints_ = new SLBag<Constrain, ConstComp>(*constraints);
   link_ = new SLBag<Link, LinkComp>(*links);
   requirements_ = new SLBag<Requirement, ReqComp>(*requirements);
   next_plans_ = new Queue<Plan, PlanComp>;
   operators_ = new SLBag<Operator,OperatorComp>(*operators);
   refinements_made_ = 0;
}



void Plan::setUpQueue(SLBag<Plan,PlanComp>* plans)
{
   SLBagIterator<Plan,PlanComp>* iterator = new SLBagIterator<Plan,PlanComp>(plans);
   for(iterator->start(); iterator->end(); iterator->next()) 
      {
         next_plans_->insert(iterator->current()->getElement());
      };
   delete iterator;
   return;
}

/****************************************************************/
/*                                                              */
/* Function Name: refine                                        */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/* Effects:                                                     */
/*   The refinement function found in the Lisp book. It creates */
/* the new plans and then puts them in a queue which has the    */
/* members popped off one at a time.                            */
/****************************************************************/


void Plan::refine()
{
   SLBag<Plan,PlanComp>* plans = new SLBag<Plan,PlanComp>;
   
   if(!(conflicts_->size() == 0))       // are there are any conflicts?
      {                                 // if so resolve them here
         plans->appendTo(conflicts()->nth(1)->getElement()->resolve(this));
         setUpQueue(plans);
         delete plans;
         return;
      } 
   
// resolve-req-new-step
   plans->appendTo(requirements()->nth(1)->getElement()->new_step(operators_, this));

// resolve-req-existing-step
   plans->appendTo(requirements()->nth(1)->getElement()->existing_step(requirements()->nth(1)->getElement(),this));

// copy plans to queue which will then be removed
   setUpQueue(plans);
   delete plans;
   return;
}


/****************************************************************/
/*                                                              */
/* Function Name: makeTransition                                */
/* Parameters: <none>                                           */
/* Returns: State* : the next plan in the state space           */
/* Effects: First calls the refine method to generate the plans */
/* and then removes each plan from the queue returning 0, when  */
/* there are no more elements in the queue.                     */
/*                                                              */
/*                                                              */
/****************************************************************/


State* Plan::makeTransition()
{
   if(!refinements_made_)        // have  the new plans been made
      {
         refinements_made_ = 1; 
         refine();              // make them
      }
   if(next_plans_->empty())     // are there any plans left?
      {
         return 0;              // no
      }
   else 
      {
         Plan* ret_val = new Plan(); // yes,
         next_plans_->remove(ret_val); // get it 
         return ret_val;               // return it 
      }
}


int Plan::compare(State* state)
{
   if((requirements()->size() == 0) && (conflicts()->size() == 0))
      {
         return State::EQUAL;
      }
   return State::NOT_EQUAL;
}



int PlanComp::equal(Plan* plan, Plan* to) // not defined
{
   return 0;
}


int PlanComp::compare(Plan* plan, Plan* to) 
{
   if(plan->requirements_->size() < to->requirements_->size())
      {
         return 1;
      }
   else
      {
         return 0;
      }
}

void PlanComp::display(Plan* plan) 
{
   cout << "Displaying the CURRENT plan" << endl;
   cout << "\tDisplaying the Steps! " << endl;
   plan->steps_->display();
   cout << "\tDisplaying the conflicts " << endl;
   plan->conflicts_->display();
   cout << plan->conflicts_->size() << endl;
   cout << "\tDisplaying the constraints " << endl;
   plan->constraints_->display();
   cout << "\tDisplaying the links " <<endl;
   plan->link_->display();
   cout << "\tDisplaying the Requirements " << endl;
   plan->requirements_->display();

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

