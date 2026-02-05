#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_SplitSurface.hpp>
class ShapeExtend_CompositeSurface;

//! Converts a plane, bspline surface, surface of revolution, surface
//! of extrusion, offset surface to grid of bezier basis surface (
//! bezier surface,
//! surface of revolution based on bezier curve,
//! offset surface based on any previous type).
class ShapeUpgrade_ConvertSurfaceToBezierBasis : public ShapeUpgrade_SplitSurface
{

public:
  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_ConvertSurfaceToBezierBasis();

  //! Splits a list of beziers computed by Compute method according
  //! the split values and splitting parameters.
  Standard_EXPORT void Build(const bool Segment) override;

  //! Converts surface into a grid of bezier based surfaces, and
  //! stores this grid.
  Standard_EXPORT void Compute(const bool Segment) override;

  //! Returns the grid of bezier based surfaces correspondent to
  //! original surface.
  Standard_EXPORT occ::handle<ShapeExtend_CompositeSurface> Segments() const;

  //! Sets mode for conversion Geom_Plane to Bezier
  void SetPlaneMode(const bool mode);

  //! Returns the Geom_Pline conversion mode.
  bool GetPlaneMode() const;

  //! Sets mode for conversion Geom_SurfaceOfRevolution to Bezier
  void SetRevolutionMode(const bool mode);

  //! Returns the Geom_SurfaceOfRevolution conversion mode.
  bool GetRevolutionMode() const;

  //! Sets mode for conversion Geom_SurfaceOfLinearExtrusion to Bezier
  void SetExtrusionMode(const bool mode);

  //! Returns the Geom_SurfaceOfLinearExtrusion conversion mode.
  bool GetExtrusionMode() const;

  //! Sets mode for conversion Geom_BSplineSurface to Bezier
  void SetBSplineMode(const bool mode);

  //! Returns the Geom_BSplineSurface conversion mode.
  bool GetBSplineMode() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ConvertSurfaceToBezierBasis, ShapeUpgrade_SplitSurface)

private:
  occ::handle<ShapeExtend_CompositeSurface> mySegments;
  bool                                      myPlaneMode;
  bool                                      myRevolutionMode;
  bool                                      myExtrusionMode;
  bool                                      myBSplineMode;
};

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetPlaneMode(const bool mode)
{
  myPlaneMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetPlaneMode() const
{
  return myPlaneMode;
}

//=================================================================================================

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetRevolutionMode(const bool mode)
{
  myRevolutionMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetRevolutionMode() const
{
  return myRevolutionMode;
}

//=================================================================================================

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetExtrusionMode(const bool mode)
{
  myExtrusionMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetExtrusionMode() const
{
  return myExtrusionMode;
}

//=================================================================================================

inline void ShapeUpgrade_ConvertSurfaceToBezierBasis::SetBSplineMode(const bool mode)
{
  myBSplineMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ConvertSurfaceToBezierBasis::GetBSplineMode() const
{
  return myBSplineMode;
}
