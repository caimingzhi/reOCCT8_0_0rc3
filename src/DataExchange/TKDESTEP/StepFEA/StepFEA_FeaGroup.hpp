#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Group.hpp>
class StepFEA_FeaModel;
class TCollection_HAsciiString;

class StepFEA_FeaGroup : public StepBasic_Group
{

public:
  Standard_EXPORT StepFEA_FeaGroup();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aGroup_Name,
                            const occ::handle<TCollection_HAsciiString>& aGroup_Description,
                            const occ::handle<StepFEA_FeaModel>&         aModelRef);

  Standard_EXPORT occ::handle<StepFEA_FeaModel> ModelRef() const;

  Standard_EXPORT void SetModelRef(const occ::handle<StepFEA_FeaModel>& ModelRef);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaGroup, StepBasic_Group)

private:
  occ::handle<StepFEA_FeaModel> theModelRef;
};
