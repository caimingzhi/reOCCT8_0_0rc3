#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Dir.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_Surface.hpp>
class Geom_Curve;

//! Describes the common behavior for surfaces
//! constructed by sweeping a curve with another curve.
//! The Geom package provides two concrete derived
//! surfaces: surface of revolution (a revolved surface),
//! and surface of linear extrusion (an extruded surface).
class Geom_SweptSurface : public Geom_Surface
{

public:
  //! returns the continuity of the surface :
  //! C0 : only geometric continuity,
  //! C1 : continuity of the first derivative all along the surface,
  //! C2 : continuity of the second derivative all along the surface,
  //! C3 : continuity of the third derivative all along the surface,
  //! G1 : tangency continuity all along the surface,
  //! G2 : curvature continuity all along the surface,
  //! CN : the order of continuity is infinite.
  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  //! Returns the reference direction of the swept surface.
  //! For a surface of revolution it is the direction of the
  //! revolution axis, for a surface of linear extrusion it is
  //! the direction of extrusion.
  Standard_EXPORT const gp_Dir& Direction() const;

  //! Returns the referenced curve of the surface.
  //! For a surface of revolution it is the revolution curve,
  //! for a surface of linear extrusion it is the extruded curve.
  Standard_EXPORT occ::handle<Geom_Curve> BasisCurve() const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_SweptSurface, Geom_Surface)

protected:
  occ::handle<Geom_Curve> basisCurve;
  gp_Dir                  direction;
  GeomAbs_Shape           smooth;
};
