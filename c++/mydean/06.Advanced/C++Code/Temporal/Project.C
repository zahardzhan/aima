/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Project.H                                           */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun 16 04:08:32 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#include <SortedQueue.H>
#include <Effects.H>
#include <FactDatabase.H>
#include <CausalRuleDatabase.H>
#include <TemporalUpdate.H>
int main(int argc, char** argv)
{
   EventCompare* comparator = new EventCompare;
   SortedQueue<Event, EventCompare>* sorted_Queue = new SortedQueue<Event,EventCompare>(comparator);
   Event* event = new Event(10, "E");
   sorted_Queue->insert(event);
   FactCompare* fact_comp = new FactCompare;
   FactDatabase* facts = new FactDatabase(fact_comp);
   Fact* fact = new Fact(0,"P",POSITIVE);
   facts->addFact(fact);
   fact = new Fact(0, "Q", POSITIVE);
   facts->addFact(fact);
   CruleComp* crule_comp = new CruleComp;
   CausalRuleDatabase* cdatabase = new CausalRuleDatabase(crule_comp);
   Crule* crule = new Crule("F");
   crule->addAntecedent("R");
   crule->addAntecedent("Q");
   crule->addConsequent(new Fact(0,"P",NEGATIVE));
   cdatabase->insert(crule);
   crule = new Crule("E");
   crule->addAntecedent("P");
   crule->addConsequent(new Fact(0,"R",POSITIVE));
   cdatabase->insert(crule);
   crule = new Crule("E");
   crule->addAntecedent("Q");
   crule->addConsequent(new Event(5,"F"));
   cdatabase->insert(crule);
   cout << " program is starting " << endl;
   temporalUpdate(sorted_Queue,cdatabase, facts);
   facts->display();
   
   if(facts->holds(new Fact(0,"P",1),5)) 
      {
         cout << "It holds" << endl;
      }
   else 
      {
         cout << "It does not hold " << endl;
      }
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

