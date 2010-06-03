/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: DataList.H                                          */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun  9 02:19:53 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef DATALIST_HEADER
#define DATALIST_HEADER


#define DATA_INTERNAL_LIST (DataNode *) (DataInternalList *)
#define DATA_TAIL_LIST (DataNode*) (DataTailList *)

#include <DataNode.H>

#include <SortedList.H>

class DataTailList;


/****************************************************************/
/* CLASS NAME : DataInternalList                                */
/*   The internal node of the data nodes in the data dependency */
/* graph. This node is derived from the SInternalNode so it     */
/* is a list node, but it also has the properties of a DataNode */
/* necessary to preform operations on the data base. These      */
/* are to visit nodes and update them.                          */
/*                                                              */
/****************************************************************/


class DataInternalList 
: public SInternalNode<DataNode,DataCompare>, public DataNode
{
public:
   DataInternalList(ListAbsNode<DataNode, DataCompare>* next,
                    DataNode* element) 
      : SInternalNode<DataNode,DataCompare>(next,element), DataNode()
      {
      }
   virtual ~DataInternalList()
      {
      }
   // calls the visit on the element
   virtual void visit()

      {
         if(getNext()->getNext() == 0)
            {
               (DATA_TAIL_LIST getNext())->visit();
            }
         else 
            {
               (DATA_INTERNAL_LIST getNext())->visit();
            }
         getElement()->visit();
       }
   // inserts a node in the list in lexical order
   virtual ListAbsNode<DataNode,DataCompare>* insert(DataNode* element,
                                                        DataCompare* comparator)
      {
         if(comparator->compare(getElement(), element))
            {
               setNext(getNext()->insert(element,comparator));
               return this;
            }
         else
            {
               DataInternalList* node = new DataInternalList(getNext(), getElement());
               setNext(node);
               setElement(element);
               return this;
            }
      }
   // is used to determine wether all the nodes in the list are 
   // IN or wether one is out. The variable state is passed to each node,
   // and if one element has state that is OUT then the variable is changed
   virtual DataNode::State update(DataNode::State& state)
      {
         if(getNext()->getNext()  == 0)
            {
               (DATA_TAIL_LIST getNext())->update(state);
            }
         else 
            {
               (DATA_INTERNAL_LIST getNext())->update(state);
            }
         return (DATA_INTERNAL_LIST getElement())->update(state);
      
      }
   // the revise message is passed to each element in the list
   virtual void revise()
      {
         if(getNext()->getNext() == 0)
            {
               (DATA_TAIL_LIST getNext())->revise();
            }
         else
            {
               (DATA_INTERNAL_LIST getNext())->revise();
            }
         (DATA_INTERNAL_LIST getElement())->revise();
      }
};
   
class DataHeadList : public SHeadNode<DataNode,DataCompare>, public DataNode
{
public:
   DataHeadList(ListAbsNode<DataNode,DataCompare>* next)
      : SHeadNode<DataNode,DataCompare>(next), DataNode()
      {
      }
   ~DataHeadList()
      {      }
   // initiates the head message
   virtual void visit()
      {
         if(getNext()->getNext() == 0)
            {
               (DATA_TAIL_LIST getNext())->visit();
            }
         else 
            {
               (DATA_INTERNAL_LIST getNext())->visit();
            }
      }
   // initiates the update message
   virtual DataNode::State update(DataNode::State& state)
      {
         if(getNext()->getNext() == 0)
            {
               state =  (DATA_TAIL_LIST getNext())->update(state);
            }
         else
            {
               return (DATA_INTERNAL_LIST getNext())->update(state);
            }
      }
   // initiates the revise message
   virtual void revise()
      {
         if(getNext()->getNext() == 0)
            {
               (DATA_TAIL_LIST getNext())->revise();
            }
         else
            {
               (DATA_INTERNAL_LIST getNext())->revise();
            }
      }
};


