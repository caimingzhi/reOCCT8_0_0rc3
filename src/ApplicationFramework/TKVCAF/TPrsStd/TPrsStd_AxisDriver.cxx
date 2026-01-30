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

#include <AIS_Axis.hpp>
#include <AIS_InteractiveContext.hpp>
#include <AIS_InteractiveObject.hpp>
#include <Geom_Line.hpp>
#include <gp_Lin.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Axis.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Tool.hpp>
#include <TopoDS_Shape.hpp>
#include <TPrsStd_AxisDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TPrsStd_AxisDriver, TPrsStd_Driver)

//=================================================================================================

TPrsStd_AxisDriver::TPrsStd_AxisDriver() = default;

//=================================================================================================

bool TPrsStd_AxisDriver::Update(const TDF_Label&                    aLabel,
                                occ::handle<AIS_InteractiveObject>& anAISObject)
{

  occ::handle<TDataXtd_Axis> apAxis;
  if (!aLabel.FindAttribute(TDataXtd_Axis::GetID(), apAxis))
  {
    return false;
  }

  gp_Lin                          lin;
  occ::handle<TNaming_NamedShape> NS;
  if (aLabel.FindAttribute(TNaming_NamedShape::GetID(), NS))
  {
    if (TNaming_Tool::GetShape(NS).IsNull())
    {
      return false;
    }
  }

  occ::handle<AIS_Axis> aistrihed;
  if (TDataXtd_Geometry::Line(aLabel, lin))
  {
    occ::handle<Geom_Line> apt = new Geom_Line(lin);

    //  Update de l'AIS
    if (anAISObject.IsNull())
      aistrihed = new AIS_Axis(apt);
    else
    {
      aistrihed = occ::down_cast<AIS_Axis>(anAISObject);
      if (aistrihed.IsNull())
        aistrihed = new AIS_Axis(apt);
      else
      {
        aistrihed->SetComponent(apt);
        aistrihed->ResetTransformation();
        aistrihed->SetToUpdate();
        aistrihed->UpdateSelection();
      }
    }
    anAISObject = aistrihed;
    return true;
  }
  return false;
}
