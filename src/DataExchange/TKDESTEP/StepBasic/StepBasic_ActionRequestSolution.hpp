#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_ActionMethod;
class StepBasic_VersionedActionRequest;

//! Representation of STEP entity ActionRequestSolution
class StepBasic_ActionRequestSolution : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ActionRequestSolution();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_ActionMethod>&           aMethod,
                            const occ::handle<StepBasic_VersionedActionRequest>& aRequest);

  //! Returns field Method
  Standard_EXPORT occ::handle<StepBasic_ActionMethod> Method() const;

  //! Set field Method
  Standard_EXPORT void SetMethod(const occ::handle<StepBasic_ActionMethod>& Method);

  //! Returns field Request
  Standard_EXPORT occ::handle<StepBasic_VersionedActionRequest> Request() const;

  //! Set field Request
  Standard_EXPORT void SetRequest(const occ::handle<StepBasic_VersionedActionRequest>& Request);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionRequestSolution, Standard_Transient)

private:
  occ::handle<StepBasic_ActionMethod>           theMethod;
  occ::handle<StepBasic_VersionedActionRequest> theRequest;
};

