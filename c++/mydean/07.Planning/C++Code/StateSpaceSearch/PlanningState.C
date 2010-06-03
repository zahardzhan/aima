/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: PlanningState.C                                     */
/*    ASGN: Final                                               */
/*    DATE: Sun Jun 19 22:31:19 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "PlanningState.H"


PlanningState::PlanningState(Queue<Operator,OperatorComp>* operators, SLBag<XDString, StringComp>* set)
{
   operators_ = operators;
   next_plans_ = new Queue<PlanningState, PlanningCompare>;
   to_be_done_operators_ = new Queue<Operator,OperatorComp>(*operators);
   symbols_ = new SLBag<XDString, StringComp>(*set);
   calculated_next_steps_ = 0;
}   


/****************************************************************/
/*                                                              */
/* Function Name: makeTranistion                                */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  State* the next state                                       */
/*  0 : no further states                                       */
/* Effects:                                                     */
/*  If no next states have been generated it generates them,    */
/* otherwise it returns the next plan from the next plans       */
/* queue. If there are no next plans(i.e all the next plans)    */
/* have been generated, it returns 0, indicating that           */
/* all possible transitions from this state have been made      */
/****************************************************************/


State* PlanningState::makeTransition()
{
  if(!calculated_next_steps_)
     {
      applyOperators();
     }
  if(next_plans_->empty())
     {
        return 0;
     }
  else
     {
        PlanningState* next_plan;
        next_plans_->remove(next_plan);
        return next_plan;
     }
}

/****************************************************************/
/*                                                              */
/* Function Name: applyOperators                                */
/* Parameters:<none>                                            */
/* Returns: <none>                                              */
/* Effects:                                                     */
/*  This method is similar in purpose to the applicable         */
/* function in the Lisp code. Given a set of operators          */
/* and the current state it generates all the next states.      */
/* It first sets the calculated flag to true, and then for      */
/* every operator it creates the next operators.  The way it    */
/* does it is identical to the method outlined in the textbook. */
/* It first determines wether the operators are a subset        */
/* (called subbag) of the symbols of the current state.         */
/* If that is so it then creates a new plan from the            */
/* unfication of the additions of the current operator and      */
/* the difference of the symbols of the current object and      */
/* the operators deletions. It then puts the next state         */
/* in a queue to be retrieved later.                            */
/****************************************************************/



void PlanningState::applyOperators()
{
   calculated_next_steps_ = 1;  // next plans have been created
   while(!to_be_done_operators_->empty()) // while there are no more operators
                                          // left to apply
      {

         Operator* opertor;
         to_be_done_operators_->remove(opertor); // get the next operator

         // are the operators preconditions a sub set of the symbols_ of 
         // of this object
         if(opertor->preconditions()->subBag(symbols_)) 
            {
               // yes so create a new plan
               SLBag<XDString, StringComp>* new_set = new SLBag<XDString, StringComp>(*(opertor->additions()));
               // temp_set = difference of symbols_ and opertor->deletions
               SLBag<XDString, StringComp>* temp_set;
               temp_set = symbols_->difference(opertor->deletions());
               new_set = new_set->unify(temp_set);
               // add new plan to queue of next plans to be
               // retrieved later
               next_plans_->insert(new PlanningState(operators_,new_set));
            }
      }
}
int PlanningState::compare(State* state)
{
   PlanningState * other = (PlanningState *) state;
   
   if(other->symbols_->subBag(this->symbols_))
      {
         return State::EQUAL;
      }
   return State::NOT_EQUAL;
};


void PlanningCompare::display(PlanningState* state)
      {
         state->symbols_->display();
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

