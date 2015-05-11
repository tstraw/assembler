/*  Tim Strawbridge
 *  CS 23001
 *  3/2/15
 *  String, Part 2
 */

#include "string.hpp"

/*Function implementation of functions prototyped in String.hpp*/


//default constructor
String::String(){

  Capacity = DEFAULT_STRING_CAPACITY;
  s = new char[Capacity];
  s[0] = '\0';

}

//initializes String to some char
String::String(char myChar){

  Capacity = DEFAULT_STRING_CAPACITY;
  s = new char[Capacity];
  s[0] = myChar;
  s[1] = '\0';


}


//initializes String to an array composed of chars
String::String(const char* myChar){

  Capacity = DEFAULT_STRING_CAPACITY;
  int i = 0;
  s = new char[Capacity];

  while (myChar[i] != 0){
    s[i] = myChar[i];
    ++i;
  }

  s[i] = '\0';

}


//initializes String to a char array with a user specified size
String::String(int n, const char* myChar){

  Capacity = n;
  s = new char[Capacity];
  int i = 0;

  while (myChar[i] != 0){
    s[i] = myChar[i];
    ++i;
  }

  s[i] = '\0';

}


//initializes String to some capacity n
String::String(int n){

  Capacity = n;
  s = new char[Capacity];
  s[0] = '\0';

}


//copy constructor
String::String(const String& rhs){

  Capacity = rhs.capacity();
  s = new char[Capacity];

  //loop to assign each value to its place in corresponding string
  for (int i = 0; i < Capacity; ++i){
    s[i] = rhs.s[i];
  }

}


//destructor
String::~String(){

  delete[] s;

}


//assignment operator overload
String& String::operator=(String rhs){

  //if the two strings are already equal, return the string
  if (s == rhs.s){
    return *this;
  }

  //if they are not equal make a new String equal to rhs and return it
  Capacity = rhs.Capacity;
  s = new char[Capacity];

  for (int i = 0; i < Capacity; ++i){
    s[i] = rhs.s[i];
  }

  return *this;

}


//swaps two Strings
void String::swap(String& rhs){

  char *tempArray = s;
  s = rhs.s;
  rhs.s = tempArray;

  int tempCap = Capacity;
  Capacity = rhs.Capacity;
  rhs.Capacity = tempCap;

}


//resets capacity, preserves string members
void String::resetCapacity(int n){

  char *tempArray = new char[n];
  int i = 0;

  //loop to preserve string while keeping string
  while (i < n){
    tempArray[i] = s[i];
    ++i;
  }

  tempArray[i] = '\0';

  Capacity = n;
  delete[] s;
  s = tempArray;

}


//overloaded [] operator to return ith digit(non-constant)
char& String::operator[](int loc){

  return s[loc];

}


//overloaded [] operator to return ith digit(constant)
char String::operator[](int loc) const{

  return s[loc];

}


//method for capacity
int String::capacity() const{

  int capacity = Capacity;
  return capacity;

}


//method for length
int String::length() const{

  int length = 0;

  //breaks loop when null character reached, until then increases length
  for (int i = 0; i < DEFAULT_STRING_CAPACITY; ++i){

    if (s[i] == '\0'){
      break;
    }

    ++length;

  }

  return length;

}


//finds a sub-string in a String
String String::subStr(int startAt, int endAt) const{

  String result;
  int pos = startAt;

  //loop to fill array from start to end and set end to null char
  while (pos <= endAt){
    result.s[pos - startAt] = s[pos];
    result.s[endAt - startAt + 1] = '\0';
    ++pos;
  }

  return result;

}


//finds a char in a String
int String::findChar(int start, char lookFor) const{

  //temp is the substring from start to end of string
  bool found = false;
  int loc = 0;
  int endLoc = (*this).length() - 1;

  //for loop that checks for loc and sets loc if found
  for (int i = start; i < endLoc; ++i){

    if (s[i] == lookFor){
      loc = i;
      found = true;
    }

  }

  if (found){
    return loc;
  }
  else{
    return -1;
  }

}


//finds the number of times a substring occurs in a string
int String::findStr(int start, const String lookFor) const{

  int timesFound = 0;
  int strLength = (*this).length();

  //begin if length of string being searched for is >= the string being sought
  if (strLength >= lookFor.length()){

    for (int i = start, j = 0; i < strLength; ++i, j = 0){

      //increments position of lookFor when two strings have equal values 
      //and j isn't "longer" than the string being sought
      while ((s[i + j] == lookFor[j]) && (j <= lookFor.length())){

	++j;

	//record string being found and start search from end of sought string
	if (j == lookFor.length()){
	  ++timesFound;
	  i = i + j;
	}

      }

    }

  }

  return timesFound;

}


