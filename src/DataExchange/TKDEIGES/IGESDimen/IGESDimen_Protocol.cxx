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

#include <IGESDimen_Protocol.hpp>

#include <IGESDimen_AngularDimension.hpp>
#include <IGESDimen_BasicDimension.hpp>
#include <IGESDimen_CenterLine.hpp>
#include <IGESDimen_CurveDimension.hpp>
#include <IGESDimen_DiameterDimension.hpp>
#include <IGESDimen_DimensionDisplayData.hpp>
#include <IGESDimen_DimensionTolerance.hpp>
#include <IGESDimen_DimensionUnits.hpp>
#include <IGESDimen_DimensionedGeometry.hpp>
#include <IGESDimen_FlagNote.hpp>
#include <IGESDimen_GeneralLabel.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_GeneralSymbol.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_LinearDimension.hpp>
#include <IGESDimen_NewDimensionedGeometry.hpp>
#include <IGESDimen_NewGeneralNote.hpp>
#include <IGESDimen_OrdinateDimension.hpp>
#include <IGESDimen_PointDimension.hpp>
#include <IGESDimen_RadiusDimension.hpp>
#include <IGESDimen_Section.hpp>
#include <IGESDimen_SectionedArea.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <IGESGeom.hpp>
#include <IGESGeom_Protocol.hpp>
#include <IGESGraph.hpp>
#include <IGESGraph_Protocol.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_Protocol, IGESData_Protocol)

IGESDimen_Protocol::IGESDimen_Protocol() = default;

int IGESDimen_Protocol::NbResources() const
{
  return 2;
}

occ::handle<Interface_Protocol> IGESDimen_Protocol::Resource(const int num) const
{
  occ::handle<Interface_Protocol> res;
  if (num == 1)
    res = IGESGraph::Protocol();
  if (num == 2)
    res = IGESGeom::Protocol();
  return res;
}

int IGESDimen_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESDimen_AngularDimension))
    return 1;
  else if (atype == STANDARD_TYPE(IGESDimen_BasicDimension))
    return 2;
  else if (atype == STANDARD_TYPE(IGESDimen_CenterLine))
    return 3;
  else if (atype == STANDARD_TYPE(IGESDimen_CurveDimension))
    return 4;
  else if (atype == STANDARD_TYPE(IGESDimen_DiameterDimension))
    return 5;
  else if (atype == STANDARD_TYPE(IGESDimen_DimensionDisplayData))
    return 6;
  else if (atype == STANDARD_TYPE(IGESDimen_DimensionTolerance))
    return 7;
  else if (atype == STANDARD_TYPE(IGESDimen_DimensionUnits))
    return 8;
  else if (atype == STANDARD_TYPE(IGESDimen_DimensionedGeometry))
    return 9;
  else if (atype == STANDARD_TYPE(IGESDimen_FlagNote))
    return 10;
  else if (atype == STANDARD_TYPE(IGESDimen_GeneralLabel))
    return 11;
  else if (atype == STANDARD_TYPE(IGESDimen_GeneralNote))
    return 12;
  else if (atype == STANDARD_TYPE(IGESDimen_GeneralSymbol))
    return 13;
  else if (atype == STANDARD_TYPE(IGESDimen_LeaderArrow))
    return 14;
  else if (atype == STANDARD_TYPE(IGESDimen_LinearDimension))
    return 15;
  else if (atype == STANDARD_TYPE(IGESDimen_NewDimensionedGeometry))
    return 16;
  else if (atype == STANDARD_TYPE(IGESDimen_NewGeneralNote))
    return 17;
  else if (atype == STANDARD_TYPE(IGESDimen_OrdinateDimension))
    return 18;
  else if (atype == STANDARD_TYPE(IGESDimen_PointDimension))
    return 19;
  else if (atype == STANDARD_TYPE(IGESDimen_RadiusDimension))
    return 20;
  else if (atype == STANDARD_TYPE(IGESDimen_Section))
    return 21;
  else if (atype == STANDARD_TYPE(IGESDimen_SectionedArea))
    return 22;
  else if (atype == STANDARD_TYPE(IGESDimen_WitnessLine))
    return 23;
  return 0;
}
