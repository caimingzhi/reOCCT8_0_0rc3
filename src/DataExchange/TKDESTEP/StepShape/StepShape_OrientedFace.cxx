

#include <StepShape_OrientedFace.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_OrientedFace, StepShape_Face)

StepShape_OrientedFace::StepShape_OrientedFace() = default;

void StepShape_OrientedFace::Init(const occ::handle<TCollection_HAsciiString>& aName,
                                  const occ::handle<StepShape_Face>&           aFaceElement,
                                  const bool                                   aOrientation)
{

  faceElement = aFaceElement;
  orientation = aOrientation;

  occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> aBounds;
  aBounds.Nullify();
  StepShape_Face::Init(aName, aBounds);
}

void StepShape_OrientedFace::SetFaceElement(const occ::handle<StepShape_Face>& aFaceElement)
{
  faceElement = aFaceElement;
}

occ::handle<StepShape_Face> StepShape_OrientedFace::FaceElement() const
{
  return faceElement;
}

void StepShape_OrientedFace::SetOrientation(const bool aOrientation)
{
  orientation = aOrientation;
}

bool StepShape_OrientedFace::Orientation() const
{
  return orientation;
}

void StepShape_OrientedFace::SetBounds(
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>&)
{

  std::cout << "Field is redefined, SetUp Forbidden" << std::endl;
}

occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> StepShape_OrientedFace::Bounds()
  const
{

  return faceElement->Bounds();
}

occ::handle<StepShape_FaceBound> StepShape_OrientedFace::BoundsValue(const int num) const
{

  return faceElement->BoundsValue(num);
}

int StepShape_OrientedFace::NbBounds() const
{

  return faceElement->NbBounds();
}
