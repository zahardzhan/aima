#ifndef SITERATOR_HEADER
#define SITERATOR_HEADER
#include<SortedList.H>
template <class T,class K>
class SortIterator 
{
   ListAbsNode<T,K>* current_;  // the current location in the list
   ListAbsNode<T,K>* head_;     // the head of the list
public:
   SortIterator(SortedList<T,K>* list)
      {
         head_ = list->head_; 
         current_ = head_;
      }
   ~SortIterator() 
      {
      }
   void start() 
      {
         current_ = head_->getNext(); // set the current pointer to the 
                                      // first element in the list
      }
   int end()                    // return 0 if true, 1 if not true
      {
         if(current_->getNext() == 0)
            {
               return 0;
            }
      return 1;
      }
   void next()                  // iterate
      {
         current_ = current_->getNext();
      }
   ListAbsNode<T,K>* current()  // return the current node
      {
         return current_;
      }
};
#endif
