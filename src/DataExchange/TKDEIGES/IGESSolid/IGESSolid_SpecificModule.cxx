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

#include <IGESData_IGESDumper.hpp>
#include <IGESSolid_Block.hpp>
#include <IGESSolid_BooleanTree.hpp>
#include <IGESSolid_ConeFrustum.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_Cylinder.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_EdgeList.hpp>
#include <IGESSolid_Ellipsoid.hpp>
#include <IGESSolid_ManifoldSolid.hpp>
#include <IGESSolid_PlaneSurface.hpp>
#include <IGESSolid_RightAngularWedge.hpp>
#include <IGESSolid_SelectedComponent.hpp>
#include <IGESSolid_Shell.hpp>
#include <IGESSolid_SolidAssembly.hpp>
#include <IGESSolid_SolidInstance.hpp>
#include <IGESSolid_SolidOfLinearExtrusion.hpp>
#include <IGESSolid_SolidOfRevolution.hpp>
#include <IGESSolid_SpecificModule.hpp>
#include <IGESSolid_Sphere.hpp>
#include <IGESSolid_SphericalSurface.hpp>
#include <IGESSolid_ToolBlock.hpp>
#include <IGESSolid_ToolBooleanTree.hpp>
#include <IGESSolid_ToolConeFrustum.hpp>
#include <IGESSolid_ToolConicalSurface.hpp>
#include <IGESSolid_ToolCylinder.hpp>
#include <IGESSolid_ToolCylindricalSurface.hpp>
#include <IGESSolid_ToolEdgeList.hpp>
#include <IGESSolid_ToolEllipsoid.hpp>
#include <IGESSolid_ToolFace.hpp>
#include <IGESSolid_ToolLoop.hpp>
#include <IGESSolid_ToolManifoldSolid.hpp>
#include <IGESSolid_ToolPlaneSurface.hpp>
#include <IGESSolid_ToolRightAngularWedge.hpp>
#include <IGESSolid_ToolSelectedComponent.hpp>
#include <IGESSolid_ToolShell.hpp>
#include <IGESSolid_ToolSolidAssembly.hpp>
#include <IGESSolid_ToolSolidInstance.hpp>
#include <IGESSolid_ToolSolidOfLinearExtrusion.hpp>
#include <IGESSolid_ToolSolidOfRevolution.hpp>
#include <IGESSolid_ToolSphere.hpp>
#include <IGESSolid_ToolSphericalSurface.hpp>
#include <IGESSolid_ToolToroidalSurface.hpp>
#include <IGESSolid_ToolTorus.hpp>
#include <IGESSolid_ToolVertexList.hpp>
#include <IGESSolid_ToroidalSurface.hpp>
#include <IGESSolid_Torus.hpp>
#include <IGESSolid_VertexList.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_SpecificModule, IGESData_SpecificModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESSolid_SpecificModule::IGESSolid_SpecificModule() = default;

void IGESSolid_SpecificModule::OwnDump(const int                               CN,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int                               own) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESSolid_Block, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBlock tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2: {
      DeclareAndCast(IGESSolid_BooleanTree, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBooleanTree tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3: {
      DeclareAndCast(IGESSolid_ConeFrustum, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConeFrustum tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4: {
      DeclareAndCast(IGESSolid_ConicalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConicalSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5: {
      DeclareAndCast(IGESSolid_Cylinder, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylinder tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6: {
      DeclareAndCast(IGESSolid_CylindricalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylindricalSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7: {
      DeclareAndCast(IGESSolid_EdgeList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEdgeList tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 8: {
      DeclareAndCast(IGESSolid_Ellipsoid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEllipsoid tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 9: {
      DeclareAndCast(IGESSolid_Face, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolFace tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 10: {
      DeclareAndCast(IGESSolid_Loop, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolLoop tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 11: {
      DeclareAndCast(IGESSolid_ManifoldSolid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolManifoldSolid tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 12: {
      DeclareAndCast(IGESSolid_PlaneSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolPlaneSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 13: {
      DeclareAndCast(IGESSolid_RightAngularWedge, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolRightAngularWedge tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 14: {
      DeclareAndCast(IGESSolid_SelectedComponent, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSelectedComponent tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 15: {
      DeclareAndCast(IGESSolid_Shell, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolShell tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 16: {
      DeclareAndCast(IGESSolid_SolidAssembly, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidAssembly tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 17: {
      DeclareAndCast(IGESSolid_SolidInstance, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidInstance tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 18: {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 19: {
      DeclareAndCast(IGESSolid_SolidOfRevolution, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfRevolution tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 20: {
      DeclareAndCast(IGESSolid_Sphere, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphere tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 21: {
      DeclareAndCast(IGESSolid_SphericalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphericalSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 22: {
      DeclareAndCast(IGESSolid_ToroidalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolToroidalSurface tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 23: {
      DeclareAndCast(IGESSolid_Torus, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolTorus tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 24: {
      DeclareAndCast(IGESSolid_VertexList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolVertexList tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}
