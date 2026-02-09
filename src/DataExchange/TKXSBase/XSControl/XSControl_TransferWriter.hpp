#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Transfer_FinderProcess.hpp>
class XSControl_Controller;
class Interface_InterfaceModel;
class TopoDS_Shape;
class Interface_CheckIterator;

class XSControl_TransferWriter : public Standard_Transient
{
public:
  XSControl_TransferWriter()
      : myTransferWriter(new Transfer_FinderProcess),
        myTransferMode(0)
  {
  }

  const occ::handle<Transfer_FinderProcess>& FinderProcess() const { return myTransferWriter; }

  void SetFinderProcess(const occ::handle<Transfer_FinderProcess>& theFP)
  {
    myTransferWriter = theFP;
  }

  const occ::handle<XSControl_Controller>& Controller() const { return myController; }

  void SetController(const occ::handle<XSControl_Controller>& theCtl)
  {
    myController = theCtl;
    Clear(-1);
  }

  Standard_EXPORT void Clear(const int theMode);

  int TransferMode() const { return myTransferMode; }

  void SetTransferMode(const int theMode) { myTransferMode = theMode; }

  Standard_EXPORT void PrintStats(const int theWhat, const int theMode = 0) const;

  Standard_EXPORT bool RecognizeTransient(const occ::handle<Standard_Transient>& theObj);

  Standard_EXPORT IFSelect_ReturnStatus
    TransferWriteTransient(const occ::handle<Interface_InterfaceModel>& theModel,
                           const occ::handle<Standard_Transient>&       theObj,
                           const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool RecognizeShape(const TopoDS_Shape& theShape);

  Standard_EXPORT IFSelect_ReturnStatus
    TransferWriteShape(const occ::handle<Interface_InterfaceModel>& theModel,
                       const TopoDS_Shape&                          theShape,
                       const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT Interface_CheckIterator CheckList() const;

  Standard_EXPORT Interface_CheckIterator
    ResultCheckList(const occ::handle<Interface_InterfaceModel>& theModel) const;

  DEFINE_STANDARD_RTTIEXT(XSControl_TransferWriter, Standard_Transient)

private:
  occ::handle<XSControl_Controller>   myController;
  occ::handle<Transfer_FinderProcess> myTransferWriter;
  int                                 myTransferMode;
};
