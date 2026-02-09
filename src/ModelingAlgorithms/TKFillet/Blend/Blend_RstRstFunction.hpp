#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Blend_AppFunction.hpp>
#include <math_Vector.hpp>
#include <Blend_DecrochStatus.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
class math_Matrix;
class gp_Pnt;
class gp_Pnt2d;
class gp_Vec;
class gp_Vec2d;
class Blend_Point;

class Blend_RstRstFunction : public Blend_AppFunction
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT int NbVariables() const override = 0;

  Standard_EXPORT int NbEquations() const override = 0;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override = 0;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override = 0;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override = 0;

  Standard_EXPORT void Set(const double Param) override = 0;

  Standard_EXPORT void Set(const double First, const double Last) override = 0;

  Standard_EXPORT void GetTolerance(math_Vector& Tolerance, const double Tol) const override = 0;

  Standard_EXPORT void GetBounds(math_Vector& InfBound, math_Vector& SupBound) const override = 0;

  Standard_EXPORT bool IsSolution(const math_Vector& Sol, const double Tol) override = 0;

  Standard_EXPORT double GetMinimalDistance() const override;

  Standard_EXPORT const gp_Pnt& Pnt1() const override;

  Standard_EXPORT const gp_Pnt& Pnt2() const override;

  Standard_EXPORT virtual const gp_Pnt& PointOnRst1() const = 0;

  Standard_EXPORT virtual const gp_Pnt& PointOnRst2() const = 0;

  Standard_EXPORT virtual const gp_Pnt2d& Pnt2dOnRst1() const = 0;

  Standard_EXPORT virtual const gp_Pnt2d& Pnt2dOnRst2() const = 0;

  Standard_EXPORT virtual double ParameterOnRst1() const = 0;

  Standard_EXPORT virtual double ParameterOnRst2() const = 0;

  Standard_EXPORT virtual bool IsTangencyPoint() const = 0;

  Standard_EXPORT virtual const gp_Vec& TangentOnRst1() const = 0;

  Standard_EXPORT virtual const gp_Vec2d& Tangent2dOnRst1() const = 0;

  Standard_EXPORT virtual const gp_Vec& TangentOnRst2() const = 0;

  Standard_EXPORT virtual const gp_Vec2d& Tangent2dOnRst2() const = 0;

  Standard_EXPORT virtual Blend_DecrochStatus Decroch(const math_Vector& Sol,
                                                      gp_Vec&            NRst1,
                                                      gp_Vec&            TgRst1,
                                                      gp_Vec&            NRst2,
                                                      gp_Vec&            TgRst2) const = 0;

  Standard_EXPORT bool IsRational() const override = 0;

  Standard_EXPORT double GetSectionSize() const override = 0;

  Standard_EXPORT void GetMinimalWeight(NCollection_Array1<double>& Weigths) const override = 0;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override = 0;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override = 0;

  Standard_EXPORT void GetShape(int& NbPoles,
                                int& NbKnots,
                                int& Degree,
                                int& NbPoles2d) override = 0;

  Standard_EXPORT void GetTolerance(const double BoundTol,
                                    const double SurfTol,
                                    const double AngleTol,
                                    math_Vector& Tol3d,
                                    math_Vector& Tol1D) const override = 0;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) override = 0;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) override = 0;

  Standard_EXPORT void Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<double>&   Weigths) override = 0;

  Standard_EXPORT bool Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths) override = 0;

  Standard_EXPORT bool Section(const Blend_Point&            P,
                               NCollection_Array1<gp_Pnt>&   Poles,
                               NCollection_Array1<gp_Vec>&   DPoles,
                               NCollection_Array1<gp_Vec>&   D2Poles,
                               NCollection_Array1<gp_Pnt2d>& Poles2d,
                               NCollection_Array1<gp_Vec2d>& DPoles2d,
                               NCollection_Array1<gp_Vec2d>& D2Poles2d,
                               NCollection_Array1<double>&   Weigths,
                               NCollection_Array1<double>&   DWeigths,
                               NCollection_Array1<double>&   D2Weigths) override = 0;
};
