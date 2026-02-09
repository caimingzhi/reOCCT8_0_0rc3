

#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
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
#include <IGESSolid_ReadWriteModule.hpp>
#include <IGESSolid_RightAngularWedge.hpp>
#include <IGESSolid_SelectedComponent.hpp>
#include <IGESSolid_Shell.hpp>
#include <IGESSolid_SolidAssembly.hpp>
#include <IGESSolid_SolidInstance.hpp>
#include <IGESSolid_SolidOfLinearExtrusion.hpp>
#include <IGESSolid_SolidOfRevolution.hpp>
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

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_ReadWriteModule, IGESData_ReadWriteModule)

IGESSolid_ReadWriteModule::IGESSolid_ReadWriteModule() = default;

int IGESSolid_ReadWriteModule::CaseIGES(const int typenum, const int) const
{
  switch (typenum)
  {
    case 150:
      return 1;
    case 152:
      return 13;
    case 154:
      return 5;
    case 156:
      return 3;
    case 158:
      return 20;
    case 160:
      return 23;
    case 162:
      return 19;
    case 164:
      return 18;
    case 168:
      return 8;
    case 180:
      return 2;
    case 182:
      return 14;
    case 184:
      return 16;
    case 186:
      return 11;
    case 190:
      return 12;
    case 192:
      return 6;
    case 194:
      return 4;
    case 196:
      return 21;
    case 198:
      return 22;
    case 430:
      return 17;
    case 502:
      return 24;
    case 504:
      return 7;
    case 508:
      return 10;
    case 510:
      return 9;
    case 514:
      return 15;
    default:
      break;
  }
  return 0;
}

void IGESSolid_ReadWriteModule::ReadOwnParams(const int                                   CN,
                                              const occ::handle<IGESData_IGESEntity>&     ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESSolid_Block, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBlock tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESSolid_BooleanTree, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBooleanTree tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESSolid_ConeFrustum, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConeFrustum tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESSolid_ConicalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConicalSurface tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESSolid_Cylinder, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylinder tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylindricalSurface tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESSolid_EdgeList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEdgeList tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESSolid_Ellipsoid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEllipsoid tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESSolid_Face, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolFace tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESSolid_Loop, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolLoop tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESSolid_ManifoldSolid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolManifoldSolid tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESSolid_PlaneSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolPlaneSurface tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESSolid_RightAngularWedge, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolRightAngularWedge tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESSolid_SelectedComponent, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSelectedComponent tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESSolid_Shell, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolShell tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESSolid_SolidAssembly, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidAssembly tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESSolid_SolidInstance, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidInstance tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESSolid_SolidOfRevolution, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfRevolution tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 20:
    {
      DeclareAndCast(IGESSolid_Sphere, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphere tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 21:
    {
      DeclareAndCast(IGESSolid_SphericalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphericalSurface tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 22:
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolToroidalSurface tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 23:
    {
      DeclareAndCast(IGESSolid_Torus, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolTorus tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 24:
    {
      DeclareAndCast(IGESSolid_VertexList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolVertexList tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    default:
      break;
  }
}

void IGESSolid_ReadWriteModule::WriteOwnParams(const int                               CN,
                                               const occ::handle<IGESData_IGESEntity>& ent,
                                               IGESData_IGESWriter&                    IW) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESSolid_Block, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBlock tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESSolid_BooleanTree, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBooleanTree tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESSolid_ConeFrustum, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConeFrustum tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESSolid_ConicalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConicalSurface tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESSolid_Cylinder, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylinder tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylindricalSurface tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESSolid_EdgeList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEdgeList tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESSolid_Ellipsoid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEllipsoid tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESSolid_Face, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolFace tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESSolid_Loop, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolLoop tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESSolid_ManifoldSolid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolManifoldSolid tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESSolid_PlaneSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolPlaneSurface tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESSolid_RightAngularWedge, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolRightAngularWedge tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESSolid_SelectedComponent, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSelectedComponent tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESSolid_Shell, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolShell tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESSolid_SolidAssembly, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidAssembly tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESSolid_SolidInstance, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidInstance tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESSolid_SolidOfRevolution, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfRevolution tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 20:
    {
      DeclareAndCast(IGESSolid_Sphere, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphere tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 21:
    {
      DeclareAndCast(IGESSolid_SphericalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphericalSurface tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 22:
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolToroidalSurface tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 23:
    {
      DeclareAndCast(IGESSolid_Torus, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolTorus tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 24:
    {
      DeclareAndCast(IGESSolid_VertexList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolVertexList tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    default:
      break;
  }
}
