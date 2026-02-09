#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class Geom_BSplineSurface;
class gp_Pnt;
class Geom_Curve;

class GeomFill_SectionLaw : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool D0(const double                Param,
                                  NCollection_Array1<gp_Pnt>& Poles,
                                  NCollection_Array1<double>& Weigths) = 0;

  Standard_EXPORT virtual bool D1(const double                Param,
                                  NCollection_Array1<gp_Pnt>& Poles,
                                  NCollection_Array1<gp_Vec>& DPoles,
                                  NCollection_Array1<double>& Weigths,
                                  NCollection_Array1<double>& DWeigths);

  Standard_EXPORT virtual bool D2(const double                Param,
                                  NCollection_Array1<gp_Pnt>& Poles,
                                  NCollection_Array1<gp_Vec>& DPoles,
                                  NCollection_Array1<gp_Vec>& D2Poles,
                                  NCollection_Array1<double>& Weigths,
                                  NCollection_Array1<double>& DWeigths,
                                  NCollection_Array1<double>& D2Weigths);

  Standard_EXPORT virtual occ::handle<Geom_BSplineSurface> BSplineSurface() const;

  Standard_EXPORT virtual void SectionShape(int& NbPoles, int& NbKnots, int& Degree) const = 0;

  Standard_EXPORT virtual void Knots(NCollection_Array1<double>& TKnots) const = 0;

  Standard_EXPORT virtual void Mults(NCollection_Array1<int>& TMults) const = 0;

  Standard_EXPORT virtual bool IsRational() const = 0;

  Standard_EXPORT virtual bool IsUPeriodic() const = 0;

  Standard_EXPORT virtual bool IsVPeriodic() const = 0;

  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const = 0;

  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const = 0;

  Standard_EXPORT virtual void SetInterval(const double First, const double Last) = 0;

  Standard_EXPORT virtual void GetInterval(double& First, double& Last) const = 0;

  Standard_EXPORT virtual void GetDomain(double& First, double& Last) const = 0;

  Standard_EXPORT virtual void GetTolerance(const double                BoundTol,
                                            const double                SurfTol,
                                            const double                AngleTol,
                                            NCollection_Array1<double>& Tol3d) const = 0;

  Standard_EXPORT virtual void SetTolerance(const double Tol3d, const double Tol2d);

  Standard_EXPORT virtual gp_Pnt BarycentreOfSurf() const;

  Standard_EXPORT virtual double MaximalSection() const = 0;

  Standard_EXPORT virtual void GetMinimalWeight(NCollection_Array1<double>& Weigths) const;

  Standard_EXPORT virtual bool IsConstant(double& Error) const;

  Standard_EXPORT virtual occ::handle<Geom_Curve> ConstantSection() const;

  Standard_EXPORT virtual bool IsConicalLaw(double& Error) const;

  Standard_EXPORT virtual occ::handle<Geom_Curve> CirclSection(const double Param) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_SectionLaw, Standard_Transient)
};
