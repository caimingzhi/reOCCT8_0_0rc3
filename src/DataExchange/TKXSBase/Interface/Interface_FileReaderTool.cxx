

#include <Interface_Check.hpp>
#include <Interface_CheckFailure.hpp>
#include <Interface_FileReaderData.hpp>
#include <Interface_FileReaderTool.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ReaderLib.hpp>
#include <Interface_ReaderModule.hpp>
#include <Interface_ReportEntity.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Transient.hpp>

#ifdef _WIN32
  #include <OSD_Exception.hpp>
#else
  #include <OSD_Signal.hpp>
#endif
#include <cstdio>

#include <Message_Msg.hpp>

#include <TCollection_HAsciiString.hpp>

Interface_FileReaderTool::Interface_FileReaderTool()
{
  themessenger = Message::DefaultMessenger();
  theerrhand   = true;
  thetrace     = 0;
  thenbrep0 = thenbreps = 0;
}

void Interface_FileReaderTool::SetData(const occ::handle<Interface_FileReaderData>& reader,
                                       const occ::handle<Interface_Protocol>&       protocol)
{
  thereader = reader;
  theproto  = protocol;
}

occ::handle<Interface_Protocol> Interface_FileReaderTool::Protocol() const
{
  return theproto;
}

occ::handle<Interface_FileReaderData> Interface_FileReaderTool::Data() const
{
  return thereader;
}

void Interface_FileReaderTool::SetModel(const occ::handle<Interface_InterfaceModel>& amodel)
{
  themodel = amodel;
}

occ::handle<Interface_InterfaceModel> Interface_FileReaderTool::Model() const
{
  return themodel;
}

void Interface_FileReaderTool::SetMessenger(const occ::handle<Message_Messenger>& messenger)
{
  if (messenger.IsNull())
    themessenger = Message::DefaultMessenger();
  else
    themessenger = messenger;
}

occ::handle<Message_Messenger> Interface_FileReaderTool::Messenger() const
{
  return themessenger;
}

void Interface_FileReaderTool::SetTraceLevel(const int tracelev)
{
  thetrace = tracelev;
}

int Interface_FileReaderTool::TraceLevel() const
{
  return thetrace;
}

void Interface_FileReaderTool::SetErrorHandle(const bool err)
{
  theerrhand = err;
}

bool Interface_FileReaderTool::ErrorHandle() const
{
  return theerrhand;
}

void Interface_FileReaderTool::SetEntities()
{
  int num;
  thenbreps = 0;
  thenbrep0 = 0;

  for (num = thereader->FindNextRecord(0); num > 0; num = thereader->FindNextRecord(num))
  {
    occ::handle<Standard_Transient> newent;
    occ::handle<Interface_Check>    ach = new Interface_Check;
    if (!Recognize(num, ach, newent))
    {
      newent = UnknownEntity();
      if (thereports.IsNull())
        thereports =
          new NCollection_HArray1<occ::handle<Standard_Transient>>(1, thereader->NbRecords());
      thenbreps++;
      thenbrep0++;
      thereports->SetValue(num, new Interface_ReportEntity(ach, newent));
    }
    else if ((ach->NbFails() + ach->NbWarnings() > 0) && !newent.IsNull())
    {
      if (thereports.IsNull())
        thereports =
          new NCollection_HArray1<occ::handle<Standard_Transient>>(1, thereader->NbRecords());
      thenbreps++;
      thenbrep0++;
      thereports->SetValue(num, new Interface_ReportEntity(ach, newent));
    }
    thereader->BindEntity(num, newent);
  }
}

