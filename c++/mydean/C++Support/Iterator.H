/****************************************************************/
/*    NAME: Smith Surasmith                                     */
/*    ACCT: sls                                                 */
/*   EMAIL: sls@cs.brown.edu                                    */
/*    FILE: Iterator.H                                          */
/*    ASGN: C++ code                                            */
/*    DATE: Fri Jun 24 10:56:37 1994                            */
/****************************************************************/


#ifndef ITERATOR_HEADER
#define ITERATOR_HEADER

template <class L ,class T, class K>
class Iterator
{
  L* list_;
  ListAbsNode<T,K>* current_;
  ListAbsNode<T,K>* head_;
public:
  Iterator(L* list)
  {
    list_ = list;
    head_ = list->head_;
    current_ = head_;
  }
  ~Iterator()
  {
  }
  void start()
  {
    current_ = head_->getNext();
  }
  int end()
  {
    if(current_->getNext() == 0)
      return 0;
    
    return 1;
  }
  void next()
  {
    current_ = current_->getNext();
  }
  ListAbsNode<T,K>* current()
  {
    return current_;
  }
};


#endif
