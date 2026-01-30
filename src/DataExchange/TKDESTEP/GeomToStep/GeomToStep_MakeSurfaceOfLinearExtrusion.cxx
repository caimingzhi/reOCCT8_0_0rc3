// Created on: 1993-06-17
// Created by: Martine LANGLOIS
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

#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <GeomToStep_MakeCurve.hpp>
#include <GeomToStep_MakeSurfaceOfLinearExtrusion.hpp>
#include <GeomToStep_MakeVector.hpp>
#include <gp_Vec.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une surface_of_linear_extrusion de prostep a partir d' une
// SurfaceOfLinearExtrusion de Geom
//=============================================================================
GeomToStep_MakeSurfaceOfLinearExtrusion::GeomToStep_MakeSurfaceOfLinearExtrusion(
  const occ::handle<Geom_SurfaceOfLinearExtrusion>& S,
  const StepData_Factors&                           theLocalFactors)
{
  occ::handle<StepGeom_SurfaceOfLinearExtrusion> Surf;
  occ::handle<StepGeom_Curve>                    aSweptCurve;
  occ::handle<StepGeom_Vector>                   aExtrusionAxis;

  GeomToStep_MakeCurve  MkCurve(S->BasisCurve(), theLocalFactors);
  GeomToStep_MakeVector MkVector(gp_Vec(S->Direction()), theLocalFactors);

  aSweptCurve    = MkCurve.Value();
  aExtrusionAxis = MkVector.Value();

  Surf                                       = new StepGeom_SurfaceOfLinearExtrusion;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Surf->Init(name, aSweptCurve, aExtrusionAxis);
  theSurfaceOfLinearExtrusion = Surf;
  done                        = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_SurfaceOfLinearExtrusion>& GeomToStep_MakeSurfaceOfLinearExtrusion::
  Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSurfaceOfLinearExtrusion::Value() - no result");
  return theSurfaceOfLinearExtrusion;
}
