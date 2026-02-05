#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <Standard_Integer.hpp>
#include <Message_ProgressRange.hpp>

class XSControl_WorkSession;
class Interface_InterfaceModel;
class TopoDS_Shape;

//! This class gives a simple way to create then write a
//! Model compliant to a given norm, from a Shape
//! The model can then be edited by tools by other appropriate tools
class XSControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a Writer from scratch
  Standard_EXPORT XSControl_Writer();

  //! Creates a Writer from scratch, with a norm name which
  //! identifie a Controller
  Standard_EXPORT XSControl_Writer(const char* norm);

  //! Creates a Writer from an already existing Session
  //! If <scratch> is True (D), clears already recorded data
  Standard_EXPORT XSControl_Writer(const occ::handle<XSControl_WorkSession>& WS,
                                   const bool                                scratch = true);

  //! Sets a specific norm to <me>
  //! Returns True if done, False if <norm> is not available
  Standard_EXPORT bool SetNorm(const char* norm);

  //! Sets a specific session to <me>
  Standard_EXPORT void SetWS(const occ::handle<XSControl_WorkSession>& WS,
                             const bool                                scratch = true);

  //! Returns the session used in <me>
  Standard_EXPORT occ::handle<XSControl_WorkSession> WS() const;

  //! Returns the produced model. Produces a new one if not yet done
  //! or if <newone> is True
  //! This method allows for instance to edit product or header
  //! data before writing
  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model(const bool newone = false);

  //! Transfers a Shape according to the mode
  Standard_EXPORT IFSelect_ReturnStatus
    TransferShape(const TopoDS_Shape&          sh,
                  const int                    mode        = 0,
                  const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Writes the produced model
  Standard_EXPORT IFSelect_ReturnStatus WriteFile(const char* filename);

  //! Prints Statistics about Transfer
  Standard_EXPORT void PrintStatsTransfer(const int what, const int mode = 0) const;

private:
  occ::handle<XSControl_WorkSession> thesession;
};
