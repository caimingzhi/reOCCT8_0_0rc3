#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductConceptContext;

//! Representation of STEP entity ProductConcept
class StepRepr_ProductConcept : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_ProductConcept();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        aId,
                            const occ::handle<TCollection_HAsciiString>&        aName,
                            const bool                                          hasDescription,
                            const occ::handle<TCollection_HAsciiString>&        aDescription,
                            const occ::handle<StepBasic_ProductConceptContext>& aMarketContext);

  //! Returns field Id
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  //! Set field Id
  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns True if optional field Description is defined
  Standard_EXPORT bool HasDescription() const;

  //! Returns field MarketContext
  Standard_EXPORT occ::handle<StepBasic_ProductConceptContext> MarketContext() const;

  //! Set field MarketContext
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

