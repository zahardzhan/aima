#ifndef COMPARE_H
#define COMPARE_H

class Plan;

class PlanComp
{
public:
   PlanComp()
      {
      }
   ~PlanComp()
      {
      }
   int equal(Plan* plan, Plan* to);
   int compare(Plan* plan, Plan* to);
   void display(Plan* plan);
};


class Step;

class StepComp
{
public:
   StepComp()
      {
      }
   ~StepComp()
      {
      }
   int compare(Step* step, Step* to);
   int equal(Step* step, Step* to);
   void display(Step* step); 
};


class Constrain;

class ConstComp
{
public:
   ConstComp()
      {
      }
   ~ConstComp()
      {
      }
   int compare(Constrain* constraint, Constrain* comp);
   int equal(Constrain* constraint, Constrain* comp);
   void display(Constrain* constrain);
};


class Link;

class LinkComp
{
public:
   LinkComp(){;}
   ~LinkComp(){;}
   int compare(Link* link, Link* to);
   int equal(Link* link, Link* to);
   void display(Link* link);

};


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


class Requirement;

class ReqComp
 {
public:
   ReqComp()
      {
      }
   ~ReqComp()
      {
      }
   int compare(Requirement* req, Requirement* to);
   int equal(Requirement* req, Requirement* to);
   void display(Requirement* rw);
};


class Conflict;

class ConflictComp
{
public:
   ConflictComp()
      {
      }
   ~ConflictComp()
      {
      }
   int equal(Conflict* conflict, Conflict* to);
   int compare(Conflict* conflict, Conflict* to);
   void display(Conflict* conflict) {;}
};


#endif
