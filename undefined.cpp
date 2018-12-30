/*
 * undefined.cpp
 *
 *  Created on: Nov 20, 2018
 *      Author: prl
 */

#include <iostream>

int main (int argc, char **argv) {
  int undefined;
  std::cout << "undefined: " << undefined << std::endl;

  int* ptr{ nullptr };
  std::cout << "ptr: " << *ptr << std::endl;
}
