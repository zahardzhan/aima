#ifndef COMPARE_H
#define COMPARE_H

#include <XDString.H>

class Word;

class WordSearch 
{
   XDString* type_;
public:
   WordSearch()
      {
      }
   ~WordSearch()
      {
      }
   void setType(XDString type);
   int compare(Word* word, Word* to);
   int equal(Word* word, Word* to);
   void display(Word* word);
};

#endif
