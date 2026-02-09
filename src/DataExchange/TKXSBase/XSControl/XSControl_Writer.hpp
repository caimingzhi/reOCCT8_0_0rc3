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

class XSControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XSControl_Writer();

  Standard_EXPORT XSControl_Writer(const char* norm);

  Standard_EXPORT XSControl_Writer(const occ::handle<XSControl_WorkSession>& WS,
                                   const bool                                scratch = true);

  Standard_EXPORT bool SetNorm(const char* norm);

  Standard_EXPORT void SetWS(const occ::handle<XSControl_WorkSession>& WS,
                             const bool                                scratch = true);

  Standard_EXPORT occ::handle<XSControl_WorkSession> WS() const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model(const bool newone = false);

  Standard_EXPORT IFSelect_ReturnStatus
    TransferShape(const TopoDS_Shape&          sh,
                  const int                    mode        = 0,
                  const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT IFSelect_ReturnStatus WriteFile(const char* filename);

  Standard_EXPORT void PrintStatsTransfer(const int what, const int mode = 0) const;

private:
  occ::handle<XSControl_WorkSession> thesession;
};
