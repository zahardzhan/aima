/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: CausalRuleDatabase.C                                */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun 16 02:21:52 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "CausalRuleDatabase.H"
#include <List.H>
#include <SIterator.H>
#define CRULE_INTERNAL ((CruleAbsNode*) (CruleInternalNode*) getNext())
#define CRULE_TAIL  ((CruleAbsNode*) (CruleTailNode*) getNext())



CruleInternalNode::CruleInternalNode(ListAbsNode<Crule,CruleComp>*next,
                                     Crule* crule)
:ListAbsInternalNode<Crule,CruleComp>(next,crule), CruleAbsNode()
{
;
}

ListAbsNode<Crule,CruleComp>* CruleInternalNode::insert(Crule* crule, CruleComp* comparator)
{
   if (comparator->compare(getElement(),crule)) 
      { 
         setNext(getNext()->insert(crule, comparator));
         return this;
      } 
   else 
      {
         CruleInternalNode* node = new CruleInternalNode(getNext(), getElement());
         setNext(node);
         setElement(crule);
         return this;
      }
}

/****************************************************************/
/*                                                              */
/* Function Name: update                                        */
/* Parameters:                                                  */
/* Event* the event currently being used to update the event    */
/* and fact database                                            */
/* events : the envent database                                 */
/* FactDatabase : the facts databse                             */
/* Time : the current time used for updating                    */
/* Returns: <none>                                              */
/* Effects: checks if the current event is the trigger of       */
/* the current rule, if not then  pass the message to the       */
/* next node. After that it checks to see if all the antecedents*/
/* hold by queerying the facts database for each event.         */
/* If all the facts hold, it then adds the consequences to      */
/* either the fact database or event database depending on the  */
/* type of the effect. Before they are added their time is      */
/* adjusted by the current time.                                */
/*                                                              */
/****************************************************************/


void CruleInternalNode::update(Event* event, 
                               SortedQueue<Event,EventCompare>* events,
                               FactDatabase* facts,
                               Time current_time)
{
   // Is the CRULE the trigger of the event
   if(event->getType() == getElement()->trigger()->getType()) 
      {
         // yes
         SortIterator<Fact,FactCompare>* antecedents;
         antecedents = new SortIterator<Fact,FactCompare>(getElement()->antecedents());
         // loop through the list to check that all the antecedents of the
         // event hold, by asking the facts database, setting valid to 0,
         // if they do not hold
         int valid = 1;
         for(antecedents->start(); antecedents->end(); antecedents->next())
            {
               // check here wether the current antecedent of the event
               // holds at the current_time
               if(!(facts->holds(antecedents->current()->getElement(),
                                 current_time)))
                  {
                     valid = 0;
                  }
            }
         delete antecedents; // delete the iterator
         if(valid)           // are the antecedents valid?
            {      // yes
               SortIterator<Effect,EffectCompare>* consequences;
               consequences = new SortIterator<Effect,EffectCompare>(getElement()->consequences()); 
               // loop through the consequences, and add them to the appropriate 
               // data base given their type
               for(consequences->start(); consequences->end(); consequences->next())
                  {
                     if(consequences->current()->getElement()->kind() == Effect::FACT) 
                        {
                           // the current consequent is a fact
                           // so create a fact and put that fact with the current time
                           // into the facts database
                           Fact* fact_temp = new Fact(*((Fact*) consequences->current()->getElement()));
                           fact_temp->setTime(fact_temp->starttime() + current_time);
                           facts->addFact(fact_temp);
                        }
                     else 
                        {
                           // the current effect is an event
                           // so add it to the events database
                           // after changing the time appropriately
                           Event* event_temp = new Event(*((Event*) consequences->current()->getElement()));
                           event_temp->setTime(event_temp->starttime() + current_time);
                           events->insert(event_temp);
                        }
                  }
               delete consequences;
            }
      }
   // depending on the next node type, 
   // call the next function
   if(getNext()->getNext() == 0) 
      {
         CRULE_TAIL->update(event,
                            events,
                            facts,
                            current_time);
      }
   else 
      {
         CRULE_INTERNAL->update(event,
                                events,
                                facts,
                                current_time);
      }
}




CruleTailNode::CruleTailNode() 
: ListAbsTailNode<Crule,CruleComp>(), CruleAbsNode()
{
}





ListAbsNode<Crule,CruleComp>*
CruleTailNode::insert(Crule* crule,
                      CruleComp* comparator)
{
   return new CruleInternalNode(this, crule);
}



void
CruleTailNode::update(Event* event,
                      SortedQueue<Event,EventCompare>* events,
                      FactDatabase* facts, 
                      Time current_time)
{
   return;
}


CruleHeadNode::CruleHeadNode(ListAbsNode<Crule,CruleComp>* next)
:ListAbsHeadNode<Crule,CruleComp>(next)
{
}



ListAbsNode<Crule,CruleComp>*
CruleHeadNode::insert(Crule* element,
                      CruleComp* comparator)
{
   setNext(getNext()->insert(element,comparator));
   return this;
}

void CruleHeadNode::update(Event* event,
                           SortedQueue<Event,EventCompare>* events,
                           FactDatabase* facts,
                           Time current_time)
{
   if(getNext()->getNext() == 0)
      {
         CRULE_TAIL->update(event,
                            events,
                            facts,
                            current_time);
         return;
      }
   CRULE_INTERNAL->update(event,
                          events,
                          facts, 
                          current_time);
}



CausalRuleDatabase::CausalRuleDatabase(CruleComp* comparator) 
{
   comparator_ = comparator;
   CruleTailNode* tail = new CruleTailNode;
   head_ = new CruleHeadNode(tail);
}



void CausalRuleDatabase::insert(Crule* element)
{
   head_->insert(element,comparator_);
}


void CausalRuleDatabase::update(Event* event,
                                SortedQueue<Event,EventCompare>* events,
                                FactDatabase* facts,
                                Time current_time)
{
   head_->update(event,events,facts,current_time);
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