class DataTailList : public STailNode<DataNode,DataCompare>, public DataNode {
public:
   DataTailList() : STailNode<DataNode,DataCompare>(), DataNode()
      {
      }
   virtual ~DataTailList() 
      { 
      }
   virtual void visit()
      {
      }
   // inserts a node at the tail
   virtual ListAbsNode<DataNode, DataCompare>* insert(DataNode* element,
                                                         DataCompare* comp)
      {
         DataInternalList* node = new DataInternalList(this, element);
         return node;
      }
   // returns the value OUT
   virtual DataNode::State update(DataNode::State& state)
      {
        return DataNode::OUT;
      }
   // does nothing
   virtual void revise()
      {
         return;
      }
};

class SortedDataList
{
   DataCompare* comparator_;
   DataHeadList* head_;
   DataTailList* tail_;
// HELPER FUNCTIONS
   void removeList()
      {
         ListAbsNode<DataNode,DataCompare>* node = head_;
         while(node != 0)
            {
                  ListAbsNode<DataNode,DataCompare>* to_be_deleted = node;
               node = node->getNext();
               delete to_be_deleted;
            }
         return;
      }
   void init()
      {
         tail_ = new DataTailList;
         head_ = new DataHeadList(tail_);
      }
public:
   SortedDataList()             // Default constructor
      {
         comparator_ = new DataCompare;
         init();
      }
   SortedDataList(SortedDataList& list) // Copy constructor
      {
         comparator_ = new DataCompare(*list.comparator_);
         init();
         ListAbsNode<DataNode, DataCompare>* node = list.head_->getNext();
         while(node->getNext() != 0)
            {
               head_->insert(node->getElement(), comparator_);
               node = node->getNext();
            }
      }
   // Assignment operator
   SortedDataList& operator=(SortedDataList& list)
      {
         delete comparator_;
         comparator_ = new DataCompare(*list.comparator_);
         removeList();
         ListAbsNode<DataNode, DataCompare>* node = list.head_->getNext();
         while(node->getNext() != 0)
            {
               head_->insert(node->getElement(), comparator_);

               node = node->getNext();
            }
         return *this;
      }
   // creates a data list with the appropriate comparator
   SortedDataList(DataCompare* comparator)
      {
         comparator_ = comparator;
         init();
      }
   ~SortedDataList() 
      {
         removeList();
      }
   void insert(DataNode* element) // insert message
      {
         head_->insert(element, comparator_);
      }
   void remove(DataNode* element) // remove message
      {
         head_->remove(element, comparator_);
      }
   int search(DataNode* element) // search message
      {
         return head_->search(element, comparator_); 
      }
   int empty()                  // empty message, return 1 if true, 0 if false
      {
         return head_->empty();
      }
   void display()               // displays the list
      {
         head_->display(comparator_);
      }
   void visit()                 // sends the visit message to all members
      {
         head_->visit();
      }
   void revise()                // sends the revise message to all members
      {
         head_->revise();
      }
   DataNode::State update()     // this is used to determine wether 
                                // wether the list members are all in or out
                                // The default is they are all in, and that
                                // is changed by the element that is out
      {
         DataNode::State state = DataNode::IN;
         head_->update(state);
         return state;
      }
};

   
   

#endif

/*
 * Copyright 1994, Brown University, Providence, RI
 *
 * Permission to use and modify this software and its documentation for
 * any purpose other than its incorporation into a commercial product is
 * hereby granted without fee.  Permission to copy and distribute this
 * software and its documentation only for non-commercial use is also
 * granted without fee, provided, however, that the above copyright notice
 * appear in all copies, that both that copyright notice and this permission
 * notice appear in supporting documentation, that the name of Brown
 * University not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission,
 * and that the person doing the distribution notify Brown University of
 * such distributions outside of his or her organization. Brown University
 * makes no representations about the suitability of this software for
 * any purpose.  It is provided "as is" without express or implied warranty.
 * Brown University requests notification of any modifications to this
 * software or its documentation.
 *
 * Send the following redistribution information:
 *
 *	Name:
 *	Organization:
 *	Address (postal and/or electronic):
 *
 * To:
 *	Software Librarian
 *	Computer Science Department, Box 1910
 *	Brown University
 *	Providence, RI 02912
 *
 *		or
 *
 *	brusd@cs.brown.edu
 *
 * We will acknowledge all electronic notifications.
 */

