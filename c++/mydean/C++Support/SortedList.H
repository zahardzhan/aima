#ifndef SORTEDLIST_HEADER
#define SORTEDLIST_HEADER

#include <List.H>
#include <SIterator.H>

/****************************************************************/
/* CLASS NAME : SInternalNode                                   */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


template <class T, class K>
class SInternalNode : public ListAbsInternalNode<T,K> 
{
public:
   // creates an SInternalNode, and the parent class
   SInternalNode(ListAbsNode<T,K>* next, T* element) 
      : ListAbsInternalNode<T,K>(next, element)
         {
         } 
    virtual ~SInternalNode()
       {
       }
   // inserts a new element in the list
   virtual ListAbsNode<T,K>* insert(T* element, K* comparator)
      {
         // if the comparison is false, then the element
         // gets inserted here, otherwise the message is 
         // past to the next node in the list
         if (comparator->compare(getElement(),element)) 
            { 
               // pass message to next element
               setNext(getNext()->insert(element, comparator));
               return this;
            }
         else 
            {
               // create a new node, with this nodes internal data
               // while this node has its internal data changed to have
               // the element and be before node
               SInternalNode<T,K>* node = new SInternalNode<T,K>(getNext(), getElement());
               setNext(node);
               setElement(element);
               return this;
            }
      }
   // remove a node,
   // This either removes the next node, or else it passes the 
   // remove message to the next node in the list
   virtual ListAbsNode<T,K>* remove(T*& element, K* comparator)
      {
         if (comparator->equal(getNext()->getElement(),element)) 
            {
               element = getNext()->getElement();
               ListAbsNode<T,K> *to_be_deleted = getNext();
               setNext(getNext()->getNext());
               return this;
            } 
         else
            {
               return getNext()->remove(element, comparator);
            }
      };
};

template <class T, class K>
class STailNode : public ListAbsTailNode<T,K> 
{
public:
   STailNode() : ListAbsTailNode<T,K>() // default constructor
      {
      }
   virtual ~STailNode()         // destructor
      {
      }
   // inserts node before the tail node
   virtual ListAbsNode<T,K>* insert(T* element, K* comparator)
      {
         SInternalNode<T,K>* node = new SInternalNode<T,K>(this, element);
         return node;
      }
   // returns this, and sets element to 0
   virtual ListAbsNode<T,K>* remove(T*& element, K* comparator)
      {
         element = 0;
         return this;
      }
};

template <class T, class K>
class SHeadNode : public ListAbsHeadNode<T,K> 
{
   SHeadNode(SHeadNode&){;}
   SHeadNode& operator=(SHeadNode&){;}
public:
   // default constructor
   SHeadNode(ListAbsNode<T,K>* next) 
      : ListAbsHeadNode<T,K>(next)
         {
         }
   // destructor
   virtual ~SHeadNode()
      {
      }
   // passes the insertion message to the next node in the list
   virtual ListAbsNode<T,K>* insert(T* element, K* comparator) 
      { 
         setNext(getNext()->insert(element, comparator));
         return this;
      }
   // removes the next item in the list, 
   // either removes the next node, or passes the message to the 
   // next node
   virtual ListAbsNode<T,K>* remove(T*& element, K* comparator) 
      {
         // is the next node the one to be removed
         if (comparator->equal(getNext()->getElement(), element))
            {
               // yes, so remove it and fix the list
               element = getNext()->getElement();
               ListAbsNode<T,K> *to_be_deleted = getNext();
               setNext(getNext()->getNext());
               delete to_be_deleted;
               return this;          
            } 
         else 
            {
               // no, so pass the message down
               return getNext()->remove(element, comparator);
            }
      }
};


/****************************************************************/
/* CLASS NAME :  Sorted List                                    */
/*                                                              */
/*      Sorted List is a linked list in which the comparator    */
/*  is supplied to the class, and will automatically sort the   */
/*  list for the user.  other operations works as it should     */
/*  be expected                                                 */
/*                                                              */
/****************************************************************/
template <class T,class K>
class SortedList
{
   K* comparator_;
   SHeadNode<T,K>* head_;
   STailNode<T,K>* tail_;
// HELPER FUNCTIONS

   // removes a list by destroying all the nodes in it
   void removeList() 
      {
         ListAbsNode<T,K>* node  = head_;
         while(node != 0) 
            {
               ListAbsNode<T,K>* to_be_deleted = node;
               node = node->getNext();
               delete to_be_deleted;
            }
         return;
      }
   // creates a new head and tail node
   void init()
      {
         tail_ = new STailNode<T,K>;
         head_ = new SHeadNode<T,K>(tail_);
      }
public:
friend class SortIterator<T,K>;
   // default constructor
   SortedList()
      {
         comparator_ = new K;
         init();
      }
   // copy constructor
   SortedList(SortedList<T,K>& list)
      {
         comparator_ = new K(*(list.comparator_));
         init();
         ListAbsNode<T,K>* node = list.head_->getNext();
         while(node->getNext() != 0)
            { // while not the tail node!
               head_->insert(node->getElement(), comparator_);
               node = node->getNext();
            };
      }
   // assignment operator
   SortedList<T,K> operator=(SortedList<T,K>& list) 
      {
         delete comparator_;
         comparator_ = new K(*(list.comparator_));
         removeList();
         ListAbsNode<T,K>* node = list.head_->getNext();
         while(node->getNext() != 0)
            { // while not the tail node!
               head_->insert(node->getElement(), comparator_);
               node = node->getNext();
            };
         return *this;
      }
   // destructor
   ~SortedList()
      {
         removeList();
      }
   // creates a sorted list with the given comparator
   SortedList(K* comparator)
      {
         comparator_ = comparator;
         init();
      }
   // inserts a new node into the list
   void insert(T* element)
      { 
         head_->insert(element, comparator_);
      }
   // removes a node from the list, element will point 
   // to the data in the list
   void remove(T*& element)
      {
         head_->remove(element, comparator_);
      }
   // searches for the element specified in search
   int search(T* element)
      { 
         return head_->search(element, comparator_);
      }
   // informs the invoker wether the list is empty
   int empty() 
      { 
         return head_->empty();
      }
   // passes the display message to the head node.
   void display()
      { 
         head_->display(comparator_); 
      }
  };


#endif


