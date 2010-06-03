/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Step.C                                              */
/*    ASGN: Final                                              */
/*    DATE: Tue Jun 21 00:31:52 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <Step.H>
#include <Plan.H>
#include <Constrain.H>
#include <Operator.H>
#include <SLBag.H>
#include <Link.H>
#include <Requirement.H>
#include <Conflict.H>
#include <SLBagIterator.H>

int Step::S_id_ = 0;               // needed to initialize static variable


Step::Step(Operator* opertor)
{
   id_ = ++Step::S_id_;
   operator_ = opertor;
}


Step::Step(Step& step)
{
   id_ = step.id_;
   operator_ = step.operator_;
}


Step& Step::operator=(Step& step)
{
   id_ = step.id_;
   operator_ = step.operator_;
   return *this;
}

Step::~Step()
{
   ;
}



int Step::operator==(Step& step)
{
   if (id_ == step.id_) 
      return 1;
   return 0;
}


/****************************************************************/
/*                                                              */
/* Function Name: constrain                                     */
/* Parameters:                                                  */
/* Step* the step to be constrained to occur after this         */
/* Plan* the current plan being considered                      */
/* Returns: A new plan or 0                                     */
/* Effects:                                                     */
/*   Creates a new plan with one step to occure before another  */
/* if the two steps are not already constrained to occure in    */
/* the opposite order                                           */
/****************************************************************/


Plan* Step::constrain(Step* step, Plan* plan)
{
   if (step->precedes(this, plan->constraints()))
      {
         return 0;
      }
   else
      {
         SLBag<Constrain,ConstComp>* constraint = new     SLBag<Constrain,ConstComp>;
         constraint->addMember(new Constrain(this, step));

                               
         return new Plan(plan->steps(), 
                         plan->conflicts()->rest(),
                         plan->constraint()->adjoin(constraint),
                         plan->links(),
                         plan->requirements(),
                         plan->operators());
      }
}

/****************************************************************/
/*                                                              */
/* Function Name: precedes                                      */
/* Parameters: Step* the step being considered                  */
/* Returns: 1 if the object precedes step, 0 otherwise          */
/* Effects: Determines if the object precedes the step          */
/*                                                              */
/****************************************************************/


int Step::precedes(Step* step, 
                   SLBag<Constrain, ConstComp> * constraints)
{
   if(*this == *step)           // are the two steps the same
      {
         return 1;              // no
      }
   else 
      {
         SLBagIterator<Constrain, ConstComp>* c_iterator = new SLBagIterator<Constrain, ConstComp>(constraints);

                                // iterate through the constraints 
                                // trying to find out wether step precedes
                                // this
         for(c_iterator->start(); c_iterator->end(); c_iterator->next()) 
            {
               if((*this == *(c_iterator->current()->getElement()->begin())) &&
                  (c_iterator->current()->getElement()->end()->precedes(step,  constraints)))
                  {
                     delete c_iterator;
                     return 1;
                  }
             }
         delete c_iterator;     // failure so return 0, and delete the iterator
         return 0;
      }
}



/****************************************************************/
/*                                                              */
/* Function Name: conflicts                                     */
/* Parameters: Plan*                                            */
/* Returns:                                                     */
/* A set of conflicts                                           */
/* Effects:                                                     */
/*   Tries to find conflicts of a step with the links in the    */
/* plan                                                         */
/****************************************************************/


SLBag<Conflict, ConflictComp>* Step::conflicts(Plan* plan)
{
   SLBag<Conflict, ConflictComp>* ret_val = new SLBag<Conflict, ConflictComp>;
   
   SLBagIterator<Link, LinkComp>* iterator = new SLBagIterator<Link, LinkComp>(plan->links());
                                // iterate through the links, 
                                // trying to find a conflict with this step   
   for(iterator->start(); iterator->end(); iterator->next())
      {
         Conflict* conflict = conflictp(iterator->current()->getElement());

         if(conflict != 0) 
            {
               ret_val->addMember(conflict); // add the new conflict 
            }
      }
   return ret_val;
}


/****************************************************************/
/*                                                              */
/* Function Name: conflictp                                     */
/* Parameters: Link                                             */
/* Returns:                                                     */
/*   0- if no conflict was generate                             */
/*   Conflict: the conflict that was generated                  */
/* Effects:                                                     */
/*   Given a link and a step it determines wether a conflict    */
/* exists, if one does, then a conflict is returned, otherwise  */
/* a null is returned.                                          */
/****************************************************************/


Conflict* Step::conflictp(Link* link)
{
   if(!(*(link->consumer()) == *this) &&
      (operator_->deletions()->memberOf(link->conditions())))
      return new Conflict(link, this); // there was a conflict so return it
   return 0;                           // there was none so return the error
}


/****************************************************************/
/*                                                              */
/* Function Name: linkable                                      */
/* Parameters:                                                  */
/* Returns:                                                     */
/*  0- if no plan could be created                              */
/*  Plan* - the plan generated                                  */
/* Effects:                                                     */
/*  Given a requirement, and a plan, and the current step,      */
/* determines wether a step is linkable, thus generating a      */
/* new plan and returning it or otherwise 0                     */
/****************************************************************/


Plan* Step::linkable(Requirement* req, Plan* plan)
{
   ;
   if(!(operators()->additions()->memberOf(req->condition())) 
      || (req->step()->precedes(this, plan->constraints())))

      {
         return 0;
      }
   Link* link = new Link(this,req->step(),  req->condition());
   Constrain* constraint  = new Constrain(this, req->step());


   SLBag<Constrain,ConstComp>* constraints = new SLBag<Constrain, ConstComp>;
   SLBag<Link,LinkComp>* new_link = new SLBag<Link, LinkComp>(*plan->links());
   new_link->addMember(link);
   constraints->addMember(constraint);
   return new Plan(plan->steps(), 
                   link->conflicts(plan)->append(plan->conflicts()), 
                   plan->constraints()->adjoin(constraints), 
                   new_link,
                   plan->requirements()->rest(),
                   plan->operators());
}
   



/****************************************************************/
/*                                                              */
/* Function Name:                                               */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

int StepComp::equal(Step* step, Step* to)
{
   return *step == *to;
}

int StepComp::compare(Step* step, Step* to)
{
   if( step->id_ < to->id_) 
      {
         return 1;
      }
   else
      {
         return 0;
      }
}

void StepComp::display(Step* step)
{
   cout << "STEPS" << endl;
   cout << "id " << step->id_ << endl;
   cout << "OPERATORS "<< endl;
   OperatorComp disp;
   disp.display(step->operator_);
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

