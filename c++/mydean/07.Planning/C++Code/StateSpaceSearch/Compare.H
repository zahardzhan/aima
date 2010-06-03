#ifndef COMPARE_H
#define COMPARE_H


class Operator;

class OperatorComp 
{
public:
   OperatorComp(){;}
   ~OperatorComp(){;}
   int compare(Operator* op, Operator* to) { return 0;}
   int equal(Operator* op, Operator* to) {return 1;}
   void display(Operator* op);
};


class PlanningState;

class PlanningCompare
{
public:
   int compare(PlanningState* element, PlanningState* to) { return 1;}
   int equal(PlanningState* element, PlanningState* to) {return 1;}
   void display(PlanningState* state);
};

#endif
