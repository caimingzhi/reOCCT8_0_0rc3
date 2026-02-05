#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationContext;
class StepRepr_RepresentationItem;

class StepRepr_Representation : public Standard_Transient
{

public:
  //! Returns a Representation
  Standard_EXPORT StepRepr_Representation();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                      aName,
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& aItems,
    const occ::handle<StepRepr_RepresentationContext>& aContextOfItems);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>>& aItems);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> Items()
    const;

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> ItemsValue(const int num) const;

  Standard_EXPORT int NbItems() const;

  Standard_EXPORT void SetContextOfItems(
    const occ::handle<StepRepr_RepresentationContext>& aContextOfItems);

  Standard_EXPORT occ::handle<StepRepr_RepresentationContext> ContextOfItems() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_Representation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                                      name;
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> items;
  occ::handle<StepRepr_RepresentationContext>                                contextOfItems;
};
