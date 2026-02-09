#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomFill_PipeError.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec2d.hpp>

class gp_Mat;
class gp_Vec;
class gp_Pnt;

class GeomFill_LocationLaw : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool SetCurve(const occ::handle<Adaptor3d_Curve>& C) = 0;

  Standard_EXPORT virtual const occ::handle<Adaptor3d_Curve>& GetCurve() const = 0;

  Standard_EXPORT virtual void SetTrsf(const gp_Mat& Transfo) = 0;

  Standard_EXPORT virtual occ::handle<GeomFill_LocationLaw> Copy() const = 0;

  Standard_EXPORT virtual bool D0(const double Param, gp_Mat& M, gp_Vec& V) = 0;

  Standard_EXPORT virtual bool D0(const double                  Param,
                                  gp_Mat&                       M,
                                  gp_Vec&                       V,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d) = 0;

  Standard_EXPORT virtual bool D1(const double                  Param,
                                  gp_Mat&                       M,
                                  gp_Vec&                       V,
                                  gp_Mat&                       DM,
                                  gp_Vec&                       DV,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d,
                                  NCollection_Array1<gp_Vec2d>& DPoles2d);

  Standard_EXPORT virtual bool D2(const double                  Param,
                                  gp_Mat&                       M,
                                  gp_Vec&                       V,
                                  gp_Mat&                       DM,
                                  gp_Vec&                       DV,
                                  gp_Mat&                       D2M,
                                  gp_Vec&                       D2V,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d,
                                  NCollection_Array1<gp_Vec2d>& DPoles2d,
                                  NCollection_Array1<gp_Vec2d>& D2Poles2d);

  Standard_EXPORT int Nb2dCurves() const;

  Standard_EXPORT virtual bool HasFirstRestriction() const;

  Standard_EXPORT virtual bool HasLastRestriction() const;

  Standard_EXPORT virtual int TraceNumber() const;

  Standard_EXPORT virtual GeomFill_PipeError ErrorStatus() const;

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const = 0;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const = 0;

  Standard_EXPORT virtual void SetInterval(const double First, const double Last) = 0;

  Standard_EXPORT virtual void GetInterval(double& First, double& Last) const = 0;

  Standard_EXPORT virtual void GetDomain(double& First, double& Last) const = 0;

  Standard_EXPORT virtual void Resolution(const int    Index,
                                          const double Tol,
                                          double&      TolU,
                                          double&      TolV) const;

  Standard_EXPORT virtual void SetTolerance(const double Tol3d, const double Tol2d);

  Standard_EXPORT virtual double GetMaximalNorm() = 0;

  Standard_EXPORT virtual void GetAverageLaw(gp_Mat& AM, gp_Vec& AV) = 0;

  Standard_EXPORT virtual bool IsTranslation(double& Error) const;

  Standard_EXPORT virtual bool IsRotation(double& Error) const;

  Standard_EXPORT virtual void Rotation(gp_Pnt& Center) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_LocationLaw, Standard_Transient)
};
