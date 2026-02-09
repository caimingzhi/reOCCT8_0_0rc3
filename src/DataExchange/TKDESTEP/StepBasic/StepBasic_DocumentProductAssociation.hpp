#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ProductOrFormationOrDefinition.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_Document;

class StepBasic_DocumentProductAssociation : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DocumentProductAssociation();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    aName,
                            const bool                                      hasDescription,
                            const occ::handle<TCollection_HAsciiString>&    aDescription,
                            const occ::handle<StepBasic_Document>&          aRelatingDocument,
                            const StepBasic_ProductOrFormationOrDefinition& aRelatedProduct);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepBasic_Document> RelatingDocument() const;

  Standard_EXPORT void SetRelatingDocument(const occ::handle<StepBasic_Document>& RelatingDocument);

  Standard_EXPORT StepBasic_ProductOrFormationOrDefinition RelatedProduct() const;

  Standard_EXPORT void SetRelatedProduct(
    const StepBasic_ProductOrFormationOrDefinition& RelatedProduct);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentProductAssociation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>    theName;
  occ::handle<TCollection_HAsciiString>    theDescription;
  occ::handle<StepBasic_Document>          theRelatingDocument;
  StepBasic_ProductOrFormationOrDefinition theRelatedProduct;
  bool                                     defDescription;
};
