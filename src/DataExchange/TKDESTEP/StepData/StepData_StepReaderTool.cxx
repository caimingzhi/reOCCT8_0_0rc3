

#include <Interface_Check.hpp>
#include <MoniTool_Macros.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Transient.hpp>
#include <StepData_FileRecognizer.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepReaderTool.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <TCollection_AsciiString.hpp>

StepData_StepReaderTool::StepData_StepReaderTool(const occ::handle<StepData_StepReaderData>& reader,
                                                 const occ::handle<StepData_Protocol>& protocol)
    : theglib(protocol),
      therlib(protocol)
{
  SetData(reader, protocol);
}

bool StepData_StepReaderTool::Recognize(const int                        num,
                                        occ::handle<Interface_Check>&    ach,
                                        occ::handle<Standard_Transient>& ent)
{

  if (!thereco.IsNull())
  {
    DeclareAndCast(StepData_StepReaderData, stepdat, Data());
    return thereco->Evaluate(stepdat->RecordType(num), ent);
  }

  return RecognizeByLib(num, theglib, therlib, ach, ent);
}

void StepData_StepReaderTool::Prepare(const occ::handle<StepData_FileRecognizer>& reco,
                                      const bool                                  optim)
{
  thereco = reco;
  Prepare(optim);
}

void StepData_StepReaderTool::Prepare(const bool optim)
{

  bool erh = ErrorHandle();
  DeclareAndCast(StepData_StepReaderData, stepdat, Data());
  if (erh)
  {
    try
    {
      OCC_CATCH_SIGNALS
      stepdat->SetEntityNumbers(optim);
      SetEntities();
    }
    catch (Standard_Failure const& anException)
    {
      Message_Messenger::StreamBuffer sout = Message::SendInfo();
      sout << " Exception Raised during Preparation :\n";
      sout << anException.what();
      sout << "\n Now, trying to continue, but with presomption of failure\n";
    }
  }
  else
  {
    stepdat->SetEntityNumbers(optim);
    SetEntities();
  }
}

void StepData_StepReaderTool::PrepareHeader(const occ::handle<StepData_FileRecognizer>& reco)
{
  int i = 0;

  DeclareAndCast(StepData_StepReaderData, stepdat, Data());
  while ((i = stepdat->FindNextHeaderRecord(i)) != 0)
  {
    occ::handle<Standard_Transient> ent;

    if (!reco.IsNull())
    {

      if (!reco->Evaluate(stepdat->RecordType(i), ent))
      {

        ent = Protocol()->UnknownEntity();
      }
    }
    else
    {

      occ::handle<Interface_Check> ach = new Interface_Check;
      RecognizeByLib(i, theglib, therlib, ach, ent);
    }
    if (ent.IsNull())
      ent = Protocol()->UnknownEntity();
    stepdat->BindEntity(i, ent);
  }

  stepdat->PrepareHeader();
}

void StepData_StepReaderTool::BeginRead(const occ::handle<Interface_InterfaceModel>& amodel)
{
  Message_Messenger::StreamBuffer sout = Message::SendTrace();
  DeclareAndCast(StepData_StepModel, model, amodel);
  DeclareAndCast(StepData_StepReaderData, stepdat, Data());

  model->ClearHeader();
  model->SetGlobalCheck(stepdat->GlobalCheck());
  int i = 0;
  while ((i = stepdat->FindNextHeaderRecord(i)) != 0)
  {
    occ::handle<Standard_Transient> ent = stepdat->BoundEntity(i);
    occ::handle<Interface_Check>    ach = new Interface_Check(ent);
    AnalyseRecord(i, ent, ach);
    if (ent->IsKind(STANDARD_TYPE(StepData_UndefinedEntity)))
    {
      TCollection_AsciiString mess("Header Entity not Recognized, StepType: ");
      mess.AssignCat(stepdat->RecordType(i));
      ach->AddWarning(mess.ToCString());
    }
    if (ach->HasFailed() || ach->HasWarnings())
    {
      occ::handle<Interface_Check> mch = model->GlobalCheck();
      mch->GetMessages(ach);
      model->SetGlobalCheck(mch);
    }
    model->AddHeaderEntity(ent);
    if (ach->HasWarnings())
    {
      occ::handle<Interface_Check> mch    = model->GlobalCheck();
      int                          nbmess = ach->NbWarnings();
      sout << nbmess << " Warnings on Reading Header Entity N0." << i << ":";
      if (!ent.IsNull())
        sout << ent->DynamicType()->Name() << std::endl;
      for (int nf = 1; nf <= nbmess; nf++)
      {
        sout << ach->CWarning(nf) << "\n";
      }
    }
    if (ach->HasFailed())
    {
      occ::handle<Interface_Check> mch    = model->GlobalCheck();
      int                          nbmess = ach->NbFails();
      sout << " Fails on Reading Header Entity N0." << i << ":";
      if (!ent.IsNull())
        sout << ent->DynamicType()->Name() << std::endl;
      for (int nf = 1; nf <= nbmess; nf++)
      {
        sout << ach->CFail(nf) << "\n";
      }
    }
  }
}

bool StepData_StepReaderTool::AnalyseRecord(const int                              num,
                                            const occ::handle<Standard_Transient>& anent,
                                            occ::handle<Interface_Check>&          acheck)
{
  DeclareAndCast(StepData_StepReaderData, stepdat, Data());
  occ::handle<Interface_ReaderModule> imodule;
  int                                 CN;

  if (therlib.Select(anent, imodule, CN))
  {

    occ::handle<StepData_ReadWriteModule> module =
      occ::down_cast<StepData_ReadWriteModule>(imodule);
    module->ReadStep(CN, stepdat, num, acheck, anent);
  }
  else
  {

    DeclareAndCast(StepData_UndefinedEntity, und, anent);
    if (und.IsNull())
      acheck->AddFail("# Entity neither Recognized nor set as UndefinedEntity from StepData #");
    else
      und->ReadRecord(stepdat, num, acheck);
  }
  return (!acheck->HasFailed());
}

void StepData_StepReaderTool::EndRead(const occ::handle<Interface_InterfaceModel>& amodel)
{
  DeclareAndCast(StepData_StepReaderData, stepdat, Data());
  DeclareAndCast(StepData_StepModel, stepmodel, amodel);
  if (stepmodel.IsNull())
    return;
  int i = 0;
  while ((i = stepdat->FindNextRecord(i)) != 0)
  {
    stepmodel->SetIdentLabel(stepdat->BoundEntity(i), stepdat->RecordIdent(i));
  }
}
