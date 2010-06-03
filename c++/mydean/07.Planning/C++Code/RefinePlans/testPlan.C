/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: testPlan.C                                          */
/*    ASGN: Final                                               */
/*    DATE: Fri Jun 24 20:16:44 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */





#include <Operator.H>
#include <Step.H>
#include <Requirement.H>
#include <Plan.H>
#include <Searches.H>
#include <XDString.H>
#include <Constrain.H>
#include <Heuristic.H>
#include <Link.H>
#include <Conflict.H>

int main(int ac, char ** av)
{
   SLBag<XDString,StringComp>* additions, *deletions, *preconditions;
   additions = new SLBag<XDString,StringComp>;          
   deletions = new SLBag<XDString,StringComp>;
   preconditions = new SLBag<XDString,StringComp>;
   additions->addMember(new XDString("on c a"));
   additions->addMember(new XDString("on a table"));
   additions->addMember(new XDString("on b table"));
   additions->addMember(new XDString("clear c"));
   additions->addMember(new XDString("clear b"));              
   Operator* one = new Operator(additions,preconditions,deletions);
   delete additions;
   delete preconditions;
   delete deletions;
   additions = new SLBag<XDString,StringComp>;          
   deletions = new SLBag<XDString,StringComp>;
   preconditions = new SLBag<XDString,StringComp>;
   preconditions->addMember(new XDString("on a b"));
   preconditions->addMember(new XDString("on b c"));
   Operator* two = new Operator(additions,preconditions,deletions);  
   delete additions;
   delete preconditions;
   delete deletions;
   
   Step *start = new Step(one);
   Step *finish = new Step(two);
   
   Requirement* req = new Requirement(finish, new XDString("on a b"));
   Requirement* req2 = new Requirement(finish, new XDString("on b c"));
   SLBag<Step,StepComp>* steps = new SLBag<Step,StepComp>;
   SLBag<Constrain,ConstComp>* constraints = new SLBag<Constrain,ConstComp>;
   SLBag<Conflict,ConflictComp>* conflicts = new SLBag<Conflict,ConflictComp>;
   SLBag<Link,LinkComp>* links = new SLBag<Link,LinkComp>;
   SLBag<Requirement,ReqComp>* requirements = new SLBag<Requirement,ReqComp>;
   SLBag<Operator, OperatorComp>* operators = new SLBag<Operator, OperatorComp>;
   Constrain* constraint = new Constrain(start, finish);
   constraints->addMember(constraint);
  
   requirements->addMember(req);
   requirements->addMember(req2);
   steps->addMember(start);
   steps->addMember(finish);

   additions = new SLBag<XDString,StringComp>;          
   deletions = new SLBag<XDString,StringComp>;
   preconditions = new SLBag<XDString,StringComp>;
   preconditions->addMember(new XDString("on c a"));
   preconditions->addMember(new XDString("clear c"));
   additions->addMember(new XDString("on c table"));
   additions->addMember(new XDString("clear a"));
   deletions->addMember(new XDString("on c a"));
   Operator* op1 = new Operator(additions,preconditions,deletions);
   delete additions;
   delete preconditions;
   delete deletions;
   additions = new SLBag<XDString,StringComp>;          
   deletions = new SLBag<XDString,StringComp>;
   preconditions = new SLBag<XDString,StringComp>;
   preconditions->addMember(new XDString("on a table"));
   preconditions->addMember(new XDString("clear a"));
   preconditions->addMember(new XDString("clear b"));
   additions->addMember(new XDString("on a b"));
   deletions->addMember(new XDString("on a table"));
   deletions->addMember(new XDString("clear b"));
   Operator* op2 = new Operator(additions,preconditions,deletions);
   delete additions;
   delete preconditions;
   delete deletions;
   additions = new SLBag<XDString,StringComp>;          
   deletions = new SLBag<XDString,StringComp>;
   preconditions = new SLBag<XDString,StringComp>;
   preconditions->addMember(new XDString("on b table"));
   preconditions->addMember(new XDString("clear b"));
   preconditions->addMember(new XDString("clear c"));
   additions->addMember(new XDString("on b c"));
   deletions->addMember(new XDString("on b table"));
   deletions->addMember(new XDString("clear c"));
   Operator* op3 = new Operator(additions,preconditions,deletions);
   operators->addMember(op1);
   operators->addMember(op2);
   operators->addMember(op3);
   Plan* plan = new Plan(steps, conflicts, constraints, links, requirements, operators);   
   Heuristic* heuristic = new Heuristic;
   plan  = (Plan* )best(plan, plan, heuristic);
   plan->display();
   return 1;
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

