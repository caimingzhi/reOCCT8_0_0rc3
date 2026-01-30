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
#include <IGESAppli_GeneralModule.hpp>
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
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Interface_Category.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_GeneralModule, IGESData_GeneralModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESAppli_GeneralModule::IGESAppli_GeneralModule() = default;

void IGESAppli_GeneralModule::OwnSharedCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& ent,
                                            Interface_EntityIterator&               iter) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESAppli_DrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolDrilledHole tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 2: {
      DeclareAndCast(IGESAppli_ElementResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolElementResults tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 3: {
      DeclareAndCast(IGESAppli_FiniteElement, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFiniteElement tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 4: {
      DeclareAndCast(IGESAppli_Flow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlow tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 5: {
      DeclareAndCast(IGESAppli_FlowLineSpec, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 6: {
      DeclareAndCast(IGESAppli_LevelFunction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelFunction tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 7: {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 8: {
      DeclareAndCast(IGESAppli_LineWidening, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLineWidening tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 9: {
      DeclareAndCast(IGESAppli_NodalConstraint, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 10: {
      DeclareAndCast(IGESAppli_NodalDisplAndRot, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 11: {
      DeclareAndCast(IGESAppli_NodalResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalResults tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 12: {
      DeclareAndCast(IGESAppli_Node, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNode tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 13: {
      DeclareAndCast(IGESAppli_PWBArtworkStackup, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 14: {
      DeclareAndCast(IGESAppli_PWBDrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 15: {
      DeclareAndCast(IGESAppli_PartNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPartNumber tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 16: {
      DeclareAndCast(IGESAppli_PinNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPinNumber tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 17: {
      DeclareAndCast(IGESAppli_PipingFlow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPipingFlow tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 18: {
      DeclareAndCast(IGESAppli_ReferenceDesignator, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 19: {
      DeclareAndCast(IGESAppli_RegionRestriction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnShared(anent, iter);
    }
    break;
    default:
      break;
  }
}

IGESData_DirChecker IGESAppli_GeneralModule::DirChecker(
  const int                               CN,
  const occ::handle<IGESData_IGESEntity>& ent) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESAppli_DrilledHole, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolDrilledHole tool;
      return tool.DirChecker(anent);
    }
    case 2: {
      DeclareAndCast(IGESAppli_ElementResults, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolElementResults tool;
      return tool.DirChecker(anent);
    }
    case 3: {
      DeclareAndCast(IGESAppli_FiniteElement, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolFiniteElement tool;
      return tool.DirChecker(anent);
    }
    case 4: {
      DeclareAndCast(IGESAppli_Flow, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolFlow tool;
      return tool.DirChecker(anent);
    }
    case 5: {
      DeclareAndCast(IGESAppli_FlowLineSpec, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolFlowLineSpec tool;
      return tool.DirChecker(anent);
    }
    case 6: {
      DeclareAndCast(IGESAppli_LevelFunction, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolLevelFunction tool;
      return tool.DirChecker(anent);
    }
    case 7: {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      return tool.DirChecker(anent);
    }
    case 8: {
      DeclareAndCast(IGESAppli_LineWidening, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolLineWidening tool;
      return tool.DirChecker(anent);
    }
    case 9: {
      DeclareAndCast(IGESAppli_NodalConstraint, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolNodalConstraint tool;
      return tool.DirChecker(anent);
    }
    case 10: {
      DeclareAndCast(IGESAppli_NodalDisplAndRot, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolNodalDisplAndRot tool;
      return tool.DirChecker(anent);
    }
    case 11: {
      DeclareAndCast(IGESAppli_NodalResults, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolNodalResults tool;
      return tool.DirChecker(anent);
    }
    case 12: {
      DeclareAndCast(IGESAppli_Node, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolNode tool;
      return tool.DirChecker(anent);
    }
    case 13: {
      DeclareAndCast(IGESAppli_PWBArtworkStackup, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolPWBArtworkStackup tool;
      return tool.DirChecker(anent);
    }
    case 14: {
      DeclareAndCast(IGESAppli_PWBDrilledHole, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolPWBDrilledHole tool;
      return tool.DirChecker(anent);
    }
    case 15: {
      DeclareAndCast(IGESAppli_PartNumber, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolPartNumber tool;
      return tool.DirChecker(anent);
    }
    case 16: {
      DeclareAndCast(IGESAppli_PinNumber, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolPinNumber tool;
      return tool.DirChecker(anent);
    }
    case 17: {
      DeclareAndCast(IGESAppli_PipingFlow, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolPipingFlow tool;
      return tool.DirChecker(anent);
    }
    case 18: {
      DeclareAndCast(IGESAppli_ReferenceDesignator, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolReferenceDesignator tool;
      return tool.DirChecker(anent);
    }
    case 19: {
      DeclareAndCast(IGESAppli_RegionRestriction, anent, ent);
      if (anent.IsNull())
        break;
      IGESAppli_ToolRegionRestriction tool;
      return tool.DirChecker(anent);
    }
    default:
      break;
  }
  return IGESData_DirChecker(); // by default, no specific criterium
}

void IGESAppli_GeneralModule::OwnCheckCase(const int                               CN,
                                           const occ::handle<IGESData_IGESEntity>& ent,
                                           const Interface_ShareTool&              shares,
                                           occ::handle<Interface_Check>&           ach) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESAppli_DrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolDrilledHole tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 2: {
      DeclareAndCast(IGESAppli_ElementResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolElementResults tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 3: {
      DeclareAndCast(IGESAppli_FiniteElement, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFiniteElement tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 4: {
      DeclareAndCast(IGESAppli_Flow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlow tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 5: {
      DeclareAndCast(IGESAppli_FlowLineSpec, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 6: {
      DeclareAndCast(IGESAppli_LevelFunction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelFunction tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 7: {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 8: {
      DeclareAndCast(IGESAppli_LineWidening, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolLineWidening tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 9: {
      DeclareAndCast(IGESAppli_NodalConstraint, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 10: {
      DeclareAndCast(IGESAppli_NodalDisplAndRot, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 11: {
      DeclareAndCast(IGESAppli_NodalResults, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNodalResults tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 12: {
      DeclareAndCast(IGESAppli_Node, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolNode tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 13: {
      DeclareAndCast(IGESAppli_PWBArtworkStackup, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 14: {
      DeclareAndCast(IGESAppli_PWBDrilledHole, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 15: {
      DeclareAndCast(IGESAppli_PartNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPartNumber tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 16: {
      DeclareAndCast(IGESAppli_PinNumber, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPinNumber tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 17: {
      DeclareAndCast(IGESAppli_PipingFlow, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolPipingFlow tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 18: {
      DeclareAndCast(IGESAppli_ReferenceDesignator, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 19: {
      DeclareAndCast(IGESAppli_RegionRestriction, anent, ent);
      if (anent.IsNull())
        return;
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    default:
      break;
  }
}

bool IGESAppli_GeneralModule::NewVoid(const int CN, occ::handle<Standard_Transient>& ent) const
{
  switch (CN)
  {
    case 1:
      ent = new IGESAppli_DrilledHole;
      break;
    case 2:
      ent = new IGESAppli_ElementResults;
      break;
    case 3:
      ent = new IGESAppli_FiniteElement;
      break;
    case 4:
      ent = new IGESAppli_Flow;
      break;
    case 5:
      ent = new IGESAppli_FlowLineSpec;
      break;
    case 6:
      ent = new IGESAppli_LevelFunction;
      break;
    case 7:
      ent = new IGESAppli_LevelToPWBLayerMap;
      break;
    case 8:
      ent = new IGESAppli_LineWidening;
      break;
    case 9:
      ent = new IGESAppli_NodalConstraint;
      break;
    case 10:
      ent = new IGESAppli_NodalDisplAndRot;
      break;
    case 11:
      ent = new IGESAppli_NodalResults;
      break;
    case 12:
      ent = new IGESAppli_Node;
      break;
    case 13:
      ent = new IGESAppli_PWBArtworkStackup;
      break;
    case 14:
      ent = new IGESAppli_PWBDrilledHole;
      break;
    case 15:
      ent = new IGESAppli_PartNumber;
      break;
    case 16:
      ent = new IGESAppli_PinNumber;
      break;
    case 17:
      ent = new IGESAppli_PipingFlow;
      break;
    case 18:
      ent = new IGESAppli_ReferenceDesignator;
      break;
    case 19:
      ent = new IGESAppli_RegionRestriction;
      break;
    default:
      return false; // by default, Failure on Recognize
  }
  return true;
}

void IGESAppli_GeneralModule::OwnCopyCase(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& entfrom,
                                          const occ::handle<IGESData_IGESEntity>& entto,
                                          Interface_CopyTool&                     TC) const
{
  switch (CN)
  {
    case 1: {
      DeclareAndCast(IGESAppli_DrilledHole, enfr, entfrom);
      DeclareAndCast(IGESAppli_DrilledHole, ento, entto);
      IGESAppli_ToolDrilledHole tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 2: {
      DeclareAndCast(IGESAppli_ElementResults, enfr, entfrom);
      DeclareAndCast(IGESAppli_ElementResults, ento, entto);
      IGESAppli_ToolElementResults tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 3: {
      DeclareAndCast(IGESAppli_FiniteElement, enfr, entfrom);
      DeclareAndCast(IGESAppli_FiniteElement, ento, entto);
      IGESAppli_ToolFiniteElement tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 4: {
      DeclareAndCast(IGESAppli_Flow, enfr, entfrom);
      DeclareAndCast(IGESAppli_Flow, ento, entto);
      IGESAppli_ToolFlow tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 5: {
      DeclareAndCast(IGESAppli_FlowLineSpec, enfr, entfrom);
      DeclareAndCast(IGESAppli_FlowLineSpec, ento, entto);
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 6: {
      DeclareAndCast(IGESAppli_LevelFunction, enfr, entfrom);
      DeclareAndCast(IGESAppli_LevelFunction, ento, entto);
      IGESAppli_ToolLevelFunction tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 7: {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, enfr, entfrom);
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap, ento, entto);
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 8: {
      DeclareAndCast(IGESAppli_LineWidening, enfr, entfrom);
      DeclareAndCast(IGESAppli_LineWidening, ento, entto);
      IGESAppli_ToolLineWidening tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 9: {
      DeclareAndCast(IGESAppli_NodalConstraint, enfr, entfrom);
      DeclareAndCast(IGESAppli_NodalConstraint, ento, entto);
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 10: {
      DeclareAndCast(IGESAppli_NodalDisplAndRot, enfr, entfrom);
      DeclareAndCast(IGESAppli_NodalDisplAndRot, ento, entto);
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 11: {
      DeclareAndCast(IGESAppli_NodalResults, enfr, entfrom);
      DeclareAndCast(IGESAppli_NodalResults, ento, entto);
      IGESAppli_ToolNodalResults tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 12: {
      DeclareAndCast(IGESAppli_Node, enfr, entfrom);
      DeclareAndCast(IGESAppli_Node, ento, entto);
      IGESAppli_ToolNode tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 13: {
      DeclareAndCast(IGESAppli_PWBArtworkStackup, enfr, entfrom);
      DeclareAndCast(IGESAppli_PWBArtworkStackup, ento, entto);
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 14: {
      DeclareAndCast(IGESAppli_PWBDrilledHole, enfr, entfrom);
      DeclareAndCast(IGESAppli_PWBDrilledHole, ento, entto);
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 15: {
      DeclareAndCast(IGESAppli_PartNumber, enfr, entfrom);
      DeclareAndCast(IGESAppli_PartNumber, ento, entto);
      IGESAppli_ToolPartNumber tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 16: {
      DeclareAndCast(IGESAppli_PinNumber, enfr, entfrom);
      DeclareAndCast(IGESAppli_PinNumber, ento, entto);
      IGESAppli_ToolPinNumber tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 17: {
      DeclareAndCast(IGESAppli_PipingFlow, enfr, entfrom);
      DeclareAndCast(IGESAppli_PipingFlow, ento, entto);
      IGESAppli_ToolPipingFlow tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 18: {
      DeclareAndCast(IGESAppli_ReferenceDesignator, enfr, entfrom);
      DeclareAndCast(IGESAppli_ReferenceDesignator, ento, entto);
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 19: {
      DeclareAndCast(IGESAppli_RegionRestriction, enfr, entfrom);
      DeclareAndCast(IGESAppli_RegionRestriction, ento, entto);
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    default:
      break;
  }
}

int IGESAppli_GeneralModule::CategoryNumber(const int CN,
                                            const occ::handle<Standard_Transient>& /*ent*/,
                                            const Interface_ShareTool&) const
{
  if (CN == 4 || CN == 5 || CN == 17)
    return Interface_Category::Number("Piping");
  if (CN == 2 || CN == 3 || (CN >= 9 && CN <= 12))
    return Interface_Category::Number("FEA");
  return Interface_Category::Number("Professional");
}
