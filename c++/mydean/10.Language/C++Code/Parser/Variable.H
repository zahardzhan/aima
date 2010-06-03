/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Variable.H                                          */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 00:52:53 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef VARIABLE_HEADER
#define VARIABLE_HEADER

class XDString;

/****************************************************************/
/* CLASS NAME :  Variable                                       */
/*   A variable in the context of this program is really        */
/* nothing more than a binding. However, to simplify the        */
/* coding a variable can be a constant if the binding and       */
/* name are the same.Otherwise name is the variable name, and   */
/* binding is what the variable is bound to.                    */
/*   A variable can bind to another variable, however, it can   */
/* not check for matching.                                      */
/*                                                              */
/****************************************************************/


class Variable
{
   XDString* name_;             // variable name
   XDString* binding_;          // binding type
public:
   enum Bind {BOUND, UNBOUND};
   Variable(XDString* name, Bind bind = UNBOUND);
   Variable(XDString* name, XDString* binding);
   Variable& operator=(Variable& var);
   // sets binding to whatever var->name_ is 
   void bind(Variable *var);
   Bind bound()
      { 
         return bind_;
      }
   XDString* name()    
      { 
         return name_; 
      }
   XDString* binding()
      { 
         return binding_;
      }
private:
   Bind bind_;   
};

/****************************************************************/
/*                                                              */
/* Function Name: match                                         */
/* Parameters:                                                  */
/*  Variabl* var1, *var2 : the two variables being              */
/*    considered for matching                                   */
/* Returns:                                                     */
/*  1 for success, as well making var1 and var2 bound           */
/*  0 the two variables did not match                           */
/* Effects:                                                     */
/*  Given two variables determines wether they match. Two       */
/* variables match if they have the same binding or one         */
/* can bind with the other. A variable can bind with another    */
/* if it is unbound. The reason for making this a function      */
/* is that what happens depends on the type of the object.      */
/****************************************************************/





int match(Variable* var1, Variable* var2);


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

