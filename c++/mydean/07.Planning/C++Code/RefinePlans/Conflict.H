/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Conflict.H                                          */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:16:06 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef CONFLICT_HEADER
#define CONFLICT_HEADER

#include <Compare.H>
#include <SLBag.H>

/****************************************************************/
/* CLASS NAME :  Conflict                                       */
/*   A conflict involves a link and a step. The step called     */
/* the clobberer has the condition of the link in the list of   */
/* deletions for its associate operators. A conflict arises     */
/* when a step is added to a plan and that step might be        */
/* carried out after the producer of a link and before the      */
/* consumer, preventing the link from satisfying the requirement*/
/* that the link was introduced to satify.                      */
/*  A conflict can resolve itself generating new plans as       */
/* a result. It resolves itself much in the same manner as      */
/* described in the text.                                       */
/*                                                              */
/****************************************************************/

class Conflict 
{
   Link* link_;
   Step* clobberer_;
 public:
   friend class ConflictComp;
   Conflict(Link* link, Step* step);
   ~Conflict();
   // Conflicts resolve them selves by constraining the clobberer to occur
   // before the producer of the associated link or after the consumer of the
   // link. Resolves returns a bag of new plans to be modified.
   SLBag<Plan, PlanComp>* resolve(Plan* plan);    
   Link* link() 
      {
         return link_;
      }
   Step* step()
      {
         return clobberer_;
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

