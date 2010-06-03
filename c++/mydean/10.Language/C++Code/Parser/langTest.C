/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: langTest.C                                          */
/*    ASGN: Final                                               */
/*    DATE: Fri Jun 24 06:49:43 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include <stdlib.h>
#include <Stack.H>
#include <Word.H>
#include <Grammar.H>
#include <Variable.H>
#include <Searches.H>
// main function of the program

int main(int ac, char ** av)
{
   if(ac < 2) {
      cerr << "Usage:   parse the dog saw the pizza" << endl;
      cerr << "         Use your own sentence instead." << endl;
      exit(1);
   }

   WordSearch* comp = new WordSearch;
   // put the words passed as command line arguments on the stack 
   // starting from the end of the parameters
   Stack<Word, WordSearch>* words = new Stack<Word, WordSearch>;
   for(int i = ac-1; i > 0 ; i--) 
      {
         Word* word = new Word(av[i]);
         words->push(word);
      }
   // create the lexicon
   Lexicon* lexicon = new Lexicon;
   // variable for the sentence
   Variable* x = new Variable(new XDString("x"));
   Sentence* sentence = new Sentence(lexicon, words, x);
   Noun* noun = new Noun(lexicon,words, x);
   // perform the dfs
   dfs(sentence, noun );
   // are there any words left in the stack, i.e. not all the words were parsed
   if(words->empty())
      {// no, so signal that by printing the word parse, and the parse tree
         cout << "parse" << endl;
         sentence->display();
         return 0;
      }
   cout << " Illegal parse " << endl;
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
