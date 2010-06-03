/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: cs032082                                            */
/*    FILE: SSString.C                                          */
/*    ASGN: Waitlist                                            */
/*    DATE: Sun Feb 27 13:13:33 1994                            */
/****************************************************************/
#include "XDString.H"
#include "KRUtility.H"
#include <strstream.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
/****************************************************************/
/*                                                              */
/* Function Name: XDString                                      */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*  creates a string of size S_STRING_SIZE                      */
/*                                                              */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


XDString::XDString()
{
  int temp_mem = S_XDString_SIZE + 4 - S_XDString_SIZE%4;
  string_ = new char[temp_mem];
  len_ = S_XDString_SIZE;
}


/****************************************************************/
/*                                                              */
/* Function Name: ~XDString                                     */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/


XDString::~XDString()
{
  delete [] string_;
}

/****************************************************************/
/*                                                              */
/* Function Name: String                                        */
/* Parameters:                                                  */
/*   string                                                     */
/* Returns:                                                     */
/* Effects:                                                     */
/*   copy Constructor                                           */
/****************************************************************/


XDString::XDString(const XDString& string)
{
  string_ = new char [string.len_ + 1];
  len_ = string.len_;
 
  ::strcpy(string_, string.string_);
  len_ = string.len_;
}

/****************************************************************/
/*                                                              */
/* Function Name: XDString                                      */
/* Parameters:                                                  */
/*  string : non-null terminated strnig                         */
/*  length : length of string                                   */
/* Returns:                                                     */
/* Effects:                                                     */
/*  creates a String of len length                              */
/*                                                              */
/****************************************************************/



XDString::XDString(char* string, int length)
{
  int temp =0;
  len_ = length;
  string_ = new char[len_+1];
 
  for (int j = 0; j < len_; j++)	
    string_[j] = '\0';
  strncpy(string_, string, length);

  string_[len_] = '\0';
}

/****************************************************************/
/*                                                              */
/* Function Name: XDString                                      */
/* Parameters:                                                  */
/*  string : null terminated string                             */
/* Returns:                                                     */
/* Effects:                                                     */
/*  creates a String that is null terminated                    */
/****************************************************************/



XDString::XDString(const char* string)
{
  int temp = 0;
  len_ = strlen(string);
 
  string_ = new char[len_+1];
  strcpy(string_, string);
}

 
/****************************************************************/
/*                                                              */
/* Function Name: XDString                                      */
/* Parameters:                                                  */
/*  int length : length of string                               */
/* Returns:                                                     */
/* Effects:                                                     */
/*  creates an XDString of len_ length                          */
/****************************************************************/

XDString::XDString(int length)
{
  int i;
  string_ = new char[length]; // create string_
  
  len_ = length; 
}


/****************************************************************/
/*                                                              */
/* Function Name: operator=                                     */
/* Parameters:                                                  */
/*  String& string:                                             */
/* Returns:                                                     */
/*  new string                                                  */
/* Effects:                                                     */
/*  aXDignment operator                                         */
/****************************************************************/

XDString& XDString::operator=(const XDString& string)
{
  delete [] string_;
  string_ = new char[string.len_];
  len_ = string.len_;
  ::strcpy (string_, string.string_);
  return *this;
}


/****************************************************************/
/*                                                              */
/* Function Name:                                               */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*                                                              */
/****************************************************************/

XDString& XDString::operator=(const char c)
{
   delete [] string_;
   string_ = new char[1];
   len_ = 1;
   string_[0] = c;
   string_[1] = '\0';
   return *this;
}   


/****************************************************************/
/*                                                              */
/* Function Name: operator+                                     */
/* Parameters: XDString& string: string to be added to          */
/* Returns:                                                     */
/*  catted string                                               */
/* Effects:                                                     */
/*   cats two strings by copying them onto a temporary string   */
/* and then createing an XDString and returning the new XDString*/
/****************************************************************/

XDString XDString::operator+(XDString& string)
{

  char *temp; // temporary string
  
  temp = new char[len_ + string.len_];

  
  for (int i = 0; i < len_; i++) // copy string_ to temp
    temp[i] = string_[i];
   
  for (int s = 0; s < string.len_; s++) // string to temp 
    temp[len_ + s] = string[s];

  temp[len_ + s] = '\0'; // set last char to '\0';
  XDString retval(temp); // create a new string

  delete [] temp;

  return retval;
}
    

/****************************************************************/
/*                                                              */
/* Function Name: operator==                                    */
/* Parameters: XDString& string: string to compare with         */
/* Returns: 1 if equal else returns 0                           */
/* Effects:                                                     */
/*  compares the string_'s of both using strcmp and if they     */
/* are equal returns them as a ret_val                          */
/****************************************************************/

