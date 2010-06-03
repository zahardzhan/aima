/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Bind.C                                              */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun  9 22:36:02 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Bind.H"
#include "LogicNode.H"

/****************************************************************/
/*                                                              */
/* Function Name: Binding                                       */
/* Parameters:                                                  */
/*  LogicNode* variable  : the variable being bound             */
/*  LogicNode* substitute : what the variable is being bound to */
/* Returns: <none>                                              */
/* Effects: creates a binding                                   */
/*                                                              */
/****************************************************************/


Binding::Binding(LogicNode* variable, LogicNode* substitute)
{
   variable_ = new LogicNode;      
   substitute_ = new LogicNode;
   *variable_ = *variable;
   if(substitute != 0)  
      *substitute_ = *substitute;
}


Binding::Binding(Binding& binding)
{
   variable_ = new LogicNode;
   substitute_ = new LogicNode;
   *variable_ = *(binding.variable_);
   *substitute_ = *(binding.substitute_);
}


Binding& Binding::operator=(Binding& binding)
{
   delete variable_;
   delete substitute_;
   variable_ = new LogicNode;
   substitute_ = new LogicNode;
   *variable_ = *(binding.variable_);
   *substitute_ = *(binding.substitute_);
   return *this;
}


/****************************************************************/
/*                                                              */
/* Function Name: BindCompare::equal                            */
/* Parameters:                                                  */
/*  Binding* binding: the element in the list structure         */
/*  Binding* to: what is being searched for                     */
/* Returns:                                                     */
/*  1 for true                                                  */
/*  0 for false                                                 */
/* Effects:                                                     */
/*    Two bindings are equal if the variable symbols are the    */
/* and what is being bound to is the same                       */
/****************************************************************/


int BindCompare::equal(Binding* binding, Binding* to)
{
   if(binding->variable_->symbol() == to->variable_->symbol())
      {
         *(to->substitute_) = *(binding->substitute_);
         return 1;
      }
   return 0;
}


int BindCompare::compare(Binding* binding, Binding* to)
{
   return 1;
}



void BindCompare::display(Binding* binding)
{
   cout << "bindings " << endl;
   cout << binding->variable_->symbol() << " " << binding->substitute_->symbol() << endl;
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

