#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class Intf_SectionPoint;

class Intf_TangentZone
{
public:
  DEFINE_STANDARD_ALLOC

  int NumberOfPoints() const;

  Standard_EXPORT const Intf_SectionPoint& GetPoint(const int Index) const;

  Standard_EXPORT bool IsEqual(const Intf_TangentZone& Other) const;

  bool operator==(const Intf_TangentZone& Other) const { return IsEqual(Other); }

  Standard_EXPORT bool Contains(const Intf_SectionPoint& ThePI) const;

  void ParamOnFirst(double& paraMin, double& paraMax) const;

  void ParamOnSecond(double& paraMin, double& paraMax) const;

  Standard_EXPORT void InfoFirst(int& segMin, double& paraMin, int& segMax, double& paraMax) const;

  Standard_EXPORT void InfoSecond(int& segMin, double& paraMin, int& segMax, double& paraMax) const;

  Standard_EXPORT bool RangeContains(const Intf_SectionPoint& ThePI) const;

  Standard_EXPORT bool HasCommonRange(const Intf_TangentZone& Other) const;

  Standard_EXPORT Intf_TangentZone();

  Standard_EXPORT void Append(const Intf_SectionPoint& Pi);

  Standard_EXPORT void Append(const Intf_TangentZone& Tzi);

  Standard_EXPORT bool Insert(const Intf_SectionPoint& Pi);

  Standard_EXPORT void PolygonInsert(const Intf_SectionPoint& Pi);

  Standard_EXPORT void InsertBefore(const int Index, const Intf_SectionPoint& Pi);

  Standard_EXPORT void InsertAfter(const int Index, const Intf_SectionPoint& Pi);

  Standard_EXPORT void Dump(const int Indent) const;

private:
  NCollection_Sequence<Intf_SectionPoint> Result;
  double                                  ParamOnFirstMin;
  double                                  ParamOnFirstMax;
  double                                  ParamOnSecondMin;
  double                                  ParamOnSecondMax;
};

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>

inline int Intf_TangentZone::NumberOfPoints() const
{
  return Result.Length();
}

inline void Intf_TangentZone::ParamOnFirst(double& paraMin, double& paraMax) const
{
  paraMin = ParamOnFirstMin;
  paraMax = ParamOnFirstMax;
}

inline void Intf_TangentZone::ParamOnSecond(double& paraMin, double& paraMax) const
{
  paraMin = ParamOnSecondMin;
  paraMax = ParamOnSecondMax;
}
