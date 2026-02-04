#pragma once


#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Real.hpp>
#include <BRep_PointRepresentation.hpp>
#include <NCollection_List.hpp>
#include <TopoDS_TVertex.hpp>
class TopoDS_TShape;

//! The TVertex from BRep inherits from the TVertex
//! from TopoDS. It contains the geometric data.
//!
//! The TVertex contains a 3d point, location and a tolerance.
class BRep_TVertex : public TopoDS_TVertex
{

public:
  Standard_EXPORT BRep_TVertex();

  double Tolerance() const;

  void Tolerance(const double T);

  //! Sets the tolerance to the max of <T> and the
  //! current tolerance.
  void UpdateTolerance(const double T);

  const gp_Pnt& Pnt() const;

  void Pnt(const gp_Pnt& P);

  const NCollection_List<occ::handle<BRep_PointRepresentation>>& Points() const;

  NCollection_List<occ::handle<BRep_PointRepresentation>>& ChangePoints();

  //! Returns a copy of the TShape with no sub-shapes.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_TVertex, TopoDS_TVertex)

private:
  gp_Pnt                                                  myPnt;
  double                                                  myTolerance;
  NCollection_List<occ::handle<BRep_PointRepresentation>> myPoints;
};
// Created on: 1992-08-25
// Created by: Modelistation
// Copyright (c) 1992-1999 Matra Datavision
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

//=================================================================================================

inline double BRep_TVertex::Tolerance() const
{
  return myTolerance;
}

//=================================================================================================

inline void BRep_TVertex::Tolerance(const double T)
{
  myTolerance = T;
}

//=================================================================================================

inline void BRep_TVertex::UpdateTolerance(const double T)
{
  if (T > myTolerance)
    myTolerance = T;
}

//=================================================================================================

inline const gp_Pnt& BRep_TVertex::Pnt() const
{
  return myPnt;
}

//=================================================================================================

inline void BRep_TVertex::Pnt(const gp_Pnt& P)
{
  myPnt = P;
}

//=================================================================================================

inline const NCollection_List<occ::handle<BRep_PointRepresentation>>& BRep_TVertex::Points() const
{
  return myPoints;
}

//=================================================================================================

inline NCollection_List<occ::handle<BRep_PointRepresentation>>& BRep_TVertex::ChangePoints()
{
  return myPoints;
}


