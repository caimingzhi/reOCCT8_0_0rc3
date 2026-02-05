#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Effectivity.hpp>
class StepBasic_ProductDefinitionRelationship;
class TCollection_HAsciiString;

class StepBasic_ProductDefinitionEffectivity : public StepBasic_Effectivity
{

public:
  Standard_EXPORT StepBasic_ProductDefinitionEffectivity();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&                aId,
                            const occ::handle<StepBasic_ProductDefinitionRelationship>& aUsage);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionRelationship> Usage() const;

  Standard_EXPORT void SetUsage(const occ::handle<StepBasic_ProductDefinitionRelationship>& aUsage);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionEffectivity, StepBasic_Effectivity)

private:
  occ::handle<StepBasic_ProductDefinitionRelationship> theUsage;
};
