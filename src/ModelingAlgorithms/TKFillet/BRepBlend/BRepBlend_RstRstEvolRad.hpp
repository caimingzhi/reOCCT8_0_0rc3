#pragma once

#include <Adaptor3d_CurveOnSurface.hpp>
#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <BlendFunc_SectionShape.hpp>
#include <Convert_ParameterisationType.hpp>
#include <Blend_RstRstFunction.hpp>
#include <math_Vector.hpp>
#include <Blend_DecrochStatus.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>

class Law_Function;
class math_Matrix;
class gp_Circ;
class Blend_Point;

class BRepBlend_RstRstEvolRad : public Blend_RstRstFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBlend_RstRstEvolRad(const occ::handle<Adaptor3d_Surface>& Surf1,
                                          const occ::handle<Adaptor2d_Curve2d>& Rst1,
                                          const occ::handle<Adaptor3d_Surface>& Surf2,
                                          const occ::handle<Adaptor2d_Curve2d>& Rst2,
                                          const occ::handle<Adaptor3d_Curve>&   CGuide,
                                          const occ::handle<Law_Function>&      Evol);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const occ::handle<Adaptor3d_Surface>& SurfRef1,
                           const occ::handle<Adaptor2d_Curve2d>& RstRef1,
                           const occ::handle<Adaptor3d_Surface>& SurfRef2,
                           const occ::handle<Adaptor2d_Curve2d>& RstRef2);

  Standard_EXPORT void Set(const double Param) override;

  Standard_EXPORT void Set(const double First, const double Last) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT double GetMinimalDistance() const override;

  Standard_EXPORT const gp_Pnt& PointOnRst1() const override;

  Standard_EXPORT const gp_Pnt& PointOnRst2() const override;

  Standard_EXPORT const gp_Pnt2d& Pnt2dOnRst1() const override;

  Standard_EXPORT const gp_Pnt2d& Pnt2dOnRst2() const override;

  Standard_EXPORT double ParameterOnRst1() const override;

  Standard_EXPORT double ParameterOnRst2() const override;

  Standard_EXPORT bool IsTangencyPoint() const override;

  Standard_EXPORT const gp_Vec& TangentOnRst1() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnRst1() const override;

  Standard_EXPORT const gp_Vec& TangentOnRst2() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnRst2() const override;

  Standard_EXPORT Blend_DecrochStatus Decroch(const math_Vector& Sol,
                                              gp_Vec&            NRst1,
                                              gp_Vec&            TgRst1,
                                              gp_Vec&            NRst2,
                                              gp_Vec&            TgRst2) const override;

  Standard_EXPORT void Set(const int Choix);

  Standard_EXPORT void Set(const BlendFunc_SectionShape TypeSection);

  Standard_EXPORT bool CenterCircleRst1Rst2(const gp_Pnt& PtRst1,
                                            const gp_Pnt& PtRst2,
                                            const gp_Vec& np,
                                            gp_Pnt&       Center,
                                            gp_Vec&       VdMed) const;

  Standard_EXPORT void Section(const double Param,
                               const double U,
                               const double V,
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

  Standard_EXPORT void Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths) override;

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

  Standard_EXPORT void Resolution(const int    IC2d,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

private:
  occ::handle<Adaptor3d_Surface> surf1;
  occ::handle<Adaptor3d_Surface> surf2;
  occ::handle<Adaptor2d_Curve2d> rst1;
  occ::handle<Adaptor2d_Curve2d> rst2;
  Adaptor3d_CurveOnSurface       cons1;
  Adaptor3d_CurveOnSurface       cons2;
  occ::handle<Adaptor3d_Curve>   guide;
  occ::handle<Adaptor3d_Curve>   tguide;
  gp_Pnt                         ptrst1;
  gp_Pnt                         ptrst2;
  gp_Pnt2d                       pt2drst1;
  gp_Pnt2d                       pt2drst2;
  double                         prmrst1;
  double                         prmrst2;
  bool                           istangent;
  gp_Vec                         tgrst1;
  gp_Vec2d                       tg2drst1;
  gp_Vec                         tgrst2;
  gp_Vec2d                       tg2drst2;
  double                         ray;
  double                         dray;
  int                            choix;
  gp_Pnt                         ptgui;
  gp_Vec                         d1gui;
  gp_Vec                         d2gui;
  gp_Vec                         nplan;
  double                         normtg;
  double                         theD;
  occ::handle<Adaptor3d_Surface> surfref1;
  occ::handle<Adaptor2d_Curve2d> rstref1;
  occ::handle<Adaptor3d_Surface> surfref2;
  occ::handle<Adaptor2d_Curve2d> rstref2;
  double                         maxang;
  double                         minang;
  double                         distmin;
  BlendFunc_SectionShape         mySShape;
  Convert_ParameterisationType   myTConv;
  occ::handle<Law_Function>      tevol;
  occ::handle<Law_Function>      fevol;
};
