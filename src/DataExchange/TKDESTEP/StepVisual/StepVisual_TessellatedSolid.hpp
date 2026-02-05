#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_TessellatedStructuredItem.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>

//! Representation of STEP entity TessellatedSolid
class StepVisual_TessellatedSolid : public StepVisual_TessellatedItem
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedSolid();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
                                                    theItems,
    const bool                                      theHasGeometricLink,
    const occ::handle<StepShape_ManifoldSolidBrep>& theGeometricLink);

  //! Returns field Items
  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>
    Items() const;

  //! Sets field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>>&
      theItems);

  //! Returns number of Items
  Standard_EXPORT int NbItems() const;

  //! Returns value of Items by its num
  Standard_EXPORT occ::handle<StepVisual_TessellatedStructuredItem> ItemsValue(
    const int theNum) const;

  //! Returns field GeometricLink
  Standard_EXPORT occ::handle<StepShape_ManifoldSolidBrep> GeometricLink() const;

  //! Sets field GeometricLink
  Standard_EXPORT void SetGeometricLink(
    const occ::handle<StepShape_ManifoldSolidBrep>& theGeometricLink);

  //! Returns True if optional field GeometricLink is defined
  Standard_EXPORT bool HasGeometricLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedSolid, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>> myItems;
  occ::handle<StepShape_ManifoldSolidBrep> myGeometricLink;    //!< optional
  bool                                     myHasGeometricLink; //!< flag "is GeometricLink defined"
};
