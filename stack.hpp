/*  Tim Strawbridge
 *  CS 23001
 *  4/6/15
 *  Stack, Part 2
 */

#ifndef STACK_HPP
#define STACK_HPP

#include "string.hpp"
#include <iostream>
#include <cassert>

/*Template for Stack project*/

//node class template
template <typename T>
class Node{
public:

  //ENSURES default constructor
  Node() : data(), next(0) {};

  //ENSURES constructor for node containing data
  Node(const T& storage) : data(storage), next(0) {};

  //ENSURES storage of variable "data"
  T data;

  //ENSURES pointer to next element in stack
  Node <T> *next;

};


//stack class template
template <typename T>
class Stack{
public:

  //ENSURES default constructor
  Stack() : tos(0) {};

  //ENSURES copy constructor
  Stack(const Stack<T>&);

  //ENSURES destructor
  ~Stack();

  //ENSURES assignment operator
  Stack<T>& operator=(Stack<T>);

  //ENSURES swap of stacks
  void swap(Stack <T>&);

  //ENSURES removal of last item from stack
  T pop();

  //ENSURES insertion of item at top of stack
  void push(const T&);

  //ENSURES test if current stack is empty
  bool isEmpty() const { return tos == 0; };

  //ENSURES overload of == operator for testing
  bool operator==(const Stack<T>&) const;

  //overload of << operator
  friend std::ostream& operator<< (std::ostream& out, const  Stack<T>& rhs){
    
    Node<T> *point = rhs.tos;
    
    if(!rhs.isEmpty()){
      out << point->data;
      while (point -> next != 0){
	point  = point -> next;
	out << point->data;
      }
    
    }

    return out;

  }

private:

  Node<T> *tos;

};


//copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T>& actual){
  
  tos = 0;
  Node<T> *top = actual.tos;
  Node<T> *temp = 0;
  

  //loop while there is data stored at top of stack
  while (top != 0){

    //first data being stored
    if (tos == 0){
      temp = new Node<T>(top->data);
      tos = temp;
    }
    //subsequent data
    else{
      temp->next = new Node<T>(top->data);
      temp = temp->next;
    }

    top = top->next;

  }

}


//destructor
template <typename T>
Stack<T>::~Stack(){
  
  //loops through data stored at top of stack until empty
  while (tos != 0){
    Node<T> *temp = tos;
    tos = tos->next;
    delete temp;
  }

}


//assignment operator
template <typename T>
Stack<T>& Stack<T>::operator= (Stack<T> rhs){
  
  swap(rhs);
  return *this;

}


//swap function
template <typename T>
void Stack<T>::swap(Stack<T>& rhs){

  //t=a, a=b, b=t swap
  Node<T> *temp = tos;
  tos = rhs.tos;
  rhs.tos = temp;

}


//removes last item of data stored from stack
template <typename T>
T Stack<T>::pop(){
  
  //only pop if there is data in top of stack
  assert(tos != 0);

  //result is data stored at top of stack
  T result = tos->data;

  //point to top of stack, go to next item in stack
  Node<T> *temp = tos;
  tos = tos->next;

  //get rid of data stored at top then return
  delete temp;
  return result;

}


//inserts data into top of the stack
template <typename T>
void Stack<T>::push(const T& stored){
  
  //create new node with data passed, put on top, assign pointer to new top
  Node<T> *temp = new Node<T>(stored);
  temp->next = tos;
  tos = temp;

}


//overload of == operator
template <typename T>
bool Stack<T>::operator==(const Stack<T>& right) const{

  Stack<T> lhs(*this);
  Stack<T> rhs(right);

  //when neither stacks are empty, return false if top of stack is a mistmatch
  while ((!lhs.isEmpty()) && (!rhs.isEmpty())){

    if (lhs.pop() != rhs.pop()){
      return false;
    }

  }

  return true;

}



#endif


