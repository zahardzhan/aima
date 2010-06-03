/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Grammar.C                                           */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 03:30:44 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

  

#include <Grammar.H>
#include <Stack.H>
#include <Lexicon.H>
#include <XDString.H>
#include <Variable.H>
#include <State.H>
#include <Word.H>

NounPhrase::NounPhrase(Lexicon* lexicon, Stack<Word,WordSearch> *words, 
                       Variable* theCase)
{
   noun_ = new Noun(lexicon, words, theCase);
   article_ = new Article(lexicon,words, theCase);
   words_ = words;
   case_ = theCase;
}

NounPhrase::~NounPhrase()
{
   delete noun_;
   delete article_;
}


/****************************************************************/
/*                                                              */
/* Function Name: makeTransition                                */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  State* the next state                                       */
/*  0 - > no further transitions can be made from this state    */
/* Effects:                                                     */
/*  Returns the next state that can be reached from this state. */
/* A state is returned provided there is a transition that can  */
/* be made. As all the states are predetermined, determination  */
/* of whether a state has been visited or not is made by        */
/* checking the marked flag of the state. The first state       */
/* returned is the article state, and the second state the      */
/* noun state                                                   */
/****************************************************************/


State* NounPhrase::makeTransition()
{
   if(article_->isMarked() == State::NOT_MARKED) // has the article state been 
      {                                          // returned

         return article_;       // no so return it
      }
   else if(noun_->isMarked() == State::NOT_MARKED) // has the noun transition
                                                   // been made
      {
         return noun_;          // no so return it
      }
   return 0;                    // no further transitions to be made
}

void NounPhrase::display()
{
   cout << "( Noun phrase ";
   article_->display();
   noun_->display();
   cout << " ) ";
}

Article::Article(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable* theCase)
{
   lexicon_ = lexicon;
   case_ = theCase;
   words_ = words;
}

Article::~Article()
{
   delete word_;
}
void Article::display()
{
   WordSearch disp;
   disp.display(word_);
}


/****************************************************************/
/*                                                              */
/* Function Name:Article::makeTransition                        */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  0 - no further transitions can be made                      */
/* Effects:                                                     */
/*   Removes a word from the stack of words and checks in       */
/* the lexicon to determine if that word is an article. If it   */
/* is an article, and the case of article matches the case      */
/* of the word provided by the lexicon then the word is not     */
/* pushed onto the stack of remaining words, and 0 is returned  */
/* otherwise the word is pushed back on and 0 is returned. A    */
/* special note should be made about the case, as the case is   */
/* a common variable to both the noun and article, if the       */
/* case is set here, then the noun will have it set as well,    */
/* so matching of features(namely) case can take place.         */
/*                                                              */
/****************************************************************/


State* Article::makeTransition()
{
   word_ = words_->pop();       // get the next word from the stack of 
                                // remaining words to be parsed
   if(lexicon_->lookup(word_,new XDString("article"))) // check that the word
                                                       // is an article
      {
         if(match(case_, word_->theCase())) // do the cases match   
            {
               return 0;
            };
      }
   words_->push(word_);         // either the word was not an article,
                                // or the cases do not match so put the 
                                // word back on the stack of words that
                                // need to be parsed
   return 0;
}

Noun::Noun(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable* theCase)
{
   case_ = theCase;
   words_ = words;
   lexicon_ = lexicon;
}

Noun::~Noun()
{
   ;
}

void Noun::display()
{
   cout << " ( " << endl;
   WordSearch disp;
   disp.display(word_);
   cout << " ) " << endl;
}
/****************************************************************/
/*                                                              */
/* Function Name:Noun::makeTransition                           */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  0 - no further transitions can be made                      */
/* Effects:                                                     */
/*   Removes a word from the stack of words and checks in       */
/* the lexicon to determine if that word is an noun. If it      */
/* is an noun, and the case of noun matches the case            */
/* of the word provided by the lexicon then the word is not     */
/* pushed onto the stack of remaining words, and 0 is returned  */
/* otherwise the word is pushed back on and 0 is returned       */
/*                                                              */
/****************************************************************/

State* Noun::makeTransition()
{
   word_ = words_->pop();
 
   if(lexicon_->lookup(word_,new XDString("noun")))
      {
         if(match(case_,word_->theCase())) 
            {
               return 0;
            }
       } 
       words_->push(word_);
       return 0;
}

