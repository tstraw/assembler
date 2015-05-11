/*  Tim Strawbridge
 *  CS 23001
 *  4/6/15
 *  Stack, Part 2
 */

#include "string.hpp"
#include "stack.hpp"
#include <fstream>


//prototype free function to convert infix to postfix
void noOutInfToPre(std::ifstream&);
void outInfToPre(std::ifstream&, std::ofstream&);

int main(int argc, char *argv[]){

  //if no output file specified
  if (argc == 2){

    //infix file is second item on command line
    std::ifstream infix(argv[1]);

    noOutInfToPre(infix);

    infix.close();

  }
  else if (argc == 3){

    //infix file is second item on command line
    std::ifstream infix(argv[1]);

    //postfix file is third item
    std::ofstream outputPost(argv[2]);

    if (outputPost.is_open()){
      outInfToPre(infix, outputPost);

      infix.close();
      outputPost.close();
    }
    else{
      std::cerr << "Unable to open output file. Exiting." << std::endl;
    }

  }
  else{
    std::cerr << "Too few or too many arguments on command line. Exiting." << std::endl;
  }

}


//function implementation if no output file specified
void noOutInfToPre(std::ifstream& in){

  //postfix expression
  Stack<String> post;

  String lhs;
  String rhs;
  String oper;

  //stores infix expression
  char expression[5000];
  in.getline(expression, 5000);


  while (!in.eof()){
    //token is now the original expression
    String newExpr = expression;
    std::vector<String> token = newExpr.split(' ');


    int i = 0;

    do{
      
      //if token is end of parenthetical expression
      //push into post with right order
      if ((token[i] == ")")){
	std::cout<<"before pop " <<post <<std::endl;
	rhs = post.pop();
	std::cout<<"rhs popped "<<post<<std::endl;
	oper = post.pop();
	std::cout<<"oper popped " << post <<std::endl;
	lhs = post.pop();
	post.push(lhs + " " + rhs + " " + oper);
      }
      else if (token[i] != "("){
	std::cout<<"post: " << post <<std::endl;
	post.push(token[i]);
      }

      ++i;

    }while(token[i] != ";");

    std::cout << post << std::endl;
    in.getline(expression, 5000);


  }



}


//function implementation for specified output file
void outInfToPre(std::ifstream& in, std::ofstream& out){

  //postfix expression
  Stack<String> post;

  String lhs;
  String rhs;
  String oper;

  //stores infix expression
  char expression[5000];
  in.getline(expression, 5000);

  while (!in.eof()){
    //token is now the original expression
    String stringExp = expression;
    std::vector<String> token = stringExp.split(' ');

    int i = 0;

    do{
      //if token is end of parenthetical expression
      //push into post with right order
      if (token[i] == ")"){
	rhs = post.pop();
	oper = post.pop();
	lhs = post.pop();
	post.push(lhs + " " + rhs + " " + oper);
      }

      else if (token[i] != "("){
	post.push(token[i]);
      }

      ++i;

    } while (token[i] != ";");

    out << post << std::endl;
    in.getline(expression, 5000);

  }


}


