/****************************************************************/
/*    NAME: Smith Surasmith                                     */
/*    ACCT: sls                                                 */
/*   EMAIL: sls@cs.brown.edu                                    */
/*    FILE: dfs.C                                               */
/*    ASGN: C++ code                                            */
/*    DATE: Wed Jun 22 13:46:54 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <State.H>
#include <Searches.H>



/****************************************************************/
/*                                                              */
/* Function Name: dfs                                           */
/* Parameters:    (State) start   state                         */
/*                (State) goal state                            */
/* Returns:       (if success) the pointer to goal state        */
/*                (if fail)    0                                */
/* Effects:       searches a state space given the start state  */
/*                until goal state is found                     */
/*                or state space is exhausted,                  */
/*                the search is a DEPTH FIRST SEARCH,           */
/*                and it is RECURSIVE.                          */
/*                                                              */
/****************************************************************/

State*
dfs (State* current,State* goal)
{
  if ((current == 0) || (goal == 0))
    return 0;
  else if (current->compare(goal) == State::EQUAL)
    return current;
  else
    {
      State* result = 0;
      State* transition = 0;
      
      current->mark();
      do
	{
	  transition = current->makeTransition();
	  if (transition)
	    transition->mark();
	  result = dfs(transition,goal);
	}
      while((transition != 0)
	    && (goal->compare(result) != State::EQUAL));
      return result;
    }
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

