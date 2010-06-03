/****************************************************************/
/*    NAME: Smith Surasmith                                     */
/*    ACCT: sls                                                 */
/*    FILE: stack.H                                             */
/*    ASGN: C++ code                                            */
/*    DATE: Tue Jun  7 14:42:53 1994                            */
/****************************************************************/


#ifndef STACK_HEADER
#define STACK_HEADER

#include <List.H>



template <class T, class K>
class StackTailNode : public ListAbsTailNode<T,K>
{
private:

  virtual int search(T* node, K* comparator){return 1;}
  virtual ListAbsNode<T,K>* remove(T*& element,K* comparator){return 0;}  
  virtual ListAbsNode<T,K>* insert(T* element,K* comparator){return 0;}
public:
  
  StackTailNode(){;}
  virtual ~StackTailNode(){;}

};  

template <class T, class K>
class StackInternalNode : public ListAbsInternalNode<T,K>
{
public:
   StackInternalNode( ListAbsNode<T,K>* next,T* element)
      :ListAbsInternalNode<T,K>(next, element){;}
   virtual ~StackInternalNode() {;}
   virtual ListAbsNode<T,K>* remove(T*& element,K* comparator){return 0;}  
   virtual ListAbsNode<T,K>* insert(T* element,K* comparator){return 0;}  

};


template <class T,class K>
class StackHeadNode : public ListAbsHeadNode<T,K>
{
private:
  
  StackHeadNode(StackHeadNode&){;}
  StackHeadNode& operator=(StackHeadNode&){return *this;}
  virtual ListAbsNode<T,K>* remove(T*& element,K* comparator){return 0;}

public:

  StackHeadNode(ListAbsNode<T,K>* next)
  : ListAbsHeadNode<T,K>(next)
  {;}

  virtual 
  ~StackHeadNode(){;}

  virtual ListAbsNode<T,K>*
  insert(T* element,K* comparator = 0)
  {
    StackInternalNode<T,K>* node 
      = new StackInternalNode<T,K>(getNext(),element);
    setNext(node);
    return this;
  }

  virtual ListAbsNode<T,K>* 
  first()
  {
    if(!empty())
      {
	ListAbsNode<T,K>* node = getNext();
	setNext(getNext()->getNext());
	node->setNext(0);
	return node;
      }
    else return 0;
  }
};

  
template <class T,class K>
class Stack
{
private:
  
  StackHeadNode<T,K>* head_;
  StackTailNode<T,K>* tail_;
 
  Stack(Stack<T,K>&){;}
  Stack<T,K>& operator=(Stack<T,K>&){;}

public:
  
  Stack()
  {
    tail_ = new StackTailNode<T,K>;
    head_ = new StackHeadNode<T,K>(tail_);
  }

  ~Stack()
  {
    delete head_;
  }

  void
  push(T* element)
  {
    head_->insert(element);
  }

  T*
  pop()
  {
    ListAbsNode<T,K>* node = head_->first();
    T* element = 0;

    if(node)
      {
	element = node->getElement();
	delete node;
      }

    return element;
  }

  ListAbsNode<T,K>*
  removeFirstNode()
  {
    head_->first();
  }
  
  int
  empty()
  {
    return head_->empty();
  }
  void display(K* comparator)
     {
        head_->display(comparator);
     }

};

    
  
       
  

    

#endif
