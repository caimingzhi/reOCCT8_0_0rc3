#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <Intf_SectionLine.hpp>
#include <Intf_TangentZone.hpp>
#include <Standard_Boolean.hpp>
class Intf_SectionPoint;
class Intf_SectionLine;
class Intf_TangentZone;

class Intf_Interference
{
public:
  DEFINE_STANDARD_ALLOC

  int NbSectionPoints() const;

  const Intf_SectionPoint& PntValue(const int Index) const;

  int NbSectionLines() const;

  const Intf_SectionLine& LineValue(const int Index) const;

  int NbTangentZones() const;

  const Intf_TangentZone& ZoneValue(const int Index) const;

  double GetTolerance() const;

  Standard_EXPORT bool Contains(const Intf_SectionPoint& ThePnt) const;

  Standard_EXPORT bool Insert(const Intf_TangentZone& TheZone);

  Standard_EXPORT void Insert(const Intf_SectionPoint& pdeb, const Intf_SectionPoint& pfin);

  Standard_EXPORT void Dump() const;

protected:
  Standard_EXPORT Intf_Interference(const bool Self);

  ~Intf_Interference() = default;

  Standard_EXPORT void SelfInterference(const bool Self);

  NCollection_Sequence<Intf_SectionPoint> mySPoins;
  NCollection_Sequence<Intf_SectionLine>  mySLines;
  NCollection_Sequence<Intf_TangentZone>  myTZones;
  bool                                    SelfIntf;
  double                                  Tolerance;
};

inline int Intf_Interference::NbSectionPoints() const
{
  return mySPoins.Length();
}

inline const Intf_SectionPoint& Intf_Interference::PntValue(const int Index) const
{
  return mySPoins(Index);
}

inline int Intf_Interference::NbSectionLines() const
{
  return mySLines.Length();
}

inline const Intf_SectionLine& Intf_Interference::LineValue(const int Index) const
{
  return mySLines(Index);
}

inline int Intf_Interference::NbTangentZones() const
{
  return myTZones.Length();
}

inline const Intf_TangentZone& Intf_Interference::ZoneValue(const int Index) const
{
  return myTZones(Index);
}

inline double Intf_Interference::GetTolerance() const
{
  return Tolerance;
}
