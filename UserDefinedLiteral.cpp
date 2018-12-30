/*
 * UserDefinedLiteral.cpp
 *  Created on: Nov 19, 2018
 * See: https://en.cppreference.com/w/cpp/language/user_literal
 */

#include <iostream>

class UserDefinedLiteral {
  int m_userDefinedLiteral{0};

public:
  explicit UserDefinedLiteral(unsigned long long val) : m_userDefinedLiteral(val) {}
  int getUserDefinedLiteral() const { return m_userDefinedLiteral; }
};

// Operator to convert value to UserDefinedLiteral object
// Note: parameter must be unsigned long long for converting an integer value
UserDefinedLiteral operator "" _udl(unsigned long long val) {
  return UserDefinedLiteral(val);
}

void printUserDefinedLiteral(const UserDefinedLiteral& userDefinedLiteral) {
  std::cout << "userDefinedLiteral: " << userDefinedLiteral.getUserDefinedLiteral() << std::endl;
}

int main (int argc, char **argv) {
  printUserDefinedLiteral(23_udl);
  return 0;
}
