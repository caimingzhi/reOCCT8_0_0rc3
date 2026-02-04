#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Document;

class StepBasic_DocumentRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DocumentRelationship();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepBasic_Document>&       aRelating,
                            const occ::handle<StepBasic_Document>&       aRelated);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<StepBasic_Document> RelatingDocument() const;

  Standard_EXPORT void SetRelatingDocument(const occ::handle<StepBasic_Document>& aRelating);

  Standard_EXPORT occ::handle<StepBasic_Document> RelatedDocument() const;

  Standard_EXPORT void SetRelatedDocument(const occ::handle<StepBasic_Document>& aRelated);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<StepBasic_Document>       theRelating;
  occ::handle<StepBasic_Document>       theRelated;
};

