#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_CurveOnSurface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <BlendFunc_SectionShape.hpp>
#include <Convert_ParameterisationType.hpp>
#include <Blend_SurfRstFunction.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>

class math_Matrix;
class gp_Circ;
class Blend_Point;

class BRepBlend_SurfRstConstRad : public Blend_SurfRstFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_SurfRstConstRad(const occ::handle<Adaptor3d_Surface>& Surf,
                                            const occ::handle<Adaptor3d_Surface>& SurfRst,
                                            const occ::handle<Adaptor2d_Curve2d>& Rst,
                                            const occ::handle<Adaptor3d_Curve>&   CGuide);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const occ::handle<Adaptor3d_Surface>& SurfRef,
                           const occ::handle<Adaptor2d_Curve2d>& RstRef);

  Standard_EXPORT void Set(const double Param) override;

  Standard_EXPORT void Set(const double First, const double Last) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT double GetMinimalDistance() const override;

  Standard_EXPORT const gp_Pnt& PointOnS() const override;

  Standard_EXPORT const gp_Pnt& PointOnRst() const override;

  Standard_EXPORT const gp_Pnt2d& Pnt2dOnS() const override;

  Standard_EXPORT const gp_Pnt2d& Pnt2dOnRst() const override;

  Standard_EXPORT double ParameterOnRst() const override;

  Standard_EXPORT bool IsTangencyPoint() const override;

  Standard_EXPORT const gp_Vec& TangentOnS() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS() const override;

  Standard_EXPORT const gp_Vec& TangentOnRst() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnRst() const override;

  Standard_EXPORT bool Decroch(const math_Vector& Sol, gp_Vec& NS, gp_Vec& TgS) const override;

  Standard_EXPORT void Set(const double Radius, const int Choix);

  Standard_EXPORT void Set(const BlendFunc_SectionShape TypeSection);

  Standard_EXPORT void Section(const double Param,
                               const double U,
                               const double V,
                               const double W,
                               double&      Pdeb,
                               double&      Pfin,
                               gp_Circ&     C);

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT double GetSectionSize() const override;

  Standard_EXPORT void GetMinimalWeight(NCollection_Array1<double>& Weigths) const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void GetShape(int& NbPoles, int& NbKnots, int& Degree, int& NbPoles2d) override;

  Standard_EXPORT void GetTolerance(const double BoundTol,
                                    const double SurfTol,
                                    const double AngleTol,
                                    math_Vector& Tol3d,
                                    math_Vector& Tol1D) const override;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) override;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) override;

  Standard_EXPORT bool Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths) override;

  Standard_EXPORT bool Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Vec>&   D2Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<gp_Vec2d>& D2Poles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths,
                               NCollection_Array1<double>&   D2Weigths) override;

  Standard_EXPORT void Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths) override;

  Standard_EXPORT void Resolution(const int    IC2d,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

private:
  occ::handle<Adaptor3d_Surface> surf;
  occ::handle<Adaptor3d_Surface> surfrst;
  occ::handle<Adaptor2d_Curve2d> rst;
  Adaptor3d_CurveOnSurface       cons;
  occ::handle<Adaptor3d_Curve>   guide;
  occ::handle<Adaptor3d_Curve>   tguide;
  gp_Pnt                         pts;
  gp_Pnt                         ptrst;
  gp_Pnt2d                       pt2ds;
  gp_Pnt2d                       pt2drst;
  double                         prmrst;
  bool                           istangent;
  gp_Vec                         tgs;
  gp_Vec2d                       tg2ds;
  gp_Vec                         tgrst;
  gp_Vec2d                       tg2drst;
  double                         ray;
  int                            choix;
  gp_Pnt                         ptgui;
  gp_Vec                         d1gui;
  gp_Vec                         d2gui;
  gp_Vec                         nplan;
  double                         normtg;
  double                         theD;
  occ::handle<Adaptor3d_Surface> surfref;
  occ::handle<Adaptor2d_Curve2d> rstref;
  double                         maxang;
  double                         minang;
  double                         distmin;
  BlendFunc_SectionShape         mySShape;
  Convert_ParameterisationType   myTConv;
};
