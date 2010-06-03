// State.H basic derived clas : better fix this one smith.


#ifndef STATE__HEADER 
#define STATE__HEADER


/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


class State 
{

 public:
   enum Marked { MARKED, NOT_MARKED };
   State();
   State(int);
   virtual ~State(){;}
   Marked isMarked();
   void mark();
   void unMark();
   virtual void unMarkTransitions() = 0;
   virtual void  setLabel(int);
   virtual int getLabel();
   virtual State* makeTransition() = 0;
   enum Comparison { NOT_EQUAL = -1, EQUAL = 0, LESS_THAN, GREATER_THAN };
   virtual int compare(State* state) = 0;
   friend class Comparator;
private:
   Marked marked_; // marked variable
   int label_;
};


class Comparator 
{
public:
   Comparator(){;}
   virtual ~Comparator(){;}
   virtual int compare(State* state, State* to){return 1;}
   virtual int equal(State* state, State* to){return 1;}
   virtual void display(State* state){return;}
};
   
#endif 
