#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Document.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinitionContext;
class StepBasic_Document;

class StepBasic_ProductDefinitionWithAssociatedDocuments : public StepBasic_ProductDefinition
{

public:
  Standard_EXPORT StepBasic_ProductDefinitionWithAssociatedDocuments();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                             aId,
    const occ::handle<TCollection_HAsciiString>&                             aDescription,
    const occ::handle<StepBasic_ProductDefinitionFormation>&                 aFormation,
    const occ::handle<StepBasic_ProductDefinitionContext>&                   aFrame,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>>& aDocIds);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>> DocIds() const;

  Standard_EXPORT void SetDocIds(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>>& DocIds);

  Standard_EXPORT int NbDocIds() const;

  Standard_EXPORT occ::handle<StepBasic_Document> DocIdsValue(const int num) const;

  Standard_EXPORT void SetDocIdsValue(const int num, const occ::handle<StepBasic_Document>& adoc);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionWithAssociatedDocuments,
                          StepBasic_ProductDefinition)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>> theDocIds;
};

