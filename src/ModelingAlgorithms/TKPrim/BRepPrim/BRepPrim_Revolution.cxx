#include <BRepPrim_Revolution.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

//=================================================================================================

BRepPrim_Revolution::BRepPrim_Revolution(const gp_Ax2&                    A,
                                         const double                     VMin,
                                         const double                     VMax,
                                         const occ::handle<Geom_Curve>&   M,
                                         const occ::handle<Geom2d_Curve>& PM)
    : BRepPrim_OneAxis(BRepPrim_Builder(), A, VMin, VMax),
      myMeridian(M),
      myPMeridian(PM)
{
}

//=================================================================================================

BRepPrim_Revolution::BRepPrim_Revolution(const gp_Ax2& A, const double VMin, const double VMax)
    : BRepPrim_OneAxis(BRepPrim_Builder(), A, VMin, VMax)
{
}

//=================================================================================================

void BRepPrim_Revolution::Meridian(const occ::handle<Geom_Curve>&   M,
                                   const occ::handle<Geom2d_Curve>& PM)
{
  myMeridian  = M;
  myPMeridian = PM;
}

//=================================================================================================

TopoDS_Face BRepPrim_Revolution::MakeEmptyLateralFace() const
{
  occ::handle<Geom_SurfaceOfRevolution> S = new Geom_SurfaceOfRevolution(myMeridian, Axes().Axis());

  TopoDS_Face F;
  myBuilder.Builder().MakeFace(F, S, Precision::Confusion());
  return F;
}

//=================================================================================================

TopoDS_Edge BRepPrim_Revolution::MakeEmptyMeridianEdge(const double Ang) const
{
  TopoDS_Edge             E;
  occ::handle<Geom_Curve> C = occ::down_cast<Geom_Curve>(myMeridian->Copy());
  gp_Trsf                 T;
  T.SetRotation(Axes().Axis(), Ang);
  C->Transform(T);
  myBuilder.Builder().MakeEdge(E, C, Precision::Confusion());
  return E;
}

//=================================================================================================

gp_Pnt2d BRepPrim_Revolution::MeridianValue(const double V) const
{
  return myPMeridian->Value(V);
}

//=================================================================================================

void BRepPrim_Revolution::SetMeridianPCurve(TopoDS_Edge& E, const TopoDS_Face& F) const
{
  myBuilder.Builder().UpdateEdge(E, myPMeridian, F, Precision::Confusion());
}
