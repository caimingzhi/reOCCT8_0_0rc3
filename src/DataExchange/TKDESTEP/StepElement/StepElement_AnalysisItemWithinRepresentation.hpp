#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationItem;
class StepRepr_Representation;

//! Representation of STEP entity AnalysisItemWithinRepresentation
class StepElement_AnalysisItemWithinRepresentation : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_AnalysisItemWithinRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    aName,
                            const occ::handle<TCollection_HAsciiString>&    aDescription,
                            const occ::handle<StepRepr_RepresentationItem>& aItem,
                            const occ::handle<StepRepr_Representation>&     aRep);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  //! Returns field Description
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  //! Set field Description
  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  //! Returns field Item
  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> Item() const;

  //! Set field Item
  Standard_EXPORT void SetItem(const occ::handle<StepRepr_RepresentationItem>& Item);

  //! Returns field Rep
  Standard_EXPORT occ::handle<StepRepr_Representation> Rep() const;

  //! Set field Rep
  Standard_EXPORT void SetRep(const occ::handle<StepRepr_Representation>& Rep);

  DEFINE_STANDARD_RTTIEXT(StepElement_AnalysisItemWithinRepresentation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>    theName;
  occ::handle<TCollection_HAsciiString>    theDescription;
  occ::handle<StepRepr_RepresentationItem> theItem;
  occ::handle<StepRepr_Representation>     theRep;
};
