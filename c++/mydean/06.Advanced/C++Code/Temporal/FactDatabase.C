/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: FactDatabase.C                                      */
/*    ASGN: Final                                               */
/*    DATE: Mon Jul  4 03:53:22 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "FactDatabase.H"
#include <Effects.H>



/****************************************************************/
/*                                                              */
/* Function Name: FactInternalNode::insert                      */
/* Parameters:                                                  */
/* ListAbsNode<Fact,FactCompare>* next                          */
/* Fact* element                                                */
/* Returns:                                                     */
/* ListAbsNode<Fact,FactCompare>*                               */
/* Effects:                                                     */
/*   Inserts a node into the list                               */
/****************************************************************/


ListAbsNode<Fact,FactCompare>* 
FactInternalNode::insert(Fact* element,
                         FactCompare* compare)
{
   if(compare->compare(getElement(), element))
      {
         setNext(getNext()->insert(element, compare));
         return this;
      }
   else
      {
         FactInternalNode* node = new FactInternalNode(getNext(), 
                                                       getElement());
         setNext(node);
         setElement(element);
         return this;
      }
}


/****************************************************************/
/*                                                              */
/* Function Name: FactInternalNode::holds                       */
/* Parameters:                                                  */
/* Fact* : the we want to check wether holds                    */
/* Time : at what time we want to know wether the fact holds    */
/* Returns:                                                     */
/*  1 - if true                                                 */
/*  0 - if false                                                */
/* Effects:                                                     */
/*  asks the fact if the current element at time isTrue, which  */
/* means that the fact holds, in which case 1 is returned,      */
/* otherwise the message is passed to the next node             */
/****************************************************************/



int FactInternalNode::holds(Fact* fact, Time time)
{
   if(fact->isTrue(getElement(),time)) //  is the message true at this time
      {
         return 1;
      }
   else                         // pass the message on in the list
      {
         if(getNext()->getNext() == 0)
            return (FACT_TAIL_NODE getNext())->holds(fact, time);
         return (FACT_INTERNAL_NODE  getNext())->holds(fact,time);
      }
}


/****************************************************************/
/*                                                              */
/* Function Name: FactInternalNode::contradicts                 */
/* Parameters: Fact* fact                                       */
/* Returns: <none>                                              */
/* Effects: asks each element to check if it is contradicted    */
/* by fact and to make the necessary adjustments, and then      */
/* pass the message on.                                         */
/*                                                              */
/****************************************************************/


void FactInternalNode::contradicts(Fact* fact)
{
   getElement()->contradicts(fact); // check wether fact contradicts element
   if(getNext()->getNext() == 0)    // pass the message on
      {
         (FACT_TAIL_NODE getNext())->contradicts(fact);
         return;
      }
   (FACT_INTERNAL_NODE getNext())->contradicts(fact);
};


/****************************************************************/
/*                                                              */
/* Function Name: FactHeadNode::insert                          */
/* Parameters:                                                  */
/* Fact* fact                                                   */
/* FactCompare* compare                                         */
/* Returns: ListAbsNode<Fact,FactCompare>                       */
/* Effects:                                                     */
/*   Starts the insertion process by calling the next node      */
/****************************************************************/



ListAbsNode<Fact,FactCompare>* 
FactHeadNode::insert(Fact* fact, FactCompare* compare)
{
   setNext(getNext()->insert(fact, compare));
   return this;
}


int FactHeadNode::holds(Fact* fact, Time time)
{
   if(getNext()->getNext() == 0) 
      {
         return (FACT_TAIL_NODE getNext())->holds(fact,time);
      }
   return (FACT_INTERNAL_NODE getNext())->holds(fact,time);
}




void FactHeadNode::contradicts(Fact* fact)
{
   if(getNext()->getNext() == 0)
      (FACT_TAIL_NODE getNext())->contradicts(fact);
   else
      (FACT_INTERNAL_NODE getNext())->contradicts(fact);
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

