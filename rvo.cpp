//
// Investigate copy/move constructor, return value optimization
//

#include <iostream>
#include <initializer_list>
#include <algorithm>

#include "rvo.h"

Rvo returnRvoWithRvo() {
	Rvo rvo(10, {1, 2, 3, 4, 5});
	std::cout << "rvo: " << rvo.getIntVal() << ", vector size: " << rvo.getVectorValsRef().size() << std::endl;
	return rvo;
}

Rvo returnRvoWithMove() {
	Rvo rvo(11, {1, 2, 3, 4, 5});
	std::cout << "rvo: " << rvo.getIntVal() << ", vector size: " << rvo.getVectorValsRef().size() << std::endl;
	return std::move(rvo);
}

int main (int argc, char **argv) {
  Rvo rvo1(1, {1, 2, 3});
  std::cout << "rvo1: " << rvo1.getIntVal() << ", vector size: " << rvo1.getVectorValsRef().size();
  if (rvo1.getVectorValsRef().size() > 0) {
    std::cout << ", values: ";
    std::for_each(rvo1.getVectorValsRef().begin(), rvo1.getVectorValsRef().end(), [](int val){ std::cout << val << " "; });
  }
  std::cout << std::endl << std::endl;

  Rvo rvo2(rvo1);
  std::cout << "rvo2: " << rvo2.getIntVal() << ", vector size: " << rvo2.getVectorValsRef().size() << std::endl << std::endl;

  Rvo rvo3(Rvo(3, {2, 3, 4}));
  std::cout << "rvo3: " << rvo3.getIntVal() << ", vector size: " << rvo3.getVectorValsRef().size() << std::endl << std::endl;

  Rvo rvo4(std::move(rvo3));
  std::cout << "rvo3: " << rvo3.getIntVal() << ", vector size: " << rvo3.getVectorValsRef().size() << std::endl;
  std::cout << "rvo4: " << rvo4.getIntVal() << ", vector size: " << rvo4.getVectorValsRef().size() << std::endl << std::endl;

  Rvo rvo5;
  rvo5 = rvo4;
  std::cout << "rvo5: " << rvo5.getIntVal() << ", vector size: " << rvo5.getVectorValsRef().size() << std::endl << std::endl;

  rvo5 = std::move(rvo4);
  std::cout << "rvo4: " << rvo4.getIntVal() << ", vector size: " << rvo4.getVectorValsRef().size() << std::endl;
  std::cout << "rvo5: " << rvo5.getIntVal() << ", vector size: " << rvo5.getVectorValsRef().size() << std::endl << std::endl;

  Rvo rvo10 = returnRvoWithRvo();
  std::cout << "rvo10 with RVO: " << rvo10.getIntVal() << ", vector size: " << rvo10.getVectorValsRef().size() << std::endl << std::endl;

  Rvo rvo11 = returnRvoWithMove();
  std::cout << "rvo11 with Move: " << rvo11.getIntVal() << ", vector size: " << rvo11.getVectorValsRef().size() << std::endl << std::endl;
}
