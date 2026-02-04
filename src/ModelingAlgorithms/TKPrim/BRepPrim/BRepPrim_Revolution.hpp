#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_OneAxis.hpp>
#include <Standard_Real.hpp>
class Geom_Curve;
class Geom2d_Curve;
class gp_Ax2;
class TopoDS_Face;
class TopoDS_Edge;
class gp_Pnt2d;

//! Implement the OneAxis algorithm for a revolution
//! surface.
class BRepPrim_Revolution : public BRepPrim_OneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create a revolution body <M> is the meridian nd
  //! must be in the XZ plane of <A>. <PM> is the
  //! meridian in the XZ plane.
  Standard_EXPORT BRepPrim_Revolution(const gp_Ax2&                    A,
                                      const double                     VMin,
                                      const double                     VMax,
                                      const occ::handle<Geom_Curve>&   M,
                                      const occ::handle<Geom2d_Curve>& PM);

  //! The surface normal should be directed towards the
  //! outside.
  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

  //! Returns an edge with a 3D curve made from the
  //! meridian in the XZ plane rotated by <Ang> around
  //! the Z-axis. Ang may be 0 or myAngle.
  Standard_EXPORT TopoDS_Edge MakeEmptyMeridianEdge(const double Ang) const override;

  //! Returns the meridian point at parameter <V> in the
  //! plane XZ.
  Standard_EXPORT gp_Pnt2d MeridianValue(const double V) const override;

  //! Sets the parametric urve of the edge <E> in the
  //! face <F> to be the 2d representation of the
  //! meridian.
  Standard_EXPORT void SetMeridianPCurve(TopoDS_Edge& E, const TopoDS_Face& F) const override;

protected:
  //! Create a revolution body. The meridian is set
  //! later. Reserved for derivated classes.
  Standard_EXPORT BRepPrim_Revolution(const gp_Ax2& A, const double VMin, const double VMax);

  Standard_EXPORT void Meridian(const occ::handle<Geom_Curve>&   M,
                                const occ::handle<Geom2d_Curve>& PM);

private:
  occ::handle<Geom_Curve>   myMeridian;
  occ::handle<Geom2d_Curve> myPMeridian;
};

