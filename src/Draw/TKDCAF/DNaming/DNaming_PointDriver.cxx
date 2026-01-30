// Created on: 2010-02-25
// Created by: Sergey ZARITCHNY
// Copyright (c) 2010-2014 OPEN CASCADE SAS
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

#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <DNaming.hpp>
#include <DNaming_PointDriver.hpp>
#include <gp_Pnt.hpp>
#include <ModelDefinitions.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Real.hpp>
#include <TDF_Label.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_Logbook.hpp>
#include <TNaming.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DNaming_PointDriver, TFunction_Driver)

// OCCT
//  OCAF
//=================================================================================================

DNaming_PointDriver::DNaming_PointDriver() = default;

//=======================================================================
// function : Validate
// purpose  : Validates labels of a function in <log>.
//=======================================================================
void DNaming_PointDriver::Validate(occ::handle<TFunction_Logbook>&) const {}

//=======================================================================
// function : MustExecute
// purpose  : Analyse in <log> if the loaded function must be executed
//=======================================================================
bool DNaming_PointDriver::MustExecute(const occ::handle<TFunction_Logbook>&) const
{
  return true;
}

//=======================================================================
// function : Execute
// purpose  : Execute the function and push in <log> the impacted labels
//=======================================================================
int DNaming_PointDriver::Execute(occ::handle<TFunction_Logbook>& theLog) const
{
  occ::handle<TFunction_Function> aFunction;
  Label().FindAttribute(TFunction_Function::GetID(), aFunction);
  if (aFunction.IsNull())
    return -1;

  // perform calculations

  double aDX = DNaming::GetReal(aFunction, PNT_DX)->Get();
  double aDY = DNaming::GetReal(aFunction, PNT_DY)->Get();
  double aDZ = DNaming::GetReal(aFunction, PNT_DZ)->Get();

  occ::handle<TNaming_NamedShape> aPrevPnt = DNaming::GetFunctionResult(aFunction);
  // Save location
  TopLoc_Location aLocation;
  if (!aPrevPnt.IsNull() && !aPrevPnt->IsEmpty())
  {
    aLocation = aPrevPnt->Get().Location();
  }
  gp_Pnt aPoint;
  if (aFunction->GetDriverGUID() == PNTRLT_GUID)
  {
    occ::handle<TDataStd_UAttribute> aRefPnt   = DNaming::GetObjectArg(aFunction, PNTRLT_REF);
    occ::handle<TNaming_NamedShape>  aRefPntNS = DNaming::GetObjectValue(aRefPnt);
    if (aRefPntNS.IsNull() || aRefPntNS->IsEmpty())
    {
#ifdef OCCT_DEBUG
      std::cout << "PointDriver:: Ref Point is empty" << std::endl;
#endif
      aFunction->SetFailure(WRONG_ARGUMENT);
      return -1;
    }
    TopoDS_Shape  aRefPntShape = aRefPntNS->Get();
    TopoDS_Vertex aVertex      = TopoDS::Vertex(aRefPntShape);
    aPoint                     = BRep_Tool::Pnt(aVertex);
    aPoint.SetX(aPoint.X() + aDX);
    aPoint.SetY(aPoint.Y() + aDY);
    aPoint.SetZ(aPoint.Z() + aDZ);
  }
  else
    aPoint = gp_Pnt(aDX, aDY, aDZ);

  BRepBuilderAPI_MakeVertex aMakeVertex(aPoint);

  if (!aMakeVertex.IsDone())
  {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }

  // Naming
  const TDF_Label& aResultLabel = RESPOSITION(aFunction);
  TNaming_Builder  aBuilder(aResultLabel);
  aBuilder.Generated(aMakeVertex.Shape());

  // restore location
  if (!aLocation.IsIdentity())
    TNaming::Displace(aResultLabel, aLocation, true);

  theLog->SetValid(aResultLabel, true);

  aFunction->SetFailure(DONE);
  return 0;
}
