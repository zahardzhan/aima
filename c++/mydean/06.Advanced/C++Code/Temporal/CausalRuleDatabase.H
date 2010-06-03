/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: CausalRuleDatabase.H                                */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun 16 01:55:01 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef CAUSALRULEDATABASE_HEADER
#define CAUSALRULEDATABASE_HEADER

#include <List.H>
#include <Effects.H>
#include <SortedQueue.H>
#include <FactDatabase.H>


/****************************************************************/
/* CLASS NAME : CruleAbsNode                                    */
/*   The abstract node for the crule list node. It adds the     */
/* property of updating to the list node already defined        */
/* by the ListAbsNode                                           */
/****************************************************************/


class CruleAbsNode 
{
public:
   CruleAbsNode()
      {
      }
   ~CruleAbsNode()
      {
      }
   virtual void update(Event* event, SortedQueue<Event,EventCompare>* events,
                       FactDatabase* facts, Time current_time) = 0;
 
};


/****************************************************************/
/* CLASS NAME : CruleTailNode                                   */
/*   The tail node for the causal rules database list           */
/* When update reaches it simply returns. Otherwise the         */
/* functions implemented by ListAbsTailNode describe the        */
/* implementation of CruleTailNode insert, remove               */
/*                                                              */
/****************************************************************/


class CruleTailNode
:public ListAbsTailNode<Crule, CruleComp>, public CruleAbsNode
{
   virtual ListAbsNode<Crule, CruleComp>* remove(Crule*& element, CruleComp*){return 0;}
public:
   CruleTailNode();
   virtual ~CruleTailNode()
      {
      }
   // inserts a node just before the tail  
   virtual ListAbsNode<Crule,CruleComp>* insert(Crule* crule, CruleComp* comp);
   // simply returns
   virtual void update(Event* event, SortedQueue<Event,EventCompare>* events,
                       FactDatabase* facts, Time current_time);
};

/****************************************************************/
/* CLASS NAME : CruleInternalNode                               */
/*  Similar to the ListAbsInternalNode except for Update        */
/****************************************************************/



class CruleInternalNode 
: public ListAbsInternalNode<Crule, CruleComp>, public CruleAbsNode
{
   virtual ListAbsNode<Crule, CruleComp>* remove(Crule*& element, CruleComp*){ return 0;}
public:
   CruleInternalNode( ListAbsNode<Crule,CruleComp>* next, Crule* crule);
   virtual ~CruleInternalNode()
      {
      }
   virtual ListAbsNode<Crule, CruleComp>* insert(Crule* crule, CruleComp* comp);
   // performs the update of the FactDatabase and events database. It 
   // checks wether the event and the crule's trigger are the same, and
   // and if so checks to see if all the antecedents hold by queerying the
   // the facts database, and if they hold adds the events and facts that
   // are the consequences of unification of the event with crule to the
   // FactDatabase. The FactDatabase handles constraining the facts already
   // in there with the new facts.
   void update(Event* event, SortedQueue<Event,EventCompare>* events,
               FactDatabase* facts, Time current_time);
};

/******************************************************************/
/* CLASS NAME : CruleHeadNode                                     */
/*  The head node of the CruleDatabase. It initiates all          */
/* update messages, otherwise is identical to the ListAbsHeadNode */
/******************************************************************/


class CruleHeadNode
:public ListAbsHeadNode<Crule, CruleComp>, public CruleAbsNode
{
   virtual ListAbsNode<Crule,CruleComp>* remove(Crule*& element, CruleComp*){return 0;}
public:
   CruleHeadNode(ListAbsNode<Crule, CruleComp>* next);
   virtual ~CruleHeadNode()
      {
      }
   virtual ListAbsNode<Crule, CruleComp>* insert(Crule* element, CruleComp*);
   virtual void update(Event* event, SortedQueue<Event,EventCompare>* events,
                       FactDatabase* facts, Time current_time);
};

/****************************************************************/
/* CLASS NAME :CausalRuleDatabase                               */
/*   Acts as the container for all the crule. It is a mechanism */
/* to perform operations on all the crules at once, A message   */
/* to the crules start here and are passed down to the head node*/
/* The result is returned here.                                 */
/*    Crules can be added but can not be removed.               */
/****************************************************************/



class CausalRuleDatabase 
{
   CruleHeadNode* head_;
   CruleComp* comparator_;
public:
   CausalRuleDatabase(CruleComp* comparator);
   ~CausalRuleDatabase(){;}
   void insert(Crule* element);
   // starts the update message
   void update(Event* event, SortedQueue<Event,EventCompare>* events,
               FactDatabase* facts, Time current_time);
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

