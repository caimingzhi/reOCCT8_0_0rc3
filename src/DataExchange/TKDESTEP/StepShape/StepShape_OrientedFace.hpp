#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepShape_Face.hpp>
#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_FaceBound;

class StepShape_OrientedFace : public StepShape_Face
{

public:
  Standard_EXPORT StepShape_OrientedFace();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_Face>&           aFaceElement,
                            const bool                                   aOrientation);

  Standard_EXPORT void SetFaceElement(const occ::handle<StepShape_Face>& aFaceElement);

  Standard_EXPORT occ::handle<StepShape_Face> FaceElement() const;

  Standard_EXPORT void SetOrientation(const bool aOrientation);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetBounds(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds) override;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> Bounds()
    const override;

  Standard_EXPORT occ::handle<StepShape_FaceBound> BoundsValue(const int num) const override;

  Standard_EXPORT int NbBounds() const override;

  DEFINE_STANDARD_RTTIEXT(StepShape_OrientedFace, StepShape_Face)

private:
  occ::handle<StepShape_Face> faceElement;
  bool                        orientation;
};
