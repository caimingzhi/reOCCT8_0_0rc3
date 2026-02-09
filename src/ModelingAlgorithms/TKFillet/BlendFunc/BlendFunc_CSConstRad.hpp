#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <BlendFunc_SectionShape.hpp>
#include <Convert_ParameterisationType.hpp>
#include <Blend_CSFunction.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>

class math_Matrix;
class gp_Circ;
class Blend_Point;

class BlendFunc_CSConstRad : public Blend_CSFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_CSConstRad(const occ::handle<Adaptor3d_Surface>& S,
                                       const occ::handle<Adaptor3d_Curve>&   C,
                                       const occ::handle<Adaptor3d_Curve>&   CGuide);

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const double Param) override;

  Standard_EXPORT void Set(const double First, const double Last) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT const gp_Pnt& PointOnS() const override;

  Standard_EXPORT const gp_Pnt& PointOnC() const override;

  Standard_EXPORT const gp_Pnt2d& Pnt2d() const override;

  Standard_EXPORT double ParameterOnC() const override;

  Standard_EXPORT bool IsTangencyPoint() const override;

  Standard_EXPORT const gp_Vec& TangentOnS() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2d() const override;

  Standard_EXPORT const gp_Vec& TangentOnC() const override;

  Standard_EXPORT void Tangent(const double U,
                               const double V,
                               gp_Vec&      TgS,
                               gp_Vec&      NormS) const override;

  Standard_EXPORT void Set(const double Radius, const int Choix);

  Standard_EXPORT void Set(const BlendFunc_SectionShape TypeSection);

  Standard_EXPORT void Section(const double Param,
                               const double U,
                               const double V,
                               const double W,
                               double&      Pdeb,
                               double&      Pfin,
                               gp_Circ&     C);

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

  Standard_EXPORT bool GetSection(const double                Param,
                                  const double                U,
                                  const double                V,
                                  const double                W,
                                  NCollection_Array1<gp_Pnt>& tabP,
                                  NCollection_Array1<gp_Vec>& tabV);

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

  Standard_EXPORT void Resolution(const int    IC2d,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

private:
  occ::handle<Adaptor3d_Surface> surf;
  occ::handle<Adaptor3d_Curve>   curv;
  occ::handle<Adaptor3d_Curve>   guide;
  gp_Pnt                         pts;
  gp_Pnt                         ptc;
  gp_Pnt2d                       pt2d;
  double                         prmc;
  bool                           istangent;
  gp_Vec                         tgs;
  gp_Vec2d                       tg2d;
  gp_Vec                         tgc;
  double                         ray;
  int                            choix;
  gp_Pnt                         ptgui;
  gp_Vec                         d1gui;
  gp_Vec                         d2gui;
  gp_Vec                         nplan;
  double                         normtg;
  double                         theD;
  double                         maxang;
  double                         minang;
  BlendFunc_SectionShape         mySShape;
  Convert_ParameterisationType   myTConv;
};
