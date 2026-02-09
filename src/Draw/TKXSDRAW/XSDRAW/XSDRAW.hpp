#pragma once

#include <Standard.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <XSControl_WorkSession.hpp>
#include <TopoDS_Shape.hpp>
class IFSelect_SessionPilot;
class XSControl_WorkSession;
class XSControl_Controller;
class Interface_Protocol;
class Interface_InterfaceModel;
class Standard_Transient;
class Transfer_TransientProcess;
class Transfer_FinderProcess;
class XSControl_TransferReader;
class TCollection_AsciiString;
class TDocStd_Document;

class XSDRAW
{
public:
  Standard_EXPORT static void ChangeCommand(const char* oldname, const char* newname);

  Standard_EXPORT static void RemoveCommand(const char* oldname);

  Standard_EXPORT static bool LoadSession();

  Standard_EXPORT static void LoadDraw(Draw_Interpretor& theCommands);

  Standard_EXPORT static int Execute(const char* command, const char* var = "");

  Standard_EXPORT static occ::handle<IFSelect_SessionPilot> Pilot();

  Standard_EXPORT static void SetSession(const occ::handle<XSControl_WorkSession>& theSession);

  Standard_EXPORT static const occ::handle<XSControl_WorkSession> Session();

  Standard_EXPORT static void SetController(const occ::handle<XSControl_Controller>& control);

  Standard_EXPORT static occ::handle<XSControl_Controller> Controller();

  Standard_EXPORT static bool SetNorm(const char* normname);

  Standard_EXPORT static occ::handle<Interface_Protocol> Protocol();

  Standard_EXPORT static occ::handle<Interface_InterfaceModel> Model();

  Standard_EXPORT static void SetModel(const occ::handle<Interface_InterfaceModel>& model,
                                       const char*                                  file = "");

  Standard_EXPORT static occ::handle<Interface_InterfaceModel> NewModel();

  Standard_EXPORT static occ::handle<Standard_Transient> Entity(const int num);

  Standard_EXPORT static int Number(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT static void SetTransferProcess(const occ::handle<Standard_Transient>& TP);

  Standard_EXPORT static occ::handle<Transfer_TransientProcess> TransientProcess();

  Standard_EXPORT static occ::handle<Transfer_FinderProcess> FinderProcess();

  Standard_EXPORT static void InitTransferReader(const int mode);

  Standard_EXPORT static occ::handle<XSControl_TransferReader> TransferReader();

  Standard_EXPORT static occ::handle<Standard_Transient> GetEntity(const char* name = "");

  Standard_EXPORT static int GetEntityNumber(const char* name = "");

  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    GetList(const char* first = "", const char* second = "");

  Standard_EXPORT static bool FileAndVar(const char*              file,
                                         const char*              var,
                                         const char*              def,
                                         TCollection_AsciiString& resfile,
                                         TCollection_AsciiString& resvar);

  Standard_EXPORT static int MoreShapes(occ::handle<NCollection_HSequence<TopoDS_Shape>>& list,
                                        const char*                                       name);

  Standard_EXPORT static double GetLengthUnit(
    const occ::handle<TDocStd_Document>& theDoc = nullptr);

  Standard_EXPORT static XSControl_WorkSessionMap& WorkSessionList();

  Standard_EXPORT static void CollectActiveWorkSessions(
    const occ::handle<XSControl_WorkSession>& theWS,
    const TCollection_AsciiString&            theName,
    XSControl_WorkSessionMap&                 theMap);

  Standard_EXPORT static void CollectActiveWorkSessions(const TCollection_AsciiString& theName);

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
