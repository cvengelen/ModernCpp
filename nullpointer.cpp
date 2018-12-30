/*
 * nullpointer.cpp
 *
 *  Created on: Nov 20, 2018
 *      Author: prl
 */

#include <iostream>
#include <gsl/gsl>

struct SomeStruct {
  int m_someStructVal{ 45 };
};

void printSomeStruct(const gsl::not_null<SomeStruct*>& someStructPointer) {
  std::cout << "pointer value: " << someStructPointer->m_someStructVal << std::endl;
}

int main (int argc, char **argv) {
  // gsl::not_null<int*> nullPointer{ nullptr };

  SomeStruct someStruct;
  gsl::not_null<SomeStruct*> someStructNotNullPointer{ &someStruct };
  printSomeStruct(someStructNotNullPointer);

  // printSomeStruct(nullptr);

  SomeStruct* someStructNullPointer{ nullptr };
  printSomeStruct(gsl::make_not_null(someStructNullPointer));
}
