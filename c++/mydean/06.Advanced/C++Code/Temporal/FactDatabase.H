/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: FactDatabase.H                                      */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 14 00:44:08 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef FACTDATABASE_HEADER
#define FACTDATABASE_HEADER

#include <SortedList.H>
#include <Effects.H>
#define FACT_TAIL_NODE (FactAbsNode *) (FactTailNode *)
#define FACT_INTERNAL_NODE (FactAbsNode *) (FactInternalNode *)

class FactTailNode;
class FactInternalNode;

/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/

class FactAbsNode 
{
public:
   FactAbsNode(){;}
   ~FactAbsNode(){;}
   virtual int holds(Fact* fact, Time time) = 0;
   virtual void contradicts(Fact* fact) = 0;
};

/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


class FactInternalNode 
: public SInternalNode<Fact, FactCompare>, public FactAbsNode
{
    virtual ListAbsNode<Fact,FactCompare>* remove(Fact*&, FactCompare*)
       {
          return 0;
       }

public:

   FactInternalNode(ListAbsNode<Fact,FactCompare>* next, Fact* element) 
      : SInternalNode<Fact,FactCompare>(next, element), FactAbsNode()
         {
         }
   ~FactInternalNode()
      {
      }
 virtual ListAbsNode<Fact,FactCompare>* insert(Fact* element, FactCompare* compare);
    
 virtual int holds(Fact* fact, Time time) ;
 virtual void contradicts(Fact* fact); 
};

/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


class FactTailNode 
: public STailNode<Fact, FactCompare>, public FactAbsNode
{
   virtual ListAbsNode<Fact,FactCompare>* remove(Fact*&, FactCompare*){ return 0;}
public:
 FactTailNode() : STailNode<Fact,FactCompare>(), FactAbsNode()
    {
    }
   ~FactTailNode()
      {
      }
   virtual ListAbsNode<Fact, FactCompare>* insert(Fact* fact, FactCompare* compare)
      {
         return new FactInternalNode(this,fact);
      };
   virtual int holds(Fact* fact,Time time) 
      { 
         return 0; 
      }
   virtual void contradicts(Fact* fact) 
      { 
         return; 
    }
};



/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


class FactHeadNode 
: public SHeadNode<Fact,FactCompare>, public FactAbsNode
{
   virtual ListAbsNode<Fact,FactCompare>* remove(Fact*&, FactCompare*)
      {
         return 0;
      }
public:
   
   FactHeadNode(ListAbsNode<Fact,FactCompare>* node)
      : SHeadNode<Fact,FactCompare>(node), FactAbsNode()
         {
         }
   
   ~FactHeadNode()
      {
      }
   
   virtual ListAbsNode<Fact, FactCompare>* insert(Fact* fact, 
                                                  FactCompare* compare);
   virtual int holds(Fact* fact, Time time); 
   virtual void contradicts(Fact* fact);
};


/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/
class FactDatabase 
{
   FactCompare* comparator_;
   FactHeadNode* head_;
public:
   FactDatabase(FactCompare* compare) 
      {
         comparator_ = compare;
         FactTailNode* tail = new FactTailNode;
         head_ = new FactHeadNode(tail);
      }
   ~FactDatabase() 
      {
         return;
      }
   void addFact(Fact* fact)
      {
         if(head_->holds(fact, fact->starttime())){
            fact->negate();
            head_->contradicts(fact);
            fact->negate();
            
         }
         head_->insert(fact, comparator_);
      }
   int holds(Fact* fact, Time time)
      {
         return head_->holds(fact,time);
      }
   void display() 
      {
         head_->display(comparator_);
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

