//
// Rvo class declaration and definition
// Investigate copy/move constructor, return value optimization

#include <iostream>
#include <vector>

class Rvo {
  int m_intVal{ 0 };
  std::vector<int> m_vectorVals;

public:
  Rvo() {
    std::cout << "default constructor" << std::endl;
  }

  Rvo(int intVal, std::initializer_list<int> vectorVals) :
    m_intVal(intVal), m_vectorVals(vectorVals) {
    std::cout << "normal constructor" << std::endl;
  }

  Rvo(const Rvo& rvo) : m_intVal(rvo.getIntVal()), m_vectorVals(rvo.getVectorValsRef()) {
    std::cout << "copy constructor" << std::endl;
  }

  Rvo(Rvo&& rvo) : m_intVal(rvo.getIntVal()), m_vectorVals(rvo.getVectorValsRval()) {
    std::cout << "move constructor" << std::endl;
  }

  ~Rvo() {}

  Rvo& operator=(const Rvo& rvo) {
    std::cout << "copy assignment" << std::endl;
    if (this != &rvo) {
      m_intVal = rvo.getIntVal();
      m_vectorVals = rvo.getVectorValsRef();
    }
    return *this;
  }

  Rvo& operator=(Rvo&& rvo) {
    std::cout << "move assignment" << std::endl;
    if (this != &rvo) {
      m_intVal = rvo.getIntVal();
      m_vectorVals = rvo.getVectorValsRval();
    }
    return *this;
  }

  int getIntVal() const noexcept { return m_intVal; }

  // Get a copy of the vector
  std::vector<int> getVectorValsCopy() const noexcept { return m_vectorVals; }

  // Get a reference to the vector
  const std::vector<int>& getVectorValsRef() const noexcept { return m_vectorVals; }

  // Get a rvalue from the vector, required so that vector applies a move constructor/assignment
  std::vector<int>&& getVectorValsRval() noexcept { return std::move(m_vectorVals); }
};
