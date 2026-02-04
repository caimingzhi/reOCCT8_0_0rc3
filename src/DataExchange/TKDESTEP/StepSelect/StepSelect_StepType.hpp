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

//! StepType is a Signature specific to Step definitions : it
//! considers the type as defined in STEP Schemas, the same which
//! is used in files.
//! For a Complex Type, if its definition is known, StepType
//! produces the list of basic types, separated by commas, the
//! whole between brackets : "(TYPE1,TYPE2..)".
//! If its precise definition is not known (simply it is known as
//! Complex, it can be recognised, but the list is produced at
//! Write time only), StepType produces : "(..COMPLEX TYPE..)"
class StepSelect_StepType : public IFSelect_Signature
{

public:
  //! Creates a Signature for Step Type. Protocol is undefined here,
  //! hence no Signature may yet be produced. The StepType signature
  //! requires a Protocol before working
  Standard_EXPORT StepSelect_StepType();

  //! Sets the StepType signature to work with a Protocol : this
  //! initialises the library
  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& proto);

  //! Returns the Step Type defined from the Protocol (see above).
  //! If <ent> is not recognised, produces "..NOT FROM SCHEMA <name>.."
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