int XDString::operator==(XDString& string)
{
 int ret_val = (!(::strcmp(string_, string.string_)));
 return ret_val;
}

/****************************************************************/
/*                                                              */
/* Function Name: oeprator !=                                   */
/* Parameters: XDString& string: string to compare to           */
/* Returns: non-zero value if not equal                         */
/* Effects:                                                     */
/*  compares the string_'s of both using strcmp and returns the */
/* result                                                       */
/****************************************************************/

int XDString::operator!=(XDString& string)
{
  return ::strcmp(string_, string.string_);
}


/****************************************************************/
/*                                                              */
/* Function Name: operator[]                                    */
/* Parameters: int index: which char you want to look at        */
/* Returns:                                                     */
/*   the char indexed by index                                  */
/* Effects:                                                     */
/*   returns the char value of string_[index] or else informst  */
/* the use that he went beyond the end of the string and exits  */
/* the program.                                                 */
/****************************************************************/

char& XDString::operator[](int index)
{
  if (index > len_){
    cerr << "tried to acceXD longer string size" << endl;
    exit(1);
  }

  return string_[index];
}


/****************************************************************/
/*                                                              */
/* Function Name: operator<<                                    */
/* Parameters:                                                  */
/*  ostream& os : ostream operator to manipulate string         */
/*  XDString& stirng: string to be manipulated                  */
/* Returns:                                                     */
/*  ostream& : os used                                          */
/* Effects:                                                     */
/*  allows the ostream to manipulate my user defined XDString   */
/* to manipulate it as a basic type.                            */
/****************************************************************/

ostream& operator<<(ostream& os, XDString& string)
{
  os << string.string_;
  return os;
}


/****************************************************************/
/*                                                              */
/* Function Name: operator>>                                    */
/* Parameters:                                                  */
/*  istream& is : istream operator to manipulate the string     */
/*  XDString& string: string to be manipulate                   */
/* Returns:                                                     */
/*  istream& is: is used                                        */
/* Effects:                                                     */
/*   allows the istream operators to manipulate my user defined */
/* type as if it were a basic type.                             */
/****************************************************************/


istream& operator>>(istream& is, XDString& string)
{
  is >> string.string_;
  return is;
}


/****************************************************************/
/*                                                              */
/* Function Name: insert                                        */
/* Parameters:                                                  */
/*  int : start : where to start from                           */
/*  int : end : where to end                                    */
/*  XDString data: what to insert                               */
/* Returns:                                                     */
/* Effects:                                                     */
/*  Inserts a substring into a string.                          */
/*  set start == 0 to insert at beginning of string             */
/*  set start == -1 to insert at end of string                  */
/*  These values were used so optimize frequently used          */
/* operations. Inserting into the middle was and is leXD        */
/* frequent.                                                    */
/****************************************************************/


void XDString::insert(int start, int end, XDString data)
{
  char *temp;
  temp = new char[len_ + data.len_]; // temporary string

  if (start == 0) { // beginning of string
    strcpy(temp, data.string_);  
    strcat(temp, string_);
    strcpy(string_, temp);
    len_ += data.len_;
    return;
  }

  if (start == -1) { // end of string
    strcpy(temp, string_);
    strcat(temp, data.string_);
    strcpy(string_,temp);
    len_ += data.len_;
    return;
  }

  if ((start >= 0) || (start <= len_)){ // somewhere in the middle of string_
 
    for (int i = 0; i < start; i++)// copy up to start
      temp[i] = string_[i];

    for (int j = 0; j < data.len_; j++) // copy from the data paXDed 
      temp[j + start] = data[j];
    
    for (i = start ; i < len_; i++) // copy remainder of string after end
      temp[data.len_ + i - 1] = string_[i];
    delete [] string_; // delete old string

    string_ = new char[len_ + data.len_]; 
    strcpy(string_, temp); // create copy temp into string
    delete [] temp;
    len_ += data.len_;
    return;
  };

      
}


/****************************************************************/
/*                                                              */
/* Function Name: eatWhiteSpace                                 */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*  removes all white space from the string by looping through  */
/* the string and using iXDpace to determine wether the char    */
/* is a whitespace. If it is not then it is copied to the       */
/* temporary string, else it is not. The temporary string       */
/* is then copied on to the original string.                    */
/****************************************************************/


