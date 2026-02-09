#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <StepFEA_FeaRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepFEA_ParametricSurface3dElementCoordinateSystem : public StepFEA_FeaRepresentationItem
{

public:
  Standard_EXPORT StepFEA_ParametricSurface3dElementCoordinateSystem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const int                                    aAxis,
                            const double                                 aAngle);

  Standard_EXPORT int Axis() const;

  Standard_EXPORT void SetAxis(const int Axis);

  Standard_EXPORT double Angle() const;

  Standard_EXPORT void SetAngle(const double Angle);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ParametricSurface3dElementCoordinateSystem,
                          StepFEA_FeaRepresentationItem)

private:
  int    theAxis;
  double theAngle;
};
