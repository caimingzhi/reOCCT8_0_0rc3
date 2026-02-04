#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Document;
class TCollection_HAsciiString;

class StepBasic_DocumentReference : public Standard_Transient
{

public:
  Standard_EXPORT void Init0(const occ::handle<StepBasic_Document>&       aAssignedDocument,
                             const occ::handle<TCollection_HAsciiString>& aSource);

  Standard_EXPORT occ::handle<StepBasic_Document> AssignedDocument() const;

  Standard_EXPORT void SetAssignedDocument(
    const occ::handle<StepBasic_Document>& aAssignedDocument);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Source() const;

  Standard_EXPORT void SetSource(const occ::handle<TCollection_HAsciiString>& aSource);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentReference, Standard_Transient)

private:
  occ::handle<StepBasic_Document>       theAssignedDocument;
  occ::handle<TCollection_HAsciiString> theSource;
};

