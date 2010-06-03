/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: SLBag.H                                             */
/*    ASGN: Final                                               */
/*    DATE: Fri Jun 17 18:45:30 1994                            */
/****************************************************************/


#ifndef SLBag_HEADER
#define SLBag_HEADER

#include <SortedList.H>
#include <SIterator.H>
#include <SLBagIterator.H>

/* 
   class SLBag, is a Bag that has as its internal representation a
   sorted list.  It is, however, not a pure implementation of a Bag,
   since elements are not repeated. It is probably more, accurate to
   label it list that can have Bag operations preformed on it such as
   Bag difference, and union.
*/

template <class T, class K>
class SLBag
{
   K* comparator_;              // comparator
   SortedList<T,K>* bag_rep_;   // Bag representation, which in this
                                // case is a sorted list
   int count_;                  // number of elements
public:
   friend class SLBagIterator<T,K>; //  the iterator
   SLBag()                          // default constructor
      {
         count_ = 0;
         comparator_ = new K;
         bag_rep_ = new SortedList<T,K>(comparator_);
      }
   SLBag(SLBag<T,K>& Bag)       // copy constructor
      {
         count_ = 0;            // count initialized to zero
         comparator_ = Bag.comparator_;
         bag_rep_ = new SortedList<T,K>(Bag.comparator_); // creates a new Bag_rep
         SortIterator<T,K>* iterator = new SortIterator<T,K>(Bag.bag_rep_);
         // copy the old material into the new list
         for(iterator->start();iterator->end(); iterator->next())
            {
               count_++;
               bag_rep_->insert(iterator->current()->getElement());
            }
      }
   // assignement operator, destroys, the previous list, 
   // creating a new one
   SLBag<T,K>& operator=(SLBag<T,K>& Bag)
      {
         count_ = 0;
         comparator_ = new K(*(Bag.comparator_));
         bag_rep_ = new SortedList<T,K>(Bag.comparator_);
         SortIterator<T,K>* iterator = new SortIterator<T,K>(Bag.bag_rep_);
         for(iterator->start();iterator->end(); iterator->next())
            {
               count_++;
               bag_rep_->insert(iterator->current()->getElement());
            }
         return *this;
      }
   SLBag(K* comparator)         // creates a Bag with a comparator
      {
         count_ = 0;
         comparator_ = comparator;
         bag_rep_ = new SortedList<T,K>(comparator);
      }
   ~SLBag()                     // destroys the Bag_rep
      {
         delete bag_rep_;
      }
   virtual int memberOf(T* element) // queery to find a member
      {
         return bag_rep_->search(element);
      }
   virtual SLBag<T,K>* difference(SLBag<T,K>* Bag) // preform Bag difference
      {
         // create a new Bag to be the return value
         SLBag<T,K>* ret_val = new SLBag<T,K>(comparator_);
         // iterate through the list addig to the ret_val all those members in 
         // Bag that are not members of this Bag
         SortIterator<T,K>* this_iterator = new SortIterator<T,K>(bag_rep_);
         for(this_iterator->start(); this_iterator->end(); this_iterator->next())
            {
               if(!(Bag->bag_rep_->search(this_iterator->current()->getElement())))
                  {
                     ret_val->addMember(this_iterator->current()->getElement());
                  }
            }
         delete this_iterator;
         return ret_val;
      }
   // unifies two Bags
   virtual SLBag<T,K>* unify(SLBag<T,K>* Bag)
      {
         // create a Bag that will be returned
         SLBag<T,K>* ret_val = new SLBag<T,K>(comparator_);
         SortIterator<T,K>* this_iterator = new SortIterator<T,K>(bag_rep_);
         SortIterator<T,K>* iterator = new SortIterator<T,K>(Bag->bag_rep_);
         for(this_iterator->start(); this_iterator->end(); this_iterator->next())
            {
               ret_val->addMember(this_iterator->current()->getElement());
            }
         for(iterator->start(); iterator->end(); iterator->next())
            {
               if(!(ret_val->memberOf(iterator->current()->getElement())))
                    {
                       ret_val->addMember(iterator->current()->getElement());
                    }
            }
         delete iterator;
         delete this_iterator;
         return ret_val;
      }
   virtual int subBag(SLBag<T,K>* Bag)
      {
         SortIterator<T,K>* this_iterator = new SortIterator<T,K>(bag_rep_);
         for(this_iterator->start(); this_iterator->end(); 
             this_iterator->next()){
            if(!(Bag->bag_rep_->search(this_iterator->current()->getElement())))
               {
                  return 0;
               }
         }
         return 1;
      }

   // Appending with Bags means inserting the element of one Bag into the 
   // next Bag, not actually appending as these Bags are not ordered, i.e.
   // there is no concept of first or last element

   // append Bag to this Bag and return a new Bag
   SLBag<T,K>* append(SLBag<T,K>* Bag)
      {
         SLBag<T,K>* ret_val = new SLBag<T,K>(*this);
         SortIterator<T,K>* iterator = new SortIterator<T,K>(Bag->bag_rep_);
         for(iterator->start(); iterator->end(); iterator->next())
            {
               ret_val->addMember(iterator->current()->getElement());
            }
         return ret_val;
      }
   // append a Bag to this and return this
   void appendTo(SLBag<T,K>* Bag)
      {
         SortIterator<T,K>* iterator = new SortIterator<T,K>(Bag->bag_rep_);
         for(iterator->start(); iterator->end(); iterator->next())
            {
               count_++;
               bag_rep_->insert(iterator->current()->getElement());
            }
         
      }
   // returns the nth node in the Bag, works similarly to first, second etc
   ListAbsNode<T,K>* nth(int index)
      {
         SortIterator<T,K>* iterator = new SortIterator<T,K>(bag_rep_);
         for(int i = 0; i < index; i++)
            {
               iterator->next();
            }
         return iterator->current();
         delete iterator;
      }

   // returns a new Bag with all the elements except for the first
   SLBag<T,K>* rest()
      {
         SLBag<T,K>* ret_val = new SLBag<T,K>;
         SortIterator<T,K>* iterator = new SortIterator<T,K>(bag_rep_);
         iterator->start();
         iterator->next();
         for(iterator->current();iterator->end(); iterator->next())
           {
                    ret_val->addMember(iterator->current()->getElement());
           }
        delete iterator;
        return ret_val;
      } 
   // adjoins two Bags
   SLBag<T,K>* adjoin(SLBag<T,K>* Bag)
      {
         SLBag<T,K>* ret_val = new SLBag<T,K>(*this);
         SLBagIterator<T,K>* iterator = new SLBagIterator<T,K>(Bag);
         for(iterator->start(); iterator->end(); iterator->next())
            {
               if(!(ret_val->memberOf(iterator->current()->getElement())))
                  {
                     ret_val->addMember(iterator->current()->getElement());
                  }
            }
         delete iterator;
         return ret_val;
      }
   // inserts a new member
   virtual void addMember(T* element) 
      {
         count_++;
         bag_rep_->insert(element);
      }
   // deletes an element
   virtual void deleteMember(T*& element)
      {
         count_--;
         bag_rep_->remove(element);
      }
   // returns the size
   virtual int size()
      {
         return count_;
      }
   // displays the Bag
   void display()
      {
         bag_rep_->display();
      }
};
            
#endif
