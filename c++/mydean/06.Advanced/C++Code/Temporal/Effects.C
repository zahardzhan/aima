/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Effects.C                                           */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 14 01:04:03 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Effects.H"


/****************************************************************/
/*                                                              */
/* Function Name: Effect::Effect                                */
/* Parameters:                                                  */
/*  Time start_time : when an effect starts                     */
/*  const XDString& symbol : the symbol of the effect           */
/*  Type kind : what kind of effect it is                       */
/* Returns: <none>                                              */
/* Effects: Creates an effect                                   */
/*                                                              */
/****************************************************************/


Effect::Effect(Time start_time, const XDString& symbol, Type kind) 
{
   start_time_ = start_time;
   symbol_ = symbol;
   kind_ = kind;
}

/****************************************************************/
/*                                                              */
/* Function Name: Effect::Effect                                */
/* Parameters: Effect&                                          */
/* Returns: <none>                                              */
/* Effects: copy constructor                                    */
/*                                                              */
/****************************************************************/


Effect::Effect(Effect& effect)
{
   start_time_ = effect.start_time_;
   symbol_ = effect.symbol_;
   kind_ = effect.kind_;
}

/****************************************************************/
/*                                                              */
/* Function Name: Effect::operator=                             */
/* Parameters:                                                  */
/*  Effect& : the effect to be assigned from                    */
/* Returns: the this pointer                                    */
/* Effects:                                                     */
/*  copies effect to this, by over writing the current          */
/* effect data.                                                 */
/****************************************************************/


Effect& Effect::operator=(Effect& effect) 
{
   start_time_ = effect.start_time_;
   symbol_ = effect.symbol_;
   kind_ = effect.kind_;
   return *this;
}

int EffectCompare::equal(Effect* effect, Effect* to)
{
   if(effect->start_time_ == to->start_time_) {
      return 1;
   }else
      return 0;
}


int EffectCompare::compare(Effect* effect, Effect* to)
{
   return 0;
}





Event::Event(Time start_time, XDString type) : Effect(start_time, type, Effect::EVENT)
{
}

Event::~Event(){;}



Event::Event(Event& event) : Effect((Effect&) event){;}



Event& Event::operator=(Event& event)
{
   (Effect&) *this = Effect::operator=((Effect&) event);
   return *this;
}


int EventCompare::equal(Event* event, Event* to)
{
   if(event->getType() == to->getType())
      {
         return 1;
      }
   else 
      return 0;
}




int EventCompare::compare(Event* event, Event* to)
{
   if(event->starttime() < to->starttime())
      {
         return 1;
      }
   else 
      return 0;
}


/****************************************************************/
/*                                                              */
/* Function Name: Fact::Fact                                    */
/* Parameters:                                                  */
/* Time  start_time: when the fact begins                       */
/* const XDString& type : the symbol for the fact               */
/* int negate : wether it is a negation or not                  */
/* Time end_time : when it ends                                 */
/* Returns: <none>                                              */
/* Effects: Creates a Fact.                                     */
/*                                                              */
/****************************************************************/


Fact::Fact(Time start_time, const XDString& type, int negate,
           Time end_time)
:Effect(start_time, type, Effect::FACT)
{
   end_time_ = end_time;
   negation_ = negate;
}


/****************************************************************/
/*                                                              */
/* Function Name:Fact::operator =                               */
/* Parameters:Fact& fact : the fact to assign from              */
/* Returns: Fact&,                                              */
/* Effects: assignment operator                                 */
/*                                                              */
/****************************************************************/


Fact& Fact::operator=(Fact& fact)
{
   // call the parent classes assignment operator
   (Effect&) *this = Effect::operator=((Effect&) fact);
   // modify your variables
   end_time_ = fact.end_time_;
   negation_ = fact.negation_;
   return *this;
}

/****************************************************************/
/*                                                              */
/* Function Name: Fact::Fact                                    */
/* Parameters: Fact&                                            */
/* Returns: <none>                                              */
/* Effects: copy constructor                                    */
/*                                                              */
/****************************************************************/


Fact::Fact(Fact& fact) : Effect((Effect&) fact)
{
   end_time_ = fact.end_time_;
   negation_ = fact.negation_;
   return;
}

/****************************************************************/
/*                                                              */
/* Function Name: negate                                        */
/* Parameters: <none>                                           */
/* Returns: <none>                                              */
/* Effects: negates the current fact                            */
/*                                                              */
/****************************************************************/


