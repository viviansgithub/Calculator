#ifndef CALC_HPP_
#define CALC_HPP_

#include <vector>
#include <set>
#include <string>

namespace Calc {
struct Token {
  char type {};
  int val {};
};

std::vector<Token> tokenise(const std::string&);
std::vector<Token> infixToPostfix(const std::vector<Token>&);
int evalPostfix(const std::vector<Token>&);
int eval(const std::string&);

}     // namespace Calc

#endif    // CALC_HPP_
