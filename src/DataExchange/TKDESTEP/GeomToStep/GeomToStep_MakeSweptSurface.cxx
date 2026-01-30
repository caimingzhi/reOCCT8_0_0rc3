// Created on: 1993-06-22
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
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_SweptSurface.hpp>
#include <GeomToStep_MakeSurfaceOfLinearExtrusion.hpp>
#include <GeomToStep_MakeSurfaceOfRevolution.hpp>
#include <GeomToStep_MakeSweptSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_SurfaceOfRevolution.hpp>
#include <StepGeom_SweptSurface.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une SweptSurface de prostep a partir d' une
// SweptSurface de Geom
//=============================================================================
GeomToStep_MakeSweptSurface::GeomToStep_MakeSweptSurface(const occ::handle<Geom_SweptSurface>& S,
                                                         const StepData_Factors& theLocalFactors)
{
  done = true;
  if (S->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)))
  {
    occ::handle<Geom_SurfaceOfLinearExtrusion> Sur =
      occ::down_cast<Geom_SurfaceOfLinearExtrusion>(S);
    GeomToStep_MakeSurfaceOfLinearExtrusion MkLinear(Sur, theLocalFactors);
    theSweptSurface = MkLinear.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
  {
    occ::handle<Geom_SurfaceOfRevolution> Sur = occ::down_cast<Geom_SurfaceOfRevolution>(S);
    GeomToStep_MakeSurfaceOfRevolution    MkRevol(Sur, theLocalFactors);
    theSweptSurface = MkRevol.Value();
  }
  else
    done = false;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_SweptSurface>& GeomToStep_MakeSweptSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSweptSurface::Value() - no result");
  return theSweptSurface;
}
