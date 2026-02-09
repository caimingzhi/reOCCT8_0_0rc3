#pragma once

#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <Precision.hpp>
#include <Select3D_SensitiveEntity.hpp>

class SelectMgr_SortCriterion
{
public:
  occ::handle<Select3D_SensitiveEntity> Entity;
  gp_Pnt                                Point;
  NCollection_Vec3<float>               Normal;
  double                                Depth;

  double MinDist;
  double Tolerance;
  int    SelectionPriority;
  int    DisplayPriority;
  int    ZLayerPosition;
  int    NbOwnerMatches;

  bool IsPreferPriority;

public:
  DEFINE_STANDARD_ALLOC

  SelectMgr_SortCriterion()
      : Depth(0.0),
        MinDist(0.0),
        Tolerance(0.0),
        SelectionPriority(0),
        DisplayPriority(0),
        ZLayerPosition(0),
        NbOwnerMatches(0),
        IsPreferPriority(false)
  {
  }

  bool IsCloserDepth(const SelectMgr_SortCriterion& theOther) const
  {

    if (ZLayerPosition != theOther.ZLayerPosition)
    {
      return ZLayerPosition > theOther.ZLayerPosition;
    }

    if (std::abs(Depth - theOther.Depth) > Tolerance + theOther.Tolerance)
    {
      return Depth < theOther.Depth;
    }

    double aCos = 1.0;
    if (Normal.Modulus() > 0 && theOther.Normal.Modulus() > 0)
    {
      gp_Dir aNormal(Normal.x(), Normal.y(), Normal.z());
      gp_Dir anOtherNormal(theOther.Normal.x(), theOther.Normal.y(), theOther.Normal.z());
      aCos = std::abs(std::cos(aNormal.Angle(anOtherNormal)));
    }

    double aDepth       = Depth - Tolerance;
    double anOtherDepth = theOther.Depth - theOther.Tolerance;

    if (std::abs(aDepth - anOtherDepth) > Precision::Confusion())
    {
      if ((aCos > 0.5 && std::abs(Tolerance - theOther.Tolerance) < Precision::Confusion())
          || std::abs(aCos - 1.0) < Precision::Confusion())
      {
        return aDepth < anOtherDepth;
      }
    }

    if (SelectionPriority > theOther.SelectionPriority)
    {
      return true;
    }

    if (DisplayPriority > theOther.DisplayPriority)
    {
      return true;
    }

    return SelectionPriority == theOther.SelectionPriority && MinDist < theOther.MinDist;
  }

  bool IsHigherPriority(const SelectMgr_SortCriterion& theOther) const
  {

    if (ZLayerPosition != theOther.ZLayerPosition)
    {
      return ZLayerPosition > theOther.ZLayerPosition;
    }

    if (SelectionPriority != theOther.SelectionPriority)
    {
      return SelectionPriority > theOther.SelectionPriority;
    }

    if (DisplayPriority != theOther.DisplayPriority)
    {
      return DisplayPriority > theOther.DisplayPriority;
    }

    if (std::abs(Depth - theOther.Depth) <= Precision::Confusion())
    {
      return MinDist < theOther.MinDist;
    }

    return Depth < theOther.Depth;
  }
};
