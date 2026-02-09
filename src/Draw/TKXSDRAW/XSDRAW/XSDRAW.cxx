

#include <DBRep.hpp>
#include <Draw_Appli.hpp>
#include <Draw_Printer.hpp>
#include <Draw_PluginMacro.hpp>
#include <IFSelect_Functions.hpp>
#include <IFSelect_SessionPilot.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Protocol.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_PrinterOStream.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopoDS_Shape.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep.hpp>
#include <XSAlgo.hpp>
#include <XSControl.hpp>
#include <XSControl_Controller.hpp>
#include <XSControl_FuncShape.hpp>
#include <XSControl_Functions.hpp>
#include <XSControl_TransferReader.hpp>
#include <XSControl_TransferWriter.hpp>
#include <XSControl_WorkSession.hpp>
#include <XSDRAW.hpp>
#include <XSDRAW_Vars.hpp>
#include <UnitsMethods.hpp>
#include <Interface_Static.hpp>
#include <XCAFDoc_DocumentTool.hpp>

#include <iostream>
#include <string>

namespace
{
  static int deja = 0, dejald = 0;

  static NCollection_DataMap<TCollection_AsciiString, int>           theolds;
  static occ::handle<NCollection_HSequence<TCollection_AsciiString>> thenews;

  static occ::handle<IFSelect_SessionPilot> thepilot;

  static void collectActiveWorkSessions(const occ::handle<XSControl_WorkSession>& theWS,
                                        const TCollection_AsciiString&            theName,
                                        XSControl_WorkSessionMap&                 theMap,
                                        const bool                                theIsFirst)
  {
    if (theIsFirst)
    {
      theMap.Clear();
    }
    if (theWS.IsNull())
    {
      return;
    }
    if (theMap.IsBound(theName))
    {
      return;
    }
    theMap.Bind(theName, theWS);
    for (XSControl_WorkSessionMap::Iterator anIter(theWS->Context()); anIter.More(); anIter.Next())
    {
      occ::handle<XSControl_WorkSession> aWS =
        occ::down_cast<XSControl_WorkSession>(anIter.Value());
      collectActiveWorkSessions(aWS, anIter.Key(), theMap, false);
    }
  }
} // namespace

static int XSTEPDRAWRUN(Draw_Interpretor& di, int argc, const char** argv)
{
  TCollection_AsciiString mess;
  for (int i = 0; i < argc; i++)
  {
    mess.AssignCat(argv[i]);
    mess.AssignCat(" ");
  }

  const occ::handle<Message_Messenger>&              aMsgMgr = Message::DefaultMessenger();
  NCollection_Sequence<occ::handle<Message_Printer>> aPrinters;
  aPrinters.Append(aMsgMgr->ChangePrinters());
  aMsgMgr->AddPrinter(new Draw_Printer(di));

  IFSelect_ReturnStatus stat = thepilot->Execute(mess.ToCString());

  aMsgMgr->RemovePrinters(STANDARD_TYPE(Draw_Printer));
  aMsgMgr->ChangePrinters().Append(aPrinters);

  if (stat == IFSelect_RetError || stat == IFSelect_RetFail)
    return 1;
  else
    return 0;
}

void XSDRAW::ChangeCommand(const char* oldname, const char* newname)
{
  int num = 0;
  if (newname[0] != '\0')
  {
    if (thenews.IsNull())
      thenews = new NCollection_HSequence<TCollection_AsciiString>();
    TCollection_AsciiString newstr(newname);
    thenews->Append(newstr);
    num = thenews->Length();
  }
  theolds.Bind(oldname, num);
}

void XSDRAW::RemoveCommand(const char* oldname)
{
  ChangeCommand(oldname, "");
}

bool XSDRAW::LoadSession()
{
  if (deja)
    return false;
  deja                                  = 1;
  thepilot                              = new IFSelect_SessionPilot("XSTEP-DRAW>");
  occ::handle<XSControl_WorkSession> WS = new XSControl_WorkSession;
  WS->SetVars(new XSDRAW_Vars);
  thepilot->SetSession(WS);

  IFSelect_Functions::Init();
  XSControl_Functions::Init();
  XSControl_FuncShape::Init();
  XSAlgo::Init();

  return true;
}

