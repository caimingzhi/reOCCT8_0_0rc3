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

#include <IGESBasic_AssocGroupType.hpp>
#include <IGESBasic_ExternalReferenceFile.hpp>
#include <IGESBasic_ExternalRefFile.hpp>
#include <IGESBasic_ExternalRefFileIndex.hpp>
#include <IGESBasic_ExternalRefFileName.hpp>
#include <IGESBasic_ExternalRefLibName.hpp>
#include <IGESBasic_ExternalRefName.hpp>
#include <IGESBasic_GeneralModule.hpp>
#include <IGESBasic_GroupWithoutBackP.hpp>
#include <IGESBasic_Hierarchy.hpp>
#include <IGESBasic_Name.hpp>
#include <IGESBasic_OrderedGroup.hpp>
#include <IGESBasic_OrderedGroupWithoutBackP.hpp>
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

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_GeneralModule, IGESData_GeneralModule)

//  Each Module is attached to a Protocol : it must interpret Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol
IGESBasic_GeneralModule::IGESBasic_GeneralModule() = default;

void IGESBasic_GeneralModule::OwnSharedCase(const int                               CN,
                                            const occ::handle<IGESData_IGESEntity>& ent,
                                            Interface_EntityIterator&               iter) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolAssocGroupType tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFile tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileName tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefLibName tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefName tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalReferenceFile tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroup tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolHierarchy tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolName tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroup tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingleParent tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingularSubfigure tool;
      tool.OwnShared(anent, iter);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSubfigureDef tool;
      tool.OwnShared(anent, iter);
    }
    break;
    default:
      break;
  }
}

IGESData_DirChecker IGESBasic_GeneralModule::DirChecker(
  const int                               CN,
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
      return tool.DirChecker(anent);
    }
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolExternalRefFile tool;
      return tool.DirChecker(anent);
    }
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolExternalRefFileIndex tool;
      return tool.DirChecker(anent);
    }
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolExternalRefFileName tool;
      return tool.DirChecker(anent);
    }
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolExternalRefLibName tool;
      return tool.DirChecker(anent);
    }
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolExternalRefName tool;
      return tool.DirChecker(anent);
    }
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolExternalReferenceFile tool;
      return tool.DirChecker(anent);
    }
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolGroup tool;
      return tool.DirChecker(anent);
    }
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolGroupWithoutBackP tool;
      return tool.DirChecker(anent);
    }
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolHierarchy tool;
      return tool.DirChecker(anent);
    }
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolName tool;
      return tool.DirChecker(anent);
    }
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolOrderedGroup tool;
      return tool.DirChecker(anent);
    }
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      return tool.DirChecker(anent);
    }
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolSingleParent tool;
      return tool.DirChecker(anent);
    }
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolSingularSubfigure tool;
      return tool.DirChecker(anent);
    }
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, anent, ent);
      if (anent.IsNull())
        break;
      IGESBasic_ToolSubfigureDef tool;
      return tool.DirChecker(anent);
    }
    default:
      break;
  }
  return IGESData_DirChecker(); // by default, no specific criterium
}

void IGESBasic_GeneralModule::OwnCheckCase(const int                               CN,
                                           const occ::handle<IGESData_IGESEntity>& ent,
                                           const Interface_ShareTool&              shares,
                                           occ::handle<Interface_Check>&           ach) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolAssocGroupType tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFile tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefFileName tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefLibName tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalRefName tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolExternalReferenceFile tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroup tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolHierarchy tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolName tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroup tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingleParent tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSingularSubfigure tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, anent, ent);
      if (anent.IsNull())
        return;
      IGESBasic_ToolSubfigureDef tool;
      tool.OwnCheck(anent, shares, ach);
    }
    break;
    default:
      break;
  }
}

bool IGESBasic_GeneralModule::NewVoid(const int CN, occ::handle<Standard_Transient>& ent) const
{
  switch (CN)
  {
    case 1:
      ent = new IGESBasic_AssocGroupType;
      break;
    case 2:
      ent = new IGESBasic_ExternalRefFile;
      break;
    case 3:
      ent = new IGESBasic_ExternalRefFileIndex;
      break;
    case 4:
      ent = new IGESBasic_ExternalRefFileName;
      break;
    case 5:
      ent = new IGESBasic_ExternalRefLibName;
      break;
    case 6:
      ent = new IGESBasic_ExternalRefName;
      break;
    case 7:
      ent = new IGESBasic_ExternalReferenceFile;
      break;
    case 8:
      ent = new IGESBasic_Group;
      break;
    case 9:
      ent = new IGESBasic_GroupWithoutBackP;
      break;
    case 10:
      ent = new IGESBasic_Hierarchy;
      break;
    case 11:
      ent = new IGESBasic_Name;
      break;
    case 12:
      ent = new IGESBasic_OrderedGroup;
      break;
    case 13:
      ent = new IGESBasic_OrderedGroupWithoutBackP;
      break;
    case 14:
      ent = new IGESBasic_SingleParent;
      break;
    case 15:
      ent = new IGESBasic_SingularSubfigure;
      break;
    case 16:
      ent = new IGESBasic_SubfigureDef;
      break;
    default:
      return false; // by default, Failure on Recognize
  }
  return true;
}