VerbPhrase::VerbPhrase(Lexicon* lexicon, Stack<Word,WordSearch> *words,
                       Variable* theCase, Variable* verb_form)
{
   case_ = theCase;
   lexicon_ = lexicon;
   words_ = words;
   Variable* v = new Variable(new XDString("v")); // this variable 
                                                  // represents the verb form
   verb_ = new Verb(lexicon,words_, theCase, v);
}

VerbPhrase::~VerbPhrase()
{
   delete verb_;
}
void VerbPhrase::display()
{
   cout << "( Verb Phrase ";
   verb_->display();
   cout << " ) ";
}

/****************************************************************/
/*                                                              */
/* Function Name: makeTransition                                */
/* Parameters: <noun>                                           */
/* Returns: State* which is a verb or 0, there are no further   */
/* transitions to be made                                       */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/



State* VerbPhrase::makeTransition()
{
  if(verb_->isMarked() == State::NOT_MARKED) 
     return verb_;
  return 0;
}

/****************************************************************/
/*                                                              */
/* Function Name: Verb::Verb                                    */
/* Parameters:                                                  */
/*  Variable* theCase : the case of the sentence                */
/*  Variable* verb_form : the verb form of the sentence         */
/* Returns: <noun>                                              */
/* Effects: creates a verb state                                */
/*                                                              */
/****************************************************************/



Verb::Verb(Lexicon* lexicon, Stack<Word,WordSearch> *words,
           Variable* theCase, Variable* verb_form)
{
   case_ = theCase;
   words_ = words;
   lexicon_ = lexicon;
   verb_form_ = verb_form;
   Variable* a = new Variable(new XDString("a"));
   result_ = -1;
   Variable* b = new Variable(new XDString("b"));
   np_ = new NounPhrase(lexicon, words,b);
}

Verb::~Verb()
{
   ;
}

/****************************************************************/
/*                                                              */
/* Function Name: makeTransition                                */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  State* : can be 0 i.e. no further transitions, or a noun    */
/*  phrase.                                                     */
/* Effects:                                                     */
/*   verifies that the next word is in the stack, and depending */
/* on the kind of the verb returns a noun phrase or 0 indicating*/
/* that there are no further transitions to be made.            */
/*   If the word is not a verb, then the word is pushed back    */
/* onto the stack and 0 is returned, indicating no further      */
/* transitions can be made from this state.                     */
/****************************************************************/

State* Verb::makeTransition()
{  
   if(result_ == -1)            // has the word been retrieved from the  
                                // from the lexicon
      {                         // -1 means no so get it from the lexicon
         word_ = words_->pop();
         result_ = lexicon_->lookup(word_, new XDString("verb"));
         if(result_)
            result_ = match(case_, word_->theCase());
      }
   if (result_)                 // was the word a verb of the correct case?
      {
         if(!(word_->sub_cat())) // does the verb have a sub_cat?
            {
               np_ = 0;
               return 0;
            }
         // has the np been returned already?
         else if (np_->isMarked() == State::NOT_MARKED) 
            {
               return np_;      // no so return it
            } 
         else
            {
               return 0;        // nothing left to return
            }
      }
   else                         // wrong case, or word type so return 0
      {                         // and put the word back on the stack of 
                                // words to be manipulated
         words_->push(word_);
         return 0;
      };
}

void Verb::display()
{
   WordSearch disp;
   disp.display(word_);
   if(np_) 
      {
         np_->display();
      }
}

Sentence::Sentence(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable* cse)
{
   case_= cse;
   np_ = new NounPhrase(lexicon, words, case_);
   vp_ = new VerbPhrase(lexicon, words, case_, new Variable(new XDString("c"),
                                                             new XDString("c")));
}

Sentence::~Sentence()
{
   delete np_;
   delete vp_;
}


/****************************************************************/
/*                                                              */
/* Function Name: makeTransition                                */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  State* the next state                                       */
/*  0 - > no further transitions can be made from this state    */
/* Effects:                                                     */
/*  Returns the next state that can be reached from this state. */
/* A state is returned provided there is a transition that can  */
/* be made. As all the states are predetermined, determination  */
/* of whether a state has been visited or not is made by        */
/* checking the marked flag of the state. The first state       */
/* returned is the article state, and the second state the      */
/* noun state                                                   */
/****************************************************************/

State* Sentence::makeTransition()
{
   if(np_->isMarked() == State::NOT_MARKED) 
      {
         return np_;
      }
   else if(vp_->isMarked() == State::NOT_MARKED)
      {
         return vp_;
      }
   else
      {
         return 0;
      };
}

void Sentence::display()
{
   cout << " ( Sentence ";
   np_->display();
   vp_->display();
   cout << " ) ";
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

