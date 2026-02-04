#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity VersionedActionRequest
class StepBasic_VersionedActionRequest : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_VersionedActionRequest();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aVersion,
                            const occ::handle<TCollection_HAsciiString>& aPurpose,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  //! Returns field Id
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  //! Set field Id
  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  //! Returns field Version
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Version() const;

  //! Set field Version
  Standard_EXPORT void SetVersion(const occ::handle<TCollection_HAsciiString>& Version);

  //! Returns field Purpose
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  //! Set field Purpose
  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns True if optional field Description is defined
  Standard_EXPORT bool HasDescription() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_VersionedActionRequest, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theId;
  occ::handle<TCollection_HAsciiString> theVersion;
  occ::handle<TCollection_HAsciiString> thePurpose;
  occ::handle<TCollection_HAsciiString> theDescription;
  bool                                  defDescription;
};

