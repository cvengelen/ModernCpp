/*
 * undefined.cpp
 *
 *  Created on: Nov 20, 2018
 *      Author: prl
 */

#include <iostream>

int main (__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv) {
  int undefined;
  std::cout << "undefined: " << undefined << std::endl;

  int* ptr{ nullptr };
  std::cout << "ptr: " << *ptr << std::endl;
}
