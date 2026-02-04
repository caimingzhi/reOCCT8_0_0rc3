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

//! TransferWriter gives help to control transfer to write a file
//! after having converted data from Cascade/Imagine
//!
//! It works with a Controller (which itself can work with an
//! Actor to Write) and a FinderProcess. It records results and
//! checks
class XSControl_TransferWriter : public Standard_Transient
{
public:
  //! Creates a TransferWriter, empty, ready to run
  //! with an empty FinderProcess (but no controller, etc)
  XSControl_TransferWriter()
      : myTransferWriter(new Transfer_FinderProcess),
        myTransferMode(0)
  {
  }

  //! Returns the FinderProcess itself
  const occ::handle<Transfer_FinderProcess>& FinderProcess() const { return myTransferWriter; }

  //! Sets a new FinderProcess and forgets the former one
  void SetFinderProcess(const occ::handle<Transfer_FinderProcess>& theFP)
  {
    myTransferWriter = theFP;
  }

  //! Returns the currently used Controller
  const occ::handle<XSControl_Controller>& Controller() const { return myController; }

  //! Sets a new Controller, also sets a new FinderProcess
  void SetController(const occ::handle<XSControl_Controller>& theCtl)
  {
    myController = theCtl;
    Clear(-1);
  }

  //! Clears recorded data according a mode
  //! 0 clears FinderProcess (results, checks)
  //! -1 create a new FinderProcess
  Standard_EXPORT void Clear(const int theMode);

  //! Returns the current Transfer Mode (an Integer)
  //! It will be interpreted by the Controller to run Transfers
  //! This call form could be later replaced by more specific ones
  //! (parameters suited for each norm / transfer case)
  int TransferMode() const { return myTransferMode; }

  //! Changes the Transfer Mode
  void SetTransferMode(const int theMode) { myTransferMode = theMode; }

  //! Prints statistics on current Trace File, according what,mode
  //! See PrintStatsProcess for details
  Standard_EXPORT void PrintStats(const int theWhat, const int theMode = 0) const;

  //! Tells if a transient object (from an application) is a valid
  //! candidate for a transfer to a model
  //! Asks the Controller (RecognizeWriteTransient)
  //! If <obj> is a HShape, calls RecognizeShape
  Standard_EXPORT bool RecognizeTransient(const occ::handle<Standard_Transient>& theObj);

  //! Transfers a Transient object (from an application) to a model
  //! of current norm, according to the last call to SetTransferMode
  //! Works by calling the Controller
  //! Returns status : =0 if OK, >0 if error during transfer, <0 if
  //! transfer badly initialised
  Standard_EXPORT IFSelect_ReturnStatus
    TransferWriteTransient(const occ::handle<Interface_InterfaceModel>& theModel,
                           const occ::handle<Standard_Transient>&       theObj,
                           const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Tells if a Shape is valid for a transfer to a model
  //! Asks the Controller (RecognizeWriteShape)
  Standard_EXPORT bool RecognizeShape(const TopoDS_Shape& theShape);

  //! Transfers a Shape from CasCade to a model of current norm,
  //! according to the last call to SetTransferMode
  //! Works by calling the Controller
  //! Returns status : =0 if OK, >0 if error during transfer, <0 if
  //! transfer badly initialised
  Standard_EXPORT IFSelect_ReturnStatus
    TransferWriteShape(const occ::handle<Interface_InterfaceModel>& theModel,
                       const TopoDS_Shape&                          theShape,
                       const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Returns the check-list of last transfer (write), i.e. the
  //! check-list currently recorded in the FinderProcess
  Standard_EXPORT Interface_CheckIterator CheckList() const;

  //! Returns the check-list of last transfer (write), but tries
  //! to bind to each check, the resulting entity in the model
  //! instead of keeping the original Mapper, whenever known
  Standard_EXPORT Interface_CheckIterator
    ResultCheckList(const occ::handle<Interface_InterfaceModel>& theModel) const;

  DEFINE_STANDARD_RTTIEXT(XSControl_TransferWriter, Standard_Transient)

private:
  occ::handle<XSControl_Controller>   myController;
  occ::handle<Transfer_FinderProcess> myTransferWriter;
  int                                 myTransferMode;
};

