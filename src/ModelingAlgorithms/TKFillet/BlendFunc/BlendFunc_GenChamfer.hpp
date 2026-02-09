#pragma once

#include <Adaptor3d_Surface.hpp>
#include <Blend_Function.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>

class math_Matrix;
class gp_Lin;
class Blend_Point;

class BlendFunc_GenChamfer : public Blend_Function
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BlendFunc_GenChamfer(const occ::handle<Adaptor3d_Surface>& S1,
                                       const occ::handle<Adaptor3d_Surface>& S2,
                                       const occ::handle<Adaptor3d_Curve>&   CG);

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void Set(const double Param) override = 0;

  Standard_EXPORT void Set(const double First, const double Last) override;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override;

  Standard_EXPORT double GetMinimalDistance() const override;

  Standard_EXPORT virtual void Set(const double Dist1, const double Dist2, const int Choix) = 0;

  Standard_EXPORT bool IsRational() const override;

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

  Standard_EXPORT void Section(const double Param,
                               const double U1,
                               const double V1,
                               const double U2,
                               const double V2,
                               double&      Pdeb,
                               double&      Pfin,
                               gp_Lin&      C);

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

protected:
  occ::handle<Adaptor3d_Surface> surf1;
  occ::handle<Adaptor3d_Surface> surf2;
  occ::handle<Adaptor3d_Curve>   curv;
  int                            choix;
  double                         tol;
  double                         distmin;
};
