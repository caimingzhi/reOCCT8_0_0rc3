#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_Representation;

class StepRepr_RepresentationRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_RepresentationRelationship();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepRepr_Representation>&  aRep1,
                            const occ::handle<StepRepr_Representation>&  aRep2);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  bool HasDescription() { return !description.IsNull(); }

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetRep1(const occ::handle<StepRepr_Representation>& aRep1);

  Standard_EXPORT occ::handle<StepRepr_Representation> Rep1() const;

  Standard_EXPORT void SetRep2(const occ::handle<StepRepr_Representation>& aRep2);

  Standard_EXPORT occ::handle<StepRepr_Representation> Rep2() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<TCollection_HAsciiString> description;
  occ::handle<StepRepr_Representation>  rep1;
  occ::handle<StepRepr_Representation>  rep2;
};