void XSDRAW::LoadDraw(Draw_Interpretor& theCommands)
{
  if (dejald)
  {
    return;
  }
  dejald = 1;

  LoadSession();

  XSDRAW::RemoveCommand("x");
  XSDRAW::RemoveCommand("exit");

  occ::handle<NCollection_HSequence<TCollection_AsciiString>> list =
    IFSelect_Activator::Commands(0);
  for (NCollection_HSequence<TCollection_AsciiString>::Iterator aCmdIter(*list); aCmdIter.More();
       aCmdIter.Next())
  {
    int                            num  = -1;
    const TCollection_AsciiString& aCmd = aCmdIter.Value();
    if (!theolds.IsEmpty())
    {
      theolds.Find(aCmd, num);
    }
    if (num == 0)
    {
      continue;
    }

    int                             nact = 0;
    occ::handle<IFSelect_Activator> anAct;
    TCollection_AsciiString         aHelp;
    if (!IFSelect_Activator::Select(aCmd.ToCString(), nact, anAct))
    {
      aHelp = TCollection_AsciiString("type :  xhelp ") + aCmd + " for help";
    }
    else if (!anAct.IsNull())
    {
      aHelp = anAct->Help(nact);
    }

    const TCollection_AsciiString& aCmdName = num < 0 ? aCmd : thenews->Value(num);
    theCommands.Add(aCmdName.ToCString(), aHelp.ToCString(), "", XSTEPDRAWRUN, anAct->Group());
  }
}

int XSDRAW::Execute(const char* command, const char* varname)
{
  char mess[100];
  Sprintf(mess, command, varname);
  thepilot->Execute(mess);
  return 1;
}

occ::handle<IFSelect_SessionPilot> XSDRAW::Pilot()
{
  return thepilot;
}

void XSDRAW::SetSession(const occ::handle<XSControl_WorkSession>& theSession)
{
  Pilot()->SetSession(theSession);
}

const occ::handle<XSControl_WorkSession> XSDRAW::Session()
{
  return XSControl::Session(thepilot);
}

void XSDRAW::SetController(const occ::handle<XSControl_Controller>& control)
{
  if (thepilot.IsNull())
    XSDRAW::LoadSession();
  if (control.IsNull())
    std::cout << "XSTEP Controller not defined" << std::endl;
  else if (!Session().IsNull())
    Session()->SetController(control);
  else
    std::cout << "XSTEP Session badly or not defined" << std::endl;
}

occ::handle<XSControl_Controller> XSDRAW::Controller()
{
  return Session()->NormAdaptor();
}

bool XSDRAW::SetNorm(const char* norm)
{
  return Session()->SelectNorm(norm);
}

occ::handle<Interface_Protocol> XSDRAW::Protocol()
{
  return thepilot->Session()->Protocol();
}

occ::handle<Interface_InterfaceModel> XSDRAW::Model()
{
  return thepilot->Session()->Model();
}

void XSDRAW::SetModel(const occ::handle<Interface_InterfaceModel>& model, const char* file)
{
  thepilot->Session()->SetModel(model);
  if (file && file[0] != '\0')
    thepilot->Session()->SetLoadedFile(file);
}

occ::handle<Interface_InterfaceModel> XSDRAW::NewModel()
{
  return Session()->NewModel();
}

occ::handle<Standard_Transient> XSDRAW::Entity(const int num)
{
  return thepilot->Session()->StartingEntity(num);
}

int XSDRAW::Number(const occ::handle<Standard_Transient>& ent)
{
  return thepilot->Session()->StartingNumber(ent);
}

void XSDRAW::SetTransferProcess(const occ::handle<Standard_Transient>& ATP)
{
  DeclareAndCast(Transfer_FinderProcess, FP, ATP);
  DeclareAndCast(Transfer_TransientProcess, TP, ATP);

  if (!FP.IsNull())
    Session()->SetMapWriter(FP);

  if (!TP.IsNull())
  {
    if (!TP->Model().IsNull() && TP->Model() != Session()->Model())
      Session()->SetModel(TP->Model());
    Session()->SetMapReader(TP);
  }
}

