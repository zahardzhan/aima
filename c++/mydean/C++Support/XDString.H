/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: cs032082                                            */
/*    FILE: String.H                                            */
/*    ASGN: Waitlist                                            */
/*    DATE: Sun Feb 27 13:09:29 1994                            */
/****************************************************************/


#ifndef XDString_HEADER
#define XDString_HEADER
#include <iostream.h>

/****************************************************************/
/* CLASS NAME :  XDString                                       */
/*   To simplify string manipulation and at the same time      */
/* not deny me access to the underlying char* which is          */
/* still necessary for most tasks SSString was invented.        */
/* XDString can be created by a variety of way, can be          */
/* assigned to each other or a char*, can be added              */
/* to each other, can be casted to an int or a double,          */
/* removing the int, double, part while still keeping the       */
/* part that can not be casted intact. Characters               */
/* can be found. Sub strings can be extracted and inserted      */
/* at arbitrary points. The XDString can be compared            */
/* The [] operator was overloaded so at to be able to assign    */
/* and examine characters of the string without actually        */
/* accessing the string_. The data members were made            */
/* public because it made more sense to do that than have       */
/* accessor functions that did the same thing.                  */
/****************************************************************/


class XDString {
friend ostream& operator<<(ostream& os, XDString& XDString);
friend istream& operator>>(istream& is, XDString& XDString);
 enum {S_XDString_SIZE = 1000};
public:
  char *string_; // string
  int len_; // len 


  XDString();
  ~XDString();
  XDString(const XDString&);
  XDString(char* XDString, int length);
  XDString(const char* XDString);
  XDString(int length);
  XDString& operator=(const XDString& string);
  XDString& operator=(const char string);
  XDString operator+(XDString& string);
  XDString operator+=(XDString& string);
  XDString operator+(char* string);
  XDString operator+=(char* string);
  operator int();
//  operator double();
  int find(char key);
  XDString extract(int start, int end);
  void  insert(int start, int end, XDString data);
  void eatWhiteSpace();
  int operator==(XDString& string);
  int operator!=(XDString& string);
  char& operator[](int);
    
 
};
  

class StringComp 
{
public:
   StringComp() 
      {;}
   ~StringComp()
      {;}
   int compare(XDString* element, XDString* to)
      {
         return 1;
      }
   int equal(XDString* element, XDString* to)
      {
         return *element == *to;
      }
   void display(XDString* string)
      {
         cout << *string << " ";
      }
};

#endif
