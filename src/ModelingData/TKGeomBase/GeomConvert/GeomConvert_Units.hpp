#pragma once

#include <Standard_Handle.hpp>
class Geom2d_Curve;
class Geom_Surface;

class GeomConvert_Units
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom2d_Curve> RadianToDegree(
    const occ::handle<Geom2d_Curve>& theCurve,
    const occ::handle<Geom_Surface>& theSurface,
    const double                     theLengthFactor,
    const double                     theFactorRadianDegree);

  Standard_EXPORT static occ::handle<Geom2d_Curve> DegreeToRadian(
    const occ::handle<Geom2d_Curve>& theCurve,
    const occ::handle<Geom_Surface>& theSurface,
    const double                     theLengthFactor,
    const double                     theFactorRadianDegree);

  Standard_EXPORT static occ::handle<Geom2d_Curve> MirrorPCurve(
    const occ::handle<Geom2d_Curve>& theCurve);
};
