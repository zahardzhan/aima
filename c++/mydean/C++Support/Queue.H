/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Queue.H                                             */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun  9 21:11:05 1994                            */
/****************************************************************/
#ifndef QUEUE__HEADER
#define QUEUE__HEADER
#include <List.H>
template <class T, class K>
class QueueInternalNode : public ListAbsInternalNode<T,K>
{
   QueueInternalNode(QueueInternalNode&)
      {
      }
   QueueInternalNode& operator=(QueueInternalNode&)
      {
      }
public:
   // creates the queue node
   QueueInternalNode(ListAbsNode<T,K>* next, T* element)
      :ListAbsInternalNode<T,K>(next, element)
         {
         }
   // destructor
   virtual ~QueueInternalNode()
      { 
      }
   // does nothing
   virtual ListAbsNode<T,K>* insert(T* element, K* comparator)
      {
         return this;
      }
   // does nothing
   virtual ListAbsNode<T,K>* remove(T*& element, K* comparator)
      { 
         return this;
      }
};

template <class T, class K>
class QueueTailNode : public ListAbsTailNode<T,K> 
{
   QueueTailNode(QueueTailNode<T,K>&)
      {
      }
   QueueTailNode& operator=(QueueTailNode<T,K>&)
      {
      }
   ListAbsNode<T,K>* previous_;
public:
   // creates the tail node in a queue
   QueueTailNode(ListAbsNode<T,K>* previous) : ListAbsTailNode<T,K>()
      {
         previous_ = previous;
      }
   // empty destructor
   virtual ~QueueTailNode()
      { 
         return;
      }
   // inserts an element at the end of the list
   virtual ListAbsNode<T,K>* insert(T* element, K* comparator)
      {
         ListAbsNode<T,K> *new_node = new QueueInternalNode<T,K>(this,element);
         previous_->setNext(new_node);
         previous_ = new_node;
         return this;
      }
   // does nothing
   virtual ListAbsNode<T,K>* remove(T*& element, K* comparator)
      {
         return this;
      }
   virtual void setPrevious(ListAbsNode<T,K>* previous)
      {
         previous_ = previous;
      }
};

template <class T, class K>
class QueueHeadNode : public ListAbsHeadNode<T,K> 
{
   QueueHeadNode(QueueHeadNode&)
      {
      }
   QueueHeadNode& operator=(QueueHeadNode&)
      {
      }
public:
   // creates a head node
   QueueHeadNode() : ListAbsHeadNode<T,K>() 
      { 
      }
   virtual ~QueueHeadNode()
      {
      }
   // does nothing
   virtual ListAbsNode<T,K> *insert(T* element, K* comparator)
      {
         return this;
      }
   // removes the current node
   virtual ListAbsNode<T,K>* remove(T*& element, K* comparator)
      {
         if(getNext()->getNext() == 0) // tried to delete a node from
                                       // an empty list
            { 
               return this;                 
            };
         element = (getNext()->getElement());
         ListAbsNode<T,K>* to_be_deleted = getNext();
         setNext(getNext()->getNext());
         delete to_be_deleted;            
         // if the next node is the tail, then its previous node is 
         // no longer valid, so you have to set it to be the 
         // head node.
         if(getNext()->getNext() == 0)
            {
               ((QueueTailNode<T,K>*)  getNext())->setPrevious(this);
            }
      }
};

template <class T, class K>
class Queue 
{
   QueueHeadNode<T,K>* head_;
   QueueTailNode<T,K>* tail_;
   K* comparator_;
   void removeList()            // deletes all the elements in a list
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
  void init()                   // preforms the intialization of the 
                                // queue
     {
        head_ = new QueueHeadNode<T,K>;
        tail_ = new QueueTailNode<T,K>(head_);

        head_->setNext(tail_);
     }
public:
   // default constructor
   Queue() 
      {
         comparator_ = new K;
         init();
      }
   // copy constructor
   Queue(Queue<T,K>& queue) 
        {
         comparator_ = new K(*(queue.comparator_));
         init();
         ListAbsNode<T,K>* node = queue.head_->getNext();
         while(node->getNext() != 0)
            { // while not the tail node!
               tail_->insert(node->getElement(), comparator_);
               node = node->getNext();
            };
      }
   // creates a queue with the specified comparator
   Queue(K* comparator)
      {
         head_ = new QueueHeadNode<T,K>;
         tail_ = new QueueTailNode<T,K>(head_);
         head_->setNext(tail_);
         comparator_ = comparator;
      }
   // overloaded assignmene operator, deletes the current queue,
   // and copies the new one
   Queue<T,K>& operator=(Queue<T,K>& queue)
      {
         delete comparator_;
         comparator_ = new K(*(queue.comparator_));
         removeList();
         ListAbsNode<T,K>* node = queue.head_->getNext();
         while(node->getNext() != 0) { // while not the tail node!
            tail_->insert(node->getElement(), comparator_);
            node = node->getNext();
         };
         return *this;
      }
   virtual ~Queue()             // destructor
      {
         removeList();
      }
   int search(T* element)       // searches through the queue
      {
         return head_->search(element, comparator_);
      }
   void remove(T*& element)     // removes the top element
      {
         head_->remove(element, comparator_);
         return;
      }
   void insert(T* element)      // inserts the element at the end
      {
         tail_->insert(element, comparator_);
         return;
      }
   int empty()                  // informs the invoker wether the queue is 
                                // empty
      {
         return head_->empty();
      }
   void display()               // displays the queue
      {
         head_->display(comparator_);
      }
};

#endif   
