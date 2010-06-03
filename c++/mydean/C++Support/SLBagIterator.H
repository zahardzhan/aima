/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: SLBagIterator.H                                     */
/*    ASGN: Final                                               */
/*    DATE: Tue Jun 21 17:36:49 1994                            */
/****************************************************************/


#ifndef SLBagITERATOR_HEADER
#define SLBagITERATOR_HEADER
#include <SIterator.H>

/****************************************************************/
/* CLASS NAME :                                                 */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


template <class T, class K>
class SLBagIterator
{
   SortIterator<T,K>* iterator_; // the iterator for the SLBag
public:
   SLBagIterator(SLBag<T,K>* Bag) // create an iterator for an SLBag
      {
         iterator_ = new SortIterator<T,K>(Bag->bag_rep_);
      }
   ~SLBagIterator()             // delete the iterator
      {
         delete iterator_;
      }
   void start()                 // start the iteration
      {
         iterator_->start();
      }
   int end()                    // are we at the end of the Bag
      {
         return iterator_->end();
      }
   void next()                  // iterate
      {
         iterator_->next();
      }
   ListAbsNode<T,K>* current()  // return the current node
      {
         return iterator_->current();
      }
};

#endif
