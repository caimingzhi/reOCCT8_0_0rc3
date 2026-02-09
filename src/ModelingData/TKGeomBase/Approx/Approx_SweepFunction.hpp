#pragma once

#include <Standard.hpp>

#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
class gp_Pnt;

class Approx_SweepFunction : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool D0(const double                  Param,
                                  const double                  First,
                                  const double                  Last,
                                  NCollection_Array1<gp_Pnt>&   Poles,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d,
                                  NCollection_Array1<double>&   Weigths) = 0;

  Standard_EXPORT virtual bool D1(const double                  Param,
                                  const double                  First,
                                  const double                  Last,
                                  NCollection_Array1<gp_Pnt>&   Poles,
                                  NCollection_Array1<gp_Vec>&   DPoles,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d,
                                  NCollection_Array1<gp_Vec2d>& DPoles2d,
                                  NCollection_Array1<double>&   Weigths,
                                  NCollection_Array1<double>&   DWeigths);

  Standard_EXPORT virtual bool D2(const double                  Param,
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
                                  NCollection_Array1<double>&   D2Weigths);

  Standard_EXPORT virtual int Nb2dCurves() const = 0;

  Standard_EXPORT virtual void SectionShape(int& NbPoles, int& NbKnots, int& Degree) const = 0;

  Standard_EXPORT virtual void Knots(NCollection_Array1<double>& TKnots) const = 0;

  Standard_EXPORT virtual void Mults(NCollection_Array1<int>& TMults) const = 0;

  Standard_EXPORT virtual bool IsRational() const = 0;

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const = 0;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const = 0;

  Standard_EXPORT virtual void SetInterval(const double First, const double Last) = 0;

  Standard_EXPORT virtual void Resolution(const int    Index,
                                          const double Tol,
                                          double&      TolU,
                                          double&      TolV) const;

  Standard_EXPORT virtual void GetTolerance(const double                BoundTol,
                                            const double                SurfTol,
                                            const double                AngleTol,
                                            NCollection_Array1<double>& Tol3d) const = 0;

  Standard_EXPORT virtual void SetTolerance(const double Tol3d, const double Tol2d) = 0;

  Standard_EXPORT virtual gp_Pnt BarycentreOfSurf() const;

  Standard_EXPORT virtual double MaximalSection() const;

  Standard_EXPORT virtual void GetMinimalWeight(NCollection_Array1<double>& Weigths) const;

  DEFINE_STANDARD_RTTIEXT(Approx_SweepFunction, Standard_Transient)
};
