

#include <IGESData_DirChecker.hpp>
#include <IGESSolid_Block.hpp>
#include <IGESSolid_BooleanTree.hpp>
#include <IGESSolid_ConeFrustum.hpp>
#include <IGESSolid_ConicalSurface.hpp>
#include <IGESSolid_Cylinder.hpp>
#include <IGESSolid_CylindricalSurface.hpp>
#include <IGESSolid_EdgeList.hpp>
#include <IGESSolid_Ellipsoid.hpp>
#include <IGESSolid_GeneralModule.hpp>
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
#include <Interface_Category.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_GeneralModule, IGESData_GeneralModule)

IGESSolid_GeneralModule::IGESSolid_GeneralModule() = default;

void IGESSolid_GeneralModule::OwnSharedCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& ent,
                                            Interface_EntityIterator&               iter) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESSolid_Block, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBlock tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESSolid_BooleanTree, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBooleanTree tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESSolid_ConeFrustum, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConeFrustum tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESSolid_ConicalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConicalSurface tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESSolid_Cylinder, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylinder tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylindricalSurface tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESSolid_EdgeList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEdgeList tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESSolid_Ellipsoid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEllipsoid tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESSolid_Face, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolFace tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESSolid_Loop, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolLoop tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESSolid_ManifoldSolid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolManifoldSolid tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESSolid_PlaneSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolPlaneSurface tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESSolid_RightAngularWedge, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolRightAngularWedge tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESSolid_SelectedComponent, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSelectedComponent tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESSolid_Shell, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolShell tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESSolid_SolidAssembly, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidAssembly tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESSolid_SolidInstance, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidInstance tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESSolid_SolidOfRevolution, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfRevolution tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 20:
    {
      DeclareAndCast(IGESSolid_Sphere, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphere tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 21:
    {
      DeclareAndCast(IGESSolid_SphericalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphericalSurface tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 22:
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolToroidalSurface tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 23:
    {
      DeclareAndCast(IGESSolid_Torus, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolTorus tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 24:
    {
      DeclareAndCast(IGESSolid_VertexList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolVertexList tool;
      tool.OwnShared(anent, iter);
    }
    break;
    default:
      break;
  }
}

IGESData_DirChecker IGESSolid_GeneralModule::DirChecker(
  const int                               CN,
  const occ::handle<IGESData_IGESEntity>& ent) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESSolid_Block, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolBlock tool;
      return tool.DirChecker(anent);
    }
    case 2:
    {
      DeclareAndCast(IGESSolid_BooleanTree, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolBooleanTree tool;
      return tool.DirChecker(anent);
    }
    case 3:
    {
      DeclareAndCast(IGESSolid_ConeFrustum, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolConeFrustum tool;
      return tool.DirChecker(anent);
    }
    case 4:
    {
      DeclareAndCast(IGESSolid_ConicalSurface, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolConicalSurface tool;
      return tool.DirChecker(anent);
    }
    case 5:
    {
      DeclareAndCast(IGESSolid_Cylinder, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolCylinder tool;
      return tool.DirChecker(anent);
    }
    case 6:
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolCylindricalSurface tool;
      return tool.DirChecker(anent);
    }
    case 7:
    {
      DeclareAndCast(IGESSolid_EdgeList, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolEdgeList tool;
      return tool.DirChecker(anent);
    }
    case 8:
    {
      DeclareAndCast(IGESSolid_Ellipsoid, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolEllipsoid tool;
      return tool.DirChecker(anent);
    }
    case 9:
    {
      DeclareAndCast(IGESSolid_Face, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolFace tool;
      return tool.DirChecker(anent);
    }
    case 10:
    {
      DeclareAndCast(IGESSolid_Loop, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolLoop tool;
      return tool.DirChecker(anent);
    }
    case 11:
    {
      DeclareAndCast(IGESSolid_ManifoldSolid, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolManifoldSolid tool;
      return tool.DirChecker(anent);
    }
    case 12:
    {
      DeclareAndCast(IGESSolid_PlaneSurface, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolPlaneSurface tool;
      return tool.DirChecker(anent);
    }
    case 13:
    {
      DeclareAndCast(IGESSolid_RightAngularWedge, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolRightAngularWedge tool;
      return tool.DirChecker(anent);
    }
    case 14:
    {
      DeclareAndCast(IGESSolid_SelectedComponent, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSelectedComponent tool;
      return tool.DirChecker(anent);
    }
    case 15:
    {
      DeclareAndCast(IGESSolid_Shell, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolShell tool;
      return tool.DirChecker(anent);
    }
    case 16:
    {
      DeclareAndCast(IGESSolid_SolidAssembly, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSolidAssembly tool;
      return tool.DirChecker(anent);
    }
    case 17:
    {
      DeclareAndCast(IGESSolid_SolidInstance, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSolidInstance tool;
      return tool.DirChecker(anent);
    }
    case 18:
    {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      return tool.DirChecker(anent);
    }
    case 19:
    {
      DeclareAndCast(IGESSolid_SolidOfRevolution, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSolidOfRevolution tool;
      return tool.DirChecker(anent);
    }
    case 20:
    {
      DeclareAndCast(IGESSolid_Sphere, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSphere tool;
      return tool.DirChecker(anent);
    }
    case 21:
    {
      DeclareAndCast(IGESSolid_SphericalSurface, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolSphericalSurface tool;
      return tool.DirChecker(anent);
    }
    case 22:
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolToroidalSurface tool;
      return tool.DirChecker(anent);
    }
    case 23:
    {
      DeclareAndCast(IGESSolid_Torus, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolTorus tool;
      return tool.DirChecker(anent);
    }
    case 24:
    {
      DeclareAndCast(IGESSolid_VertexList, anent, ent);
      if (anent.IsNull())
        break;
      IGESSolid_ToolVertexList tool;
      return tool.DirChecker(anent);
    }
    default:
      break;
  }
  return IGESData_DirChecker();
}

void IGESSolid_GeneralModule::OwnCheckCase(const int                               CN,
                                           const occ::handle<IGESData_IGESEntity>& ent,
                                           const Interface_ShareTool&              shares,
                                           occ::handle<Interface_Check>&           ach) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESSolid_Block, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBlock tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESSolid_BooleanTree, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolBooleanTree tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESSolid_ConeFrustum, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConeFrustum tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESSolid_ConicalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolConicalSurface tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESSolid_Cylinder, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylinder tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolCylindricalSurface tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESSolid_EdgeList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEdgeList tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESSolid_Ellipsoid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolEllipsoid tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESSolid_Face, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolFace tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESSolid_Loop, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolLoop tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESSolid_ManifoldSolid, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolManifoldSolid tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESSolid_PlaneSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolPlaneSurface tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESSolid_RightAngularWedge, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolRightAngularWedge tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESSolid_SelectedComponent, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSelectedComponent tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESSolid_Shell, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolShell tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESSolid_SolidAssembly, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidAssembly tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESSolid_SolidInstance, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidInstance tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESSolid_SolidOfRevolution, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSolidOfRevolution tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 20:
    {
      DeclareAndCast(IGESSolid_Sphere, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphere tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 21:
    {
      DeclareAndCast(IGESSolid_SphericalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolSphericalSurface tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 22:
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolToroidalSurface tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 23:
    {
      DeclareAndCast(IGESSolid_Torus, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolTorus tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 24:
    {
      DeclareAndCast(IGESSolid_VertexList, anent, ent);
      if (anent.IsNull())
        return;
      IGESSolid_ToolVertexList tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    default:
      break;
  }
}

bool IGESSolid_GeneralModule::NewVoid(const int CN, occ::handle<Standard_Transient>& ent) const
{
  switch (CN)
  {
    case 1:
      ent = new IGESSolid_Block;
      break;
    case 2:
      ent = new IGESSolid_BooleanTree;
      break;
    case 3:
      ent = new IGESSolid_ConeFrustum;
      break;
    case 4:
      ent = new IGESSolid_ConicalSurface;
      break;
    case 5:
      ent = new IGESSolid_Cylinder;
      break;
    case 6:
      ent = new IGESSolid_CylindricalSurface;
      break;
    case 7:
      ent = new IGESSolid_EdgeList;
      break;
    case 8:
      ent = new IGESSolid_Ellipsoid;
      break;
    case 9:
      ent = new IGESSolid_Face;
      break;
    case 10:
      ent = new IGESSolid_Loop;
      break;
    case 11:
      ent = new IGESSolid_ManifoldSolid;
      break;
    case 12:
      ent = new IGESSolid_PlaneSurface;
      break;
    case 13:
      ent = new IGESSolid_RightAngularWedge;
      break;
    case 14:
      ent = new IGESSolid_SelectedComponent;
      break;
    case 15:
      ent = new IGESSolid_Shell;
      break;
    case 16:
      ent = new IGESSolid_SolidAssembly;
      break;
    case 17:
      ent = new IGESSolid_SolidInstance;
      break;
    case 18:
      ent = new IGESSolid_SolidOfLinearExtrusion;
      break;
    case 19:
      ent = new IGESSolid_SolidOfRevolution;
      break;
    case 20:
      ent = new IGESSolid_Sphere;
      break;
    case 21:
      ent = new IGESSolid_SphericalSurface;
      break;
    case 22:
      ent = new IGESSolid_ToroidalSurface;
      break;
    case 23:
      ent = new IGESSolid_Torus;
      break;
    case 24:
      ent = new IGESSolid_VertexList;
      break;
    default:
      return false;
  }
  return true;
}

void IGESSolid_GeneralModule::OwnCopyCase(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& entfrom,
                                          const occ::handle<IGESData_IGESEntity>& entto,
                                          Interface_CopyTool&                     TC) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESSolid_Block, enfr, entfrom);
      DeclareAndCast(IGESSolid_Block, ento, entto);
      IGESSolid_ToolBlock tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESSolid_BooleanTree, enfr, entfrom);
      DeclareAndCast(IGESSolid_BooleanTree, ento, entto);
      IGESSolid_ToolBooleanTree tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESSolid_ConeFrustum, enfr, entfrom);
      DeclareAndCast(IGESSolid_ConeFrustum, ento, entto);
      IGESSolid_ToolConeFrustum tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESSolid_ConicalSurface, enfr, entfrom);
      DeclareAndCast(IGESSolid_ConicalSurface, ento, entto);
      IGESSolid_ToolConicalSurface tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESSolid_Cylinder, enfr, entfrom);
      DeclareAndCast(IGESSolid_Cylinder, ento, entto);
      IGESSolid_ToolCylinder tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESSolid_CylindricalSurface, enfr, entfrom);
      DeclareAndCast(IGESSolid_CylindricalSurface, ento, entto);
      IGESSolid_ToolCylindricalSurface tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESSolid_EdgeList, enfr, entfrom);
      DeclareAndCast(IGESSolid_EdgeList, ento, entto);
      IGESSolid_ToolEdgeList tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESSolid_Ellipsoid, enfr, entfrom);
      DeclareAndCast(IGESSolid_Ellipsoid, ento, entto);
      IGESSolid_ToolEllipsoid tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESSolid_Face, enfr, entfrom);
      DeclareAndCast(IGESSolid_Face, ento, entto);
      IGESSolid_ToolFace tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESSolid_Loop, enfr, entfrom);
      DeclareAndCast(IGESSolid_Loop, ento, entto);
      IGESSolid_ToolLoop tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESSolid_ManifoldSolid, enfr, entfrom);
      DeclareAndCast(IGESSolid_ManifoldSolid, ento, entto);
      IGESSolid_ToolManifoldSolid tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESSolid_PlaneSurface, enfr, entfrom);
      DeclareAndCast(IGESSolid_PlaneSurface, ento, entto);
      IGESSolid_ToolPlaneSurface tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESSolid_RightAngularWedge, enfr, entfrom);
      DeclareAndCast(IGESSolid_RightAngularWedge, ento, entto);
      IGESSolid_ToolRightAngularWedge tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESSolid_SelectedComponent, enfr, entfrom);
      DeclareAndCast(IGESSolid_SelectedComponent, ento, entto);
      IGESSolid_ToolSelectedComponent tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESSolid_Shell, enfr, entfrom);
      DeclareAndCast(IGESSolid_Shell, ento, entto);
      IGESSolid_ToolShell tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESSolid_SolidAssembly, enfr, entfrom);
      DeclareAndCast(IGESSolid_SolidAssembly, ento, entto);
      IGESSolid_ToolSolidAssembly tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESSolid_SolidInstance, enfr, entfrom);
      DeclareAndCast(IGESSolid_SolidInstance, ento, entto);
      IGESSolid_ToolSolidInstance tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, enfr, entfrom);
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion, ento, entto);
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESSolid_SolidOfRevolution, enfr, entfrom);
      DeclareAndCast(IGESSolid_SolidOfRevolution, ento, entto);
      IGESSolid_ToolSolidOfRevolution tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 20:
    {
      DeclareAndCast(IGESSolid_Sphere, enfr, entfrom);
      DeclareAndCast(IGESSolid_Sphere, ento, entto);
      IGESSolid_ToolSphere tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 21:
    {
      DeclareAndCast(IGESSolid_SphericalSurface, enfr, entfrom);
      DeclareAndCast(IGESSolid_SphericalSurface, ento, entto);
      IGESSolid_ToolSphericalSurface tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 22:
    {
      DeclareAndCast(IGESSolid_ToroidalSurface, enfr, entfrom);
      DeclareAndCast(IGESSolid_ToroidalSurface, ento, entto);
      IGESSolid_ToolToroidalSurface tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 23:
    {
      DeclareAndCast(IGESSolid_Torus, enfr, entfrom);
      DeclareAndCast(IGESSolid_Torus, ento, entto);
      IGESSolid_ToolTorus tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 24:
    {
      DeclareAndCast(IGESSolid_VertexList, enfr, entfrom);
      DeclareAndCast(IGESSolid_VertexList, ento, entto);
      IGESSolid_ToolVertexList tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    default:
      break;
  }
}

int IGESSolid_GeneralModule::CategoryNumber(const int,
                                            const occ::handle<Standard_Transient>&,
                                            const Interface_ShareTool&) const
{
  return Interface_Category::Number("Shape");
}
