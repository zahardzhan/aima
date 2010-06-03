/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: SortedQueue.H                                       */
/*    ASGN: Final                                               */
/*    DATE: Fri Jun 17 01:18:29 1994                            */
/****************************************************************/


#ifndef SORTEDQUEUE_HEADER
#define SORTEDQUEUE_HEADER

#include <SortedList.H>
#include <SIterator.H>

template <class T, class K>
/*
   Adds elements in a sorted fashion, as per a sorted list,
   but removes the first rather than remove any element.
*/

class SortedQueue 
{
   K* comparator_;
   SHeadNode<T,K>* head_;
   STailNode<T,K>* tail_;
   SortedQueue(SortedQueue<T,K>&){;}
   SortedQueue<T,K>& operator=(SortedQueue<T,K>&){;}
public:
friend class SortIterator<T,K>; // iterator
   SortedQueue(K* comparator)
      {
         comparator_ = comparator;
         tail_ = new STailNode<T,K>;
         head_ = new SHeadNode<T,K>(tail_);
      }
   ~SortedQueue()
      {
         delete head_;
      }
   void insert(T* element)
      {
         head_->insert(element, comparator_);
      }
   void remove(T*& element)
      {
         if(head_->empty())
            { // tail node is next?
               element = 0;
               return;
            };
         element = head_->getNext()->getElement();
         ListAbsNode<T,K>* to_be_deleted = head_->getNext();
         head_->setNext(head_->getNext()->getNext());
         delete to_be_deleted; 
      }
   int search(T* element)
      { 
         return head_->search(element, comparator_);
      }
   int empty() 
      {
         return head_->empty();
      }
   void display()
      {
         head_->display(comparator_); 
      }
};


#endif
