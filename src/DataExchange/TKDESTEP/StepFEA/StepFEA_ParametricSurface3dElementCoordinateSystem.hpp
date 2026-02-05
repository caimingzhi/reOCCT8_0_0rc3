#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <StepFEA_FeaRepresentationItem.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity ParametricSurface3dElementCoordinateSystem
class StepFEA_ParametricSurface3dElementCoordinateSystem : public StepFEA_FeaRepresentationItem
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_ParametricSurface3dElementCoordinateSystem();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const int                                    aAxis,
                            const double                                 aAngle);

  //! Returns field Axis
  Standard_EXPORT int Axis() const;

  //! Set field Axis
  Standard_EXPORT void SetAxis(const int Axis);

  //! Returns field Angle
  Standard_EXPORT double Angle() const;

  //! Set field Angle
  Standard_EXPORT void SetAngle(const double Angle);

  DEFINE_STANDARD_RTTIEXT(StepFEA_ParametricSurface3dElementCoordinateSystem,
                          StepFEA_FeaRepresentationItem)

private:
  int    theAxis;
  double theAngle;
};