bool Interface_FileReaderTool::RecognizeByLib(const int                        num,
                                              Interface_GeneralLib&            glib,
                                              Interface_ReaderLib&             rlib,
                                              occ::handle<Interface_Check>&    ach,
                                              occ::handle<Standard_Transient>& ent) const
{
  occ::handle<Interface_GeneralModule> gmod;
  occ::handle<Interface_ReaderModule>  rmod;
  occ::handle<Interface_Protocol>      proto;
  int                                  CN = 0;

  for (rlib.Start(); rlib.More(); rlib.Next())
  {
    rmod = rlib.Module();
    if (rmod.IsNull())
      continue;
    CN = rmod->CaseNum(thereader, num);
    if (CN > 0)
    {
      proto = rlib.Protocol();
      break;
    }
  }
  if (CN <= 0 || proto.IsNull())
    return false;

  occ::handle<Standard_Type> typrot = proto->DynamicType();
  for (glib.Start(); glib.More(); glib.Next())
  {
    proto = glib.Protocol();
    if (proto.IsNull())
      continue;
    if (proto->DynamicType() != typrot)
      continue;
    bool res = glib.Module()->NewVoid(CN, ent);
    if (res)
      return res;
    if (!rmod.IsNull())
      return rmod->NewRead(CN, thereader, num, ach, ent);
  }
  return false;
}

occ::handle<Standard_Transient> Interface_FileReaderTool::UnknownEntity() const
{
  return theproto->UnknownEntity();
}

occ::handle<Interface_InterfaceModel> Interface_FileReaderTool::NewModel() const
{
  return theproto->NewModel();
}

void Interface_FileReaderTool::EndRead(const occ::handle<Interface_InterfaceModel>&) {}

void Interface_FileReaderTool::LoadModel(const occ::handle<Interface_InterfaceModel>& amodel)

{

  occ::handle<Message_Messenger> TF = Messenger();

  occ::handle<Interface_Check> ach = new Interface_Check;

  SetModel(amodel);

  if (theerrhand)
  {
    try
    {
      OCC_CATCH_SIGNALS
      BeginRead(amodel);
    }
    catch (Standard_Failure const&)
    {

      if (!TF.IsNull())
      {
        Message_Msg Msg11("XSTEP_11");
        TF->Send(Msg11, Message_Info);
      }
    }
  }
  else
    BeginRead(amodel);

  amodel->Reservate(thereader->NbEntities());

  int num, num0 = thereader->FindNextRecord(0);
  num = num0;

  while (num > 0)
  {
    int                             ierr = 0;
    occ::handle<Standard_Transient> anent;
    try
    {
      OCC_CATCH_SIGNALS
      for (num = num0; num > 0; num = thereader->FindNextRecord(num))
      {
        num0 = num;

        anent = LoadedEntity(num);

        if (anent.IsNull())
        {

          if (!TF.IsNull())
          {
            Message_Msg Msg21("XSTEP_21");
            Msg21.Arg(amodel->NbEntities());
            TF->Send(Msg21, Message_Info);
          }
          continue;
        }
      }
      num0 = 0;
    }

    catch (Standard_Failure const& anException)
    {

      num0 = thereader->FindNextRecord(num);

#ifdef _WIN32
      if (dynamic_cast<const OSD_Exception*>(&anException) != nullptr)
        ierr = 2;
#else
      if (dynamic_cast<const OSD_Signal*>(&anException) != nullptr)
        ierr = 2;
#endif

      anent = thereader->BoundEntity(num);
      if (anent.IsNull())
      {
        if (thetrace > 0)
        {

          if (!TF.IsNull())
          {

            Message_Msg Msg21("XSTEP_21");
            Msg21.Arg(amodel->NbEntities() + 1);

            TF->Send(Msg21, Message_Info);
          }
          continue;
        }
      }
      ach = new Interface_Check(anent);

      Message_Msg Msg278("XSTEP_278");
      Msg278.Arg(amodel->StringLabel(anent));
      ach->SendFail(Msg278);

      if (ierr == 2)
      {

        if (!TF.IsNull())
        {
          Message_Msg Msg22("XSTEP_22");
          Msg22.Arg(amodel->StringLabel(anent));
          TF->Send(Msg22, Message_Info);
        }
        return;
      }

      if (!ierr)
      {

        ierr = 1;

        if (thetrace > 0)
        {

          if (!TF.IsNull())
          {
            Message_Msg Msg23("XSTEP_23");
            Msg23.Arg(num);
            TF->Send(Msg23, Message_Info);
          }
        }

        thenbreps++;
        occ::handle<Interface_ReportEntity> rep   = new Interface_ReportEntity(ach, anent);
        occ::handle<Standard_Transient>     undef = UnknownEntity();
        AnalyseRecord(num, undef, ach);
        rep->SetContent(undef);

        if (thereports.IsNull())
          thereports =
            new NCollection_HArray1<occ::handle<Standard_Transient>>(1, thereader->NbRecords());
        thenbreps++;
        thereports->SetValue(num, rep);

        amodel->AddEntity(anent);
      }
      else
      {
        if (thetrace > 0)
        {

          if (!TF.IsNull())
          {
            Message_Msg Msg22("XSTEP_22");
            Msg22.Arg(amodel->StringLabel(anent));
            TF->Send(Msg22, Message_Info);
          }
        }
      }
    }
  }

  if (!thereports.IsNull())
  {
    if (thetrace > 0)
    {

      if (!TF.IsNull())
      {
        Message_Msg Msg24("XSTEP_24");
        Msg24.Arg(thenbreps);
        TF->Send(Msg24, Message_Info);
      }
    }
    amodel->Reservate(-thenbreps - 10);
    thenbreps = thereports->Upper();
    for (int nr = 1; nr <= thenbreps; nr++)
    {
      if (thereports->Value(nr).IsNull())
        continue;
      occ::handle<Standard_Transient>     anent = thereader->BoundEntity(nr);
      occ::handle<Interface_ReportEntity> rep =
        occ::down_cast<Interface_ReportEntity>(thereports->Value(nr));
      amodel->SetReportEntity(-amodel->Number(anent), rep);
    }
  }

  if (theerrhand)
  {
    try
    {
      OCC_CATCH_SIGNALS
      EndRead(amodel);
    }
    catch (Standard_Failure const&)
    {

      if (!TF.IsNull())
      {
        Message_Msg Msg11("XSTEP_11");
        TF->Send(Msg11, Message_Info);
      }
    }
  }
  else
    EndRead(amodel);
}

