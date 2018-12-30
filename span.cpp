// test GSL span

#include <iostream>
#include <algorithm>
#include <vector>
#include <gsl/gsl>

void printSpan(const gsl::span<const int> arraySpan) {
  std::cout << "for: ";
  for (const auto arrayVal: arraySpan) {
    std::cout << arrayVal << " ";
  }
  std::cout << std::endl;

  std::cout << "for_each: ";
  std::for_each(arraySpan.begin(), arraySpan.end(), [](const int arrayVal){ std::cout << arrayVal << " "; });
  std::cout << std::endl;

  try {
    std::cout << "Invalid dereference: " << arraySpan[5] << std::endl;
  } catch(gsl::fail_fast& gslFailFast) {
    std::cerr << "Fail fast exception: " << gslFailFast.what() << std::endl;
  }
}

void printSpan(const gsl::span<char*> arraySpan) {
  std::cout << "for: ";
  for (const auto arrayVal: arraySpan) {
    std::cout << arrayVal << " ";
  }
  std::cout << std::endl;

  std::cout << "for_each: ";
  std::for_each(arraySpan.begin(), arraySpan.end(), [](const char* arrayVal){ std::cout << arrayVal << " "; });
  std::cout << std::endl;
}

int main (int argc, char **argv) {
  // Convert basic array to span object
  int array[]{ 1, 2, 3, 4 };
  printSpan(array);

  // Convert vector to span object
  std::vector<int> vector{ 5, 6, 7 };
  printSpan(vector);

  // Make span object from argv array: also specify count argc
  gsl::span<char*> argvSpan(argv, argc);
  std::cout << "for_each: ";
  std::for_each(argvSpan.begin(), argvSpan.end(), [](char* argv){ std::cout << argv << " "; });
  std::cout << std::endl;

  // Convert argv array to span object by using span initializer list
  printSpan({ &(*argv), argc });

  return 0;
}
