// Created on: 1992-10-14
// Created by: Christophe MARION
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

#include <HLRBRep_TheQuadCurvExactInterCSurf.hpp>

#include <gp_Lin.hpp>
#include <HLRBRep_LineTool.hpp>
#include <HLRBRep_Surface.hpp>
#include <HLRBRep_SurfaceTool.hpp>
#include <HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf.hpp>

#include "../../TKGeomAlgo/IntCurveSurface/IntCurveSurface_QuadricCurveExactInterUtils.hpp"

//==================================================================================================

HLRBRep_TheQuadCurvExactInterCSurf::HLRBRep_TheQuadCurvExactInterCSurf(HLRBRep_Surface* S,
                                                                       const gp_Lin&    C)
    : nbpnts(-1),
      nbintv(-1)
{
  IntCurveSurface_QuadricCurveExactInterUtils::PerformIntersection<
    HLRBRep_Surface*,
    HLRBRep_SurfaceTool,
    gp_Lin,
    HLRBRep_LineTool,
    HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf>(S, C, pnts, intv, nbpnts, nbintv);
}

//==================================================================================================

bool HLRBRep_TheQuadCurvExactInterCSurf::IsDone() const
{
  return (nbpnts != -1);
}

//==================================================================================================

int HLRBRep_TheQuadCurvExactInterCSurf::NbRoots() const
{
  return nbpnts;
}

//==================================================================================================

int HLRBRep_TheQuadCurvExactInterCSurf::NbIntervals() const
{
  return nbintv;
}

//==================================================================================================

double HLRBRep_TheQuadCurvExactInterCSurf::Root(const int Index) const
{
  return pnts(Index);
}

//==================================================================================================

void HLRBRep_TheQuadCurvExactInterCSurf::Intervals(const int Index, double& a, double& b) const
{
  int Index2 = Index + Index - 1;
  a          = intv(Index2);
  b          = intv(Index2 + 1);
}
