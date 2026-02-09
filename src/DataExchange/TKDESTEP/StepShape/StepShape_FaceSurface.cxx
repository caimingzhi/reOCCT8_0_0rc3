

#include <StepGeom_Surface.hpp>
#include <StepShape_FaceSurface.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_FaceSurface, StepShape_Face)

StepShape_FaceSurface::StepShape_FaceSurface() = default;

void StepShape_FaceSurface::Init(
  const occ::handle<TCollection_HAsciiString>&                              aName,
  const occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>>& aBounds,
  const occ::handle<StepGeom_Surface>&                                      aFaceGeometry,
  const bool                                                                aSameSense)
{

  faceGeometry = aFaceGeometry;
  sameSense    = aSameSense;

  StepShape_Face::Init(aName, aBounds);
}

void StepShape_FaceSurface::SetFaceGeometry(const occ::handle<StepGeom_Surface>& aFaceGeometry)
{
  faceGeometry = aFaceGeometry;
}

occ::handle<StepGeom_Surface> StepShape_FaceSurface::FaceGeometry() const
{
  return faceGeometry;
}

void StepShape_FaceSurface::SetSameSense(const bool aSameSense)
{
  sameSense = aSameSense;
}

bool StepShape_FaceSurface::SameSense() const
{
  return sameSense;
}
