
#ifndef ListNode__HEADER
#define ListNode__HEADER

#include <iostream.h>



/****************************************************************/
/* CLASS NAME : ListAbsNode                                     */
/*   The abstract base class for all list nodes.                */
/*  A list node can insert, remove, display, search, return     */
/* wether the list is empty, and display itself. The elements   */
/* can be accessed                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


template <class T,class K>
class ListAbsNode { 
protected:
   ListAbsNode(){;}
public:
   ListAbsNode(ListAbsNode<T,K>&){;}
   ListAbsNode<T,K>& operator=(ListAbsNode<T,K>&){;}
   virtual ~ListAbsNode(){;}
   virtual ListAbsNode<T,K>* insert(T* element,K* comparator){}
   virtual ListAbsNode<T,K>* remove(T*& element,K* comparator){}
   virtual int search(T* element, K* comparator) = 0;
   virtual int empty() = 0;
   virtual void display(K* visualizer) = 0;
   virtual ListAbsNode<T,K>* getNext() = 0;
   virtual void setNext(ListAbsNode<T,K>* next) = 0;
   virtual T* getElement() = 0;
   virtual void setElement(T* ) = 0;
};




/****************************************************************/
/* CLASS NAME : ListAbsInternalNode                             */
/*   Represents the internal node of a list data structure.     */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/



template <class T,class K>
class ListAbsInternalNode : public ListAbsNode<T,K>
{
   T* element_;
   ListAbsNode<T,K>* next_;
 public:
   // Default constructor
   ListAbsInternalNode()
      {
         element_ = 0;
         next_ = 0;
      }
   // Copy constructor
   ListAbsInternalNode(ListAbsInternalNode& node)
      {
         element_ = node.element_;
         if(node.getNext() == 0) 
            {
               ListAbsTailNode<T,K>* tail_node = new ListAbsTailNode<T,K>;
               next_ = tail_node;
            }
         else 
            {
               next_ = new ListAbsInternalNode
                            (*((ListAbsInternalNode *) node.getNext()));
            }
         return;
      }
   // assignment operator
   ListAbsInternalNode& operator=(ListAbsInternalNode& node )
      {
         element_ = node.element_;
         if(node.getNext() == 0) 
            {
               ListAbsTailNode<T,K>* tail_node = new ListAbsTailNode<T,K>;
               next_ = tail_node;
            }
         else 
            {
               next_ = new ListAbsInternalNode
                            (*((ListAbsInternalNode *) node.getNext()));
            }
         return *this;
      }
   // creates an internal node
   ListAbsInternalNode(ListAbsNode<T,K>* next, T* element)
      {
         next_ = next;
         element_ = element;
      }
   // destructor
   virtual ~ListAbsInternalNode()
      {
         ;
      }
   // if the current element_ is equal to the element
   // as defined by the comparator equal function,
   // then a 1, is returned, otherwise the next
   // node is passed the search message
   virtual int search(T* element, K* comparator)
      {
         if (comparator->equal(element_, element))
            {
               return 1;
            }
         else 
            {
               return next_->search(element, comparator);
            }
      }
   // returns 0, i.e. the list is not empty
   virtual int empty() 
      { 
         return 0;
      }
   // uses the visualizer to display the node, and then 
   // and then passes the display message to the next node
   virtual void display(K* visualizer) 
      {
         visualizer->display(element_); 
         getNext()->display(visualizer);
      }

   // ACCESSORS
   virtual ListAbsNode<T,K>* getNext() 
      { 
         return next_;
      }
   virtual void setNext(ListAbsNode<T,K>* next)  
      { 
         next_ = next;
      }
   virtual void setElement(T* element) 
      { 
         element_ = element;
      }
   virtual T* getElement() 
      { 
         return element_;
      }

};


/****************************************************************/
/* CLASS NAME : ListAbsTailNode                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


template <class T,class K>
class ListAbsTailNode : public ListAbsNode<T,K> {
 public:
   ListAbsTailNode() 
      {                         // Default Constructor
      }
   ListAbsTailNode(ListAbsTailNode<T,K>& node)
      {                         // Copy constructor
      }
   ListAbsTailNode<T,K>& operator=(ListAbsTailNode<T,K>& node)
      {                         // Assignment operator
      }
   virtual ~ListAbsTailNode()
      {                         // Destructor
      }
   virtual int empty() 
      {                         // returns, true
         return 1;
      }
   // ACCESSORS
   // returns 0, i.e. there is no next node
   virtual ListAbsNode<T,K>* getNext() 
      {                     
         return 0;
      }
   virtual void setNext(ListAbsNode<T,K>* next) 
      {
      }
   virtual T* getElement() 
      { 
         return 0;
      }
   virtual void setElement(T*)
      {
      }
   virtual int search(T* node, K* comparator) 
      { 
         return 0;
      }
   virtual void display(K* visualizer) {;}
};  


/****************************************************************/
/* CLASS NAME : ListAbsHeadNode                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/



template <class T,class K>
class ListAbsHeadNode : public ListAbsNode<T,K> 
{
   ListAbsNode<T,K>* next_;     // the next node
public:
   // Default constructor
   ListAbsHeadNode() 
      {
         next_ = 0;
      }
   // copy constructor
   ListAbsHeadNode(ListAbsHeadNode& node)
      {
         if(node.getNext() == 0) 
            {
               next_ = new ListAbsTailNode<T,K>;
         }
         else 
            {
               next_ = new ListAbsInternalNode<T,K>
                            (*((ListAbsInternalNode<T,K> *) node.getNext()));
            }
      }
   // creates a head node, with a next pointer
   ListAbsHeadNode(ListAbsNode<T,K>* next) 
       {
         next_ = next;
      }
   // overloaded assignment operator
   ListAbsHeadNode& operator=(ListAbsHeadNode& node)
      {
         if(node.getNext() == 0) 
            {
               next_ = new ListAbsTailNode<T,K>;
            }
         else 
            {
               next_ = new ListAbsInternalNode<T,K>
                            (*((ListAbsInternalNode<T,K> *) node.getNext()));
            }
         return *this;
      }
   // Destructor
   virtual ~ListAbsHeadNode() 
      {
      }
   // passes the search message to the next node, and returns the 
   // result from the next node
   virtual int search(T* element, K* comparator) 
      { 
         return next_->search(element, comparator);
      }
   // passes the message to the next node, which then returns the result
   virtual int empty() 
      { 
         return next_->empty();
      }
   // ACCESSORS
   virtual void setNext(ListAbsNode<T,K>* next)
      {
         next_ = next;
      }
   virtual void display(K* visualizer)
      { 
         getNext()->display(visualizer);
      }
   virtual ListAbsNode<T,K>* getNext() 
      { 
         return next_;
      }
   virtual T* getElement() 
      {
         return 0;
      }
   virtual void setElement(T*)
      {
      }
};
#endif