void XDString::eatWhiteSpace()
{
// variables used
  char *temp = new char[len_]; // temporary string to copy data into
  int j = 0; // length of non-whitespace string

  for ( int i = 0; i < len_; i++){ // loop through to find non-whitespace char
    if (!isspace(string_[i])){  // is a whitespace
      temp[j] = string_[i]; // not so copy to tem
      j++; 
    }
  }
  len_ = j; // lenght of non-whitespaced string
  temp[j] = '\0'; // set last value to null
    strcpy(string_,temp);
  delete [] temp;
}


/****************************************************************/
/*                                                              */
/* Function Name: extract                                       */
/* Parameters:                                                  */
/*   start : where to start extracting from                     */
/*   end : where to end the extraction at                       */
/* to remove first character set end = 0                        */
/* to remove up to last character set start = len               */
/*                                                              */
/* Returns:                                                     */
/*  the extracted string                                        */
/* Effects:                                                     */
/*  removes a string of length end-start from the already       */
/* existing string.                                             */
/*                                                              */
/****************************************************************/



XDString XDString::extract(int start, int end)
{
// variables used
  char* new_string = new char[len_-(end-start+1)]; // new string after extraction
  char* return_string = new char [end-start+1]; // extracted string
  XDString *ret_val; // return string

  ClearOut(return_string, end-start+1); // set all values to null of return_sting

  ClearOut(new_string, len_); // clear all of the new_string

// EXTRACTION

// copy from start in string end-start+1 bytes into the return string  
  strncpy(return_string, &string_[start], end-start+1); 
// set string_[start] = '\0' so you can use sprintf
  string_[start] = '\0';
// print from the start to the first null char, and the from the end to the end
// of string onto new_string
  sprintf(&new_string[0],"%s%s",&string_[0], &string_[end+1]);

  delete [] string_;
  len_ = len_ - (end- start + 1);
  string_ = new char[len_];
  strcpy(string_, new_string); // copy new_string onto the old one.
  
  ret_val = new XDString(return_string);
  return *ret_val;
}
  
  

/****************************************************************/
/*                                                              */
/* Function Name: find                                          */
/* Parameters: char c: character to find                        */
/* Returns: first instance of the character                     */
/* Effects:                                                     */
/*  searches through the string to find the first occurence of  */ 
/* of the character. Returning either the location or -1        */
/****************************************************************/


int XDString::find(char c)
{
  for ( int loc = 0; loc < len_; loc++)	{
    if (string_[loc] == c) return loc; // location when found
  }	

  return -1; // did not find it
}

/****************************************************************/
/*                                                              */
/* Function Name:  int ()                                       */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*  casts a string into an int. Will return a -1 if it could    */
/* not cast all of the int. As such can not cast a string of    */
/* -1 back into an int.                                         */
/****************************************************************/



XDString::operator int()
{
 
  char *buffer = new char[len_];
  ClearOut(buffer, len_);
  int ret_val = 0;
  int i = 0;
  while ((string_[i] <= '9') && (string_[i] >= '0')  && (i < len_)){
    buffer[i] = string_[i];
    i++;
  }
  if  ( i == 0) return -1; // could not convert any part of it

  extract(0,i-1); // extract part to be converted converted

// convert into an integer using istream
  istrstream buf(buffer, i);        
  buf >> ret_val;

  delete [] buffer;
  return ret_val;
}


/****************************************************************/
/*                                                              */
/* Function Name: operator double()                             */
/* Parameters:                                                  */
/* Returns:                                                     */
/* Effects:                                                     */
/*  converts as much  of the string as it can into a double     */
/* If it fails to convert anything then the string length is    */
/* unchanged, otherwise the string length has changed.          */
/* The part that is converted is extracted from the string.     */
/**************************************************************


double XDString::operator double()
{ 
// Variables used
  char *buffer = new char[len_]; // buffer for double to be converted
  ClearOut(buffer,len_); // clear out buffer
  double ret_val = 0; // return vlaue
  int i = 0;
// is the first character a + or a minus sign?
  if((string_[i] == '+') || (string_[i] == '-')) {
    buffer[i] = string_[i]; // put into the start of the buffer
    i++;
  }
// while a char can be converted to a double and the end of the 
// string has not been reached loop through the string putting the chars
// into the buffer
  while ((string_[i] <= '9') && (string_[i] >= '0') 
	   || (string_[i] == '.') && (i < len_)){ 
    
    buffer[i] = string_[i];
    i++;
  }
// convert to double 
  extract(0,i-1); // extract from string_
// use streams to convert
  istrstream buf(buffer, i);
  buf >> ret_val;
  delete [] buffer;
  return ret_val;
}

*/









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

