#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntPolyh_StartPoint.hpp>
#include <NCollection_Sequence.hpp>
class IntPolyh_StartPoint;

class IntPolyh_SectionLine
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPolyh_SectionLine();

  Standard_EXPORT IntPolyh_SectionLine(const int nn);

  IntPolyh_SectionLine(const IntPolyh_SectionLine& theOther) { Copy(theOther); }

  Standard_EXPORT void Init(const int nn);

  Standard_EXPORT const IntPolyh_StartPoint& Value(const int nn) const;

  const IntPolyh_StartPoint& operator[](const int nn) const { return Value(nn); }

  Standard_EXPORT IntPolyh_StartPoint& ChangeValue(const int nn);

  IntPolyh_StartPoint& operator[](const int nn) { return ChangeValue(nn); }

  Standard_EXPORT IntPolyh_SectionLine& Copy(const IntPolyh_SectionLine& Other);

  IntPolyh_SectionLine& operator=(const IntPolyh_SectionLine& Other) { return Copy(Other); }

  Standard_EXPORT int GetN() const;

  Standard_EXPORT int NbStartPoints() const;

  Standard_EXPORT void IncrementNbStartPoints();

  Standard_EXPORT void Destroy();

  ~IntPolyh_SectionLine() { Destroy(); }

  Standard_EXPORT void Dump() const;

  Standard_EXPORT void Prepend(const IntPolyh_StartPoint& SP);

private:
  NCollection_Sequence<IntPolyh_StartPoint> mySeqOfSPoints;
};