void Fact::negate()
{
   negation_ *= -1;
}


/****************************************************************/
/*                                                              */
/* Function Name: Fact::isTrue                                  */
/* Parameters:                                                  */
/* Fact* fact : the fact being compared to                      */
/* Time tiem : the current time                                 */
/* Returns:                                                     */
/*  1 for true                                                  */
/*  0 for false                                                 */
/* Effects:                                                     */
/*  Determines wether a fact is true if the this->fact is       */
/* the same fact and time is between the starttime and          */
/* endTime of this->fact                                        */
/****************************************************************/


int Fact::isTrue(Fact* fact, Time time)
{
   if((fact->getType() == getType()) && 
      ((time > (starttime())) || (time == starttime())) &&
      (time < endTime()))
      {
         return 1;
      }
   else
      {
         return 0;
      }
}


/****************************************************************/
/*                                                              */
/* Function Name: Fact::contradicts                             */
/* Parameters:                                                  */
/*  Fact* fact : the fact to check for contradiction            */
/* Returns:                                                     */
/*  <none>                                                      */
/* Effects:                                                     */
/*  Checks to see if fact contradicts with the object, and if   */
/* so sets the objects end time to before fact start time       */
/****************************************************************/


void Fact::contradicts(Fact* fact)
{
   if((fact->getType() == getType()) 
      && (negation_ == fact->negation_))
      {
         if(isTrue(fact, fact->starttime())) 
            {
               setEndTime(fact->starttime());
               return;
            }
      }
}


/****************************************************************/
/*                                                              */
/* Function Name:                                               */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/


int FactCompare::compare(Fact* fact, Fact* fact2)
{
   if(fact->starttime() > fact2->starttime())
      {
         return 1;
      }
   else
         return 0;
}


/****************************************************************/
/*                                                              */
/* Function Name:                                               */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/


int FactCompare::equal(Fact* fact, Fact* fact2)
{
   if((fact->getType() == fact2->getType()) && 
      (fact->negation_ == fact2->negation_) && 
      (fact->starttime() == fact2->starttime()) && 
      (fact->endTime() == fact2->endTime()))
      {
         return 1;
      }
   else
      return 0;
}

/****************************************************************/
/*                                                              */
/* Function Name: FactCompare::display                          */
/* Parameters: Fact* fact                                       */
/* Returns:                                                     */
/* Effects: Display fact                                        */
/*                                                              */
/****************************************************************/

void FactCompare::display(Fact* fact)
{
   cout << "Fact " << fact->getType() << "start time "
      << fact->starttime() << "end time "
         << fact->endTime() << endl;
         
   if(fact->negation_ == NEGATIVE) 
      { 
         cout << "negative" << endl;
      }
   else 
      {
         cout << "positive" << endl;
      }
}


/****************************************************************/
/*                                                              */
/* Function Name: Crule::Crule                                  */
/* Parameters:                                                  */
/*  XDString trigger : the trigger for the causal rule          */
/* Returns: <none>                                              */
/* Effects: Creates a causal rule and sets up the internal      */
/*  data structures                                             */
/*                                                              */
/****************************************************************/



Crule::Crule(XDString trigger)
{
   trigger_ = new Event(0,trigger);
   antecedents_ = new SortedList<Fact,FactCompare>(new FactCompare);
   consequence_ = new SortedList<Effect,EffectCompare>(new EffectCompare);
}


/****************************************************************/
/*                                                              */
/* Function Name: Crule::~Crule                                 */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/


Crule::~Crule()
{
   delete antecedents_;
   delete consequence_;
}

/****************************************************************/
/*                                                              */
/* Function Name: Crule::addAntecedent                          */
/* Parameters: XDString type : the symbol of the antecedent     */
/* int negate : wether it is negated or not                     */
/* Returns: <none>                                              */
/* Effects: Adds the antecedent to the crule. The new fact      */
/* is assumed to start at time 0                                */
/*                                                              */
/****************************************************************/

void Crule::addAntecedent(XDString type, int negate)
{
   antecedents_->insert(new Fact(0,type,negate));
}


/****************************************************************/
/*                                                              */
/* Function Name: Crule::addConsequent                          */
/* Parameters:Effect* effect : the consequent being added       */
/* Returns: <none>                                              */
/* Effects: Adds a consequent to the consequences of the crule
/*                                                              */
/****************************************************************/


void Crule::addConsequent(Effect* effect)
{
   consequence_->insert(effect);
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

