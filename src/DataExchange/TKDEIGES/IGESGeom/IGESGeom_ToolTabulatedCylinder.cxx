// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Status.hpp>
#include <IGESGeom_TabulatedCylinder.hpp>
#include <IGESGeom_ToolTabulatedCylinder.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

// MGE 31/07/98
IGESGeom_ToolTabulatedCylinder::IGESGeom_ToolTabulatedCylinder() = default;

void IGESGeom_ToolTabulatedCylinder::ReadOwnParams(
  const occ::handle<IGESGeom_TabulatedCylinder>& ent,
  const occ::handle<IGESData_IGESReaderData>&    IR,
  IGESData_ParamReader&                          PR) const
{
  // MGE 31/07/98
  // Building of messages
  //========================================
  Message_Msg Msg157("XSTEP_157");
  //========================================

  occ::handle<IGESData_IGESEntity> aDirectrix;
  gp_XYZ                           anEnd;
  IGESData_Status                  aStatus;

  // bool st; //szv#4:S4163:12Mar99 not needed

  // Reading the directrix curve entity
  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aDirectrix))
  { // szv#4:S4163:12Mar99 `st=` not needed
    Message_Msg Msg156("XSTEP_156");
    switch (aStatus)
    {
      case IGESData_ReferenceError: {
        Message_Msg Msg216("IGES_216");
        Msg156.Arg(Msg216.Value());
        PR.SendFail(Msg156);
        break;
      }
      case IGESData_EntityError: {
        Message_Msg Msg217("IGES_217");
        Msg156.Arg(Msg217.Value());
        PR.SendFail(Msg156);
        break;
      }
      default: {
      }
    }
  }
  // st = PR.ReadEntity(IR, PR.Current(), "Directrix", aDirectrix);

  // Reading the terminate point of the generatrix
  PR.ReadXYZ(PR.CurrentList(1, 3), Msg157, anEnd); // szv#4:S4163:12Mar99 `st=` not needed
  // st = PR.ReadXYZ(PR.CurrentList(1, 3), "Terminate Point", anEnd);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aDirectrix, anEnd);
}

void IGESGeom_ToolTabulatedCylinder::WriteOwnParams(
  const occ::handle<IGESGeom_TabulatedCylinder>& ent,
  IGESData_IGESWriter&                           IW) const
{
  IW.Send(ent->Directrix());
  IW.Send(ent->EndPoint().X());
  IW.Send(ent->EndPoint().Y());
  IW.Send(ent->EndPoint().Z());
}

void IGESGeom_ToolTabulatedCylinder::OwnShared(const occ::handle<IGESGeom_TabulatedCylinder>& ent,
                                               Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Directrix());
}

void IGESGeom_ToolTabulatedCylinder::OwnCopy(const occ::handle<IGESGeom_TabulatedCylinder>& another,
                                             const occ::handle<IGESGeom_TabulatedCylinder>& ent,
                                             Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESData_IGESEntity, aDirectrix, TC.Transferred(another->Directrix()));

  gp_XYZ anEnd = another->EndPoint().XYZ();

  ent->Init(aDirectrix, anEnd);
}

IGESData_DirChecker IGESGeom_ToolTabulatedCylinder::DirChecker(
  const occ::handle<IGESGeom_TabulatedCylinder>& /* ent */) const
{
  IGESData_DirChecker DC(122, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  //  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGeom_ToolTabulatedCylinder::OwnCheck(
  const occ::handle<IGESGeom_TabulatedCylinder>& /* ent */,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& /* ach */) const
{
}

void IGESGeom_ToolTabulatedCylinder::OwnDump(const occ::handle<IGESGeom_TabulatedCylinder>& ent,
                                             const IGESData_IGESDumper&                     dumper,
                                             Standard_OStream&                              S,
                                             const int level) const
{
  int sublevel = (level <= 4) ? 0 : 1;

  S << "IGESGeom_TabulatedCylinder\n"
    << "Directrix       : ";
  dumper.Dump(ent->Directrix(), S, sublevel);
  S << "\n"
    << "Terminate Point : ";
  IGESData_DumpXYZL(S, level, ent->EndPoint(), ent->Location());
  S << std::endl;
}
