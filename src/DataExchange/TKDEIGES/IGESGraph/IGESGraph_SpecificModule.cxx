

#include <IGESData_IGESDumper.hpp>
#include <IGESGraph_Color.hpp>
#include <IGESGraph_DefinitionLevel.hpp>
#include <IGESGraph_DrawingSize.hpp>
#include <IGESGraph_DrawingUnits.hpp>
#include <IGESGraph_HighLight.hpp>
#include <IGESGraph_IntercharacterSpacing.hpp>
#include <IGESGraph_LineFontDefPattern.hpp>
#include <IGESGraph_LineFontDefTemplate.hpp>
#include <IGESGraph_LineFontPredefined.hpp>
#include <IGESGraph_NominalSize.hpp>
#include <IGESGraph_Pick.hpp>
#include <IGESGraph_SpecificModule.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <IGESGraph_TextFontDef.hpp>
#include <IGESGraph_ToolColor.hpp>
#include <IGESGraph_ToolDefinitionLevel.hpp>
#include <IGESGraph_ToolDrawingSize.hpp>
#include <IGESGraph_ToolDrawingUnits.hpp>
#include <IGESGraph_ToolHighLight.hpp>
#include <IGESGraph_ToolIntercharacterSpacing.hpp>
#include <IGESGraph_ToolLineFontDefPattern.hpp>
#include <IGESGraph_ToolLineFontDefTemplate.hpp>
#include <IGESGraph_ToolLineFontPredefined.hpp>
#include <IGESGraph_ToolNominalSize.hpp>
#include <IGESGraph_ToolPick.hpp>
#include <IGESGraph_ToolTextDisplayTemplate.hpp>
#include <IGESGraph_ToolTextFontDef.hpp>
#include <IGESGraph_ToolUniformRectGrid.hpp>
#include <IGESGraph_UniformRectGrid.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_SpecificModule, IGESData_SpecificModule)

IGESGraph_SpecificModule::IGESGraph_SpecificModule() = default;

void IGESGraph_SpecificModule::OwnDump(const int                               CN,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int                               own) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESGraph_Color, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolColor tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESGraph_DefinitionLevel, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDefinitionLevel tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESGraph_DrawingSize, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDrawingSize tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESGraph_DrawingUnits, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDrawingUnits tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESGraph_HighLight, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolHighLight tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESGraph_IntercharacterSpacing, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESGraph_LineFontDefPattern, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontDefPattern tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESGraph_LineFontPredefined, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontPredefined tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESGraph_LineFontDefTemplate, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESGraph_NominalSize, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolNominalSize tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESGraph_Pick, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolPick tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESGraph_TextDisplayTemplate, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESGraph_TextFontDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolTextFontDef tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESGraph_UniformRectGrid, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolUniformRectGrid tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}

bool IGESGraph_SpecificModule::OwnCorrect(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& ent) const
{

  switch (CN)
  {
    case 3:
    {
      DeclareAndCast(IGESGraph_DrawingSize, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolDrawingSize tool;
      return tool.OwnCorrect(anent);
    }
    case 4:
    {
      DeclareAndCast(IGESGraph_DrawingUnits, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolDrawingUnits tool;
      return tool.OwnCorrect(anent);
    }
    case 5:
    {
      DeclareAndCast(IGESGraph_HighLight, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolHighLight tool;
      return tool.OwnCorrect(anent);
    }
    case 6:
    {
      DeclareAndCast(IGESGraph_IntercharacterSpacing, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolIntercharacterSpacing tool;
      return tool.OwnCorrect(anent);
    }
    case 8:
    {
      DeclareAndCast(IGESGraph_LineFontPredefined, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolLineFontPredefined tool;
      return tool.OwnCorrect(anent);
    }
    case 10:
    {
      DeclareAndCast(IGESGraph_NominalSize, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolNominalSize tool;
      return tool.OwnCorrect(anent);
    }
    case 11:
    {
      DeclareAndCast(IGESGraph_Pick, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolPick tool;
      return tool.OwnCorrect(anent);
    }
    case 14:
    {
      DeclareAndCast(IGESGraph_UniformRectGrid, anent, ent);
      if (anent.IsNull())
        break;
      IGESGraph_ToolUniformRectGrid tool;
      return tool.OwnCorrect(anent);
    }
    default:
      break;
  }
  return false;
}
