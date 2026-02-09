#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductConceptContext;

class StepRepr_ProductConcept : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_ProductConcept();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        aId,
                            const occ::handle<TCollection_HAsciiString>&        aName,
                            const bool                                          hasDescription,
                            const occ::handle<TCollection_HAsciiString>&        aDescription,
                            const occ::handle<StepBasic_ProductConceptContext>& aMarketContext);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepBasic_ProductConceptContext> MarketContext() const;

  Standard_EXPORT void SetMarketContext(
    const occ::handle<StepBasic_ProductConceptContext>& MarketContext);

  DEFINE_STANDARD_RTTIEXT(StepRepr_ProductConcept, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>        theId;
  occ::handle<TCollection_HAsciiString>        theName;
  occ::handle<TCollection_HAsciiString>        theDescription;
  occ::handle<StepBasic_ProductConceptContext> theMarketContext;
  bool                                         defDescription;
};
