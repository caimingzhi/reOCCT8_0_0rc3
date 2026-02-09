#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_WriterLib.hpp>
#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
#include <TCollection_AsciiString.hpp>

#include <mutex>

class StepData_Protocol;
class Interface_Protocol;
class Standard_Transient;
class Interface_InterfaceModel;

class StepSelect_StepType : public IFSelect_Signature
{

public:
  Standard_EXPORT StepSelect_StepType();

  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& proto);

  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(StepSelect_StepType, IFSelect_Signature)

protected:
  StepData_WriterLib thelib;

private:
  occ::handle<StepData_Protocol>  theproto;
  mutable TCollection_AsciiString theLastValue;
  mutable std::mutex              myMutex;
};
