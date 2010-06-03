/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: testBFS.C                                           */
/*    ASGN: Final                                               */
/*    DATE: Sun Jul 10 18:45:51 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <PlanningState.H>
#include <Operator.H>
#include <SLBag.H>
#include <XDString.H>
#include <Searches.H>
#include <Operator.H>
#include <Heuristic.H>
#include <StateSearches.H>

int main(int ac, char ** av)
{
   SLBag<XDString, StringComp>* additions,*deletions, *preconditions;
   additions = new SLBag<XDString, StringComp>;
   deletions = new SLBag<XDString, StringComp>;
   preconditions = new SLBag<XDString, StringComp>;
   
   preconditions->addMember(new XDString("not assembled 1"));
   additions->addMember(new XDString("assembled 1"));
   deletions->addMember(new XDString("not assembled 1"));
   Operator* op1 = new Operator( additions, preconditions,deletions);
   delete additions;
   delete preconditions;
   delete deletions;
  
   additions = new SLBag<XDString, StringComp>;
   deletions = new SLBag<XDString, StringComp>;
   preconditions = new SLBag<XDString, StringComp>;
   
   preconditions->addMember(new XDString("not assembled 1"));
   additions->addMember(new XDString("assembled 2"));
   deletions->addMember(new XDString("not assembled 2"));
   Operator* op2 = new Operator( additions,preconditions, deletions);
   delete additions;
   delete preconditions;
   delete deletions;
   
   additions = new SLBag<XDString, StringComp>;
   deletions = new SLBag<XDString, StringComp>;
   preconditions = new SLBag<XDString, StringComp>;
   
   preconditions->addMember(new XDString("assembled 1"));
   additions->addMember(new XDString("assembled 1"));
   deletions->addMember(new XDString("not assembled 2"));
   deletions->addMember(new XDString("assembled 1"));
   Operator* op3 = new Operator( additions, preconditions,deletions);
   delete additions;
   delete preconditions;
   delete deletions;

   additions = new SLBag<XDString, StringComp>;
   deletions = new SLBag<XDString, StringComp>;
   preconditions = new SLBag<XDString, StringComp>;
   preconditions->addMember(new XDString("assembled 1"));
   preconditions->addMember(new XDString("assembled 2"));
   additions->addMember(new XDString("assembled 3"));
   deletions->addMember(new XDString("not assembled 3"));
   Operator* op4 = new Operator( additions, preconditions,deletions);
   delete additions;
   delete preconditions;
   delete deletions;
   Queue<Operator, OperatorComp>* ops = new Queue<Operator, OperatorComp>;
   ops->insert(op1);
   ops->insert(op2);
   ops->insert(op3);
   ops->insert(op4);

   SLBag<XDString,StringComp>* symbols = new SLBag<XDString,StringComp>;
   symbols->addMember(new XDString("not assembled 1"));
   symbols->addMember(new XDString("not assembled 2"));
   symbols->addMember(new XDString("not assembled 3"));
   PlanningState* initial = new PlanningState(ops, symbols);
   symbols = new SLBag<XDString,StringComp>;
   symbols->addMember(new XDString("assembled 1"));
   symbols->addMember(new XDString("assembled 2"));
   symbols->addMember(new XDString("assembled 3"));
   PlanningState* goal = new PlanningState(ops, symbols);
   PlanningState* result;
   PlanningCompare displayer;

   result =  sss(initial,goal);   
   cout << " The state we found using mea" << endl;
   displayer.display(result);
   cout << endl;

   return 0;
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

