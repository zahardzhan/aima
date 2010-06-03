/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Plan.H                                              */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:05:54 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef PLAN_HEADER
#define PLAN_HEADER

#include <Compare.H>
#include <Queue.H>
#include <SLBag.H>
#include <State.H>

/****************************************************************/
/* CLASS NAME : Plan                                            */
/*  A plan consists of a set of steps corresponding to operators*/
/* on the order in which these steps are to be carried out,     */
/* and information regarding how the steps depend on one another*/
/* The dependcy information is of three different types.        */
/* First there are objects called requirements indicating       */
/* propositions that are required in order that certain         */
/* operators have their desired effect. Next there are records  */
/* called links describing how consequences of one operator     */
/* are used to satisfy the requirements of another. Finally     */
/* there are records called conflicts describing potential      */
/* undesirable interactions between operators.                  */
/*  A plan is a state in a state space, derived from the        */
/* abstract class. A plan knows how to refine itself and        */
/* generate new plans, given the operators that can be applied  */
/* in the state space. The refine method works in a similar     */
/* fashion to the refine function in the Lisp code. The refine  */
/* generates a bag of new plans, which are then returned one    */
/* at a time by the makeTransition method. A flag is kept       */
/* around to know wether refinements have been made or not.     */
/*                                                              */
/****************************************************************/
 


class Plan : public State 
{
   SLBag<Step, StepComp>* steps_;
   SLBag<Conflict, ConflictComp>* conflicts_;
   SLBag<Constrain, ConstComp>* constraints_;
   SLBag<Link,LinkComp>* link_;
   SLBag<Operator, OperatorComp>* operators_;
   SLBag<Requirement, ReqComp>* requirements_;
   Queue<Plan, PlanComp>* next_plans_;
   int refinements_made_;
   virtual void unMarkTransitions() {;}
   // copies the bag of plans created by refine into the next_plans queue
   void setUpQueue(SLBag<Plan, PlanComp>* plans);
public:
   Plan();
   friend class PlanComp;
   Plan(Plan& plan);
   Plan& operator=(Plan& plan);
   Plan(SLBag<Step, StepComp>* steps,
        SLBag<Conflict, ConflictComp>* conflicts,
        SLBag<Constrain, ConstComp>* constraints,
        SLBag<Link, LinkComp>* links,
        SLBag<Requirement, ReqComp>* requirements,
        SLBag<Operator, OperatorComp>* operators);
   Plan(Plan* plan, SLBag<Constrain, ConstComp>* constraints);
 
   // generates refined plans from this plan
   void refine();

   // displays the plans steps
   void display()
      {
         steps_->display();
      }
  
   // returns the next plan if there is one still left in the queue,
   // else returns 0. 
   virtual State* makeTransition();
   // checks wether the current plan has reached the goal.
   virtual int compare(State* state);
   SLBag<Step, StepComp>* steps() 
         {
          return steps_;
       }
   SLBag<Constrain, ConstComp> * constraints()
      {
         return constraints_;
      } 
   SLBag<Conflict, ConflictComp>* conflicts()
      {
         return conflicts_;
      }
   SLBag<Constrain, ConstComp>* constraint()
      {
         return constraints_;
      }
   SLBag<Link,LinkComp>* links()
      {
         return link_;
      }
   SLBag<Requirement, ReqComp>* requirements()
      {
         return requirements_;
      }
   SLBag<Operator, OperatorComp>* operators()
      {
         return operators_;
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