void IGESBasic_GeneralModule::OwnCopyCase(const int                               CN,
                                          const occ::handle<IGESData_IGESEntity>& entfrom,
                                          const occ::handle<IGESData_IGESEntity>& entto,
                                          Interface_CopyTool&                     TC) const
{
  switch (CN)
  {
    case 1:
    {
      DeclareAndCast(IGESBasic_AssocGroupType, enfr, entfrom);
      DeclareAndCast(IGESBasic_AssocGroupType, ento, entto);
      IGESBasic_ToolAssocGroupType tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 2:
    {
      DeclareAndCast(IGESBasic_ExternalRefFile, enfr, entfrom);
      DeclareAndCast(IGESBasic_ExternalRefFile, ento, entto);
      IGESBasic_ToolExternalRefFile tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 3:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, enfr, entfrom);
      DeclareAndCast(IGESBasic_ExternalRefFileIndex, ento, entto);
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 4:
    {
      DeclareAndCast(IGESBasic_ExternalRefFileName, enfr, entfrom);
      DeclareAndCast(IGESBasic_ExternalRefFileName, ento, entto);
      IGESBasic_ToolExternalRefFileName tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 5:
    {
      DeclareAndCast(IGESBasic_ExternalRefLibName, enfr, entfrom);
      DeclareAndCast(IGESBasic_ExternalRefLibName, ento, entto);
      IGESBasic_ToolExternalRefLibName tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 6:
    {
      DeclareAndCast(IGESBasic_ExternalRefName, enfr, entfrom);
      DeclareAndCast(IGESBasic_ExternalRefName, ento, entto);
      IGESBasic_ToolExternalRefName tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 7:
    {
      DeclareAndCast(IGESBasic_ExternalReferenceFile, enfr, entfrom);
      DeclareAndCast(IGESBasic_ExternalReferenceFile, ento, entto);
      IGESBasic_ToolExternalReferenceFile tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 8:
    {
      DeclareAndCast(IGESBasic_Group, enfr, entfrom);
      DeclareAndCast(IGESBasic_Group, ento, entto);
      IGESBasic_ToolGroup tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 9:
    {
      DeclareAndCast(IGESBasic_GroupWithoutBackP, enfr, entfrom);
      DeclareAndCast(IGESBasic_GroupWithoutBackP, ento, entto);
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 10:
    {
      DeclareAndCast(IGESBasic_Hierarchy, enfr, entfrom);
      DeclareAndCast(IGESBasic_Hierarchy, ento, entto);
      IGESBasic_ToolHierarchy tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 11:
    {
      DeclareAndCast(IGESBasic_Name, enfr, entfrom);
      DeclareAndCast(IGESBasic_Name, ento, entto);
      IGESBasic_ToolName tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 12:
    {
      DeclareAndCast(IGESBasic_OrderedGroup, enfr, entfrom);
      DeclareAndCast(IGESBasic_OrderedGroup, ento, entto);
      IGESBasic_ToolOrderedGroup tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 13:
    {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, enfr, entfrom);
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP, ento, entto);
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 14:
    {
      DeclareAndCast(IGESBasic_SingleParent, enfr, entfrom);
      DeclareAndCast(IGESBasic_SingleParent, ento, entto);
      IGESBasic_ToolSingleParent tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 15:
    {
      DeclareAndCast(IGESBasic_SingularSubfigure, enfr, entfrom);
      DeclareAndCast(IGESBasic_SingularSubfigure, ento, entto);
      IGESBasic_ToolSingularSubfigure tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    case 16:
    {
      DeclareAndCast(IGESBasic_SubfigureDef, enfr, entfrom);
      DeclareAndCast(IGESBasic_SubfigureDef, ento, entto);
      IGESBasic_ToolSubfigureDef tool;
      tool.OwnCopy(enfr, ento, TC);
    }
    break;
    default:
      break;
  }
}

int IGESBasic_GeneralModule::CategoryNumber(const int CN,
                                            const occ::handle<Standard_Transient>&,
                                            const Interface_ShareTool&) const
{
  if (CN == 10 || CN == 11)
    return Interface_Category::Number("Auxiliary");
  if (CN >= 2 && CN <= 6)
    return Interface_Category::Number("Description");
  return Interface_Category::Number("Structure");
}
