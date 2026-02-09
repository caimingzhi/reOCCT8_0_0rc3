#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

class ShapeCustom_RestrictionParameters : public Standard_Transient
{

public:
  Standard_EXPORT ShapeCustom_RestrictionParameters();

  int& GMaxDegree();

  int& GMaxSeg();

  bool& ConvertPlane();

  bool& ConvertBezierSurf();

  bool& ConvertRevolutionSurf();

  bool& ConvertExtrusionSurf();

  bool& ConvertOffsetSurf();

  bool& ConvertCylindricalSurf();

  bool& ConvertConicalSurf();

  bool& ConvertToroidalSurf();

  bool& ConvertSphericalSurf();

  bool& SegmentSurfaceMode();

  bool& ConvertCurve3d();

  bool& ConvertOffsetCurv3d();

  bool& ConvertCurve2d();

  bool& ConvertOffsetCurv2d();

  DEFINE_STANDARD_RTTIEXT(ShapeCustom_RestrictionParameters, Standard_Transient)

private:
  int  myGMaxDegree;
  int  myGMaxSeg;
  bool myConvPlane;
  bool myConvConicalSurf;
  bool myConvSphericalSurf;
  bool myConvCylindricalSurf;
  bool myConvToroidalSurf;
  bool myConvBezierSurf;
  bool myConvRevolSurf;
  bool myConvExtrSurf;
  bool myConvOffsetSurf;
  bool mySegmentSurfaceMode;
  bool myConvCurve3d;
  bool myConvOffsetCurv3d;
  bool myConvCurve2d;
  bool myConvOffsetCurv2d;
};

inline int& ShapeCustom_RestrictionParameters::GMaxDegree()
{
  return myGMaxDegree;
}

inline int& ShapeCustom_RestrictionParameters::GMaxSeg()
{
  return myGMaxSeg;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertPlane()
{
  return myConvPlane;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertBezierSurf()
{
  return myConvBezierSurf;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertRevolutionSurf()
{
  return myConvRevolSurf;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertExtrusionSurf()
{
  return myConvExtrSurf;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertOffsetSurf()
{
  return myConvOffsetSurf;
}

inline bool& ShapeCustom_RestrictionParameters::SegmentSurfaceMode()
{
  return mySegmentSurfaceMode;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertCurve3d()
{
  return myConvCurve3d;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertOffsetCurv3d()
{
  return myConvOffsetCurv3d;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertCurve2d()
{
  return myConvCurve2d;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertOffsetCurv2d()
{
  return myConvOffsetCurv2d;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertConicalSurf()
{
  return myConvConicalSurf;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertSphericalSurf()
{
  return myConvSphericalSurf;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertToroidalSurf()
{
  return myConvCylindricalSurf;
}

inline bool& ShapeCustom_RestrictionParameters::ConvertCylindricalSurf()
{
  return myConvToroidalSurf;
}
