#include <StepFEA_FeaParametricPoint.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaParametricPoint, StepGeom_Point)

StepFEA_FeaParametricPoint::StepFEA_FeaParametricPoint() = default;

void StepFEA_FeaParametricPoint::Init(
  const occ::handle<TCollection_HAsciiString>&    aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<double>>& aCoordinates)
{
  StepGeom_Point::Init(aRepresentationItem_Name);

  theCoordinates = aCoordinates;
}

occ::handle<NCollection_HArray1<double>> StepFEA_FeaParametricPoint::Coordinates() const
{
  return theCoordinates;
}

void StepFEA_FeaParametricPoint::SetCoordinates(
  const occ::handle<NCollection_HArray1<double>>& aCoordinates)
{
  theCoordinates = aCoordinates;
}
