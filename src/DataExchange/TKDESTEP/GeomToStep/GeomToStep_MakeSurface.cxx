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

#include <Geom_BoundedSurface.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SweptSurface.hpp>
#include <GeomToStep_MakeBoundedSurface.hpp>
#include <GeomToStep_MakeElementarySurface.hpp>
#include <GeomToStep_MakeSurface.hpp>
#include <GeomToStep_MakeSweptSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Logical.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <StepGeom_ElementarySurface.hpp>
#include <StepGeom_OffsetSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <StepGeom_SweptSurface.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une Surface de prostep a partir d' une Surface de Geom
//=============================================================================
GeomToStep_MakeSurface::GeomToStep_MakeSurface(const occ::handle<Geom_Surface>& S,
                                               const StepData_Factors&          theLocalFactors)
{
  done = true;
  if (S->IsKind(STANDARD_TYPE(Geom_BoundedSurface)))
  {
    occ::handle<Geom_BoundedSurface> S1 = occ::down_cast<Geom_BoundedSurface>(S);
    GeomToStep_MakeBoundedSurface    MkBoundedS(S1, theLocalFactors);
    theSurface = MkBoundedS.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_ElementarySurface)))
  {
    occ::handle<Geom_ElementarySurface> S1 = occ::down_cast<Geom_ElementarySurface>(S);
    GeomToStep_MakeElementarySurface    MkElementaryS(S1, theLocalFactors);
    theSurface = MkElementaryS.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_SweptSurface)))
  {
    occ::handle<Geom_SweptSurface> S1 = occ::down_cast<Geom_SweptSurface>(S);
    GeomToStep_MakeSweptSurface    MkSwept(S1, theLocalFactors);
    theSurface = MkSwept.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
  {
    occ::handle<Geom_OffsetSurface> S1 = occ::down_cast<Geom_OffsetSurface>(S);
    GeomToStep_MakeSurface          MkBasis(S1->BasisSurface(), theLocalFactors);
    done = MkBasis.IsDone();
    if (!done)
      return;
    occ::handle<StepGeom_OffsetSurface> Surf = new StepGeom_OffsetSurface;
    Surf->Init(new TCollection_HAsciiString(""),
               MkBasis.Value(),
               S1->Offset() / theLocalFactors.LengthFactor(),
               StepData_LFalse);
    theSurface = Surf;
  }
  else
  {
    done = false;
#ifdef OCCT_DEBUG
    std::cout << " unknown type " << S->DynamicType()->Name() << std::endl;
#endif
  }
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_Surface>& GeomToStep_MakeSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSurface::Value() - no result");
  return theSurface;
}
