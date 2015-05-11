/*  Tim Strawbridge
 *  CS 23001
 *  4/13/15
 *  Stack, Part 3
 */

#include "string.hpp"
#include "stack.hpp"
#include <fstream>


//prototype free function to convert infix to postfix
void noOutInfToPre(std::ifstream&);
void outInfToPre(std::ifstream&, std::ofstream&);
void noOutEvaluate(std::ifstream&);
void outEvaluate(std::ifstream&, std::ofstream&);

int main(int argc, char *argv[]){

  String infixString;

  //if no output file specified
  if (argc == 2){

    //infix file is second item on command line
    std::ifstream infix(argv[1]);

    while (infix >> infixString){

      std::cout << "Infix expression: " << infixString << std::endl;

      //outputs postfix expression
      noOutInfToPre(infix);

      //outputs assembly
      noOutEvaluate(infix);

    }

    infix.close();

  }
  else if (argc == 3){

    //infix file is second item on command line
    std::ifstream infix(argv[1]);

    //postfix file is third item
    std::ofstream outputPost(argv[2]);

    while (infix >> infixString){

      if (outputPost.is_open()){
	outputPost << "Infix expression: " << infixString << std::endl;

	outInfToPre(infix, outputPost);

	outEvaluate(infix, outputPost);
	
	infix.close();
	outputPost.close();

      }
      else{
	std::cerr << "Unable to open output file. Exiting." << std::endl;
      }

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
      if (token[i] == ")"){
	if (!post.isEmpty()){
	  rhs = post.pop();
	}
	if (!post.isEmpty()){
	  oper = post.pop();
	}
	if (!post.isEmpty()){
	  lhs = post.pop();
	}
	post.push(lhs + " " + rhs + " " + oper);
      }
      else if ((token[i] != "("){
	  post.push(token[i]);
	}

	++i;

	}while (token[i] != ";");

      std::cout << "Postfix expression: " << post << std::endl;
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

      out << "Postfix expression: " << post << std::endl;
      in.getline(expression, 5000);

    }


  }


  //function implementation to convert to assembler language
  void noOutEvaluate(std::ifstream& in){

    Stack<String> assem;

    String lhs;
    String rhs;
    String oper;
    int tempNum = 1;

    //stores infix expression
    char expression[5000];
    in.getline(expression, 5000);

    while (!in.eof()){
      //token is now the original expression
      String stringExp = expression;
      std::vector<String> token = stringExp.split(' ');

      int i = 0;
      
      if ((token[i] != "+") && (token[i] != "-") && (token[i] != "*") && (token[i] != "/") && (token[i] != "(")){
	assem.push(token[i]);
	++i;
      }
      else if (token[i] == ";"){

      }


    }

  }


  //function implementation to convert to assembler language with ofstream output
  void outEvaluate(std::ifstream& in, std::ofstream& out){



  }
