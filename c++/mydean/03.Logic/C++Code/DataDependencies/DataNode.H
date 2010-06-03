
/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: DataNode.H                                          */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun  9 01:54:44 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef DATANODE_HEADER
#define DATANODE_HEADER

#include <string.h>
class SortedDataList;



/****************************************************************/
/* CLASS NAME : DataNode                                        */
/*   A data node is similar to the data node in the book.       */
/****************************************************************/


class DataNode 
{
   char* label_;                //  the symbol that the data node represents
   SortedDataList* justifications_;    
   SortedDataList* justificands_;
public:
   friend class DataCompare;

   DataNode() {;}
   enum State{IN, OUT,  VISITED};
   DataNode(char* label, State state = OUT);
   ~DataNode();
   void addJustification(DataNode* node);
   void addJustificand(DataNode* node);
   void removeJustification(DataNode* node);
   void removeJustificand(DataNode* node);
   void update();

   virtual void visit();
   virtual DataNode::State update(DataNode::State&  state);
   virtual void revise();
   DataNode::State state() 
      {
         return state_;
      }
private:
      DataNode::State state_;
};


/****************************************************************/
/* CLASS NAME :  DataCompare                                    */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/



class DataCompare
{
public:
   DataCompare(){;}
   ~DataCompare(){;}
   int equal(DataNode* element, DataNode* to){
      if(!strcmp(element->label_, to->label_))
         return 1;
      return 0;
   }
   int compare(DataNode*, DataNode*) {return 1;}
   void display(DataNode* data) {}

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