occ::handle<Transfer_TransientProcess> XSDRAW::TransientProcess()
{
  return Session()->TransferReader()->TransientProcess();
}

occ::handle<Transfer_FinderProcess> XSDRAW::FinderProcess()
{
  return Session()->TransferWriter()->FinderProcess();
}

void XSDRAW::InitTransferReader(const int mode)
{

  Session()->InitTransferReader(mode);
}

occ::handle<XSControl_TransferReader> XSDRAW::TransferReader()
{
  return Session()->TransferReader();
}

occ::handle<Standard_Transient> XSDRAW::GetEntity(const char* name)
{
  return IFSelect_Functions::GiveEntity(Session(), name);
}

int XSDRAW::GetEntityNumber(const char* name)
{
  return IFSelect_Functions::GiveEntityNumber(Session(), name);
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> XSDRAW::GetList(
  const char* first,
  const char* second)
{
  if (!first || first[0] == '\0')
  {
    std::string aLineFirst;
    std::cin >> aLineFirst;

    char terminateSymbol = '\0';
    std::cin.get(terminateSymbol);

    if (terminateSymbol == '\n')
      return XSDRAW::GetList(aLineFirst.c_str(), nullptr);
    else
    {
      std::string aLineSecond;
      std::cin >> aLineSecond;
      return XSDRAW::GetList(aLineFirst.c_str(), aLineSecond.c_str());
    }
  }
  return IFSelect_Functions::GiveList(Session(), first, second);
}

bool XSDRAW::FileAndVar(const char*              file,
                        const char*              var,
                        const char*              def,
                        TCollection_AsciiString& resfile,
                        TCollection_AsciiString& resvar)
{
  return XSControl_FuncShape::FileAndVar(XSDRAW::Session(), file, var, def, resfile, resvar);
}

int XSDRAW::MoreShapes(occ::handle<NCollection_HSequence<TopoDS_Shape>>& list, const char* name)
{
  return XSControl_FuncShape::MoreShapes(XSDRAW::Session(), list, name);
}

double XSDRAW::GetLengthUnit(const occ::handle<TDocStd_Document>& theDoc)
{
  if (!theDoc.IsNull())
  {
    double aUnit = 1.;
    if (XCAFDoc_DocumentTool::GetLengthUnit(theDoc, aUnit, UnitsMethods_LengthUnit_Millimeter))
    {
      return aUnit;
    }
  }
  if (Interface_Static::IsPresent("xstep.cascade.unit"))
  {
    UnitsMethods::SetCasCadeLengthUnit(Interface_Static::IVal("xstep.cascade.unit"));
  }
  return UnitsMethods::GetCasCadeLengthUnit();
}

XSControl_WorkSessionMap& XSDRAW::WorkSessionList()
{
  static std::shared_ptr<XSControl_WorkSessionMap> THE_PREVIOUS_WORK_SESSIONS;
  if (THE_PREVIOUS_WORK_SESSIONS == nullptr)
  {
    THE_PREVIOUS_WORK_SESSIONS = std::make_shared<XSControl_WorkSessionMap>();
  }
  return *THE_PREVIOUS_WORK_SESSIONS;
}

void XSDRAW::CollectActiveWorkSessions(const occ::handle<XSControl_WorkSession>& theWS,
                                       const TCollection_AsciiString&            theName,
                                       XSControl_WorkSessionMap&                 theMap)
{
  collectActiveWorkSessions(theWS, theName, theMap, true);
}

void XSDRAW::CollectActiveWorkSessions(const TCollection_AsciiString& theName)
{
  collectActiveWorkSessions(Session(), theName, WorkSessionList(), true);
}

void XSDRAW::Factory(Draw_Interpretor& theDI)
{
  XSDRAW::LoadDraw(theDI);
}

DPLUGIN(XSDRAW)
