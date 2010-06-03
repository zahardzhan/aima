/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Constrain.H                                         */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 00:36:52 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef CONSTRAIN_HEADER
#define CONSTRAIN_HEADER

#include <Compare.H>
#include <SLBag.H>

/****************************************************************/
/* CLASS NAME : Constrain                                       */
/*    This represents a constraint. A constraint has a beginning*/
/* step and an end step. It has no behaviours associated to it. */
/*                                                              */
/****************************************************************/

class Constrain 
{
   Step* begin_;                // the beginning step
   Step* end_;                  // the end step
public:
   friend class ConstComp;
   Constrain(Step* begin, Step* end);
   ~Constrain();
   Step* begin() 
      {
         return begin_;
      }
   Step* end()
      {
         return end_;
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

