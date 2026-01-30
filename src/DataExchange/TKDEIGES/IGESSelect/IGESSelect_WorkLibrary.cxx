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

#include <IFSelect_ContextWrite.hpp>
#include <IGESAppli.hpp>
#include <IGESAppli_Protocol.hpp>
#include <IGESData_FileProtocol.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESDefs.hpp>
#include <IGESFile_Read.hpp>
#include <IGESSelect_Dumper.hpp>
#include <IGESSelect_FileModifier.hpp>
#include <IGESSelect_WorkLibrary.hpp>
#include <IGESSolid.hpp>
#include <IGESSolid_Protocol.hpp>
#include <Interface_Check.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ReportEntity.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <OSD_FileSystem.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

#include <cerrno>
IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_WorkLibrary, IFSelect_WorkLibrary)

static int                                deja = 0;
static occ::handle<IGESData_FileProtocol> IGESProto;

IGESSelect_WorkLibrary::IGESSelect_WorkLibrary(const bool modefnes)
    : themodefnes(modefnes)
{
  IGESSolid::Init();
  IGESAppli::Init();
  IGESDefs::Init();

  if (!deja)
  {
    occ::handle<IGESSelect_Dumper> sesdump = new IGESSelect_Dumper; // ainsi,cestfait
    deja                                   = 1;
  }
  SetDumpLevels(4, 6);
  SetDumpHelp(0, "Only DNum");
  SetDumpHelp(1, "DNum, IGES Type & Form");
  SetDumpHelp(2, "Main Directory Information");
  SetDumpHelp(3, "Complete Directory Part");
  SetDumpHelp(4, "Directory + Fields (except list contents)");
  SetDumpHelp(5, "Complete (with list contents)");
  SetDumpHelp(6, "Complete + Transformed data");
}

int IGESSelect_WorkLibrary::ReadFile(const char*                            name,
                                     occ::handle<Interface_InterfaceModel>& model,
                                     const occ::handle<Interface_Protocol>& protocol) const
{
  Message_Messenger::StreamBuffer sout    = Message::SendInfo();
  occ::handle<IGESData_IGESModel> igesmod = new IGESData_IGESModel;
  DeclareAndCast(IGESData_Protocol, prot, protocol);

  char* pname  = (char*)name;
  int   status = IGESFile_Read(pname, igesmod, prot);

  if (status < 0)
    sout << "File not found : " << name << std::endl;
  if (status > 0)
    sout << "Error when reading file : " << name << std::endl;
  if (status == 0)
    model = igesmod;
  else
    model.Nullify();
  return status;
}

bool IGESSelect_WorkLibrary::WriteFile(IFSelect_ContextWrite& ctx) const
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  //  Preparation
  DeclareAndCast(IGESData_IGESModel, igesmod, ctx.Model());
  DeclareAndCast(IGESData_Protocol, prot, ctx.Protocol());

  if (igesmod.IsNull() || prot.IsNull())
    return false;
  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::ostream>      aStream =
    aFileSystem->OpenOStream(ctx.FileName(), std::ios::out | std::ios::binary);
  if (aStream.get() == nullptr)
  {
    ctx.CCheck(0)->AddFail("IGES File could not be created");
    sout << " - IGES File could not be created : " << ctx.FileName() << std::endl;
    return false;
  }
  sout << " IGES File Name : " << ctx.FileName();
  IGESData_IGESWriter VW(igesmod);
  sout << "(" << igesmod->NbEntities() << " ents) ";

  //  File Modifiers
  int nbmod = ctx.NbModifiers();
  for (int numod = 1; numod <= nbmod; numod++)
  {
    ctx.SetModifier(numod);
    DeclareAndCast(IGESSelect_FileModifier, filemod, ctx.FileModifier());
    if (!filemod.IsNull())
      filemod->Perform(ctx, VW);
    //   (impressions de mise au point)
    sout << " .. FileMod." << numod << " " << filemod->Label();
    if (ctx.IsForAll())
      sout << " (all model)";
    else
      sout << " (" << ctx.NbEntities() << " entities)";
    //    sout << std::flush;
  }

  //  Envoi
  VW.SendModel(prot);
  sout << " Write ";
  if (themodefnes)
    VW.WriteMode() = 10;
  bool status = VW.Print(*aStream);
  sout << " Done" << std::endl;

  errno = 0;
  aStream->flush();
  status = aStream->good() && status && !errno;
  aStream.reset();
  if (errno)
    sout << strerror(errno) << std::endl;

  return status;
}

occ::handle<IGESData_Protocol> IGESSelect_WorkLibrary::DefineProtocol()
{
  if (!IGESProto.IsNull())
    return IGESProto;
  occ::handle<IGESData_Protocol> IGESProto1 = IGESSolid::Protocol();
  occ::handle<IGESData_Protocol> IGESProto2 = IGESAppli::Protocol();
  //  occ::handle<IGESData_FileProtocol> IGESProto  = new IGESData_FileProtocol;
  IGESProto = new IGESData_FileProtocol;
  IGESProto->Add(IGESProto1);
  IGESProto->Add(IGESProto2);
  return IGESProto;
}

void IGESSelect_WorkLibrary::DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                        const occ::handle<Interface_Protocol>&       protocol,
                                        const occ::handle<Standard_Transient>&       entity,
                                        Standard_OStream&                            S,
                                        const int                                    level) const
{
  DeclareAndCast(IGESData_IGESModel, igesmod, model);
  DeclareAndCast(IGESData_Protocol, igespro, protocol);
  DeclareAndCast(IGESData_IGESEntity, igesent, entity);
  if (igesmod.IsNull() || igespro.IsNull() || igesent.IsNull())
    return;
  int num = igesmod->Number(igesent);
  if (num == 0)
    return;

  S << " --- Entity " << num;
  bool                            iserr = model->IsRedefinedContent(num);
  occ::handle<Standard_Transient> con;
  if (iserr)
    con = model->ReportEntity(num)->Content();
  if (entity.IsNull())
  {
    S << " Null" << std::endl;
    return;
  }

  //  We start the dump : first the Error case
  if (iserr)
  {
    S << " ERRONEOUS, Content, Type cdl : ";
    if (!con.IsNull())
      S << con->DynamicType()->Name();
    else
      S << "(undefined)" << std::endl;
    igesent = GetCasted(IGESData_IGESEntity, con);
    con.Nullify();
    occ::handle<Interface_Check> check = model->ReportEntity(num)->Check();
    Interface_CheckIterator      chlist;
    chlist.Add(check, num);
    chlist.Print(S, igesmod, false);
    if (igesent.IsNull())
      return;
  }
  else
    S << " Type cdl : " << igesent->DynamicType()->Name();

  IGESData_IGESDumper dump(igesmod, igespro);
  try
  {
    OCC_CATCH_SIGNALS
    dump.Dump(igesent, S, level, (level - 1) / 3);
  }
  catch (Standard_Failure const&)
  {
    S << " **  Dump Interrupt **" << std::endl;
  }
}
