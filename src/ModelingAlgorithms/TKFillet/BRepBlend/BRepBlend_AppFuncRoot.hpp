#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <math_Vector.hpp>
#include <Blend_Point.hpp>
#include <gp_Pnt.hpp>
#include <Approx_SweepFunction.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class BRepBlend_Line;
class Blend_AppFunction;

class BRepBlend_AppFuncRoot : public Approx_SweepFunction
{

public:
  Standard_EXPORT bool D0(const double                  Param,
                          const double                  First,
                          const double                  Last,
                          NCollection_Array1<gp_Pnt>&   Poles,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<double>&   Weigths) override;

  Standard_EXPORT bool D1(const double                  Param,
                          const double                  First,
                          const double                  Last,
                          NCollection_Array1<gp_Pnt>&   Poles,
                          NCollection_Array1<gp_Vec>&   DPoles,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<gp_Vec2d>& DPoles2d,
                          NCollection_Array1<double>&   Weigths,
                          NCollection_Array1<double>&   DWeigths) override;

  Standard_EXPORT bool D2(const double                  Param,
                          const double                  First,
                          const double                  Last,
                          NCollection_Array1<gp_Pnt>&   Poles,
                          NCollection_Array1<gp_Vec>&   DPoles,
                          NCollection_Array1<gp_Vec>&   D2Poles,
                          NCollection_Array1<gp_Pnt2d>& Poles2d,
                          NCollection_Array1<gp_Vec2d>& DPoles2d,
                          NCollection_Array1<gp_Vec2d>& D2Poles2d,
                          NCollection_Array1<double>&   Weigths,
                          NCollection_Array1<double>&   DWeigths,
                          NCollection_Array1<double>&   D2Weigths) override;

  Standard_EXPORT int Nb2dCurves() const override;

  Standard_EXPORT void SectionShape(int& NbPoles, int& NbKnots, int& Degree) const override;

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const override;

  Standard_EXPORT void Mults(NCollection_Array1<int>& TMults) const override;

  Standard_EXPORT bool IsRational() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

  Standard_EXPORT void Resolution(const int    Index,
                                  const double Tol,
                                  double&      TolU,
                                  double&      TolV) const override;

  Standard_EXPORT void GetTolerance(const double                BoundTol,
                                    const double                SurfTol,
                                    const double                AngleTol,
                                    NCollection_Array1<double>& Tol3d) const override;

  Standard_EXPORT void SetTolerance(const double Tol3d, const double Tol2d) override;

  Standard_EXPORT gp_Pnt BarycentreOfSurf() const override;

  Standard_EXPORT double MaximalSection() const override;

  Standard_EXPORT void GetMinimalWeight(NCollection_Array1<double>& Weigths) const override;

  Standard_EXPORT virtual void Point(const Blend_AppFunction& Func,
                                     const double             Param,
                                     const math_Vector&       Sol,
                                     Blend_Point&             Pnt) const = 0;

  Standard_EXPORT virtual void Vec(math_Vector& Sol, const Blend_Point& Pnt) const = 0;

  DEFINE_STANDARD_RTTIEXT(BRepBlend_AppFuncRoot, Approx_SweepFunction)

protected:
  Standard_EXPORT BRepBlend_AppFuncRoot(occ::handle<BRepBlend_Line>& Line,
                                        Blend_AppFunction&           Func,
                                        const double                 Tol3d,
                                        const double                 Tol2d);

private:
  Standard_EXPORT bool SearchPoint(Blend_AppFunction& Func, const double Param, Blend_Point& Pnt);

  Standard_EXPORT bool SearchLocation(const double Param,
                                      const int    FirstIndex,
                                      const int    LastIndex,
                                      int&         ParamIndex) const;

  occ::handle<BRepBlend_Line> myLine;
  void*                       myFunc;
  math_Vector                 myTolerance;
  Blend_Point                 myPnt;
  gp_Pnt                      myBary;
  math_Vector                 X1;
  math_Vector                 X2;
  math_Vector                 XInit;
  math_Vector                 Sol;
};
