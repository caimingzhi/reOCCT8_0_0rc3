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

#include <IGESAppli_DrilledHole.hpp>
#include <IGESAppli_ElementResults.hpp>
#include <IGESAppli_FiniteElement.hpp>
#include <IGESAppli_Flow.hpp>
#include <IGESAppli_FlowLineSpec.hpp>
#include <IGESAppli_LevelFunction.hpp>
#include <IGESAppli_LevelToPWBLayerMap.hpp>
#include <IGESAppli_LineWidening.hpp>
#include <IGESAppli_NodalConstraint.hpp>
#include <IGESAppli_NodalDisplAndRot.hpp>
#include <IGESAppli_NodalResults.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESAppli_PartNumber.hpp>
#include <IGESAppli_PinNumber.hpp>
#include <IGESAppli_PipingFlow.hpp>
#include <IGESAppli_PWBArtworkStackup.hpp>
#include <IGESAppli_PWBDrilledHole.hpp>
#include <IGESAppli_ReadWriteModule.hpp>
#include <IGESAppli_ReferenceDesignator.hpp>
#include <IGESAppli_RegionRestriction.hpp>
#include <IGESAppli_ToolDrilledHole.hpp>
#include <IGESAppli_ToolElementResults.hpp>
#include <IGESAppli_ToolFiniteElement.hpp>
#include <IGESAppli_ToolFlow.hpp>
#include <IGESAppli_ToolFlowLineSpec.hpp>
#include <IGESAppli_ToolLevelFunction.hpp>
#include <IGESAppli_ToolLevelToPWBLayerMap.hpp>
#include <IGESAppli_ToolLineWidening.hpp>
#include <IGESAppli_ToolNodalConstraint.hpp>
#include <IGESAppli_ToolNodalDisplAndRot.hpp>
#include <IGESAppli_ToolNodalResults.hpp>
#include <IGESAppli_ToolNode.hpp>
#include <IGESAppli_ToolPartNumber.hpp>
#include <IGESAppli_ToolPinNumber.hpp>
#include <IGESAppli_ToolPipingFlow.hpp>
#include <IGESAppli_ToolPWBArtworkStackup.hpp>
#include <IGESAppli_ToolPWBDrilledHole.hpp>
#include <IGESAppli_ToolReferenceDesignator.hpp>
#include <IGESAppli_ToolRegionRestriction.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_ReadWriteModule, IGESData_ReadWriteModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESAppli_ReadWriteModule::IGESAppli_ReadWriteModule() = default;

int IGESAppli_ReadWriteModule::CaseIGES(const int typenum, const int formnum) const
{
  switch (typenum)
  {
    case 134:
      return 12;
    case 136:
      return 3;
    case 138:
      return 10;
    case 146:
      return 11;
    case 148:
      return 2;
    case 402:
      switch (formnum)
      {
        case 18:
          return 4;
        case 20:
          return 17;
        default:
          break;
      }
      break;
    case 406:
      switch (formnum)
      {
        case 2:
          return 19;
        case 3:
          return 6;
        case 5:
          return 8;
        case 6:
          return 1;
        case 7:
          return 18;
        case 8:
          return 16;
        case 9:
          return 15;
        case 14:
          return 5;
        case 24:
          return 7;
        case 25:
          return 13;
        case 26:
          return 14;
        default:
          break;
      }
      break;
    case 418:
      return 9;
    default:
      break;
  }
  return 0;
}

void IGESAppli_ReadWriteModule::ReadOwnParams(const int                                   CN,
                                              const occ::handle<IGESData_IGESEntity>&     ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESAppli_DrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolDrilledHole tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESAppli_ElementResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolElementResults tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESAppli_FiniteElement, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFiniteElement tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESAppli_Flow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlow tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESAppli_FlowLineSpec, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESAppli_LevelFunction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelFunction tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESAppli_LineWidening, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLineWidening tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESAppli_NodalConstraint, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalConstraint tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESAppli_NodalDisplAndRot, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESAppli_NodalResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalResults tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESAppli_Node, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNode tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESAppli_PWBArtworkStackup, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESAppli_PWBDrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESAppli_PartNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPartNumber tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESAppli_PinNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPinNumber tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESAppli_PipingFlow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPipingFlow tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESAppli_ReferenceDesignator, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESAppli_RegionRestriction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolRegionRestriction tool;
      tool.ReadOwnParams(anent, IR, PR);
    }
    break;
    default:
      break;
  }
}

void IGESAppli_ReadWriteModule::WriteOwnParams(const int                               CN,
                                               const occ::handle<IGESData_IGESEntity>& ent,
                                               IGESData_IGESWriter&                    IW) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESAppli_DrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolDrilledHole tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESAppli_ElementResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolElementResults tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESAppli_FiniteElement, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFiniteElement tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESAppli_Flow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlow tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESAppli_FlowLineSpec, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESAppli_LevelFunction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelFunction tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESAppli_LineWidening, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLineWidening tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESAppli_NodalConstraint, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalConstraint tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESAppli_NodalDisplAndRot, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESAppli_NodalResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalResults tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESAppli_Node, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNode tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESAppli_PWBArtworkStackup, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESAppli_PWBDrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESAppli_PartNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPartNumber tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESAppli_PinNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPinNumber tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 17:
    {
      DeclareAndCast(IGESAppli_PipingFlow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPipingFlow tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 18:
    {
      DeclareAndCast(IGESAppli_ReferenceDesignator, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    case 19:
    {
      DeclareAndCast(IGESAppli_RegionRestriction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolRegionRestriction tool;
      tool.WriteOwnParams(anent, IW);
    }
    break;
    default:
      break;
  }
}
