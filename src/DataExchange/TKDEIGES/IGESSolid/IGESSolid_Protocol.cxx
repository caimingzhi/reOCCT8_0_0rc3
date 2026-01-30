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

#include <IGESSolid_Protocol.hpp>

#include <IGESGeom.hpp>
#include <IGESGeom_Protocol.hpp>
#include <IGESSolid_Block.hpp>
#include <IGESSolid_BooleanTree.hpp>
#include <IGESSolid_ConeFrustum.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_Cylinder.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_EdgeList.hpp>
#include <IGESSolid_Ellipsoid.hpp>
#include <IGESSolid_Loop.hpp>
#include <IGESSolid_ManifoldSolid.hpp>
#include <IGESSolid_PlaneSurface.hpp>
#include <IGESSolid_RightAngularWedge.hpp>
#include <IGESSolid_SelectedComponent.hpp>
#include <IGESSolid_Shell.hpp>
#include <IGESSolid_SolidAssembly.hpp>
#include <IGESSolid_SolidInstance.hpp>
#include <IGESSolid_SolidOfLinearExtrusion.hpp>
#include <IGESSolid_SolidOfRevolution.hpp>
#include <IGESSolid_Sphere.hpp>
#include <IGESSolid_SphericalSurface.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <IGESSolid_Torus.hpp>
#include <IGESSolid_VertexList.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_Protocol, IGESData_Protocol)

IGESSolid_Protocol::IGESSolid_Protocol() = default;

int IGESSolid_Protocol::NbResources() const
{
  return 1;
}

occ::handle<Interface_Protocol> IGESSolid_Protocol::Resource(const int /*num*/) const
{
  occ::handle<Interface_Protocol> res = IGESGeom::Protocol();
  return res;
}

int IGESSolid_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESSolid_Block))
    return 1;
  else if (atype == STANDARD_TYPE(IGESSolid_BooleanTree))
    return 2;
  else if (atype == STANDARD_TYPE(IGESSolid_ConeFrustum))
    return 3;
  else if (atype == STANDARD_TYPE(IGESSolid_ConicalSurface))
    return 4;
  else if (atype == STANDARD_TYPE(IGESSolid_Cylinder))
    return 5;
  else if (atype == STANDARD_TYPE(IGESSolid_CylindricalSurface))
    return 6;
  else if (atype == STANDARD_TYPE(IGESSolid_EdgeList))
    return 7;
  else if (atype == STANDARD_TYPE(IGESSolid_Ellipsoid))
    return 8;
  else if (atype == STANDARD_TYPE(IGESSolid_Face))
    return 9;
  else if (atype == STANDARD_TYPE(IGESSolid_Loop))
    return 10;
  else if (atype == STANDARD_TYPE(IGESSolid_ManifoldSolid))
    return 11;
  else if (atype == STANDARD_TYPE(IGESSolid_PlaneSurface))
    return 12;
  else if (atype == STANDARD_TYPE(IGESSolid_RightAngularWedge))
    return 13;
  else if (atype == STANDARD_TYPE(IGESSolid_SelectedComponent))
    return 14;
  else if (atype == STANDARD_TYPE(IGESSolid_Shell))
    return 15;
  else if (atype == STANDARD_TYPE(IGESSolid_SolidAssembly))
    return 16;
  else if (atype == STANDARD_TYPE(IGESSolid_SolidInstance))
    return 17;
  else if (atype == STANDARD_TYPE(IGESSolid_SolidOfLinearExtrusion))
    return 18;
  else if (atype == STANDARD_TYPE(IGESSolid_SolidOfRevolution))
    return 19;
  else if (atype == STANDARD_TYPE(IGESSolid_Sphere))
    return 20;
  else if (atype == STANDARD_TYPE(IGESSolid_SphericalSurface))
    return 21;
  else if (atype == STANDARD_TYPE(IGESSolid_ToroidalSurface))
    return 22;
  else if (atype == STANDARD_TYPE(IGESSolid_Torus))
    return 23;
  else if (atype == STANDARD_TYPE(IGESSolid_VertexList))
    return 24;
  return 0;
}