//splits a string at given char
std::vector<String> String::split(char myChar) const{

  std::vector <String> result;
  String temp;
  int length = (*this).length();

  int startAt = 0;
  int endAt = 0;


  for (int i = 0; i <= length; ++i){

    //gets ending location
    if ((s[i] != myChar) && (s[i] != '\0')) {
      ++endAt;
    }

    else{

      //subsequent strings
      if (startAt > 0){

	if (s[startAt] == myChar){
	  ++startAt;
	}
	else if (s[endAt] == myChar){
	  ++endAt;
	}

	//temp is subStr, store temp in vector
	temp = (*this).subStr(startAt, endAt);
	endAt = i;
	startAt = endAt;
	result.push_back(temp);
      }

      //initial string
      else{
	temp = (*this).subStr(startAt, endAt - 1);
	startAt = endAt;
	result.push_back(temp);
      }

    }

  }

  result.push_back(temp);
  return result;

}


//checks if two Strings are equal
bool String::operator==(const String& rhs) const{

  int stringLen = (*this).length();
  int inputLen = rhs.length();

  if (stringLen == inputLen){

    //loop that goes over each value stored in array and returns false if mismatch is found
    for (int i = 0; i < rhs.length(); ++i){

      if (rhs.s[i] != s[i]){
	return false;
      }

    }

    return true;

  }

  return false;

}


//checks if one String is less than the other
bool String::operator<(const String& rhs) const{

  int loc = 0;

  //do while loop that advances if two locations are equal
  //returns a bool value if not
  do{

    if (s[loc] < rhs.s[loc]){
      return true;
    }
    else if (s[loc] == rhs.s[loc]) {
      ++loc;
    }
    else if (s[loc] > rhs.s[loc]){
      return false;
    }

  } while ((s[loc] != '\0') && (rhs.s[loc] != '\0'));

  //if end of rhs is reached and no value has been returned
  //this is longer than rhs, meaning it is false
  if (rhs.s[loc] == '\0'){
    return false;
  }

  return true;

}


//overload of addition operator to add one String to another
String String::operator+(const String& rhs) const{

  int addLength = (*this).length();
  String result = s;

  //while loop to append rhs to result

  int i = 0;

  while ((rhs.s[i] != '\0') && (i + addLength < DEFAULT_STRING_CAPACITY)){
    result.s[addLength + i] = rhs.s[i];
    ++i;
  }

  result.s[i + addLength] = '\0';
  return result;

}


//overload of output operator
std::ostream& operator<<(std::ostream& out, const String& myString){

  out << myString.s;
  return out;

}


//overload of input operator
std::istream& operator>>(std::istream& in, String& myString){

  int i = 0;
  char chr;
  in.get(chr);
  char tempArray[DEFAULT_STRING_CAPACITY] = { 0 };

  //do while loop that reads a character, inserts it into array and reads next digit
  do{
    tempArray[i] = chr;
    in.get(chr);
    ++i;
  } while ((chr != (';')) && (!in.eof()));

  //sets the string passed by reference equal to the array
  tempArray[i] = 0;
  myString = tempArray;

  return in;

}


//overloaded addition operator to add char array to string
String operator+(const char myChar[], const String& myString){

  //determines length of char array
  int lengthOfChar = 0;
  for (int i = 0; myChar[i] != '\0'; ++i){
    ++lengthOfChar;
  }

  //sets the result capacity to the capacity of the string + myChar
  String result = myString;

  //while loop to append myChar to result

  int i = 0;

  while ((result[i] != '\0') && (i + lengthOfChar < DEFAULT_STRING_CAPACITY)){
    result[lengthOfChar + i] = myChar[i];
    ++i;
  }

  result[i + lengthOfChar] = '\0';
  return result;

}


//overloaded addition operator to add char to string
String operator+(char myChar, const String& myString){

  String result = myString;
  int lengthOfString = myString.length();

  //while loop to append char to result
  while ((result[lengthOfString] != '\0') && (lengthOfString + 1 < DEFAULT_STRING_CAPACITY)){
    result[1 + lengthOfString] = myChar;
  }

  result[lengthOfString + 2] = '\0';
  return result;

}


