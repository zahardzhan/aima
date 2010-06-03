/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Constrain.C                                         */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 19:17:32 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <Constrain.H>
#include <SLBag.H>
#include <SLBagIterator.H>
#include <Step.H>



/****************************************************************/
/*                                                              */
/* Function Name: Constrain                                     */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

Constrain::Constrain(Step* begin, Step* end)
{
   begin_ = new Step(*begin);
   end_ = new Step(*end);
}

Constrain::~Constrain()
{
   delete begin_;
   delete end_;
}

int ConstComp::equal(Constrain* constraint, Constrain* to)
{
   StepComp comparator;
   if((comparator.equal(constraint->begin(), to->begin()))
      && (comparator.equal(constraint->end(), to->end())))
      {
         return 1;
      }
   else 
      {
         return 0;
      }
}

int ConstComp::compare(Constrain* constraint, Constrain* to)
{
   return 0;
}


void ConstComp::display(Constrain* constrain)
{
   cout << " DISPLAYING A CONSTRAINT " << endl;
   StepComp d;
   cout << "displaying begin step" << endl;
   d.display(constrain->begin_);
   cout << endl;
   cout << "displaying end step " << endl;
   d.display(constrain->end_);
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

