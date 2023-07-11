This code is a continuation of a Stack Calculator I built in my Week 6 Tutorial where I wrote a program that evaluated an arithmetic expression given in postfix notation, like 3 5 +, instead of more familiar infix notation, like 3 + 5.  In this part of my assignment, I completed the construction of a calculator for infix expressions by writing a function to convert an infix arithmetical expression into a postfix one.  

Here is the important part of the calc.hpp header file:
namespace Calc {
// type is either '+', '-', '*', '/' for the operators or 'n' to indicate a number
// in the case of a number val holds its integer value.
struct Token {
  char type {};
  int val {};
};

std::vector<Token> tokenise(const std::string&);
std::vector<Token> infixToPostfix(const std::vector<Token>&);
int evalPostfix(const std::vector<Token>&);
int eval(const std::string&);

}     // namespace Calc

The function tokenise takes a string of an arithmetic expression like "(3+5) * 2 - 3" and outputs a vector of Tokens.  A Token has 2 parts. The first part is a char that represents the token type.  It is one of the operators '+', '-', '*', '/' or 'n' to indicate that the token holds a number.  In the case the Token holds a number, the second member variable, val, holds the integer value of the number.  In the case of an operator the val member variable can be ignored (and is left as 0).  As an example, on input "(3+5) * 2 - 3" the tokeniser function would output { {'(', 0}, {'n', 3}, {'+', 0}, {'n', 5}, {')', 0}, {'*',0}, {'n', 2}, {'-', 0}, {'n', 3} }.  

The function I implemented is infixToPostfix.  This function takes a vector of tokens derived from an infix expression and converts it into a vector of tokens in postfix notation which will be described how to do below.  For now, I will continue to review the functions in calc.hpp.  The function evalPostfix was provided for me.  This function is essentially from my Week 6 Tutorial and evaluates an arithmetic expression in postfix notation.  The function eval puts all the parts together to evaluate an infix expression: 

int Calc::eval(const std::string& expression) {
  std::vector<Token> tokens = tokenise(expression);
  std::vector<Token> postfix = infixToPostfix(tokens);
  return evalPostfix(postfix);
}

Implementation:
I implemented the infixToPostfix function in the file calc.cpp.  There is a famous algorithm to go from infix notation to postfix notation due to Dijkstra called the shunting yard algorithm.  The algorithm is described here with a pseudocode for it.  See also the wikipedia article : https://en.wikipedia.org/wiki/Shunting_yard_algorithm.  Note that the wikipedia article talks about a more general situation where the expression can also contain functions like sinx.  This does not apply in this scenario.

In order to correctly convert an infix expression into a postfix one, it is important to note the precedence of operations.  '+' and '-' have the equal precedence, and '*' and '/' have equal precedence which is greater than that of '+' and '-'.  I needed to somehow represent the precedence of all these operators in my program.  

vector of Tokens output;
vector of Tokens operatorStack;
for each Token t in the input
    if the token is a number, push it back to the output;
    else if the token is '(', push it back to the operatorStack;
    else if the token is ')', pop tokens off of the operatorStack
        and push them back onto output until you reach '('.  Pop
        '(' off the operatorStack too;
    else:
        As long as there operators on operatorStack that are not '(':
            if the operator at the top of the operatorStack 
            has >= precedence to t, push it onto output and pop it 
            off of the operatorStack.
        Push back t to the operatorStack.
// At this point we have finished iterating over the input
reverse operatorStack and append it to the end of output. 
