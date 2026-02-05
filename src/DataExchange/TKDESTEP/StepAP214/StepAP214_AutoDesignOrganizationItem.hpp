#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepAP214_AutoDesignGeneralOrgItem.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepBasic_Document;
class StepBasic_PhysicallyModeledProductDefinition;

class StepAP214_AutoDesignOrganizationItem : public StepAP214_AutoDesignGeneralOrgItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP214_AutoDesignOrganizationItem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepBasic_Document> Document() const;

  Standard_EXPORT occ::handle<StepBasic_PhysicallyModeledProductDefinition>
                  PhysicallyModeledProductDefinition() const;
};
