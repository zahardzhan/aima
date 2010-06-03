/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Requirement.H                                       */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:52:29 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef REQUIREMENT_HEADER
#define REQUIREMENT_HEADER

#include <Compare.H>
#include <SLBag.H>
#include <SLBagIterator.H>

/****************************************************************/
/* CLASS NAME : Requirement                                     */
/*   A requirement corresponds to a step and a condition that   */
/* must be true immediately prior to that step. The condition   */
/* of the requirement corresponds to the precondition of the    */
/* operator indicated in the step.                              */
/*   A Requirement object can create new plans when a new step  */
/* is added, resolve existing requirement, determine given      */
/* the requirement what steps are applicable and generate       */
/* new requirements from an operators preconditions.            */
/*                                                              */
/****************************************************************/

class XDString;

class Requirement 
{
   XDString* condition_;
   Step* step_;
public:
   friend class ReqComp;
   Requirement(Step* step, XDString* condition);
   ~Requirement();

   // Identical in functionality to the Lisp function     
   // resolve-req-new-step. This function eliminates a          
   // requirement by adding a new step, and create a new plan      
   // for each applicable operator                                 
   SLBag<Plan, PlanComp>* new_step(SLBag<Operator, OperatorComp>* operators, Plan* plan);

   //  works exactly like the resolve-req-existing-step    
   // It eliminates a requirement using an existing step, creating 
   // a new plan for each existing step that can be linked to      
   // satisfy the requirement.                                     
SLBag<Plan, PlanComp>* existing_step(Requirement*,
                                     Plan* plan);
   //  Generates a requirement for every precondition      
   // of the operator with the step being the condition of the     
   // requirement                                                  
   SLBag<Requirement, ReqComp>* generateRequirements(Operator* oprator, Step* step);

   //  Identical to the applicablep function in the Lisp   
   // text. An operator is applicable just in case the condition   
   // of the requirement is added by the operator. If applicable,  
   // create a new plan from the old one by adding a new           
   // requirement, constraining the new step to precede the        
   // step of the resolved requirement, eliminating this           
   // requirement, adding a link resolving the requirement with    
   // the new step as producer, adding a new set of requirements   
   // corresponding to the preconditions of the operator, and      
   // updating the set of conflicts.                               
   // The implementation follows that of the book.                 
   Plan* applicable(Operator* oprator, Plan* plan);
   Step* step()
      {
         return step_;
      }
   XDString* condition()
      {
         return condition_;
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

