#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_TessellatedEdgeOrVertex.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_PathOrCompositeCurve.hpp>

//! Representation of STEP entity TessellatedWire
class StepVisual_TessellatedWire : public StepVisual_TessellatedItem
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedWire();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>>& theItems,
    const bool                             theHasGeometricModelLink,
    const StepVisual_PathOrCompositeCurve& theGeometricModelLink);

  //! Returns field Items
  Standard_EXPORT occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>> Items()
    const;

  //! Sets field Items
  Standard_EXPORT void SetItems(
    const occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>>& theItems);

  //! Returns number of Items
  Standard_EXPORT int NbItems() const;

  //! Returns value of Items by its num
  Standard_EXPORT const StepVisual_TessellatedEdgeOrVertex& ItemsValue(const int theNum) const;

  //! Returns field GeometricModelLink
  Standard_EXPORT StepVisual_PathOrCompositeCurve GeometricModelLink() const;

  //! Sets field GeometricModelLink
  Standard_EXPORT void SetGeometricModelLink(
    const StepVisual_PathOrCompositeCurve& theGeometricModelLink);

  //! Returns True if optional field GeometricModelLink is defined
  Standard_EXPORT bool HasGeometricModelLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedWire, StepVisual_TessellatedItem)

private:
  occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>> myItems;
  StepVisual_PathOrCompositeCurve myGeometricModelLink;    //!< optional
  bool                            myHasGeometricModelLink; //!< flag "is GeometricModelLink defined"
};
