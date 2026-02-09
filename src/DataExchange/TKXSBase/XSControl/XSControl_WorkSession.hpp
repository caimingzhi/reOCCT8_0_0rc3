#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_WorkSession.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <XSControl_TransferWriter.hpp>
class XSControl_Controller;
class XSControl_TransferReader;
class XSControl_Vars;
class Transfer_TransientProcess;
class Interface_InterfaceModel;
class Transfer_FinderProcess;
class TopoDS_Shape;
class Interface_CheckIterator;

using XSControl_WorkSessionMap =
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>;

class XSControl_WorkSession : public IFSelect_WorkSession
{
public:
  Standard_EXPORT XSControl_WorkSession();

  ~XSControl_WorkSession() override { ClearBinders(); }

  Standard_EXPORT void ClearData(const int theMode) override;

  Standard_EXPORT bool SelectNorm(const char* theNormName);

  Standard_EXPORT void SetController(const occ::handle<XSControl_Controller>& theCtl);

  Standard_EXPORT const char* SelectedNorm(const bool theRsc = false) const;

  const occ::handle<XSControl_Controller>& NormAdaptor() const { return myController; }

  const XSControl_WorkSessionMap& Context() const { return myContext; }

  Standard_EXPORT void SetAllContext(const XSControl_WorkSessionMap& theContext);

  Standard_EXPORT void ClearContext();

  Standard_EXPORT bool PrintTransferStatus(const int         theNum,
                                           const bool        theWri,
                                           Standard_OStream& theS) const;

  Standard_EXPORT void InitTransferReader(const int theMode);

  Standard_EXPORT void SetTransferReader(const occ::handle<XSControl_TransferReader>& theTR);

  const occ::handle<XSControl_TransferReader>& TransferReader() const { return myTransferReader; }

  Standard_EXPORT occ::handle<Transfer_TransientProcess> MapReader() const;

  Standard_EXPORT bool SetMapReader(const occ::handle<Transfer_TransientProcess>& theTP);

  Standard_EXPORT occ::handle<Standard_Transient> Result(
    const occ::handle<Standard_Transient>& theEnt,
    const int                              theMode) const;

  Standard_EXPORT int TransferReadOne(
    const occ::handle<Standard_Transient>& theEnts,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  Standard_EXPORT int TransferReadRoots(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel();

  const occ::handle<XSControl_TransferWriter>& TransferWriter() const { return myTransferWriter; }

  bool SetMapWriter(const occ::handle<Transfer_FinderProcess>& theFP)
  {
    if (theFP.IsNull())
      return false;
    myTransferWriter->SetFinderProcess(theFP);
    return true;
  }

  Standard_EXPORT IFSelect_ReturnStatus
    TransferWriteShape(const TopoDS_Shape&          theShape,
                       const bool                   theCompGraph = true,
                       const Message_ProgressRange& theProgress  = Message_ProgressRange());

  Standard_EXPORT Interface_CheckIterator TransferWriteCheckList() const;

  const occ::handle<XSControl_Vars>& Vars() const { return myVars; }

  void SetVars(const occ::handle<XSControl_Vars>& theVars) { myVars = theVars; }

  DEFINE_STANDARD_RTTIEXT(XSControl_WorkSession, IFSelect_WorkSession)

private:
  Standard_EXPORT void ClearBinders();

private:
  occ::handle<XSControl_Controller>     myController;
  occ::handle<XSControl_TransferReader> myTransferReader;
  occ::handle<XSControl_TransferWriter> myTransferWriter;
  XSControl_WorkSessionMap              myContext;
  occ::handle<XSControl_Vars>           myVars;
};
