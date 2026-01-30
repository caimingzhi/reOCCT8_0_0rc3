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

#include <AIS_InteractiveContext.hpp>
#include <AIS_InteractiveObject.hpp>
#include <AIS_Plane.hpp>
#include <Geom_Plane.hpp>
#include <gp_Pln.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDataXtd_Plane.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Tool.hpp>
#include <TPrsStd_PlaneDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TPrsStd_PlaneDriver, TPrsStd_Driver)

// #include <TDataStd_Datum.hxx>
//=================================================================================================

TPrsStd_PlaneDriver::TPrsStd_PlaneDriver() = default;

//=================================================================================================

bool TPrsStd_PlaneDriver::Update(const TDF_Label&                    aLabel,
                                 occ::handle<AIS_InteractiveObject>& anAISObject)
{
  occ::handle<TDataXtd_Plane> apPlane;

  if (!aLabel.FindAttribute(TDataXtd_Plane::GetID(), apPlane))
  {
    return false;
  }

  gp_Pln pln;
  if (!TDataXtd_Geometry::Plane(aLabel, pln))
  {
    return false;
  }
  occ::handle<Geom_Plane> apt = new Geom_Plane(pln);

  //  Update AIS
  occ::handle<AIS_Plane> aisplane;
  if (anAISObject.IsNull())
    aisplane = new AIS_Plane(apt, pln.Location());
  else
  {
    aisplane = occ::down_cast<AIS_Plane>(anAISObject);
    if (aisplane.IsNull())
      aisplane = new AIS_Plane(apt, pln.Location());
    else
    {
      aisplane->SetComponent(apt);
      aisplane->SetCenter(pln.Location());
      aisplane->ResetTransformation();
      aisplane->SetToUpdate();
      aisplane->UpdateSelection();
    }
  }
  anAISObject = aisplane;
  return true;
}
