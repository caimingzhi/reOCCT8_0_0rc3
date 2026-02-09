

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
#include <IGESBasic_SingleParent.hpp>
#include <IGESBasic_SingularSubfigure.hpp>
#include <IGESBasic_SpecificModule.hpp>
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
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESEntity.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_SpecificModule, IGESData_SpecificModule)

IGESBasic_SpecificModule::IGESBasic_SpecificModule() = default;

void IGESBasic_SpecificModule::OwnDump(const int                               CN,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int                               own) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolAssocGroupType tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFile tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileName tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefLibName tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefName tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalReferenceFile tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroup tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolHierarchy tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolName tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroup tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingleParent tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingularSubfigure tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSubfigureDef tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}

bool IGESBasic_SpecificModule::OwnCorrect(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& ent) const
{

  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolAssocGroupType tool;
      return tool.OwnCorrect(anent);
    }
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolGroup tool;
      return tool.OwnCorrect(anent);
    }
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolGroupWithoutBackP tool;
      return tool.OwnCorrect(anent);
    }
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolHierarchy tool;
      return tool.OwnCorrect(anent);
    }
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolName tool;
      return tool.OwnCorrect(anent);
    }
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolOrderedGroup tool;
      return tool.OwnCorrect(anent);
    }
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      return tool.OwnCorrect(anent);
    }
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolSingleParent tool;
      return tool.OwnCorrect(anent);
    }
    default:
      break;
  }
  return false;
}
