/*  Tim Strawbridge
 *  CS 23001
 *  3/16/15
 *  String, Part 4
 */


#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

/*Function prototypes for String project*/

const int DEFAULT_STRING_CAPACITY = 256;

class String {
public:
  //ENSURES default constructor
  String();

  //ENSURES initializes String to some char
  String(char);

  //ENSURES initializes String to an array composed of chars
  String(const char*);

  //ENSURES String of capacity n with initial value
  String(int, const char*);

  //ENSURES creates string of capacity n
  String(int);

  //ENSURES copy constructor
  String(const String&);

  //ENSURES destuctor
  ~String();

  //ENSURES assignment operator overload
  String& operator=(String);

  //ENSURES swaps two Strings
  void swap(String&);

  //ENSURES resets capacity private member, preserves string members
  void resetCapacity(int);

  //ENSURES overloaded [] operator to return ith digit (non-constant)
  char& operator[](int);

  //ENSURES overloaded [] operator to return ith digit (constant)
  char operator[](int) const;

  //ENSURES method for capacity
  int capacity() const;

  //ENSURES method for length
  int length() const;

  //ENSURES finds a sub-string in a String
  String subStr(int, int) const;

  //ENSURES finds a char in a String
  int findChar(int, char) const;

  //ENSURES finds a String in a String
  int findStr(int, const String) const;

  //ENSURES split of string at char
  std::vector<String> split(char) const;

  //ENSURES checks if two Strings are equal
  bool operator==(const String&) const;

  //ENSURES checks if one String is less than the other
  bool operator<(const String&) const;

  //ENSURES overload of addition operator
  String operator+(const String&) const;

  //ENSURES conversion of String to int
  int stringToInt(const String&);

  //ENSURES overload of output method
  friend std::ostream& operator<<(std::ostream&, const String&);

private:
  char *s;
  int Capacity;
};

std::istream& operator>>(std::istream&, String&);

//ENSURES free functions to overload operators
String operator+(const char[], const String&);
String operator+(char, const String&);
bool operator==(const char[], const String&);
bool operator==(char, const String&);
bool operator<(const char[], const String&);
bool operator<(char, const String&);
bool operator<=(const String&, const String&);
bool operator!=(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator>(const String&, const String&);

#endif


