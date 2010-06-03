/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Heuristic.C                                         */
/*    ASGN: Final                                               */
/*    DATE: Mon Jun 27 18:39:30 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Heuristic.H"
#include <Plan.H>
Heuristic::Heuristic()
{
;
}

Heuristic::~Heuristic()
{
   ;
}

int Heuristic::equal(State* element, State* to)
{
   return 0;
}


/****************************************************************/
/*                                                              */
/* Function Name: compare                                       */
/* Parameters:                                                  */
/* element : teh element in the container                       */
/* to : the element being added                                 */
/* Returns:                                                     */
/*  1) for success                                              */
/*  0) for failure                                              */
/* Effects:                                                     */
/*  Determines whether a plan occurs before or after the current*/
/* element in the container.This is identical in purpose to     */
/* the comparep function in the LISP text.                      */
/****************************************************************/


int Heuristic::compare(State* element, State* to)
{
   if(((Plan*) element)->requirements()->size() < ((Plan*) to)->requirements()->size())
      return 1;
   return 0;
}



void Heuristic::display(State* state)
{
   cout << " in HEURISTICS " << endl;
  PlanComp displ;
  displ.display((Plan *) state);
   cout << endl;
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

