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

#include <IGESDraw_Protocol.hpp>

#include <IGESDimen.hpp>
#include <IGESDimen_Protocol.hpp>
#include <IGESDraw_CircArraySubfigure.hpp>
#include <IGESDraw_Drawing.hpp>
#include <IGESDraw_DrawingWithRotation.hpp>
#include <IGESDraw_LabelDisplay.hpp>
#include <IGESDraw_NetworkSubfigure.hpp>
#include <IGESDraw_NetworkSubfigureDef.hpp>
#include <IGESDraw_PerspectiveView.hpp>
#include <IGESDraw_Planar.hpp>
#include <IGESDraw_RectArraySubfigure.hpp>
#include <IGESDraw_SegmentedViewsVisible.hpp>
#include <IGESDraw_View.hpp>
#include <IGESDraw_ViewsVisible.hpp>
#include <IGESDraw_ViewsVisibleWithAttr.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDraw_Protocol, IGESData_Protocol)

IGESDraw_Protocol::IGESDraw_Protocol() = default;

int IGESDraw_Protocol::NbResources() const
{
  return 1;
}

occ::handle<Interface_Protocol> IGESDraw_Protocol::Resource(const int /*num*/) const
{
  occ::handle<Interface_Protocol> res = IGESDimen::Protocol();
  return res;
}

int IGESDraw_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESDraw_CircArraySubfigure))
    return 1;
  else if (atype == STANDARD_TYPE(IGESDraw_ConnectPoint))
    return 2;
  else if (atype == STANDARD_TYPE(IGESDraw_Drawing))
    return 3;
  else if (atype == STANDARD_TYPE(IGESDraw_DrawingWithRotation))
    return 4;
  else if (atype == STANDARD_TYPE(IGESDraw_LabelDisplay))
    return 5;
  else if (atype == STANDARD_TYPE(IGESDraw_NetworkSubfigure))
    return 6;
  else if (atype == STANDARD_TYPE(IGESDraw_NetworkSubfigureDef))
    return 7;
  else if (atype == STANDARD_TYPE(IGESDraw_PerspectiveView))
    return 8;
  else if (atype == STANDARD_TYPE(IGESDraw_Planar))
    return 9;
  else if (atype == STANDARD_TYPE(IGESDraw_RectArraySubfigure))
    return 10;
  else if (atype == STANDARD_TYPE(IGESDraw_SegmentedViewsVisible))
    return 11;
  else if (atype == STANDARD_TYPE(IGESDraw_View))
    return 12;
  else if (atype == STANDARD_TYPE(IGESDraw_ViewsVisible))
    return 13;
  else if (atype == STANDARD_TYPE(IGESDraw_ViewsVisibleWithAttr))
    return 14;
  return 0;
}
