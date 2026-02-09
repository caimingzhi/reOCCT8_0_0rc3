#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class Intf_SectionPoint;

class Intf_SectionLine
{
public:
  DEFINE_STANDARD_ALLOC

  int NumberOfPoints() const;

  Standard_EXPORT const Intf_SectionPoint& GetPoint(const int Index) const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT bool Contains(const Intf_SectionPoint& ThePI) const;

  Standard_EXPORT int IsEnd(const Intf_SectionPoint& ThePI) const;

  Standard_EXPORT bool IsEqual(const Intf_SectionLine& Other) const;

  bool operator==(const Intf_SectionLine& Other) const { return IsEqual(Other); }

  Standard_EXPORT Intf_SectionLine();

  Standard_EXPORT Intf_SectionLine(const Intf_SectionLine& Other);

  Intf_SectionLine& operator=(const Intf_SectionLine& theOther)
  {

    myPoints = theOther.myPoints;
    return *this;
  }

  Standard_EXPORT void Append(const Intf_SectionPoint& Pi);

  Standard_EXPORT void Append(Intf_SectionLine& LS);

  Standard_EXPORT void Prepend(const Intf_SectionPoint& Pi);

  Standard_EXPORT void Prepend(Intf_SectionLine& LS);

  Standard_EXPORT void Reverse();

  Standard_EXPORT void Close();

  Standard_EXPORT void Dump(const int Indent) const;

private:
  NCollection_Sequence<Intf_SectionPoint> myPoints;
  bool                                    closed;
};

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>

inline int Intf_SectionLine::NumberOfPoints() const
{
  return myPoints.Length();
}
