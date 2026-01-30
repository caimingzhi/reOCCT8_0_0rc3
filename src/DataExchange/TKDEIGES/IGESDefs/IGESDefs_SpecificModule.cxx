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
#include <IGESDefs_AssociativityDef.hpp>
#include <IGESDefs_AttributeDef.hpp>
#include <IGESDefs_AttributeTable.hpp>
#include <IGESDefs_GenericData.hpp>
#include <IGESDefs_MacroDef.hpp>
#include <IGESDefs_SpecificModule.hpp>
#include <IGESDefs_TabularData.hpp>
#include <IGESDefs_ToolAssociativityDef.hpp>
#include <IGESDefs_ToolAttributeDef.hpp>
#include <IGESDefs_ToolAttributeTable.hpp>
#include <IGESDefs_ToolGenericData.hpp>
#include <IGESDefs_ToolMacroDef.hpp>
#include <IGESDefs_ToolTabularData.hpp>
#include <IGESDefs_ToolUnitsData.hpp>
#include <IGESDefs_UnitsData.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_SpecificModule, IGESData_SpecificModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESDefs_SpecificModule::IGESDefs_SpecificModule() = default;

void IGESDefs_SpecificModule::OwnDump(const int                               CN,
                                      const occ::handle<IGESData_IGESEntity>& ent,
                                      const IGESData_IGESDumper&              dumper,
                                      Standard_OStream&                       S,
                                      const int                               own) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESDefs_AssociativityDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolAssociativityDef tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 2: {
      DeclareAndCast(IGESDefs_AttributeDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolAttributeDef tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 3: {
      DeclareAndCast(IGESDefs_AttributeTable, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolAttributeTable tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 4: {
      DeclareAndCast(IGESDefs_GenericData, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolGenericData tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 5: {
      DeclareAndCast(IGESDefs_MacroDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolMacroDef tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 6: {
      DeclareAndCast(IGESDefs_TabularData, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolTabularData tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    case 7: {
      DeclareAndCast(IGESDefs_UnitsData, anent, ent);
      if (anent.IsNull())
        return;
      IGESDefs_ToolUnitsData tool;
      tool.OwnDump(anent, dumper, S, own);
    }
    break;
    default:
      break;
  }
}
