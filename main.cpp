#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "calc.hpp"

TEST(Calc, addTwoNumbers) {
  std::string input {"3 +5"};
  EXPECT_EQ(Calc::eval(input), 8);
}

TEST(Calc, addTwoBiggerNumbers) {
  std::string input {"123+ 576"};
  EXPECT_EQ(Calc::eval(input), 699);
}

TEST(Calc, subtractTwoNumbers) {
  std::string input {"5 - 8"};
  EXPECT_EQ(Calc::eval(input), -3);
}

TEST(Calc, subtractTwoBiggerNumbers) {
  std::string input {"5000 - 8"};
  EXPECT_EQ(Calc::eval(input), 4992);
}

TEST(Calc, divideTwoNumbers) {
  std::string input {"8/3"};
  EXPECT_EQ(Calc::eval(input), 2);
}

TEST(Calc, divideTwoBiggerNumbers) {
  std::string input {"1000/103"};
  EXPECT_EQ(Calc::eval(input), 9);
}

TEST(Calc, multiplyTwoNumbers) {
  std::string input {"12 * 13"};
  EXPECT_EQ(Calc::eval(input), 156);
}

TEST(Calc, multiplyTwoBiggerNumbers) {
  std::string input {"120 * 136"};
  EXPECT_EQ(Calc::eval(input), 16320);
}

TEST(Calc, divideByZero) {
  std::string input {"(3+5) / ((8-3) * 0)"};
  EXPECT_THROW(Calc::eval(input), std::runtime_error);
}

TEST(Calc, divideByZeroAgain) {
  std::string input {"(3+5) / (8 / 3 -2 )"};
  EXPECT_THROW(Calc::eval(input), std::runtime_error);
}

TEST(Calc, compoundExpression) {
  std::string input {"3 * 4 + (2-1)"};
  EXPECT_EQ(Calc::eval(input), 13);
}

TEST(Calc, leftAssociative) {
  std::string input {"10/2/2"};
  EXPECT_EQ(Calc::eval(input), 2);
}

TEST(Calc, sameExampleWithParens) {
  std::string input {"10/(2/2)"};
  EXPECT_EQ(Calc::eval(input), 10);
}

TEST(Calc, biggerFormula) {
  std::string input {"(9 - 4)* (3 - 2 + 7 - 2 *3)"};
  EXPECT_EQ(Calc::eval(input), 10);
}

TEST(Calc, gauss) {
  std::string input {};
  for (int i = 1; i < 100; ++i) {
    input.append(std::to_string(i));
    input.push_back('+');
  }
  input.append("100");
  EXPECT_EQ(Calc::eval(input), 5050);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
