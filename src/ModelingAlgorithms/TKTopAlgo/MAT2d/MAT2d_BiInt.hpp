#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_HashUtils.hpp>

//! BiInt is a set of two integers.
class MAT2d_BiInt
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT MAT2d_BiInt(const int I1, const int I2);

  Standard_EXPORT int FirstIndex() const;

  Standard_EXPORT int SecondIndex() const;

  Standard_EXPORT void FirstIndex(const int I1);

  Standard_EXPORT void SecondIndex(const int I2);

  Standard_EXPORT bool IsEqual(const MAT2d_BiInt& B) const;

  bool operator==(const MAT2d_BiInt& B) const { return IsEqual(B); }

private:
  int i1;
  int i2;
};

namespace std
{
template <>
struct hash<MAT2d_BiInt>
{
  size_t operator()(const MAT2d_BiInt& theBiInt) const noexcept
  {
    // Combine two int values into a single hash value.
    int aCombination[2]{theBiInt.FirstIndex(), theBiInt.SecondIndex()};
    return opencascade::hashBytes(aCombination, sizeof(aCombination));
  }
};
} // namespace std

