/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Word.H                                              */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 02:54:45 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef WORD_HEADER
#define WORD_HEADER

#include "Compare.H"
#include <Variable.H>
#include <XDString.H>


/****************************************************************/
/* CLASS NAME :  Word                                           */
/*  A word is a symbol in a sentence. A word can be a noun,     */
/* article or a verb. As such the different types of word       */
/* are in one object for simplicity's sake. There are different */
/* constructors for the different identities the words can      */
/* have from - simple symbol, to noun article, and then verb.   */
/* The word is merely an encapsulation over the data members    */
/* and does little.                                             */
/*                                                              */
/****************************************************************/


class Word 
{
   XDString* name_;             // the symbol of the word
   XDString* tense_;            // its tense (relevant for verbs only)
   XDString* root_;             // the root of the symbol
   XDString* type_;             // what type (noun, verb,article)
   Variable* theCase_;          // the case of the word
 public:
   Word(Word& word);            // copy constructor
   Word& operator=(Word& word); // assignment operator
   enum SubCat{ NONE, NOUN_PHRASE}; // wether a word has a sub cat or none
                                    // only relevant if type = "verb"
   // constructor for a word for which we only know the symbol
   // used when parsing the sentence to begin with
   Word(XDString name)
      {
         name_ = new XDString(name);
      }
   // constructor for nouns and articles
   Word(XDString* name, Variable* , XDString*, XDString* root);
   // constructor for verbs, it has parameters for tense, and tense
   Word(XDString *name, Variable* , XDString*, XDString* , SubCat sub_cat, XDString* root);
   // destructor
   ~Word();
   // accessors
   XDString* word();
   XDString* root();
   XDString* type();
   SubCat sub_cat();
   Variable* theCase();
friend class WordSearch;
private:
   Word::SubCat sub_cat_;
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

