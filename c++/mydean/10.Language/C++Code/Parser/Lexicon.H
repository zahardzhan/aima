/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Lexicon.H                                           */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 02:51:54 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef LEXICON_HEADER
#define LEXICON_HEADER

#include "Compare.H"
#include <XDString.H>
#include <SortedList.H>


/****************************************************************/
/* CLASS NAME :  Lexicon                                        */
/*   This acts in a similar fashion to the Lexicon in the lisp  */
/* implementation. The Lexicon has a sorted list of words,      */
/* and given a key performs a search in the date base for that  */
/* key. The key is the word, and the word type. If the word     */
/* and word type match, then the word in the database is        */
/* returned, otherwise 0 is returned. The Lexicons words are    */
/* predefined at compile time in the default constructor.       */
/*                                                              */
/****************************************************************/



class Lexicon 
{
   WordSearch* search_;         // the comparator used by the word list
   SortedList<Word, WordSearch>* list_; // the words
 public:
   Lexicon(); // creates the list and puts the words in them.
   ~Lexicon();
   int lookup(Word* word, XDString* type); // the search engine
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

