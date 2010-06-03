#ifndef COMPARE_H
#define COMPARE_H


class Binding;

class BindCompare {
 public:
   BindCompare(){;}
   int equal(Binding*, Binding*);
   int compare(Binding*, Binding*);
   void display(Binding*);
};


class LogicNode;

class LogicComparator {
public:
   LogicComparator(){;}
   ~LogicComparator();
   int compare(LogicNode*, LogicNode*);
   int equal(LogicNode*, LogicNode*);
   void display(LogicNode* node);
};


#endif
