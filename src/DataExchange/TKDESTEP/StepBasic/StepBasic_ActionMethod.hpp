#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity ActionMethod
class StepBasic_ActionMethod : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_ActionMethod();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<TCollection_HAsciiString>& aConsequence,
                            const occ::handle<TCollection_HAsciiString>& aPurpose);

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

  //! Returns field Consequence
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Consequence() const;

  //! Set field Consequence
  Standard_EXPORT void SetConsequence(const occ::handle<TCollection_HAsciiString>& Consequence);

  //! Returns field Purpose
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  //! Set field Purpose
  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionMethod, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<TCollection_HAsciiString> theConsequence;
  occ::handle<TCollection_HAsciiString> thePurpose;
  bool                                  defDescription;
};

