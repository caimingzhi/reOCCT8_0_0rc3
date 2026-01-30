// Copyright (c) 2025 OPEN CASCADE SAS
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

#include <GeomHash_CurveHasher.hpp>

#include <Standard_CStringHasher.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_Circle.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Parabola.hpp>
#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Geom_OffsetCurve.hpp>

#include <GeomHash_LineHasher.hpp>
#include <GeomHash_CircleHasher.hpp>
#include <GeomHash_EllipseHasher.hpp>
#include <GeomHash_HyperbolaHasher.hpp>
#include <GeomHash_ParabolaHasher.hpp>
#include <GeomHash_BezierCurveHasher.hpp>
#include <GeomHash_BSplineCurveHasher.hpp>
#include <GeomHash_TrimmedCurveHasher.hpp>
#include <GeomHash_OffsetCurveHasher.hpp>

//=================================================================================================

std::size_t GeomHash_CurveHasher::operator()(const occ::handle<Geom_Curve>& theCurve) const noexcept
{
  if (theCurve.IsNull())
  {
    return 0;
  }

  // Dispatch based on actual curve type
  if (occ::handle<Geom_Line> aLine = occ::down_cast<Geom_Line>(theCurve))
  {
    return GeomHash_LineHasher{}(aLine);
  }
  if (occ::handle<Geom_Circle> aCircle = occ::down_cast<Geom_Circle>(theCurve))
  {
    return GeomHash_CircleHasher{}(aCircle);
  }
  if (occ::handle<Geom_Ellipse> anEllipse = occ::down_cast<Geom_Ellipse>(theCurve))
  {
    return GeomHash_EllipseHasher{}(anEllipse);
  }
  if (occ::handle<Geom_Hyperbola> aHyperbola = occ::down_cast<Geom_Hyperbola>(theCurve))
  {
    return GeomHash_HyperbolaHasher{}(aHyperbola);
  }
  if (occ::handle<Geom_Parabola> aParabola = occ::down_cast<Geom_Parabola>(theCurve))
  {
    return GeomHash_ParabolaHasher{}(aParabola);
  }
  if (occ::handle<Geom_BezierCurve> aBezier = occ::down_cast<Geom_BezierCurve>(theCurve))
  {
    return GeomHash_BezierCurveHasher{}(aBezier);
  }
  if (occ::handle<Geom_BSplineCurve> aBSpline = occ::down_cast<Geom_BSplineCurve>(theCurve))
  {
    return GeomHash_BSplineCurveHasher{}(aBSpline);
  }
  if (occ::handle<Geom_TrimmedCurve> aTrimmed = occ::down_cast<Geom_TrimmedCurve>(theCurve))
  {
    return GeomHash_TrimmedCurveHasher{}(aTrimmed);
  }
  if (occ::handle<Geom_OffsetCurve> anOffset = occ::down_cast<Geom_OffsetCurve>(theCurve))
  {
    return GeomHash_OffsetCurveHasher{}(anOffset);
  }

  // Unknown curve type - hash the type name
  return Standard_CStringHasher{}(theCurve->DynamicType()->Name());
}

//=================================================================================================

bool GeomHash_CurveHasher::operator()(const occ::handle<Geom_Curve>& theCurve1,
                                      const occ::handle<Geom_Curve>& theCurve2) const noexcept
{
  if (theCurve1.IsNull() || theCurve2.IsNull())
  {
    return theCurve1.IsNull() && theCurve2.IsNull();
  }

  if (theCurve1 == theCurve2)
  {
    return true;
  }

  // Must be same type
  if (theCurve1->DynamicType() != theCurve2->DynamicType())
  {
    return false;
  }

  // Dispatch based on actual curve type
  if (occ::handle<Geom_Line> aLine1 = occ::down_cast<Geom_Line>(theCurve1))
  {
    return GeomHash_LineHasher{}(aLine1, occ::down_cast<Geom_Line>(theCurve2));
  }
  if (occ::handle<Geom_Circle> aCircle1 = occ::down_cast<Geom_Circle>(theCurve1))
  {
    return GeomHash_CircleHasher{}(aCircle1, occ::down_cast<Geom_Circle>(theCurve2));
  }
  if (occ::handle<Geom_Ellipse> anEllipse1 = occ::down_cast<Geom_Ellipse>(theCurve1))
  {
    return GeomHash_EllipseHasher{}(anEllipse1, occ::down_cast<Geom_Ellipse>(theCurve2));
  }
  if (occ::handle<Geom_Hyperbola> aHyp1 = occ::down_cast<Geom_Hyperbola>(theCurve1))
  {
    return GeomHash_HyperbolaHasher{}(aHyp1, occ::down_cast<Geom_Hyperbola>(theCurve2));
  }
  if (occ::handle<Geom_Parabola> aPar1 = occ::down_cast<Geom_Parabola>(theCurve1))
  {
    return GeomHash_ParabolaHasher{}(aPar1, occ::down_cast<Geom_Parabola>(theCurve2));
  }
  if (occ::handle<Geom_BezierCurve> aBez1 = occ::down_cast<Geom_BezierCurve>(theCurve1))
  {
    return GeomHash_BezierCurveHasher{}(aBez1, occ::down_cast<Geom_BezierCurve>(theCurve2));
  }
  if (occ::handle<Geom_BSplineCurve> aBSpl1 = occ::down_cast<Geom_BSplineCurve>(theCurve1))
  {
    return GeomHash_BSplineCurveHasher{}(aBSpl1, occ::down_cast<Geom_BSplineCurve>(theCurve2));
  }
  if (occ::handle<Geom_TrimmedCurve> aTrim1 = occ::down_cast<Geom_TrimmedCurve>(theCurve1))
  {
    return GeomHash_TrimmedCurveHasher{}(aTrim1, occ::down_cast<Geom_TrimmedCurve>(theCurve2));
  }
  if (occ::handle<Geom_OffsetCurve> aOff1 = occ::down_cast<Geom_OffsetCurve>(theCurve1))
  {
    return GeomHash_OffsetCurveHasher{}(aOff1, occ::down_cast<Geom_OffsetCurve>(theCurve2));
  }

  // Unknown curve type - compare by pointer
  return theCurve1.get() == theCurve2.get();
}
