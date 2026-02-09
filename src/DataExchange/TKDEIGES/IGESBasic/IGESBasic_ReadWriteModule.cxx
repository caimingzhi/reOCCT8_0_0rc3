

#include <IGESBasic_AssocGroupType.hpp>
#include <IGESBasic_ExternalReferenceFile.hpp>
#include <IGESBasic_ExternalRefFile.hpp>
#include <IGESBasic_ExternalRefFileIndex.hpp>
#include <IGESBasic_ExternalRefFileName.hpp>
#include <IGESBasic_ExternalRefLibName.hpp>
#include <IGESBasic_ExternalRefName.hpp>
#include <IGESBasic_GroupWithoutBackP.hpp>
#include <IGESBasic_Hierarchy.hpp>
#include <IGESBasic_Name.hpp>
#include <IGESBasic_OrderedGroup.hpp>
#include <IGESBasic_OrderedGroupWithoutBackP.hpp>
#include <IGESBasic_ReadWriteModule.hpp>
#include <IGESBasic_SingleParent.hpp>
#include <IGESBasic_SingularSubfigure.hpp>
#include <IGESBasic_SubfigureDef.hpp>
#include <IGESBasic_ToolAssocGroupType.hpp>
#include <IGESBasic_ToolExternalReferenceFile.hpp>
#include <IGESBasic_ToolExternalRefFile.hpp>
#include <IGESBasic_ToolExternalRefFileIndex.hpp>
#include <IGESBasic_ToolExternalRefFileName.hpp>
#include <IGESBasic_ToolExternalRefLibName.hpp>
#include <IGESBasic_ToolExternalRefName.hpp>
#include <IGESBasic_ToolGroup.hpp>
#include <IGESBasic_ToolGroupWithoutBackP.hpp>
#include <IGESBasic_ToolHierarchy.hpp>
#include <IGESBasic_ToolName.hpp>
#include <IGESBasic_ToolOrderedGroup.hpp>
#include <IGESBasic_ToolOrderedGroupWithoutBackP.hpp>
#include <IGESBasic_ToolSingleParent.hpp>
#include <IGESBasic_ToolSingularSubfigure.hpp>
#include <IGESBasic_ToolSubfigureDef.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_ReadWriteModule, IGESData_ReadWriteModule)

IGESBasic_ReadWriteModule::IGESBasic_ReadWriteModule() = default;

int IGESBasic_ReadWriteModule::CaseIGES(const int typenum, const int formnum) const
{
  switch (typenum)
  {
    case 308:
      return 16;
    case 402:
      switch (formnum)
      {
        case 1:
          return 8;
        case 7:
          return 9;
        case 9:
          return 14;
        case 12:
          return 3;
        case 14:
          return 12;
        case 15:
          return 13;
        default:
          break;
      }
      break;
    case 406:
      switch (formnum)
      {
        case 10:
          return 10;
        case 12:
          return 7;
        case 15:
          return 11;
        case 23:
          return 1;
        default:
          break;
      }
      break;
    case 408:
      return 15;
    case 416:
      switch (formnum)
      {
        case 0:
          return 4;
        case 1:
          return 2;
        case 2:
          return 4;
        case 3:
          return 6;
        case 4:
          return 5;
        default:
          break;
      }
      break;
    default:
      break;
  }
  return 0;
}

void IGESBasic_ReadWriteModule::ReadOwnParams(const int                                   CN,
                                              const occ::handle<IGESData_IGESEntity>&     ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolAssocGroupType tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFile tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileName tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefLibName tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefName tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalReferenceFile tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroup tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolHierarchy tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolName tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroup tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingleParent tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingularSubfigure tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSubfigureDef tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    default:
      break;
  }
}

void IGESBasic_ReadWriteModule::WriteOwnParams(const int                               CN,
                                               const occ::handle<IGESData_IGESEntity>& ent,
                                               IGESData_IGESWriter&                    IW) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolAssocGroupType tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFile tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileName tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefLibName tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefName tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalReferenceFile tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroup tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolHierarchy tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolName tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroup tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingleParent tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingularSubfigure tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSubfigureDef tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    default:
      break;
  }
}
