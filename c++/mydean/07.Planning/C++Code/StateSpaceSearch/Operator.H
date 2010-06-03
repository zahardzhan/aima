/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Operator.H                                          */
/*    ASGN: Final                                               */
/*    DATE: Sun Jun 19 22:45:59 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef OPERATOR_HEADER
#define OPERATOR_HEADER

#include "Compare.H"
#include <SLBag.H>
#include <XDString.H>


/****************************************************************/
/* CLASS NAME :  Operator                                       */
/*   This class is the implementation of the abstract operator  */
/* type described in the text. It merely serves as a structure. */
/* It is also used in earlier programs in this chapter.         */
/*                                                              */
/****************************************************************/

class Operator 
{
    SLBag<XDString, StringComp>* additions_, *preconditions_, *deletions_;
public:
   Operator(SLBag<XDString, StringComp>* additions, 
            SLBag<XDString, StringComp>*preconditions,
            SLBag<XDString, StringComp>* deletions);
   friend class OperatorComp;
   SLBag<XDString, StringComp>* additions();
   SLBag<XDString, StringComp>* preconditions();
   SLBag<XDString, StringComp>* deletions();
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

