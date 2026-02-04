#pragma once


#include <GeomAbs_CurveType.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Standard.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class gp_Sphere;
class gp_Cylinder;
class gp_Cone;
class gp_Lin;

//! This class provides the computation of the contours
//! for quadric surfaces.
class Contap_ContAna
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Contap_ContAna();

  Standard_EXPORT void Perform(const gp_Sphere& S, const gp_Dir& D);

  Standard_EXPORT void Perform(const gp_Sphere& S, const gp_Dir& D, const double Ang);

  Standard_EXPORT void Perform(const gp_Sphere& S, const gp_Pnt& Eye);

  Standard_EXPORT void Perform(const gp_Cylinder& C, const gp_Dir& D);

  Standard_EXPORT void Perform(const gp_Cylinder& C, const gp_Dir& D, const double Ang);

  Standard_EXPORT void Perform(const gp_Cylinder& C, const gp_Pnt& Eye);

  Standard_EXPORT void Perform(const gp_Cone& C, const gp_Dir& D);

  Standard_EXPORT void Perform(const gp_Cone& C, const gp_Dir& D, const double Ang);

  Standard_EXPORT void Perform(const gp_Cone& C, const gp_Pnt& Eye);

  bool IsDone() const;

  int NbContours() const;

  //! Returns GeomAbs_Line or GeomAbs_Circle, when
  //! IsDone() returns True.
  GeomAbs_CurveType TypeContour() const;

  gp_Circ Circle() const;

  Standard_EXPORT gp_Lin Line(const int Index) const;

private:
  bool              done;
  int               nbSol;
  GeomAbs_CurveType typL;
  gp_Pnt            pt1;
  gp_Pnt            pt2;
  gp_Pnt            pt3;
  gp_Pnt            pt4;
  gp_Dir            dir1;
  gp_Dir            dir2;
  gp_Dir            dir3;
  gp_Dir            dir4;
  double            prm;
};
// Created on: 1993-03-04
// Created by: Jacques GOUSSARD
// Copyright (c) 1993-1999 Matra Datavision
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

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>

#include <gp_Lin.hpp>
#include <gp_Circ.hpp>

inline bool Contap_ContAna::IsDone() const
{
  return done;
}

inline int Contap_ContAna::NbContours() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return nbSol;
}

inline GeomAbs_CurveType Contap_ContAna::TypeContour() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (nbSol == 0)
  {
    throw Standard_DomainError();
  }
  return typL;
}

inline gp_Circ Contap_ContAna::Circle() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (typL != GeomAbs_Circle || nbSol == 0)
  {
    throw Standard_DomainError();
  }
  return gp_Circ(gp_Ax2(pt1, dir1, dir2), prm);
}


