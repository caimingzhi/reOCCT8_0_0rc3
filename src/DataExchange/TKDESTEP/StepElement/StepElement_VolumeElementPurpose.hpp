#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

enum StepElement_EnumeratedVolumeElementPurpose
{
  StepElement_StressDisplacement
};

class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

class StepElement_VolumeElementPurpose : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepElement_VolumeElementPurpose();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT void SetEnumeratedVolumeElementPurpose(
    const StepElement_EnumeratedVolumeElementPurpose aVal);

  Standard_EXPORT StepElement_EnumeratedVolumeElementPurpose EnumeratedVolumeElementPurpose() const;

  Standard_EXPORT void SetApplicationDefinedElementPurpose(
    const occ::handle<TCollection_HAsciiString>& aVal);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationDefinedElementPurpose() const;
};
