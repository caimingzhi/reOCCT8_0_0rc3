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

class BRepPrim_Revolution : public BRepPrim_OneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_Revolution(const gp_Ax2&                    A,
                                      const double                     VMin,
                                      const double                     VMax,
                                      const occ::handle<Geom_Curve>&   M,
                                      const occ::handle<Geom2d_Curve>& PM);

  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

  Standard_EXPORT TopoDS_Edge MakeEmptyMeridianEdge(const double Ang) const override;

  Standard_EXPORT gp_Pnt2d MeridianValue(const double V) const override;

  Standard_EXPORT void SetMeridianPCurve(TopoDS_Edge& E, const TopoDS_Face& F) const override;

protected:
  Standard_EXPORT BRepPrim_Revolution(const gp_Ax2& A, const double VMin, const double VMax);

  Standard_EXPORT void Meridian(const occ::handle<Geom_Curve>&   M,
                                const occ::handle<Geom2d_Curve>& PM);

private:
  occ::handle<Geom_Curve>   myMeridian;
  occ::handle<Geom2d_Curve> myPMeridian;
};
