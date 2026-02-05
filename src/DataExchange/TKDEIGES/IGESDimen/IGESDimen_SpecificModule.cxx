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
#include <IGESDimen_AngularDimension.hpp>
#include <IGESDimen_BasicDimension.hpp>
#include <IGESDimen_CenterLine.hpp>
#include <IGESDimen_CurveDimension.hpp>
#include <IGESDimen_DiameterDimension.hpp>
#include <IGESDimen_DimensionDisplayData.hpp>
#include <IGESDimen_DimensionedGeometry.hpp>
#include <IGESDimen_DimensionTolerance.hpp>
#include <IGESDimen_DimensionUnits.hpp>
#include <IGESDimen_FlagNote.hpp>
#include <IGESDimen_GeneralLabel.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_GeneralSymbol.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <IGESDimen_LinearDimension.hpp>
#include <IGESDimen_NewDimensionedGeometry.hpp>
#include <IGESDimen_NewGeneralNote.hpp>
#include <IGESDimen_OrdinateDimension.hpp>
#include <IGESDimen_PointDimension.hpp>
#include <IGESDimen_RadiusDimension.hpp>
#include <IGESDimen_Section.hpp>
#include <IGESDimen_SectionedArea.hpp>
#include <IGESDimen_SpecificModule.hpp>
#include <IGESDimen_ToolAngularDimension.hpp>
#include <IGESDimen_ToolBasicDimension.hpp>
#include <IGESDimen_ToolCenterLine.hpp>
#include <IGESDimen_ToolCurveDimension.hpp>
#include <IGESDimen_ToolDiameterDimension.hpp>
#include <IGESDimen_ToolDimensionDisplayData.hpp>
#include <IGESDimen_ToolDimensionedGeometry.hpp>
#include <IGESDimen_ToolDimensionTolerance.hpp>
#include <IGESDimen_ToolDimensionUnits.hpp>
#include <IGESDimen_ToolFlagNote.hpp>
#include <IGESDimen_ToolGeneralLabel.hpp>
#include <IGESDimen_ToolGeneralNote.hpp>
#include <IGESDimen_ToolGeneralSymbol.hpp>
#include <IGESDimen_ToolLeaderArrow.hpp>
#include <IGESDimen_ToolLinearDimension.hpp>
#include <IGESDimen_ToolNewDimensionedGeometry.hpp>
#include <IGESDimen_ToolNewGeneralNote.hpp>
#include <IGESDimen_ToolOrdinateDimension.hpp>
#include <IGESDimen_ToolPointDimension.hpp>
#include <IGESDimen_ToolRadiusDimension.hpp>
#include <IGESDimen_ToolSection.hpp>
#include <IGESDimen_ToolSectionedArea.hpp>
#include <IGESDimen_ToolWitnessLine.hpp>
#include <IGESDimen_WitnessLine.hpp>
#include <MoniTool_Macros.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDimen_SpecificModule, IGESData_SpecificModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESDimen_SpecificModule::IGESDimen_SpecificModule() = default;

void IGESDimen_SpecificModule::OwnDump(const int                               CN,
                                       const occ::handle<IGESData_IGESEntity>& ent,
                                       const IGESData_IGESDumper&              dumper,
                                       Standard_OStream&                       S,
                                       const int                               own) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESDimen_AngularDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolAngularDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESDimen_BasicDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolBasicDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESDimen_CenterLine, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolCenterLine tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESDimen_CurveDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolCurveDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESDimen_DiameterDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolDiameterDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESDimen_DimensionDisplayData, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolDimensionDisplayData tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESDimen_DimensionTolerance, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolDimensionTolerance tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESDimen_DimensionUnits, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolDimensionUnits tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESDimen_DimensionedGeometry, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolDimensionedGeometry tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESDimen_FlagNote, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolFlagNote tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESDimen_GeneralLabel, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolGeneralLabel tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESDimen_GeneralNote, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolGeneralNote tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESDimen_GeneralSymbol, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolGeneralSymbol tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESDimen_LeaderArrow, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolLeaderArrow tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESDimen_LinearDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolLinearDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESDimen_NewDimensionedGeometry, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolNewDimensionedGeometry tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESDimen_NewGeneralNote, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolNewGeneralNote tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESDimen_OrdinateDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolOrdinateDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESDimen_PointDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolPointDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 20:
    {
      DeclareAndCast(IGESDimen_RadiusDimension, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolRadiusDimension tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 21:
    {
      DeclareAndCast(IGESDimen_Section, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolSection tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 22:
    {
      DeclareAndCast(IGESDimen_SectionedArea, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolSectionedArea tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 23:
    {
      DeclareAndCast(IGESDimen_WitnessLine, anent, ent);
      if (anent.IsNull())
        return;
      IGESDimen_ToolWitnessLine tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}

bool IGESDimen_SpecificModule::OwnCorrect(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& ent) const
{
  //   Applies only on some types
  switch (CN)
  {
    case 2:
    {
      DeclareAndCast(IGESDimen_BasicDimension, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolBasicDimension tool;
      return tool.OwnCorrect(anent);
    }
    case 3:
    {
      DeclareAndCast(IGESDimen_CenterLine, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolCenterLine tool;
      return tool.OwnCorrect(anent);
    }
    case 6:
    {
      DeclareAndCast(IGESDimen_DimensionDisplayData, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolDimensionDisplayData tool;
      return tool.OwnCorrect(anent);
    }
    case 7:
    {
      DeclareAndCast(IGESDimen_DimensionTolerance, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolDimensionTolerance tool;
      return tool.OwnCorrect(anent);
    }
    case 8:
    {
      DeclareAndCast(IGESDimen_DimensionUnits, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolDimensionUnits tool;
      return tool.OwnCorrect(anent);
    }
    case 9:
    {
      DeclareAndCast(IGESDimen_DimensionedGeometry, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolDimensionedGeometry tool;
      return tool.OwnCorrect(anent);
    }
    case 16:
    {
      DeclareAndCast(IGESDimen_NewDimensionedGeometry, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolNewDimensionedGeometry tool;
      return tool.OwnCorrect(anent);
    }
    case 21:
    {
      DeclareAndCast(IGESDimen_Section, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolSection tool;
      return tool.OwnCorrect(anent);
    }
    case 23:
    {
      DeclareAndCast(IGESDimen_WitnessLine, anent, ent);
      if (anent.IsNull())
        break;
      IGESDimen_ToolWitnessLine tool;
      return tool.OwnCorrect(anent);
    }
    default:
      break;
  }
  return false;
}
