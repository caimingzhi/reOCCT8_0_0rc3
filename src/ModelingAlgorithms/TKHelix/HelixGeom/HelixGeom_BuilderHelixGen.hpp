#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <HelixGeom_BuilderApproxCurve.hpp>

//! Base class for helix curve building algorithms with parameter management.
//!
//! This class extends HelixGeom_BuilderApproxCurve by adding helix-specific
//! geometric parameters:
//! - Parameter range (T1, T2) - angular range in radians
//! - Pitch - vertical distance per full turn (2*PI radians)
//! - Start radius (RStart) - radius at parameter T1
//! - Taper angle - angle for radius variation (0 = cylindrical)
//! - Orientation - clockwise or counter-clockwise
//!
//! Concrete implementations include:
//! - HelixGeom_BuilderHelix: Single helix approximation
//! - HelixGeom_BuilderHelixCoil: Multi-coil helix approximation
//!
//! @sa HelixGeom_BuilderApproxCurve, HelixGeom_HelixCurve
class HelixGeom_BuilderHelixGen : public HelixGeom_BuilderApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Sets parameters for building helix curves
  Standard_EXPORT void SetCurveParameters(const double aT1,
                                          const double aT2,
                                          const double aPitch,
                                          const double aRStart,
                                          const double aTaperAngle,
                                          const bool   bIsClockwise);

  //! Gets parameters for building helix curves
  Standard_EXPORT void CurveParameters(double& aT1,
                                       double& aT2,
                                       double& aPitch,
                                       double& aRStart,
                                       double& aTaperAngle,
                                       bool&   bIsClockwise) const;

protected:
  //! Sets default parameters
  Standard_EXPORT HelixGeom_BuilderHelixGen();
  Standard_EXPORT ~HelixGeom_BuilderHelixGen() override;

  double myT1;
  double myT2;
  double myPitch;
  double myRStart;
  double myTaperAngle;
  bool   myIsClockWise;
};

