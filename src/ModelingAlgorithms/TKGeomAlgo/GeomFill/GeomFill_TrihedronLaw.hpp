#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomFill_PipeError.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>

class gp_Vec;

class GeomFill_TrihedronLaw : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool SetCurve(const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT virtual occ::handle<GeomFill_TrihedronLaw> Copy() const = 0;

  Standard_EXPORT virtual GeomFill_PipeError ErrorStatus() const;

  Standard_EXPORT virtual bool D0(const double Param,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      Normal,
                                  gp_Vec&      BiNormal) = 0;

  Standard_EXPORT virtual bool D1(const double Param,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      DTangent,
                                  gp_Vec&      Normal,
                                  gp_Vec&      DNormal,
                                  gp_Vec&      BiNormal,
                                  gp_Vec&      DBiNormal);

  Standard_EXPORT virtual bool D2(const double Param,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      DTangent,
                                  gp_Vec&      D2Tangent,
                                  gp_Vec&      Normal,
                                  gp_Vec&      DNormal,
                                  gp_Vec&      D2Normal,
                                  gp_Vec&      BiNormal,
                                  gp_Vec&      DBiNormal,
                                  gp_Vec&      D2BiNormal);

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const = 0;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const = 0;

  Standard_EXPORT virtual void SetInterval(const double First, const double Last);

  Standard_EXPORT void GetInterval(double& First, double& Last);

  Standard_EXPORT virtual void GetAverageLaw(gp_Vec& ATangent,
                                             gp_Vec& ANormal,
                                             gp_Vec& ABiNormal) = 0;

  Standard_EXPORT virtual bool IsConstant() const;

  Standard_EXPORT virtual bool IsOnlyBy3dCurve() const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_TrihedronLaw, Standard_Transient)

protected:
  occ::handle<Adaptor3d_Curve> myCurve;
  occ::handle<Adaptor3d_Curve> myTrimmed;
};
