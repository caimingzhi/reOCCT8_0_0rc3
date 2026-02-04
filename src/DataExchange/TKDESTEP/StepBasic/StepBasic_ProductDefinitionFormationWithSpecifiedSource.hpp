#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Source.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
class TCollection_HAsciiString;
class StepBasic_Product;

class StepBasic_ProductDefinitionFormationWithSpecifiedSource
    : public StepBasic_ProductDefinitionFormation
{

public:
  //! Returns a ProductDefinitionFormationWithSpecifiedSource
  Standard_EXPORT StepBasic_ProductDefinitionFormationWithSpecifiedSource();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_Product>&        aOfProduct,
                            const StepBasic_Source                       aMakeOrBuy);

  Standard_EXPORT void SetMakeOrBuy(const StepBasic_Source aMakeOrBuy);

  Standard_EXPORT StepBasic_Source MakeOrBuy() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormationWithSpecifiedSource,
                          StepBasic_ProductDefinitionFormation)

private:
  StepBasic_Source makeOrBuy;
};

