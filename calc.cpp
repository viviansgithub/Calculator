#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stack>
#include "calc.hpp"


std::vector<Calc::Token> Calc::infixToPostfix(const std::vector<Token>& input) {
  std::vector<Token> output;
  std::vector<Token> operatorStack;
  std::map<char, int> precedence {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

  for (const Token& t : input) {
    if (t.type == 'n') {
      output.push_back(t);
    } else if (t.type == '(') {
      operatorStack.push_back(t);
    } else if (t.type == ')') {
      while (!operatorStack.empty() && operatorStack.back().type != '(') {
        output.push_back(operatorStack.back());
        operatorStack.pop_back();
      }
      if (!operatorStack.empty() && operatorStack.back().type == '(') {
        operatorStack.pop_back();
      } else {
        // Handle mismatched parentheses error
        throw std::runtime_error("Mismatched parentheses");
      }
    } else {
      while (!operatorStack.empty() && operatorStack.back().type != '(' &&
             precedence[operatorStack.back().type] >= precedence[t.type]) {
        output.push_back(operatorStack.back());
        operatorStack.pop_back();
      }
      operatorStack.push_back(t);
    }
  }

  while (!operatorStack.empty()) {
    if (operatorStack.back().type == '(') {
      // Handle mismatched parentheses error
      throw std::runtime_error("Mismatched parentheses");
    }
    output.push_back(operatorStack.back());
    operatorStack.pop_back();
  }

  return output;
}

int Calc::evalPostfix(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
    return 0;
    }
    std::vector<int> stack;
    for (Token t : tokens) {
    if (t.type == 'n') {
        stack.push_back(t.val);
    } else {
        int val = 0;
        if (t.type == '+') {
            val = stack.back() + *(stack.end()-2);
        } else if (t.type == '*') {
            val = stack.back() * *(stack.end()-2);
        } else if (t.type == '-') {
            val = *(stack.end()-2) - stack.back();
        } else if (t.type == '/') {
            if (stack.back() == 0) {
                throw std::runtime_error("divide by zero");
            }
            val = *(stack.end()-2) / stack.back();
        } else {
            std::cout << "invalid token\n";
        }
        stack.pop_back();
        stack.pop_back();
        stack.push_back(val);
    }
    }
    return stack.back();
}

std::vector<Calc::Token> Calc::tokenise(const std::string& expression) {
    const std::vector<char> symbols = {'+', '-', '*', '/', '(', ')'};
    std::vector<Token> tokens {};
    for (std::size_t i =0; i < expression.size(); ++i) {
    const char c = expression[i];
    // check if c is one of '+', '-', '*', '/', '(', ')'
    if (std::find(symbols.begin(), symbols.end(), c) != symbols.end()) {
        tokens.push_back({c});
    } else if (isdigit(c)) {
      // process multiple digit integers
        std::string num {c};
        while (i + 1 < expression.size() && isdigit(expression[i + 1])) {
        ++i;
        num.push_back(expression[i]);
        }
        tokens.push_back({'n', std::stoi(num)});
    }
    }
    return tokens;
}

int Calc::eval(const std::string& expression) {
    std::vector<Token> tokens = tokenise(expression);
    std::vector<Token> postfix = infixToPostfix(tokens);
    return evalPostfix(postfix);
}

