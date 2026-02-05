#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepGeom_CartesianTransformationOperator.hpp>
class StepGeom_Direction;
class TCollection_HAsciiString;
class StepGeom_CartesianPoint;

class StepGeom_CartesianTransformationOperator3d : public StepGeom_CartesianTransformationOperator
{

public:
  //! Returns a CartesianTransformationOperator3d
  Standard_EXPORT StepGeom_CartesianTransformationOperator3d();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasAaxis1,
                            const occ::handle<StepGeom_Direction>&       aAxis1,
                            const bool                                   hasAaxis2,
                            const occ::handle<StepGeom_Direction>&       aAxis2,
                            const occ::handle<StepGeom_CartesianPoint>&  aLocalOrigin,
                            const bool                                   hasAscale,
                            const double                                 aScale,
                            const bool                                   hasAaxis3,
                            const occ::handle<StepGeom_Direction>&       aAxis3);

  Standard_EXPORT void SetAxis3(const occ::handle<StepGeom_Direction>& aAxis3);

  Standard_EXPORT void UnSetAxis3();

  Standard_EXPORT occ::handle<StepGeom_Direction> Axis3() const;

  Standard_EXPORT bool HasAxis3() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_CartesianTransformationOperator3d,
                          StepGeom_CartesianTransformationOperator)

private:
  occ::handle<StepGeom_Direction> axis3;
  bool                            hasAxis3;
};
