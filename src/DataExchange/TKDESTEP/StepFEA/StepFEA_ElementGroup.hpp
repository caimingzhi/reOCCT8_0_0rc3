#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_ElementRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_FeaGroup.hpp>
class TCollection_HAsciiString;
class StepFEA_FeaModel;

//! Representation of STEP entity ElementGroup
class StepFEA_ElementGroup : public StepFEA_FeaGroup
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_ElementGroup();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aGroup_Name,
    const occ::handle<TCollection_HAsciiString>& aGroup_Description,
    const occ::handle<StepFEA_FeaModel>&         aFeaGroup_ModelRef,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>& aElements);

  //! Returns field Elements
  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>
                  Elements() const;

  //! Set field Elements
  Standard_EXPORT void SetElements(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>& Elements);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ElementGroup, StepFEA_FeaGroup)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>> theElements;
};

