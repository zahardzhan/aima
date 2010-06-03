#ifndef COMPARE_H
#define COMPARE_H

#include <iostream.h>

/****************************************************************/
/* CLASS NAME : EffectCompare                                   */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/

class Effect;

class EffectCompare {
public:
   EffectCompare()
      {
      }
   ~EffectCompare()
      {
      }
   int equal(Effect* effect, Effect* to);
   int compare(Effect* effect, Effect* to);
   void display(Effect* effect){;}
};

/****************************************************************/
/* CLASS NAME : EventCompare                                    */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/

class Event;

class EventCompare { 
public:
   EventCompare(){;}
   ~EventCompare(){;}
   int equal(Event* event, Event* to);
   int compare(Event* event, Event* to);
   void display(Event* event){;}
};
   
/****************************************************************/
/* CLASS NAME : FactCompare                                     */
/*   This is used by the container classes to sort, and search  */
/* and display Facts.                                           */
/*                                                              */
/****************************************************************/

class Fact;

class FactCompare 
{ 
public:
   FactCompare(){;}
   int compare(Fact* fact, Fact* fact2);
   int equal(Fact* fact, Fact* fact2);
   void display(Fact* fact);
};

/****************************************************************/
/* CLASS NAME : CruleComp                                       */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/

class Crule;

class CruleComp {
public:
   CruleComp()
      {
      }
   ~CruleComp()
      {
      }
   int equal(Crule* effect, Crule* to) 
      {
         return 0;
      }
   int compare(Crule* effect, Crule* to) 
      { 
         return 0;
      }
   void display(Crule* crule)
      {
      }
};

#endif
