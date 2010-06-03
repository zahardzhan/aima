/****************************************************************/
/*    NAME: Smith Surasmith                                     */
/*    ACCT: sls                                                 */
/*   EMAIL: sls@cs.brown.edu                                    */
/*    FILE: ids.C                                               */
/*    ASGN: C++ code                                            */
/*    DATE: Wed Jun 22 13:45:30 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <State.H>
#include <Searches.H>
	

/****************************************************************/
/*                                                              */
/* Function Name: dfs-fd                                        */
/* Parameters:    (State*) current state                        */
/*                (State*) goal state                           */
/*                (int)    current depth                        */
/*                (int)    fixed depth                          */
/* Returns:       (State*) 0 if not found                       */
/*                (State*) goal if found                        */
/* Effects:       this is an implementation of a                */
/*                DEPTH FIRST SEARCH in which                   */
/*                the depth is restricted to the depth          */
/*                given by the fixed depth                      */
/*                                                              */
/****************************************************************/

State*
dfs_fd (State* current,State* goal,
	int current_depth,int fixed_depth)
{
  if ((current == 0) || (current_depth > fixed_depth))
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
	  result = dfs_fd(transition,goal,current_depth + 1,fixed_depth);
	}
      while((transition != 0) 
	    && (goal->compare(result) != State::EQUAL));
      
      current->unMarkTransitions();
      current->unMark();
      return result;
    }
}



/****************************************************************/
/*                                                              */
/* Function Name: ids                                           */
/* Parameters:    (State*) current start state                  */
/*                (State*) goal state                           */
/* Returns:       (State*) goal if successful                   */
/*                (State*) 0 if not successful                  */
/* Effects:       implements an INTERATIVE DEEPENING SEARCH     */
/*                using depth first search with fixed depth     */
/*                                                              */
/****************************************************************/

State*
ids(State* current,State* goal)
{
  int fixed_depth;
  State* result = 0;

  if (goal == 0)
    return 0;

  for(fixed_depth = 1;
      result != 0;
      fixed_depth++)
    {
      result = dfs_fd(current,goal,0,fixed_depth);
    }
  return result;
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
