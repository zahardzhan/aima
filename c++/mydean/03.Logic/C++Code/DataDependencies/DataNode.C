/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: DataNode.C                                          */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun  9 02:40:11 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <DataNode.H>
#include <string.h>
#include <DataList.H>





/****************************************************************/
/*                                                              */
/* Function Name: DataNode                                      */
/* Parameters:                                                  */
/* char* label : the symbol                                     */
/* DataNode::State state : the initial state, which defaults to */
/*                         0                                    */
/* Returns: <none>                                              */
/* Effects: creates a data node                                 */
/*                                                              */
/****************************************************************/



DataNode::DataNode(char* label, DataNode::State state)
{
   label_ = new char[strlen(label)];
   strcpy(label_, label);
   justifications_ =  new SortedDataList;
   justificands_ = new SortedDataList;
   state_ = state;
}

DataNode::~DataNode(){
   delete [] label_;
}



/****************************************************************/
/*                                                              */
/* Function Name: addJustification                              */
/* Parameters:                                                  */
/*  DataNode* node : the justification to add                   */
/* Returns: <none>                                              */
/* Effects: adds node to the justifications, then tells mode    */
/* to add this to its justificands. Finally it preforms an      */
/* update on the entire graph starting at this node.            */
/*                                                              */
/****************************************************************/


void DataNode::addJustification(DataNode* node)
{
   justifications_->insert(node);
   node->addJustificand(this);
   update();
}

void DataNode::addJustificand(DataNode* node)
{
   justificands_->insert(node);
}


/****************************************************************/
/*                                                              */
/* Function Name: removeJustification(DataNode* node)           */
/* Parameters: DataNode* node : the justification to remove     */
/* Returns: <none>                                              */
/* Effects: removes the mentioned justification, passes the     */
/* message to node to remove this from its justificands and     */
/* then preforms an update on the graph                         */
/*                                                              */
/****************************************************************/


void DataNode::removeJustification(DataNode* node)
{
   justifications_->remove(node);
   node->removeJustificand(this);
   update();
}

/****************************************************************/
/*                                                              */
/* Function Name: update                                        */
/* Parameters: <none>                                           */
/* Returns: <none>                                              */
/* Effects: first calls visit which visits all reachable nodes  */
/* and then calls revise which revises the states of the nodes  */
/*                                                              */
/****************************************************************/


void DataNode::update()
{
   visit();
   revise();
}

/****************************************************************/
/*                                                              */
/* Function Name: visit                                         */
/* Parameters: <none>                                           */
/* Returns: <none>                                              */
/* Effects: checks wether the current node is visited, and if   */
/* not changes its state to visited, and then visits all of its */
/* justificands. Each justificand in turn will have this        */
/* function called and accordingly repeat the process.          */
/*                                                              */
/****************************************************************/

void DataNode::visit()
{
   if (state_ != DataNode::VISITED)
      {
         state_ = DataNode::VISITED;
          justificands_->visit();
      }
return;
  
}

/****************************************************************/
/*                                                              */
/* Function Name: revise()                                      */
/* Parameters:<none>                                            */
/* Returns: <none>                                              */
/* Effects: First attempts to update all of the justifications, */
/*          and if the net result is that the state of the      */
/* justifications is different of the current state, then       */
/* the current state is changed and all of its justificands     */
/* are passed the revise message. Otherwise nothing takes       */
/* place and the function returns.                              */
/****************************************************************/


void DataNode::revise()
{
   if((justifications_->update() == DataNode::IN)
      && (state_ != DataNode::IN))
      {
         state_ = DataNode::IN;
         justificands_->revise();
      }
   else if ((justifications_->update() == DataNode::OUT) 
            && (state_ != DataNode::OUT))
      {
         state_ = DataNode::OUT;
         justificands_->revise();
      }
   else
      return;
}
/****************************************************************/
/*                                                              */
/* Function Name: update                                        */
/* Parameters: DataNode::State& state                           */
/* Returns: <none>                                              */
/* Effects: This function is called SortedDataList to check     */
/* wether all the justifications are in or not. What this does  */
/* is if the state_ is OUT then the state of all of the         */
/* justifications is out, otherwise do nothing                  */
/*                                                              */
/****************************************************************/


DataNode::State DataNode::update(DataNode::State& state)
{
  
   if(( state == IN) && (state_ == OUT))
      {
         state = state_;
         return state_;
      }
   return state;
}
void DataNode::removeJustificand(DataNode* node)
{
   justificands_->remove(node);
}




      

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

