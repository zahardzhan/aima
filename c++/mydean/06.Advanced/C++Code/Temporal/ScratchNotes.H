/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: ScratchNotes.H                                      */
/*    ASGN: Final                                               */
/*    DATE: Sat Jun 11 19:47:41 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef SCRATCHNOTES_HEADER
#define SCRATCHNOTES_HEADER


 notes:

 1) initialize the database with all the TempNode
   -- create a heap with all the nodes .
 2) create an empty heap
 3) create a list of causal rules
 4) get first token -- 
 
   b) repeat a) until all causal rules are constrained.
   or there are no more causal rules to constrain
(Smart list?)
 5)
 

#endif


Well according to dean the algorithm works something like this:

class CausalRules :
   list of antecedents  -> fact not trigger.
   string with symbol -> trigger which is an event not a fact
   list of new symbols -> facts, events
   delay;



class Effect 


class Fact and class Event derive from Effect.

project(intitial facts,initial events, rules) 
add facts, and events to the database
 but facts and events are separate databases
Then pop first event from the queue.
  if ( event = nil, end) else 
  get all the rules whose trigger and event are the same
  then check each rule to determine that its antecedents are true.
   which means looking at the facts of the database.
   

   Lets start again:

The program takes as inputs initial events, facts, and a list of rules.

The facts and events databases are initialized.
--list of facts, list of events
Pop an event from the database of events,
find all rules with that event as a trigger,
check to make sure that the facts of the rule are valid, and if so then add the facts, and events add the appropriate delay to them.

Check that the facts are not contradictory.

Repeat until there are no events.




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

