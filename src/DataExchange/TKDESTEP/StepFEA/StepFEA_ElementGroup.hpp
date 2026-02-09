#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepFEA_ElementRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepFEA_FeaGroup.hpp>
class TCollection_HAsciiString;
class StepFEA_FeaModel;

class StepFEA_ElementGroup : public StepFEA_FeaGroup
{

public:
  Standard_EXPORT StepFEA_ElementGroup();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aGroup_Name,
    const occ::handle<TCollection_HAsciiString>& aGroup_Description,
    const occ::handle<StepFEA_FeaModel>&         aFeaGroup_ModelRef,
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>& aElements);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>
                  Elements() const;

  Standard_EXPORT void SetElements(
    const occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>& Elements);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ElementGroup, StepFEA_FeaGroup)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>> theElements;
};
