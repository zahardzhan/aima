/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Lexicon.C                                           */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 03:03:32 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Lexicon.H"
#include <XDString.H>
#include <SortedList.H>
#include <Word.H>
#include <Variable.H>
#include <XDString.H>



/****************************************************************/
/*                                                              */
/* Function Name: Lexicon::Lexicon()                            */
/* Parameters: <none>                                           */
/* Returns: <none>                                              */
/* Effects:                                                     */
/*   Creates the Lexicon database.                              */
/****************************************************************/



Lexicon::Lexicon()
{
   search_ = new WordSearch;    // creates the search class
   list_ = new SortedList<Word, WordSearch>(search_); // creates teh database
   // the variables used by the words specifying their case, 
   // the symbols are identical to the ones found in the Lisp text.
   // p is plural and a number is the person.
   // as is explained in Variable.H a variable with the same symbol
   // specified twice is a constant.
   Variable* p3 = new Variable(new XDString("3p"),new XDString("3p"));
   Variable* s3 = new Variable(new XDString("3s"),new XDString("3s"));
   Variable* past = new Variable(new XDString("past"),new XDString("past"));
   // this creates an actual variable that is used for case
   Variable* x = new Variable(new XDString("x"));
   // this creates a word and adds it to the database.
   list_->insert(new Word(new XDString("dog"),s3,new XDString("noun"),new XDString("dog")));
   list_->insert(new Word(new XDString("dogs"),p3,new XDString("noun"),new XDString("dog")));
   list_->insert(new Word(new XDString("pizza"),s3,new XDString("noun"),new XDString("pizza")));
   // these two insertions add a verbs to the database. In addition to the
   // case, the root, and the word, must be added the case(x) and wether
   // the verb has a noun phrase.
   list_->insert(new Word(new XDString("saw"),x,new XDString("verb"),new XDString("past"),Word::NOUN_PHRASE,new XDString("see")));
   list_->insert(new Word(new XDString("barks"),s3,new XDString("verb"),new XDString("present"),Word::NONE,new XDString("bark")));
   list_->insert(new Word(new XDString("the"),s3,new XDString("article"), new XDString("the")));
};


/****************************************************************/
/*                                                              */
/* Function Name: lookup                                        */
/* Parameters: Word* word the string word                       */
/* XDString* tpe : for what case to search the word             */
/* Returns:                                                     */
/*  1 - success and word now points to the word in the database */
/*  0 - word is unchanged, word with type tpe not found         */
/* Effects:                                                     */
/*  Searches in the database for a word matching word, and      */
/* having type tpe. That it is looking for that type is         */
/* specified in the search class.                               */
/****************************************************************/

int  Lexicon::lookup(Word* word, XDString* tpe)
{
   search_->setType(*tpe);
   if(list_->search(word) == 0) return 0;
   return 1;
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

