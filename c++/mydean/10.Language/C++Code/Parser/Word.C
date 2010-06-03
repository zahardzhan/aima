/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Word.C                                              */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 17:49:18 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <Word.H>
#include <Variable.H>
#include <iostream.h>
#include <XDString.H>

Word::Word(Word& word)
{
   name_ = new XDString(*word.name_);
   theCase_ = word.theCase_;
   type_ = new XDString(*word.type_);
   root_ = new XDString(*word.root_);
   sub_cat_ = word.sub_cat_;
   if(word.tense_)
      tense_ = new XDString(*word.tense_);
}

Word& Word::operator=(Word& word)
{
   // since there are different words, it is first necessary
   // to check wether the types exist before they are deleted 
   if(name_)
      delete name_;
   if(type_)
      delete type_;
   if(root_)
      delete root_;
   if(tense_)
      delete tense_;

   name_ = new XDString(*word.name_);
   theCase_ = word.theCase_;
   type_ = new XDString(*word.type_);
   root_ = new XDString(*word.root_);
   sub_cat_ = word.sub_cat_;
   return *this;
}

Word::Word(XDString *name, Variable* theCase, XDString* type, XDString* root)
{
   name_ = new XDString(*name);
   theCase_ = theCase;
   type_ = new XDString(*type);
   root_ = new XDString(*root);
   sub_cat_ = Word::NONE;       // default for noun, article type
}

Word::Word(XDString* name, Variable* theCase, XDString* type, XDString* tense,
           Word::SubCat sub_cat, XDString* root)
{
   name_ = new XDString(*name);
   theCase_ = theCase;
   type_ = new XDString(*type);
   tense_ = new XDString(*tense);

   root_ = new XDString(*root);
   sub_cat_ = sub_cat;
}

Word::~Word()
{
   delete name_;
   delete theCase_;
   delete root_;
}

XDString* Word::word()
{
   return name_;
}

XDString* Word::root()
{
   return root_;
}

XDString* Word::type()
{
   return type_;
}

Variable* Word::theCase()
{
   return theCase_;
}

Word::SubCat Word::sub_cat()
{
   return sub_cat_;
}

void WordSearch::setType(XDString type)
{
   type_ = new XDString(type);
}


int WordSearch::compare(Word* word, Word* to)
{
   return 0;
}

int WordSearch::equal(Word* word, Word* to)
{
   if(*(word->word()) == *(to->word()))
      {
         *to = *word;
         return 1;
      }
   return 0;
}

void WordSearch::display(Word* word)
{
   cout << "(Word  " << *word->name_ << " ) ";
   if(word->type_)
      cout << " (type " << *word->type_ << " ) ";
      
   if(word->root_) 
      cout << "( root " << *word->root_ << " ) ";
   if(word->tense_)
      cout << "( tense " <<*word->tense_ << " ) ";
   if(word->theCase_)
   cout << "(case " << *word->theCase_->binding() << " )";
   cout << endl;
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

