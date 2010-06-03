/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Link.C                                              */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 01:43:04 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <Link.H>
#include <Plan.H>
#include <Conflict.H>
#include <SLBag.H>
#include <SLBagIterator.H>
#include <Step.H>

#include <XDString.H>
    
Link::Link(Step* producer, Step* consumer, XDString* condition)
{
   producer_ = new Step(*producer);
   consumer_ = new Step(*consumer);
   conditions_ = new XDString(*condition);
}



Link::Link(Link& link)
{
   producer_ = new Step(*link.producer_);
   consumer_ = new Step(*link.consumer_);
}

Link::~Link()
{
   delete producer_;
   delete consumer_;
}


Link& Link::operator=(Link& link)
{
   delete producer_;
   delete consumer_;
   producer_ = new Step(*link.producer_);
   consumer_ = new Step(*link.consumer_);
   conditions_ = new XDString(*link.conditions_); 
   return *this;
}



/****************************************************************/
/*                                                              */
/* Function Name: conflicts                                     */
/* Parameters: Plan* the current plan                           */
/* Returns: All the conflicts                                   */
/* Effects:                                                     */
/*  This mimics the functionality in the Lisp code. Given a     */
/* link and a plan, determines wether new conflicts can be      */
/* generated.                                                   */
/****************************************************************/


SLBag<Conflict,ConflictComp>* Link::conflicts(Plan* plan)
{
   // create the bag of return values
   SLBag<Conflict,ConflictComp>* ret_val = new SLBag<Conflict, ConflictComp>;
   
   // iterate through each step calling the conflictp method with 
   // this link and the current plan, and return all the generated conflicts
   SLBagIterator<Step,StepComp>* iterator = new SLBagIterator<Step, StepComp>(plan->steps());
   
   for(iterator->start(); iterator->end(); iterator->next())
      {
         Conflict* conflict = iterator->current()->getElement()->conflictp(this);
         if(conflict != 0 )
            ret_val->addMember(conflict);
      }
   return ret_val;
}


int LinkComp::compare(Link* link, Link* to)
{
   StepComp step_comp;
   return step_comp.equal(link->producer_,to->producer_);
}


int LinkComp::equal(Link* link, Link* to)
{
   StepComp step_comp;
   StringComp string_comp;
   if((step_comp.equal(link->producer_, to->producer_))  &&
      (step_comp.equal(link->consumer_, to->consumer_))  &&
      (string_comp.equal(link->conditions_, to->conditions_)))
      {
         return 1;
      }
   else
      {
         return 0;
      }
}

void LinkComp::display(Link* link)
{
   cout << "Display the links " << endl;
   cout << "display the producer " << endl;
   StepComp disp_step;
   disp_step.display(link->producer_);
   cout << endl;
   cout << "the consumer ";
   disp_step.display(link->consumer_);
   cout << endl;
   cout << "conditions " << *link->conditions_ << endl;
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

