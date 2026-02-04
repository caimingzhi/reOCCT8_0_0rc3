#pragma once


#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <Precision.hpp>
#include <Select3D_SensitiveEntity.hpp>

//! This class provides data and criterion for sorting candidate
//! entities in the process of interactive selection by mouse click
class SelectMgr_SortCriterion
{
public:
  occ::handle<Select3D_SensitiveEntity> Entity; //!< detected entity
  gp_Pnt                                Point;  //!< 3D point
  NCollection_Vec3<float>               Normal; //!< surface normal or 0 vector if undefined
  double                                Depth;  //!< distance from the view plane to the entity
                                                // clang-format off
  double      MinDist;           //!< distance from the clicked point to the entity on the view plane
  double      Tolerance;         //!< tolerance used for selecting candidates
  int   SelectionPriority; //!< selection priority
  int   DisplayPriority;   //!< display priority
  int   ZLayerPosition;    //!< ZLayer rendering order index, stronger than a depth
  int   NbOwnerMatches;    //!< overall number of entities collected for the same owner
                                                // clang-format on
  bool IsPreferPriority; //!< flag to signal comparison to be done over priority

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
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

  //! Compare with another item by depth, priority and minDist.
  bool IsCloserDepth(const SelectMgr_SortCriterion& theOther) const
  {
    // the object within different ZLayer groups can not be compared by depth
    if (ZLayerPosition != theOther.ZLayerPosition)
    {
      return ZLayerPosition > theOther.ZLayerPosition;
    }

    // closest object is selected if their depths are not equal within tolerance
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
    // Comparison depths taking into account tolerances occurs when the surfaces are parallel
    // or have the same sensitivity and the angle between them is less than 60 degrees.
    if (std::abs(aDepth - anOtherDepth) > Precision::Confusion())
    {
      if ((aCos > 0.5 && std::abs(Tolerance - theOther.Tolerance) < Precision::Confusion())
          || std::abs(aCos - 1.0) < Precision::Confusion())
      {
        return aDepth < anOtherDepth;
      }
    }

    // if two objects have similar depth, select the one with higher priority
    if (SelectionPriority > theOther.SelectionPriority)
    {
      return true;
    }

    if (DisplayPriority > theOther.DisplayPriority)
    {
      return true;
    }

    // if priorities are equal, one closest to the mouse
    return SelectionPriority == theOther.SelectionPriority && MinDist < theOther.MinDist;
  }

  //! Compare with another item using old logic (OCCT version <= 6.3.1) with priority considered
  //! preceding depth.
  bool IsHigherPriority(const SelectMgr_SortCriterion& theOther) const
  {
    // the object within different ZLayer groups can not be compared by depth
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

    // if (Abs (Depth - theOther.Depth) <= (Tolerance + theOther.Tolerance))
    if (std::abs(Depth - theOther.Depth) <= Precision::Confusion())
    {
      return MinDist < theOther.MinDist;
    }

    return Depth < theOther.Depth;
  }
};

