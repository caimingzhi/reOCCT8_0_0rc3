#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class StepFEA_FeaModel;
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;

//! Representation of STEP entity NodeRepresentation
class StepFEA_NodeRepresentation : public StepRepr_Representation
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_NodeRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentation_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
                                                       aRepresentation_Items,
    const occ::handle<StepRepr_RepresentationContext>& aRepresentation_ContextOfItems,
    const occ::handle<StepFEA_FeaModel>&               aModelRef);

  //! Returns field ModelRef
  Standard_EXPORT occ::handle<StepFEA_FeaModel> ModelRef() const;

  //! Set field ModelRef
  Standard_EXPORT void SetModelRef(const occ::handle<StepFEA_FeaModel>& ModelRef);

  DEFINE_STANDARD_RTTIEXT(StepFEA_NodeRepresentation, StepRepr_Representation)

private:
  occ::handle<StepFEA_FeaModel> theModelRef;
};

