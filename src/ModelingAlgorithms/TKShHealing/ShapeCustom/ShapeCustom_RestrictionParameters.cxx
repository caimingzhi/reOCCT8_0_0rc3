#include <ShapeCustom_RestrictionParameters.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeCustom_RestrictionParameters, Standard_Transient)

ShapeCustom_RestrictionParameters::ShapeCustom_RestrictionParameters()
{
  myGMaxSeg    = 10000;
  myGMaxDegree = 15;

  myConvPlane = false;

  myConvConicalSurf     = false;
  myConvSphericalSurf   = false;
  myConvCylindricalSurf = false;
  myConvToroidalSurf    = false;

  myConvBezierSurf     = false;
  myConvRevolSurf      = true;
  myConvExtrSurf       = true;
  myConvOffsetSurf     = true;
  mySegmentSurfaceMode = true;
  myConvCurve3d        = true;
  myConvOffsetCurv3d   = true;
  myConvCurve2d        = true;
  myConvOffsetCurv2d   = true;
}
