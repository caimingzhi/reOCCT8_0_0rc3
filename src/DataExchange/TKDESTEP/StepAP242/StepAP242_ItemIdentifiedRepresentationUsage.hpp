#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <StepAP242_ItemIdentifiedRepresentationUsageDefinition.hpp>
#include <Standard_Integer.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class TCollection_HAsciiString;
class StepRepr_Representation;
class StepRepr_RepresentationItem;

class StepAP242_ItemIdentifiedRepresentationUsage : public Standard_Transient
{

public:
  Standard_EXPORT StepAP242_ItemIdentifiedRepresentationUsage();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                 theName,
    const occ::handle<TCollection_HAsciiString>&                 theDescription,
    const StepAP242_ItemIdentifiedRepresentationUsageDefinition& theDefinition,
    const occ::handle<StepRepr_Representation>&                  theUsedRepresentation,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
      theIdentifiedItem);

  inline void SetName(const occ::handle<TCollection_HAsciiString>& theName) { name = theName; }

  inline occ::handle<TCollection_HAsciiString> Name() const { return name; }

  inline void SetDescription(const occ::handle<TCollection_HAsciiString>& theDescription)
  {
    description = theDescription;
  }

  inline occ::handle<TCollection_HAsciiString> Description() const { return description; }

  inline void SetDefinition(
    const StepAP242_ItemIdentifiedRepresentationUsageDefinition& theDefinition)
  {
    definition = theDefinition;
  }

  inline StepAP242_ItemIdentifiedRepresentationUsageDefinition Definition() const
  {
    return definition;
  }

  inline void SetUsedRepresentation(
    const occ::handle<StepRepr_Representation>& theUsedRepresentation)
  {
    usedRepresentation = theUsedRepresentation;
  }

  inline occ::handle<StepRepr_Representation> UsedRepresentation() const
  {
    return usedRepresentation;
  }

  inline occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> IdentifiedItem()
    const
  {
    return identifiedItem;
  }

  inline int NbIdentifiedItem() const
  {
    return (identifiedItem.IsNull() ? 0 : identifiedItem->Length());
  }

  inline void SetIdentifiedItem(
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>&
      theIdentifiedItem)
  {
    identifiedItem = theIdentifiedItem;
  }

  inline occ::handle<StepRepr_RepresentationItem> IdentifiedItemValue(const int num) const
  {
    return identifiedItem->Value(num);
  }

  inline void SetIdentifiedItemValue(const int                                       num,
                                     const occ::handle<StepRepr_RepresentationItem>& theItem)
  {
    identifiedItem->SetValue(num, theItem);
  }

  DEFINE_STANDARD_RTTIEXT(StepAP242_ItemIdentifiedRepresentationUsage, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                      name;
  occ::handle<TCollection_HAsciiString>                                      description;
  StepAP242_ItemIdentifiedRepresentationUsageDefinition                      definition;
  occ::handle<StepRepr_Representation>                                       usedRepresentation;
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> identifiedItem;
};
