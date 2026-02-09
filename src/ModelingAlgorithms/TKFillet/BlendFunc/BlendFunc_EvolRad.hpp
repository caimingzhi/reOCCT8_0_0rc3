#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <math_Matrix.hpp>
#include <BlendFunc_Tensor.hpp>
#include <BlendFunc_SectionShape.hpp>
#include <Convert_ParameterisationType.hpp>
#include <Blend_Function.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>

class Law_Function;
class gp_Circ;
class Blend_Point;

class BlendFunc_EvolRad : public Blend_Function
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_EvolRad(const occ::handle<Adaptor3d_Surface>& S1,
                                    const occ::handle<Adaptor3d_Surface>& S2,
                                    const occ::handle<Adaptor3d_Curve>&   C,
                                    const occ::handle<Law_Function>&      Law);

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const double Param) override;

  Standard_EXPORT void Set(const double First, const double Last) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override;

  Standard_EXPORT double GetMinimalDistance() const override;

  Standard_EXPORT const gp_Pnt& PointOnS1() const override;

  Standard_EXPORT const gp_Pnt& PointOnS2() const override;

  Standard_EXPORT bool IsTangencyPoint() const override;

  Standard_EXPORT const gp_Vec& TangentOnS1() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS1() const override;

  Standard_EXPORT const gp_Vec& TangentOnS2() const override;

  Standard_EXPORT const gp_Vec2d& Tangent2dOnS2() const override;

  Standard_EXPORT void Tangent(const double U1,
                               const double V1,
                               const double U2,
                               const double V2,
                               gp_Vec&      TgFirst,
                               gp_Vec&      TgLast,
                               gp_Vec&      NormFirst,
                               gp_Vec&      NormLast) const override;

  Standard_EXPORT bool TwistOnS1() const override;

  Standard_EXPORT bool TwistOnS2() const override;

  Standard_EXPORT void Set(const int Choix);

  Standard_EXPORT void Set(const BlendFunc_SectionShape TypeSection);

  Standard_EXPORT void Section(const double Param,
                               const double U1,
                               const double V1,
                               const double U2,
                               const double V2,
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
                               NCollection_Array1<gp_Vec>&   D2Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<gp_Vec2d>& D2Poles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths,
                               NCollection_Array1<double>&   D2Weigths) override;

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
  Standard_EXPORT bool ComputeValues(const math_Vector& X,
                                     const int          Order,
                                     const bool         ByParam = false,
                                     const double       Param   = 0);

  occ::handle<Adaptor3d_Surface> surf1;
  occ::handle<Adaptor3d_Surface> surf2;
  occ::handle<Adaptor3d_Curve>   curv;
  occ::handle<Adaptor3d_Curve>   tcurv;
  occ::handle<Law_Function>      fevol;
  occ::handle<Law_Function>      tevol;
  gp_Pnt                         pts1;
  gp_Pnt                         pts2;
  bool                           istangent;
  gp_Vec                         tg1;
  gp_Vec2d                       tg12d;
  gp_Vec                         tg2;
  gp_Vec2d                       tg22d;
  double                         param;
  double                         sg1;
  double                         sg2;
  double                         ray;
  double                         dray;
  double                         d2ray;
  int                            choix;
  int                            myXOrder;
  int                            myTOrder;
  math_Vector                    xval;
  double                         tval;
  gp_Vec                         d1u1;
  gp_Vec                         d1u2;
  gp_Vec                         d1v1;
  gp_Vec                         d1v2;
  gp_Vec                         d2u1;
  gp_Vec                         d2v1;
  gp_Vec                         d2uv1;
  gp_Vec                         d2u2;
  gp_Vec                         d2v2;
  gp_Vec                         d2uv2;
  gp_Vec                         dn1w;
  gp_Vec                         dn2w;
  gp_Vec                         d2n1w;
  gp_Vec                         d2n2w;
  gp_Vec                         nplan;
  gp_Vec                         nsurf1;
  gp_Vec                         nsurf2;
  gp_Vec                         dns1u1;
  gp_Vec                         dns1u2;
  gp_Vec                         dns1v1;
  gp_Vec                         dns1v2;
  gp_Vec                         dnplan;
  gp_Vec                         d2nplan;
  gp_Vec                         dnsurf1;
  gp_Vec                         dnsurf2;
  gp_Vec                         dndu1;
  gp_Vec                         dndu2;
  gp_Vec                         dndv1;
  gp_Vec                         dndv2;
  gp_Vec                         d2ndu1;
  gp_Vec                         d2ndu2;
  gp_Vec                         d2ndv1;
  gp_Vec                         d2ndv2;
  gp_Vec                         d2nduv1;
  gp_Vec                         d2nduv2;
  gp_Vec                         d2ndtu1;
  gp_Vec                         d2ndtu2;
  gp_Vec                         d2ndtv1;
  gp_Vec                         d2ndtv2;
  math_Vector                    E;
  math_Matrix                    DEDX;
  math_Vector                    DEDT;
  BlendFunc_Tensor               D2EDX2;
  math_Matrix                    D2EDXDT;
  math_Vector                    D2EDT2;
  double                         minang;
  double                         maxang;
  double                         lengthmin;
  double                         lengthmax;
  double                         distmin;
  BlendFunc_SectionShape         mySShape;
  Convert_ParameterisationType   myTConv;
};
