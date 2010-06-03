/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: SortedSet.H                                         */
/*    ASGN: Final                                               */
/*    DATE: Fri Jun 17 17:30:52 1994                            */
/****************************************************************/


#ifndef SORTEDSET_HEADER
#define SORTEDSET_HEADER
#include <SortedList.H>
#include <SIterator.H>

template<class T,class K>
class SortedSet : public Set {
 SortedList<T,K>* set_rep_;
 K* comparator_;    
public:
 SortedSet(K* comparator) 
    {
       set_rep_ = new SortedSet<T,K>(comparator);
       comparator_ = comparator;
    }
 virtual ~SortedSet() 
    {
       delete set_rep_;
    }

 virtual void addMember(T* element)
    {
       set_rep_->insert(element);
    }
 virtual void removeMember(T* element)
   {
      set_rep_->delete(element);
   }
 virtual int memberOf(T* element) 
    {
       return set_rep_->search(element);
    }
 virtual Set<T,K>* difference(Set<T,K>* set) 
    {
       SortIterator<T,K>* this_set = new SortedIterator<T,K>(set_rep_);
       
  }
}
       

#endif
