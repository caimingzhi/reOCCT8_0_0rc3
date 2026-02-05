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

#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
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
#include <IGESGraph_ReadWriteModule.hpp>
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
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_ReadWriteModule, IGESData_ReadWriteModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESGraph_ReadWriteModule::IGESGraph_ReadWriteModule() = default;

int IGESGraph_ReadWriteModule::CaseIGES(const int typenum, const int formnum) const
{
  switch (typenum)
  {
    case 304:
      if (formnum == 1)
        return 9;
      else if (formnum == 2)
        return 7;
      break;
    case 310:
      return 13;
    case 312:
      return 12;
    case 314:
      return 1;
    case 406:
      switch (formnum)
      {
        case 1:
          return 2;
        case 13:
          return 10;
        case 16:
          return 3;
        case 17:
          return 4;
        case 18:
          return 6;
        case 19:
          return 8;
        case 20:
          return 5;
        case 21:
          return 11;
        case 22:
          return 14;
        default:
          break;
      }
      break;
    default:
      break;
  }
  return 0;
}

void IGESGraph_ReadWriteModule::ReadOwnParams(const int                                   CN,
                                              const occ::handle<IGESData_IGESEntity>&     ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESGraph_Color, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolColor tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESGraph_DefinitionLevel, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDefinitionLevel tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESGraph_DrawingSize, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDrawingSize tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESGraph_DrawingUnits, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDrawingUnits tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESGraph_HighLight, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolHighLight tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESGraph_IntercharacterSpacing, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESGraph_LineFontDefPattern, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontDefPattern tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESGraph_LineFontPredefined, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontPredefined tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESGraph_LineFontDefTemplate, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESGraph_NominalSize, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolNominalSize tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESGraph_Pick, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolPick tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESGraph_TextDisplayTemplate, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESGraph_TextFontDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolTextFontDef tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESGraph_UniformRectGrid, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolUniformRectGrid tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    default:
      break;
  }
}

void IGESGraph_ReadWriteModule::WriteOwnParams(const int                               CN,
                                               const occ::handle<IGESData_IGESEntity>& ent,
                                               IGESData_IGESWriter&                    IW) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESGraph_Color, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolColor tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESGraph_DefinitionLevel, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDefinitionLevel tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESGraph_DrawingSize, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDrawingSize tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESGraph_DrawingUnits, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolDrawingUnits tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESGraph_HighLight, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolHighLight tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESGraph_IntercharacterSpacing, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESGraph_LineFontDefPattern, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontDefPattern tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESGraph_LineFontPredefined, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontPredefined tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESGraph_LineFontDefTemplate, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESGraph_NominalSize, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolNominalSize tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESGraph_Pick, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolPick tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESGraph_TextDisplayTemplate, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESGraph_TextFontDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolTextFontDef tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESGraph_UniformRectGrid, anent, ent);
      if (anent.IsNull())
        return;
      IGESGraph_ToolUniformRectGrid tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    default:
      break;
  }
}
