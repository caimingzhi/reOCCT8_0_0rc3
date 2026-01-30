// Created on: 1994-09-02
// Created by: Frederic MAUPAS
// Copyright (c) 1994-1999 Matra Datavision
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

#include <Geom2d_Ellipse.hpp>
#include <Geom_Ellipse.hpp>
#include <GeomToStep_MakeAxis2Placement2d.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeEllipse.hpp>
#include <gp_Elips.hpp>
#include <gp_Elips2d.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement2d.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_Ellipse.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d'une ellipse de prostep a partir d'une ellipse 3d de gp
//=============================================================================
GeomToStep_MakeEllipse::GeomToStep_MakeEllipse(const gp_Elips&         E,
                                               const StepData_Factors& theLocalFactors)
{
#include "GeomToStep_MakeEllipse_gen.hpp"
}

//=============================================================================
// Creation d'une ellipse de prostep a partir d'une ellipse de
// Geom
//=============================================================================

GeomToStep_MakeEllipse::GeomToStep_MakeEllipse(const occ::handle<Geom_Ellipse>& Cer,
                                               const StepData_Factors&          theLocalFactors)
{
  gp_Elips E;
  E = Cer->Elips();
#include "GeomToStep_MakeEllipse_gen.hpp"
}

//=============================================================================
// Creation d'une ellipse 2d de prostep a partir d'une ellipse de
// Geom2d
//=============================================================================

GeomToStep_MakeEllipse::GeomToStep_MakeEllipse(const occ::handle<Geom2d_Ellipse>& Cer,
                                               const StepData_Factors&            theLocalFactors)
{
  gp_Elips2d E2d;
  E2d = Cer->Elips2d();

  occ::handle<StepGeom_Ellipse>          EStep = new StepGeom_Ellipse;
  StepGeom_Axis2Placement                Ax2;
  occ::handle<StepGeom_Axis2Placement2d> Ax2Step;
  double                                 majorR, minorR;

  GeomToStep_MakeAxis2Placement2d MkAxis2(E2d.Axis(), theLocalFactors);
  Ax2Step = MkAxis2.Value();
  majorR  = E2d.MajorRadius();
  minorR  = E2d.MinorRadius();
  Ax2.SetValue(Ax2Step);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  EStep->Init(name, Ax2, majorR, minorR);
  theEllipse = EStep;
  done       = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Ellipse>& GeomToStep_MakeEllipse::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeEllipse::Value() - no result");
  return theEllipse;
}
