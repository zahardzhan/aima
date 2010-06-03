/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Effects.H                                           */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 14 00:25:58 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef EFFECTS_HEADER
#define EFFECTS_HEADER

#include "Compare.H"
#include <Time.H>
#include <XDString.H>
#include <SortedList.H>

const int NEGATIVE = 1;
const int POSITIVE = -1;

/****************************************************************/
/* CLASS NAME : Effect                                          */
/*   Base class for events and facts. An effect is something    */
/* that exists in a temporal data base. An effect has a symbol  */
/* a start time and a type.                                     */
/*                                                              */
/****************************************************************/


class Effect 
{
   Time start_time_;
   XDString symbol_;
  
public:
   friend class EffectCompare;
   enum Type {EVENT, FACT};
   Effect(Time start_time, const XDString& symbol, Type kind);
   ~Effect()
      {
      }
   Effect(Effect& effect);
   Effect& operator=(Effect& effect);
   Type kind()                  // returns the kind of effect  
      { 
         return kind_;
      }
   XDString& getType()          // returns the symbol  
      {
         return symbol_;
      }
   Time starttime()             // return the starttime
      {
         return start_time_;
      }
   void setTime(Time time)      // sets the start time
      { 
         start_time_ = time;
      }
private:
   Type kind_;
};


/****************************************************************/
/* CLASS NAME : Event                                           */
/*   An event is an effect that is instantaneous in nature.     */
/* It is derived from Effect inheriting all of Effects         */
/* accessors                                                    */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


class Event : public Effect{
public:
   friend class EventCompare;
   Event(Time start_time, XDString symbol);
   ~Event();
   Event(Event& event);
   Event& operator=(Event& event);

};


/****************************************************************/
/* CLASS NAME : Fact                                            */
/*   A fact derives from effect, inheriting its accessors, and  */
/* adds to an Effect the concept of an end time. The            */
/* default for end time is -1 which is infinity.                */
/* A fact can be negated, it can say wether another fact        */
/* at a given is time is true, and if a given fact is           */
/* contradicting the object                                     */
/****************************************************************/


class Fact : public Effect
{

   Time end_time_;
   int negation_;               // wether the fact is negated or not
public:
   friend class FactCompare;
   Fact();                      // Default constructor
   // copy constructor
   Fact(Fact& fact);
   // creates a fact with the given parameters
   Fact(Time start_time,const XDString& symbol,int negate, Time end_time = -1);
   // over loaded assignment operator
   Fact& operator=(Fact& fact);
   // changes the negation value
   void negate();
   // this function operates in the same fashion as is-true in the
   // lisp book. Since we already know that they are the same
   // type we only have to determine if fact begins before or coincident
   // with the time and ends prior to the time
   int isTrue(Fact* fact, Time time);
   // This function differs from the lisp implementation of the same name.
   // It checks to see if the fact contradicts the object, and if so sets      
   // the objects end_time_ to be before the facts start_time_
   // this to begin before fact
   void contradicts(Fact* fact);
   Time endTime()
      {
         return end_time_;
      } 
   void setEndTime(Time end_time) 
      {
         end_time_ = end_time;
      }
};


/****************************************************************/
/* CLASS NAME : Crule                                           */
/*    A Crule is a causal rule. A causal rule has a trigger,    */
/* which is an event. It has a series of antecedents which are  */
/* facts and consequences which are either facts or events.     */
/* They are stored internally as a list of Effects.The trigger  */
/* the antecedents, and the consequences can be accessed.       */
/*                                                              */
/****************************************************************/

class Crule 
{
   SortedList<Fact,FactCompare>* antecedents_;
   SortedList<Effect, EffectCompare>* consequence_;
   Event* trigger_;
public:
   friend class CruleComp;
   Crule(XDString trigger);
   ~Crule();
   void addAntecedent(XDString  symbol, int negation = NEGATIVE);
   void addConsequent(Effect* effect);
   SortedList<Fact,FactCompare>* antecedents() 
      {
         return antecedents_;
      }
   SortedList<Effect,EffectCompare>* consequences() 
      {
         return consequence_;
      }
   Event* trigger()
      { 
         return trigger_;
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

