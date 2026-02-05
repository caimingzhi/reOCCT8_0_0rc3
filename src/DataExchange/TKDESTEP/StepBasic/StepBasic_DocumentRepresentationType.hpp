#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Document;

//! Representation of STEP entity DocumentRepresentationType
class StepBasic_DocumentRepresentationType : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_DocumentRepresentationType();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepBasic_Document>&       aRepresentedDocument);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field RepresentedDocument
  Standard_EXPORT occ::handle<StepBasic_Document> RepresentedDocument() const;

  //! Set field RepresentedDocument
  Standard_EXPORT void SetRepresentedDocument(
    const occ::handle<StepBasic_Document>& RepresentedDocument);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentRepresentationType, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<StepBasic_Document>       theRepresentedDocument;
};
