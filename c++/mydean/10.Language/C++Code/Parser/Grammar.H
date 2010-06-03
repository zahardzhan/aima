/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Grammar.H                                           */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 03:27:27 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef GRAMMAR_HEADER
#define GRAMMAR_HEADER

#include "Compare.H"
#include <State.H>
#include <Stack.H>
class NounPhrase;
class VerbPhrase;
#include <Lexicon.H>
#include <Variable.H>
#include <Word.H>
#include <XDString.H>

/****************************************************************/
/* CLASS NAME : Sentence                                        */
/*  A sentence is the initial state of the string that is being */
/* parsed. A string now how to make the transition from         */
/* sentence to NounPhrase and VerbPhrase. Furhtermore a sentence*/
/* has a case which is a variable and is common to the          */
/* noun phase and the verb phrase. A sentence also knows        */
/* how to display itself.                                       */
/*                                                              */
/****************************************************************/



class Sentence : public State
{
   Lexicon* lexicon_;           // The lexicon of the language
   NounPhrase* np_;             // A nounphrase state
   VerbPhrase* vp_;             // verb phrase state
   Variable* case_;             // The case of the sentence
   Stack<Word,WordSearch>* words_; // words in the sentence
public:
   // create a sentence state
   Sentence(Lexicon* lexicon_, Stack<Word,WordSearch>*words, Variable*);
   ~Sentence();
   virtual State* makeTransition(); // make the transition to the next state
   virtual int compare(State* state){return 1;}
   virtual void unMarkTransitions(){;}
   void display();              // display this state and then pass the message
                                // to the next state
};


/****************************************************************/
/* CLASS NAME : Article : derived from State                    */
/*   An article is another state in the search space for the    */
/* parser. An article is defined to be a single word, which     */
/* is specified in the lexicon. The article has a case, which   */
/* must be the same as the case of the noun.                    */
/*                                                              */
/****************************************************************/



class Article : public State 
{
   Lexicon* lexicon_;           // the lexicon of the language
   Variable* case_;             // the case of the sentence
   Word* word_;                 // article 
   Stack<Word, WordSearch> *words_; // the unparse words
public:
   Article(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable* );
   ~Article();
   virtual State* makeTransition(); // make teh next transition which is none
   virtual int compare(State* state){return 1;}
   virtual void unMarkTransitions(){;}
   void display();
};

/****************************************************************/
/* CLASS NAME : Noun : public State                             */
/*   A noun is a terminal state in the search space. There      */
/* are no further derivations possible. A noun is a word that   */
/* is specified in the lexicon. A noun has a case that must     */
/* be the same as the article. A noun state can not make a      */
/* next transition.                                             */
/****************************************************************/


class Noun : public State 
{
   Lexicon* lexicon_;           // lexicon of words
   Variable* case_;             // the case of the noun
   Word* word_;                 // the noune
   Stack<Word,WordSearch>* words_; // the remaining word
public:
   // create a noun state
   Noun(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable* );
   ~Noun();
   // make a transition to the next state, which in this case is none
   virtual State* makeTransition();
   virtual int compare(State* state){return 1;}
   virtual void unMarkTransitions(){;}
   void display();
};


/****************************************************************/
/* CLASS NAME : NounPhrase : public State                       */
/*   A noun phrase is a state object that can be rewritten as   */
/* a noun and an article, the next state transition. The noun   */
/* phrase can generate a noun state, and the article state.     */
/* The NounPhrase has a common case with the noun and article.  */
/* The NounPhrase can display itself and pass the message to the*/
/* next states in the state space.                              */
/*                                                              */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/


class NounPhrase : public State {
   Lexicon* lexicon_;
   Noun* noun_;
   Article* article_;
   Variable* case_;
   Stack<Word,WordSearch> *words_;
public:
   NounPhrase(Lexicon* lexicon_, Stack<Word,WordSearch> *words, Variable*);
   ~NounPhrase();
   virtual State* makeTransition();
    virtual int compare(State* state){return 1;}
   virtual void unMarkTransitions(){;}
   void display();
};


/****************************************************************/
/* CLASS NAME : Verb : public State                             */
/*   A verb is either a terminal state or a state that has      */
/* a next state as well which is a noun phrase. The type of     */
/* verb is determined by the verb itself as specified by the    */
/* lexicon.                                                     */
/*                                                              */
/****************************************************************/


class Verb : public State {
   Lexicon* lexicon_;                  
   Stack<Word,WordSearch> *words_; // the remaining words
   Word* word_;                    // the verb
   Variable* case_;                // the case of the verb
   int result_;                    // an internal flag for making transitions
   Verb* verb_;                    
   NounPhrase* np_;                // the noun phrase of a verb 
   Variable* verb_form_;           // the verb form
public:
   Verb(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable* ,
        Variable* verb_form);
   ~Verb();
   virtual State* makeTransition();
   virtual int compare(State* state){ return 1;}
   virtual void unMarkTransitions(){;}
   void display();
};



/****************************************************************/
/* CLASS NAME : VerbPhrase : public                             */
/*   A VP is a non terminal state. A VP has case. A VP can  be  */
/* rewriten as a verb.                                          */
/*                                                              */
/****************************************************************/


class VerbPhrase : public State {
   Lexicon* lexicon_;
   Stack<Word,WordSearch> *words_;
   Verb* verb_;
   Variable* case_;
public:
   VerbPhrase(Lexicon* lexicon, Stack<Word,WordSearch> *words, Variable *,Variable* );
   ~VerbPhrase();
   virtual State* makeTransition();
   virtual int compare(State* state){ return 1;}
   virtual void unMarkTransitions(){;}
   void display();
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