//overloaded equal to operator for char array and String
bool operator==(const char myChar[], const String& myString){

  //determines length of char array
  int lengthOfChar = 0;
  for (int i = 0; myChar[i] != '\0'; ++i){
    ++lengthOfChar;
  }

  //determines length of string
  int lengthOfString = 0;
  for (int i = 0; myString[i] != '\0'; ++i){
    ++lengthOfString;
  }

  if (lengthOfString == lengthOfChar){

    //loop that goes over each value stored in array
    //returns false if mismatch is found
    for (int i = 0; i < DEFAULT_STRING_CAPACITY; ++i){

      if (myChar[i] != myString[i]){
	return false;
      }

      return true;

    }

  }

  return false;

}


//overloaded equal to operator for char and String
bool operator==(char myChar, const String& myString){

  //returns true the first character of the string is equal to the char
  if ((myChar == myString[0]) && (myString.length() == 2)){
    return true;
  }

  return false;

}


//overload of less than operator for char array and String
bool operator<(const char myChar[], const String& myString){

  int loc = 0;

  //do while loop that advances if two locations are equal
  //returns a bool value if not
  do{

    if (myChar[loc] < myString[loc]){
      return true;
    }
    else if (myChar[loc] == myString[loc]) {
      ++loc;
    }
    else if (myChar[loc] > myString[loc]){
      return false;
    }

  } while ((myChar[loc] != '\0') && (myString[loc] != '\0'));

  //if end of myString is reached and no value has been returned
  //myChar is longer than myString, meaning it is false
  if (myString[loc] == '\0'){
    return false;
  }

  return true;

}


//overload of less than operator for char and String
bool operator<(char myChar, const String& myString){

  //returns true the first character of the string is less than the char
  if ((myChar < myString[0]) && (myString.length() == 2)){
    return true;
  }

  return false;

}


//overload of less than or equal to operator for two Strings
bool operator<=(const String& lhs, const String& rhs){

  int loc = 0;
  bool flag = false;

  //do while loop that advances if two locations are equal
  //returns a bool value if not
  for (int i = 0; (lhs[i] != '\0') && (rhs[i] != '\0'); ++i){

    if (lhs[i] < rhs[i]){
      return true;
    }
    else if (lhs[i] == rhs[i]) {
      flag = true;
    }
    else if (lhs[i] > rhs[i]){
      return false;
    }

    ++loc;

  }

  //if end of rhs is reached and no value has been returned
  //lhs is longer than rhs, meaning it is false
  if ((flag) && (rhs[loc] == '\0')){
    return false;
  }

  return true;
}


//overload of not equal to operator for two Strings
bool operator!=(const String& lhs, const String& rhs){

  //for loop that goes over both strings
  //returns true if one is not equal to the other
  for (int i = 0; ((lhs[i] != '\0') && (rhs[i] != '\0')); ++i){

    if (lhs[i] == rhs[i]){
      return false;
    }

  }

  return true;

}


//overload of greater than or equal to operator for two Strings
bool operator>=(const String& lhs, const String& rhs){

  int loc = 0;
  bool flag = false;

  //do while loop that advances if two locations are equal
  //returns a bool value if not
  for (int i = 0; (lhs[i] != '\0') && (rhs[i] != '\0'); ++i){

    if (lhs[i] > rhs[i]){
      return true;
    }
    else if (lhs[i] == rhs[i]) {
      flag = true;
    }
    else if (lhs[i] < rhs[i]){
      return false;
    }

    ++loc;

  }

  //if end of lhs is reached and no value has been returned
  //rhs is longer than lhs, meaning it is false
  if ((flag) && (lhs[loc] == '\0')){
    return false;
  }

  return true;

}


//overload of greater than operator for two Strings
bool operator>(const String& lhs, const String& rhs){

  int loc = 0;

  //do while loop that advances if two locations are equal
  //returns a bool value if not
  do{

    if (lhs[loc] > rhs[loc]){
      return true;
    }
    else if (lhs[loc] == rhs[loc]) {
      ++loc;
    }
    else if (lhs[loc] > rhs[loc]){
      return false;
    }

  } while ((lhs[loc] != '\0') && (rhs[loc] != '\0'));

  //if end of lhs is reached and no value has been returned
  //rhs is longer than lhs, meaning it is false
  if (lhs[loc] == '\0'){
    return false;
  }

  return true;

}


