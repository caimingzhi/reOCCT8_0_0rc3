#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class Intf_SectionPoint;

//! Describes a zone of tangence between polygons or
//! polyhedra as a sequence of points of intersection.
class Intf_TangentZone
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns number of SectionPoint in this TangentZone.
  int NumberOfPoints() const;

  //! Gives the SectionPoint of address <Index> in the
  //! TangentZone.
  Standard_EXPORT const Intf_SectionPoint& GetPoint(const int Index) const;

  //! Compares two TangentZones.
  Standard_EXPORT bool IsEqual(const Intf_TangentZone& Other) const;

  bool operator==(const Intf_TangentZone& Other) const { return IsEqual(Other); }

  //! Checks if <ThePI> is in TangentZone.
  Standard_EXPORT bool Contains(const Intf_SectionPoint& ThePI) const;

  //! Gives the parameter range of the TangentZone on the first
  //! argument of the Interference. (Usable only for polygon)
  void ParamOnFirst(double& paraMin, double& paraMax) const;

  //! Gives the parameter range of the TangentZone on the second
  //! argument of the Interference. (Usable only for polygon)
  void ParamOnSecond(double& paraMin, double& paraMax) const;

  //! Gives information about the first argument of the
  //! Interference. (Usable only for polygon)
  Standard_EXPORT void InfoFirst(int& segMin, double& paraMin, int& segMax, double& paraMax) const;

  //! Gives information about the second argument of the
  //! Interference. (Usable only for polygon)
  Standard_EXPORT void InfoSecond(int& segMin, double& paraMin, int& segMax, double& paraMax) const;

  //! Returns True if <ThePI> is in the parameter range of the
  //! TangentZone.
  Standard_EXPORT bool RangeContains(const Intf_SectionPoint& ThePI) const;

  //! Returns True if the TangentZone <Other> has a common part
  //! with <me>.
  Standard_EXPORT bool HasCommonRange(const Intf_TangentZone& Other) const;

  //! Builds an empty tangent zone.
  Standard_EXPORT Intf_TangentZone();

  //! Adds a SectionPoint to the TangentZone.
  Standard_EXPORT void Append(const Intf_SectionPoint& Pi);

  //! Adds the TangentZone <Tzi> to <me>.
  Standard_EXPORT void Append(const Intf_TangentZone& Tzi);

  //! Inserts a SectionPoint in the TangentZone.
  Standard_EXPORT bool Insert(const Intf_SectionPoint& Pi);

  //! Inserts a point in the polygonal TangentZone.
  Standard_EXPORT void PolygonInsert(const Intf_SectionPoint& Pi);

  //! Inserts a SectionPoint before <Index> in the TangentZone.
  Standard_EXPORT void InsertBefore(const int Index, const Intf_SectionPoint& Pi);

  //! Inserts a SectionPoint after <Index> in the TangentZone.
  Standard_EXPORT void InsertAfter(const int Index, const Intf_SectionPoint& Pi);

  Standard_EXPORT void Dump(const int Indent) const;

private:
  NCollection_Sequence<Intf_SectionPoint> Result;
  double                                  ParamOnFirstMin;
  double                                  ParamOnFirstMax;
  double                                  ParamOnSecondMin;
  double                                  ParamOnSecondMax;
};
// Created on: 1991-06-25
// Created by: Didier PIFFAULT
// Copyright (c) 1991-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <Intf_SectionPoint.hpp>
#include <NCollection_Sequence.hpp>

//=======================================================================
// function : NumberOfPoint
// purpose  : Return the points number of the tangent zone.
//=======================================================================

inline int Intf_TangentZone::NumberOfPoints() const
{
  return Result.Length();
}

//=================================================================================================

inline void Intf_TangentZone::ParamOnFirst(double& paraMin, double& paraMax) const
{
  paraMin = ParamOnFirstMin;
  paraMax = ParamOnFirstMax;
}

//=================================================================================================

inline void Intf_TangentZone::ParamOnSecond(double& paraMin, double& paraMax) const
{
  paraMin = ParamOnSecondMin;
  paraMax = ParamOnSecondMax;
}


