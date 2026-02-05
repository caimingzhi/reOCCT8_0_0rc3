#include <MAT2d_BiInt.hpp>

MAT2d_BiInt::MAT2d_BiInt(const int I1, const int I2)
    : i1(I1),
      i2(I2)
{
}

int MAT2d_BiInt::FirstIndex() const
{
  return i1;
}

int MAT2d_BiInt::SecondIndex() const
{
  return i2;
}

void MAT2d_BiInt::FirstIndex(const int I1)
{
  i1 = I1;
}

void MAT2d_BiInt::SecondIndex(const int I2)
{
  i2 = I2;
}

bool MAT2d_BiInt::IsEqual(const MAT2d_BiInt& B) const
{
  return (i1 == B.FirstIndex() && i2 == B.SecondIndex());
}
