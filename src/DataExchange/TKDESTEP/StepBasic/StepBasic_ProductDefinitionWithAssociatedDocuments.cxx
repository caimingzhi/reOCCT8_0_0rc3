

#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionWithAssociatedDocuments.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionWithAssociatedDocuments,
                           StepBasic_ProductDefinition)

StepBasic_ProductDefinitionWithAssociatedDocuments::
  StepBasic_ProductDefinitionWithAssociatedDocuments() = default;

void StepBasic_ProductDefinitionWithAssociatedDocuments::Init(
  const occ::handle<TCollection_HAsciiString>&                             aId,
  const occ::handle<TCollection_HAsciiString>&                             aDescription,
  const occ::handle<StepBasic_ProductDefinitionFormation>&                 aFormation,
  const occ::handle<StepBasic_ProductDefinitionContext>&                   aFrame,
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>>& aDocIds)
{
  StepBasic_ProductDefinition::Init(aId, aDescription, aFormation, aFrame);
  theDocIds = aDocIds;
}

occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>>
  StepBasic_ProductDefinitionWithAssociatedDocuments::DocIds() const
{
  return theDocIds;
}

void StepBasic_ProductDefinitionWithAssociatedDocuments::SetDocIds(
  const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>>& aDocIds)
{
  theDocIds = aDocIds;
}

int StepBasic_ProductDefinitionWithAssociatedDocuments::NbDocIds() const
{
  return (theDocIds.IsNull() ? 0 : theDocIds->Length());
}

occ::handle<StepBasic_Document> StepBasic_ProductDefinitionWithAssociatedDocuments::DocIdsValue(
  const int num) const
{
  return theDocIds->Value(num);
}

void StepBasic_ProductDefinitionWithAssociatedDocuments::SetDocIdsValue(
  const int                              num,
  const occ::handle<StepBasic_Document>& adoc)
{
  theDocIds->SetValue(num, adoc);
}
