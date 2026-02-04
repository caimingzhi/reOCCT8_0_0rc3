#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IntPatch_PrmPrmIntersection_T3Bits
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_PrmPrmIntersection_T3Bits(const int size);

  Standard_EXPORT ~IntPatch_PrmPrmIntersection_T3Bits();

  void Add(const int t) { p[t >> 5] |= (1 << (((unsigned int)t) & 31)); }

  int Val(const int t) const { return (p[t >> 5] & (1 << (((unsigned int)t) & 31))); }

  void Raz(const int t) { p[t >> 5] &= ~(1 << (((unsigned int)t) & 31)); }

  Standard_EXPORT void ResetAnd();

  Standard_EXPORT int And(IntPatch_PrmPrmIntersection_T3Bits& Oth, int& indiceprecedent);

private:
  int* p;
  int  Isize;
};

