#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Sequence.hpp>

enum LProp_CIType
{
  LProp_Inflection,
  LProp_MinCur,
  LProp_MaxCur
};

#include <Standard_Boolean.hpp>

class LProp_CurAndInf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LProp_CurAndInf();

  Standard_EXPORT void AddInflection(const double Param);

  Standard_EXPORT void AddExtCur(const double Param, const bool IsMin);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT double Parameter(const int N) const;

  Standard_EXPORT LProp_CIType Type(const int N) const;

private:
  NCollection_Sequence<double>       theParams;
  NCollection_Sequence<LProp_CIType> theTypes;
};
