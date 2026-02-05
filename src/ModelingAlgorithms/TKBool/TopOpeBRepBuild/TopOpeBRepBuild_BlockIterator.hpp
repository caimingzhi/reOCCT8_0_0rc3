#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

//! Iterator on the elements of a block.
class TopOpeBRepBuild_BlockIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_BlockIterator();

  Standard_EXPORT TopOpeBRepBuild_BlockIterator(const int Lower, const int Upper);

  void Initialize();

  bool More() const;

  void Next();

  int Value() const;

  int Extent() const;

private:
  int myLower;
  int myUpper;
  int myValue;
};

inline void TopOpeBRepBuild_BlockIterator::Initialize()
{
  myValue = myLower;
}

//=================================================================================================

inline bool TopOpeBRepBuild_BlockIterator::More() const
{
  bool b = (myValue <= myUpper);
  return b;
}

//=================================================================================================

inline void TopOpeBRepBuild_BlockIterator::Next()
{
  myValue++;
}

//=================================================================================================

inline int TopOpeBRepBuild_BlockIterator::Value() const
{
  return myValue;
}

//=================================================================================================

inline int TopOpeBRepBuild_BlockIterator::Extent() const
{
  if (myLower != 0)
  {
    int n = myUpper - myLower + 1;
    return n;
  }
  return 0;
}
