/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Variable.C                                          */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 00:52:30 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <Variable.H>
#include <XDString.H>

 

Variable::Variable(XDString* name, Variable::Bind bind)
{  
   name_ = new XDString(*name);
   binding_ = 0;
   if (bind == Variable::BOUND)
      {
         bind_ = Variable::BOUND;
         binding_ = new XDString(*name);
      }
   else 
      {
         bind_ = bind;
         binding_ = new XDString;
      };
}
      
Variable::Variable(XDString* name, XDString* binding)
{
   name_ = new XDString(*name);
   bind_ = Variable::BOUND;
   binding_ = new XDString(*name);
}


void Variable::bind(Variable* var)
{
   bind_ = Variable::BOUND;
   delete binding_;
   binding_ = new XDString(*var->name());
};


Variable& Variable::operator=(Variable& var)
{
   delete name_;
   delete binding_;
   name_ = new XDString(*var.name());
   binding_ = new XDString(*var.binding());
   return *this;
}

                    


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




int match(Variable* var1, Variable* var2)
{
   switch(var1->bound()) 
      {
      case Variable::BOUND:
         switch(var2->bound()) 
            {
            case Variable::BOUND:
               return *var1->binding() == *var2->binding();
               
            case Variable::UNBOUND:
               var2->bind(var1);
               return 1;
            }
      case Variable::UNBOUND:
         var1->bind(var2);
         return 1;
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

