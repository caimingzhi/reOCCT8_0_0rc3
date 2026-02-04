#pragma once


#include <Standard_Handle.hpp>
class Geom2d_Curve;
class Geom_Surface;

//! Class contains conversion methods for 2d geom objects
class GeomConvert_Units
{
public:
  DEFINE_STANDARD_ALLOC

  //! Convert 2d curve for change angle unit from radian to degree
  Standard_EXPORT static occ::handle<Geom2d_Curve> RadianToDegree(
    const occ::handle<Geom2d_Curve>& theCurve,
    const occ::handle<Geom_Surface>& theSurface,
    const double                     theLengthFactor,
    const double                     theFactorRadianDegree);

  //! Convert 2d curve for change angle unit from degree to radian
  Standard_EXPORT static occ::handle<Geom2d_Curve> DegreeToRadian(
    const occ::handle<Geom2d_Curve>& theCurve,
    const occ::handle<Geom_Surface>& theSurface,
    const double                     theLengthFactor,
    const double                     theFactorRadianDegree);

  //! return 2d curve as 'mirror' for given
  Standard_EXPORT static occ::handle<Geom2d_Curve> MirrorPCurve(
    const occ::handle<Geom2d_Curve>& theCurve);
};

