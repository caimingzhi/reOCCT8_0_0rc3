#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

enum StepElement_EnumeratedSurfaceElementPurpose
{
  StepElement_MembraneDirect,
  StepElement_MembraneShear,
  StepElement_BendingDirect,
  StepElement_BendingTorsion,
  StepElement_NormalToPlaneShear
};

class Standard_Transient;
class StepData_SelectMember;
class TCollection_HAsciiString;

class StepElement_SurfaceElementPurpose : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepElement_SurfaceElementPurpose();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  Standard_EXPORT void SetEnumeratedSurfaceElementPurpose(
    const StepElement_EnumeratedSurfaceElementPurpose aVal);

  Standard_EXPORT StepElement_EnumeratedSurfaceElementPurpose
    EnumeratedSurfaceElementPurpose() const;

  Standard_EXPORT void SetApplicationDefinedElementPurpose(
    const occ::handle<TCollection_HAsciiString>& aVal);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationDefinedElementPurpose() const;
};
