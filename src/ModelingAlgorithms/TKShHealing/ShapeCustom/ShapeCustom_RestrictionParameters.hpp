// Created on: 2000-05-22
// Created by: data exchange team
// Copyright (c) 2000-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _ShapeCustom_RestrictionParameters_HeaderFile
#define _ShapeCustom_RestrictionParameters_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

//! This class is axuluary tool which contains parameters for
//! BSplineRestriction class.
class ShapeCustom_RestrictionParameters : public Standard_Transient
{

public:
  //! Sets default parameters.
  Standard_EXPORT ShapeCustom_RestrictionParameters();

  //! Returns (modifiable) maximal degree of approximation.
  int& GMaxDegree();

  //! Returns (modifiable) maximal number of spans of
  //! approximation.
  int& GMaxSeg();

  //! Sets flag for define if Plane converted to BSpline surface.
  bool& ConvertPlane();

  //! Sets flag for define if Bezier surface converted to BSpline
  //! surface.
  bool& ConvertBezierSurf();

  //! Sets flag for define if surface of Revolution converted to
  //! BSpline surface.
  bool& ConvertRevolutionSurf();

  //! Sets flag for define if surface of LinearExtrusion converted
  //! to BSpline surface.
  bool& ConvertExtrusionSurf();

  //! Sets flag for define if Offset surface converted to BSpline
  //! surface.
  bool& ConvertOffsetSurf();

  //! Sets flag for define if cylindrical surface converted to BSpline
  //! surface.
  bool& ConvertCylindricalSurf();

  //! Sets flag for define if conical surface converted to BSpline
  //! surface.
  bool& ConvertConicalSurf();

  //! Sets flag for define if toroidal surface converted to BSpline
  //! surface.
  bool& ConvertToroidalSurf();

  //! Sets flag for define if spherical surface converted to BSpline
  //! surface.
  bool& ConvertSphericalSurf();

  //! Sets Segment mode for surface. If Segment is True surface is
  //! approximated in the bondaries of face lying on this surface.
  bool& SegmentSurfaceMode();

  //! Sets flag for define if 3d curve converted to BSpline curve.
  bool& ConvertCurve3d();

  //! Sets flag for define if Offset curve3d converted to BSpline
  //! surface.
  bool& ConvertOffsetCurv3d();

  //! Returns (modifiable) flag for define if 2d curve converted
  //! to BSpline curve.
  bool& ConvertCurve2d();

  //! Returns (modifiable) flag for define if Offset curve2d
  //! converted to BSpline surface.
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
// Created on: 2000-05-22
// Created by: data exchange team
// Copyright (c) 2000-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//=================================================================================================

inline int& ShapeCustom_RestrictionParameters::GMaxDegree()
{
  return myGMaxDegree;
}

//=================================================================================================

inline int& ShapeCustom_RestrictionParameters::GMaxSeg()
{
  return myGMaxSeg;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertPlane()
{
  return myConvPlane;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertBezierSurf()
{
  return myConvBezierSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertRevolutionSurf()
{
  return myConvRevolSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertExtrusionSurf()
{
  return myConvExtrSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertOffsetSurf()
{
  return myConvOffsetSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::SegmentSurfaceMode()
{
  return mySegmentSurfaceMode;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertCurve3d()
{
  return myConvCurve3d;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertOffsetCurv3d()
{
  return myConvOffsetCurv3d;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertCurve2d()
{
  return myConvCurve2d;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertOffsetCurv2d()
{
  return myConvOffsetCurv2d;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertConicalSurf()
{
  return myConvConicalSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertSphericalSurf()
{
  return myConvSphericalSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertToroidalSurf()
{
  return myConvCylindricalSurf;
}

//=================================================================================================

inline bool& ShapeCustom_RestrictionParameters::ConvertCylindricalSurf()
{
  return myConvToroidalSurf;
}


#endif // _ShapeCustom_RestrictionParameters_HeaderFile