occ::handle<Standard_Transient> Interface_FileReaderTool::LoadedEntity(const int num)
{
  occ::handle<Standard_Transient>     anent = thereader->BoundEntity(num);
  occ::handle<Interface_Check>        ach   = new Interface_Check(anent);
  occ::handle<Interface_ReportEntity> rep;
  int                                 irep = 0;

  if (thenbrep0 > 0)
  {
    rep = occ::down_cast<Interface_ReportEntity>(thereports->Value(num));
    if (!rep.IsNull())
    {
      irep = num;
      ach  = rep->Check();
    }
  }

  if (thetrace >= 2 && theproto->IsUnknownEntity(anent))
  {
    occ::handle<Message_Messenger> TF = Messenger();
    if (!TF.IsNull())
    {
      Message_Msg Msg22("XSTEP_22");

      Msg22.Arg(themodel->StringLabel(anent)->String());
      TF->Send(Msg22, Message_Info);
    }
  }

  AnalyseRecord(num, anent, ach);

  themodel->AddEntity(anent);

  int nbf = ach->NbFails();
  int nbw = ach->NbWarnings();
  if (nbf + nbw > 0)
  {

    themodel->NbEntities();
    rep = new Interface_ReportEntity(ach, anent);
    if (irep == 0)
    {
      if (thereports.IsNull())
        thereports =
          new NCollection_HArray1<occ::handle<Standard_Transient>>(1, thereader->NbRecords());
      irep = num;
      thenbreps++;
    }
    thereports->SetValue(irep, rep);

    if (thetrace >= 2 && !Messenger().IsNull())
    {
      Message_Messenger::StreamBuffer sout = Messenger()->SendInfo();
      ach->Print(sout, 2);
    }
  }

  if (thereader->IsErrorLoad())
    nbf = (thereader->ResetErrorLoad() ? 1 : 0);
  if (nbf > 0)
  {
    occ::handle<Standard_Transient> undef = UnknownEntity();
    AnalyseRecord(num, undef, ach);
    rep->SetContent(undef);
  }

  return anent;
}

Interface_FileReaderTool::~Interface_FileReaderTool() = default;

void Interface_FileReaderTool::Clear()
{
  theproto.Nullify();
  thereader.Nullify();
  themodel.Nullify();
  thereports.Nullify();
}
