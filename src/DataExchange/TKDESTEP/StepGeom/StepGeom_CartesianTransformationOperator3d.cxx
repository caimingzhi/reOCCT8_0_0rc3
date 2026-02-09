

#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_Direction.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepGeom_CartesianTransformationOperator3d,
                           StepGeom_CartesianTransformationOperator)

StepGeom_CartesianTransformationOperator3d::StepGeom_CartesianTransformationOperator3d() = default;

void StepGeom_CartesianTransformationOperator3d::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const bool                                   hasAaxis1,
  const occ::handle<StepGeom_Direction>&       aAxis1,
  const bool                                   hasAaxis2,
  const occ::handle<StepGeom_Direction>&       aAxis2,
  const occ::handle<StepGeom_CartesianPoint>&  aLocalOrigin,
  const bool                                   hasAscale,
  const double                                 aScale,
  const bool                                   hasAaxis3,
  const occ::handle<StepGeom_Direction>&       aAxis3)
{

  hasAxis3 = hasAaxis3;
  axis3    = aAxis3;

  StepGeom_CartesianTransformationOperator::Init(aName,
                                                 hasAaxis1,
                                                 aAxis1,
                                                 hasAaxis2,
                                                 aAxis2,
                                                 aLocalOrigin,
                                                 hasAscale,
                                                 aScale);
}

void StepGeom_CartesianTransformationOperator3d::SetAxis3(
  const occ::handle<StepGeom_Direction>& aAxis3)
{
  axis3    = aAxis3;
  hasAxis3 = true;
}

void StepGeom_CartesianTransformationOperator3d::UnSetAxis3()
{
  hasAxis3 = false;
  axis3.Nullify();
}

occ::handle<StepGeom_Direction> StepGeom_CartesianTransformationOperator3d::Axis3() const
{
  return axis3;
}

bool StepGeom_CartesianTransformationOperator3d::HasAxis3() const
{
  return hasAxis3;
}
