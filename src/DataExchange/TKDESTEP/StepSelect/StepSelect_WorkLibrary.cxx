

#include <IFSelect_ContextWrite.hpp>
#include <Interface_Check.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ReportEntity.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <OSD_FileSystem.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_StepDumper.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFile_Read.hpp>
#include <StepSelect_FileModifier.hpp>
#include <StepSelect_WorkLibrary.hpp>

#include <cerrno>
IMPLEMENT_STANDARD_RTTIEXT(StepSelect_WorkLibrary, IFSelect_WorkLibrary)

StepSelect_WorkLibrary::StepSelect_WorkLibrary(const bool copymode)
    : thecopymode(copymode),
      thelabmode(0)
{
  SetDumpLevels(1, 2);
  SetDumpHelp(0, "#id + Step Type");
  SetDumpHelp(1, "Entity as in file");
  SetDumpHelp(2, "Entity + shareds (level 1) as in file");
}

void StepSelect_WorkLibrary::SetDumpLabel(const int mode)
{
  thelabmode = mode;
}

int StepSelect_WorkLibrary::ReadFile(const char*                            name,
                                     occ::handle<Interface_InterfaceModel>& model,
                                     const occ::handle<Interface_Protocol>& protocol) const
{
  DeclareAndCast(StepData_Protocol, stepro, protocol);
  if (stepro.IsNull())
    return 1;
  int aStatus = StepFile_Read(name, nullptr, occ::down_cast<StepData_StepModel>(model), stepro);
  return aStatus;
}

int StepSelect_WorkLibrary::ReadStream(const char*                            theName,
                                       std::istream&                          theIStream,
                                       occ::handle<Interface_InterfaceModel>& model,
                                       const occ::handle<Interface_Protocol>& protocol) const
{
  DeclareAndCast(StepData_Protocol, stepro, protocol);
  if (stepro.IsNull())
    return 1;
  int aStatus =
    StepFile_Read(theName, &theIStream, occ::down_cast<StepData_StepModel>(model), stepro);
  return aStatus;
}

bool StepSelect_WorkLibrary::WriteFile(IFSelect_ContextWrite& ctx) const
{

  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  DeclareAndCast(StepData_StepModel, stepmodel, ctx.Model());
  DeclareAndCast(StepData_Protocol, stepro, ctx.Protocol());
  if (stepmodel.IsNull() || stepro.IsNull())
    return false;

  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::ostream>      aStream =
    aFileSystem->OpenOStream(ctx.FileName(), std::ios::out | std::ios::binary | std::ios::trunc);

  if (aStream.get() == nullptr)
  {
    ctx.CCheck(0)->AddFail("Step File could not be created");
    sout << " Step File could not be created : " << ctx.FileName() << std::endl;
    return false;
  }
  sout << " Step File Name : " << ctx.FileName();
  StepData_StepWriter SW(stepmodel);
  sout << "(" << stepmodel->NbEntities() << " ents) ";

  int nbmod = ctx.NbModifiers();
  for (int numod = 1; numod <= nbmod; numod++)
  {
    ctx.SetModifier(numod);
    DeclareAndCast(StepSelect_FileModifier, filemod, ctx.FileModifier());
    if (!filemod.IsNull())
      filemod->Perform(ctx, SW);

    sout << " .. FileMod." << numod << filemod->Label();
    if (ctx.IsForAll())
      sout << " (all model)";
    else
      sout << " (" << ctx.NbEntities() << " entities)";
  }

  SW.SendModel(stepro);
  Interface_CheckIterator chl = SW.CheckList();
  for (chl.Start(); chl.More(); chl.Next())
    ctx.CCheck(chl.Number())->GetMessages(chl.Value());
  sout << " Write ";
  bool isGood = SW.Print(*aStream);
  sout << " Done" << std::endl;

  errno = 0;
  aStream->flush();
  isGood = aStream->good() && isGood && !errno;
  aStream.reset();
  if (errno)
    sout << strerror(errno) << std::endl;
  return isGood;
}

bool StepSelect_WorkLibrary::CopyModel(const occ::handle<Interface_InterfaceModel>& original,
                                       const occ::handle<Interface_InterfaceModel>& newmodel,
                                       const Interface_EntityIterator&              list,
                                       Interface_CopyTool&                          TC) const
{
  if (thecopymode)
    return IFSelect_WorkLibrary::CopyModel(original, newmodel, list, TC);
  return thecopymode;
}

void StepSelect_WorkLibrary::DumpEntity(const occ::handle<Interface_InterfaceModel>& model,
                                        const occ::handle<Interface_Protocol>&       protocol,
                                        const occ::handle<Standard_Transient>&       entity,
                                        Standard_OStream&                            S,
                                        const int                                    level) const
{
  int nument = model->Number(entity);
  if (nument <= 0 || nument > model->NbEntities())
    return;
  bool                            iserr = model->IsRedefinedContent(nument);
  occ::handle<Standard_Transient> ent, con;
  ent = entity;
  S << " --- (STEP) Entity ";
  model->Print(entity, S);
  if (iserr)
    con = model->ReportEntity(nument)->Content();
  if (entity.IsNull())
  {
    S << " Null" << std::endl;
    return;
  }

  S << " Type cdl : " << entity->DynamicType()->Name() << std::endl;
  if (iserr)
    S << " ***  NOT WELL LOADED : CONTENT FROM FILE  ***" << std::endl;
  else if (model->IsUnknownEntity(nument))
    S << " ***  UNKNOWN TYPE  ***" << std::endl;

  StepData_StepDumper dump(GetCasted(StepData_StepModel, model),
                           GetCasted(StepData_Protocol, protocol),
                           thelabmode);
  dump.Dump(S, ent, level);
}
