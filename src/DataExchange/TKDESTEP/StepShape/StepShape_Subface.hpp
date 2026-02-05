#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_Face.hpp>
#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity Subface
class StepShape_Subface : public StepShape_Face
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_Subface();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aFace_Bounds,
    const occ::handle<StepShape_Face>&                                        aParentFace);

  //! Returns field ParentFace
  Standard_EXPORT occ::handle<StepShape_Face> ParentFace() const;

  //! Set field ParentFace
  Standard_EXPORT void SetParentFace(const occ::handle<StepShape_Face>& ParentFace);

  DEFINE_STANDARD_RTTIEXT(StepShape_Subface, StepShape_Face)

private:
  occ::handle<StepShape_Face> theParentFace;
};
