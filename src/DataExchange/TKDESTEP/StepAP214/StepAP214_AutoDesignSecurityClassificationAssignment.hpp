#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Approval.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_SecurityClassificationAssignment.hpp>
#include <Standard_Integer.hpp>
class StepBasic_SecurityClassification;
class StepBasic_Approval;

class StepAP214_AutoDesignSecurityClassificationAssignment
    : public StepBasic_SecurityClassificationAssignment
{

public:
  //! Returns a AutoDesignSecurityClassificationAssignment
  Standard_EXPORT StepAP214_AutoDesignSecurityClassificationAssignment();

  Standard_EXPORT void Init(
    const occ::handle<StepBasic_SecurityClassification>& aAssignedSecurityClassification,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>>& aItems);

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>> Items() const;

  Standard_EXPORT occ::handle<StepBasic_Approval> ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  DEFINE_STANDARD_RTTIEXT(StepAP214_AutoDesignSecurityClassificationAssignment,
                          StepBasic_SecurityClassificationAssignment)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Approval>>> items;
};

