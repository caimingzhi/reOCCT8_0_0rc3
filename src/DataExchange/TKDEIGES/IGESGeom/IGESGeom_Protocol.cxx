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

#include <IGESGeom_Protocol.hpp>

#include <IGESBasic.hpp>
#include <IGESBasic_Protocol.hpp>
#include <IGESGeom_BSplineCurve.hpp>
#include <IGESGeom_BSplineSurface.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_CircularArc.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <IGESGeom_ConicArc.hpp>
#include <IGESGeom_CopiousData.hpp>
#include <IGESGeom_Direction.hpp>
#include <IGESGeom_Flash.hpp>
#include <IGESGeom_Line.hpp>
#include <IGESGeom_OffsetCurve.hpp>
#include <IGESGeom_OffsetSurface.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_Point.hpp>
#include <IGESGeom_RuledSurface.hpp>
#include <IGESGeom_SplineCurve.hpp>
#include <IGESGeom_SplineSurface.hpp>
#include <IGESGeom_SurfaceOfRevolution.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <IGESGeom_TransformationMatrix.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGeom_Protocol, IGESData_Protocol)

IGESGeom_Protocol::IGESGeom_Protocol() = default;

int IGESGeom_Protocol::NbResources() const
{
  return 1;
}

occ::handle<Interface_Protocol> IGESGeom_Protocol::Resource(const int /*num*/) const
{
  occ::handle<Interface_Protocol> res = IGESBasic::Protocol();
  return res;
}

int IGESGeom_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESGeom_BSplineCurve))
    return 1;
  else if (atype == STANDARD_TYPE(IGESGeom_BSplineSurface))
    return 2;
  else if (atype == STANDARD_TYPE(IGESGeom_Boundary))
    return 3;
  else if (atype == STANDARD_TYPE(IGESGeom_BoundedSurface))
    return 4;
  else if (atype == STANDARD_TYPE(IGESGeom_CircularArc))
    return 5;
  else if (atype == STANDARD_TYPE(IGESGeom_CompositeCurve))
    return 6;
  else if (atype == STANDARD_TYPE(IGESGeom_ConicArc))
    return 7;
  else if (atype == STANDARD_TYPE(IGESGeom_CopiousData))
    return 8;
  else if (atype == STANDARD_TYPE(IGESGeom_CurveOnSurface))
    return 9;
  else if (atype == STANDARD_TYPE(IGESGeom_Direction))
    return 10;
  else if (atype == STANDARD_TYPE(IGESGeom_Flash))
    return 11;
  else if (atype == STANDARD_TYPE(IGESGeom_Line))
    return 12;
  else if (atype == STANDARD_TYPE(IGESGeom_OffsetCurve))
    return 13;
  else if (atype == STANDARD_TYPE(IGESGeom_OffsetSurface))
    return 14;
  else if (atype == STANDARD_TYPE(IGESGeom_Plane))
    return 15;
  else if (atype == STANDARD_TYPE(IGESGeom_Point))
    return 16;
  else if (atype == STANDARD_TYPE(IGESGeom_RuledSurface))
    return 17;
  else if (atype == STANDARD_TYPE(IGESGeom_SplineCurve))
    return 18;
  else if (atype == STANDARD_TYPE(IGESGeom_SplineSurface))
    return 19;
  else if (atype == STANDARD_TYPE(IGESGeom_SurfaceOfRevolution))
    return 20;
  else if (atype == STANDARD_TYPE(IGESGeom_TabulatedCylinder))
    return 21;
  else if (atype == STANDARD_TYPE(IGESGeom_TransformationMatrix))
    return 22;
  else if (atype == STANDARD_TYPE(IGESGeom_TrimmedSurface))
    return 23;
  return 0;
}
