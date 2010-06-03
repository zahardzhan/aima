/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: PlanningState.H                                     */
/*    ASGN: Final                                               */
/*    DATE: Sun Jun 19 22:05:35 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef PLANNINGSTATE_HEADER
#define PLANNINGSTATE_HEADER


/****************************************************************/
/* CLASS NAME :  PlanningState                                  */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/

#include "Compare.H"
#include <XDString.H>
#include <State.H>
#include <SLBag.H>
#include <Queue.H>
#include <Operator.H>

class PlanningState : public State 
{
   int  calculated_next_steps_; // a flag to indicate whether the next 
                                // have been found
   Queue<PlanningState, PlanningCompare>* next_plans_;
                                // the next plans
   SLBag<XDString, StringComp>* symbols_;
                                // the symbols 
   Queue<Operator, OperatorComp>* operators_;
                                // the operators that can be applied
                                // to the state to generate further
                                // states
   Queue<Operator, OperatorComp>* to_be_done_operators_;
                                // the operators not yet applied
public:

   friend PlanningCompare;
   friend class Heuristic;            // the heuristic for best search
   PlanningState(Queue<Operator, OperatorComp>* operators, SLBag<XDString, StringComp>* set);
   virtual State* makeTransition(); // returns the next state
   virtual int compare(State* state); // used to check whether this state
                                      // is equal to the goal state
   virtual void unMarkTransitions(){}; // used for ids, not implemented
   void applyOperators();                  // creates all the next states
                                       // that can reached from this state
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

