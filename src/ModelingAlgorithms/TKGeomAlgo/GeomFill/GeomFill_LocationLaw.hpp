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

//! To define location law in Sweeping location is
//! defined by an Matrix M and an Vector V, and
//! transform an point P in MP+V.
class GeomFill_LocationLaw : public Standard_Transient
{

public:
  //! initialize curve of location law
  Standard_EXPORT virtual bool SetCurve(const occ::handle<Adaptor3d_Curve>& C) = 0;

  Standard_EXPORT virtual const occ::handle<Adaptor3d_Curve>& GetCurve() const = 0;

  //! Set a transformation Matrix like the law M(t) become
  //! Mat * M(t)
  Standard_EXPORT virtual void SetTrsf(const gp_Mat& Transfo) = 0;

  Standard_EXPORT virtual occ::handle<GeomFill_LocationLaw> Copy() const = 0;

  //! compute Location
  Standard_EXPORT virtual bool D0(const double Param, gp_Mat& M, gp_Vec& V) = 0;

  //! compute Location and 2d points
  Standard_EXPORT virtual bool D0(const double                  Param,
                                  gp_Mat&                       M,
                                  gp_Vec&                       V,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d) = 0;

  //! compute location 2d points and associated
  //! first derivatives.
  //! Warning: It used only for C1 or C2 approximation
  Standard_EXPORT virtual bool D1(const double                  Param,
                                  gp_Mat&                       M,
                                  gp_Vec&                       V,
                                  gp_Mat&                       DM,
                                  gp_Vec&                       DV,
                                  NCollection_Array1<gp_Pnt2d>& Poles2d,
                                  NCollection_Array1<gp_Vec2d>& DPoles2d);

  //! compute location 2d points and associated
  //! first and second derivatives.
  //! Warning: It used only for C2 approximation
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

  //! get the number of 2d curves (Restrictions + Traces)
  //! to approximate.
  Standard_EXPORT int Nb2dCurves() const;

  //! Say if the first restriction is defined in this class.
  //! If it is true the first element of poles array in
  //! D0,D1,D2... Correspond to this restriction.
  //! Returns false (default implementation)
  Standard_EXPORT virtual bool HasFirstRestriction() const;

  //! Say if the last restriction is defined in this class.
  //! If it is true the last element of poles array in
  //! D0,D1,D2... Correspond to this restriction.
  //! Returns false (default implementation)
  Standard_EXPORT virtual bool HasLastRestriction() const;

  //! Give the number of trace (Curves 2d which are not restriction)
  //! Returns 0 (default implementation)
  Standard_EXPORT virtual int TraceNumber() const;

  //! Give a status to the Law
  //! Returns PipeOk (default implementation)
  Standard_EXPORT virtual GeomFill_PipeError ErrorStatus() const;

  //! Returns the number of intervals for continuity <S>.
  //! May be one if Continuity(me) >= <S>
  Standard_EXPORT virtual int NbIntervals(const GeomAbs_Shape S) const = 0;

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  Standard_EXPORT virtual void Intervals(NCollection_Array1<double>& T,
                                         const GeomAbs_Shape         S) const = 0;

  //! Sets the bounds of the parametric interval on
  //! the function
  //! This determines the derivatives in these values if the
  //! function is not Cn.
  Standard_EXPORT virtual void SetInterval(const double First, const double Last) = 0;

  //! Gets the bounds of the parametric interval on
  //! the function
  Standard_EXPORT virtual void GetInterval(double& First, double& Last) const = 0;

  //! Gets the bounds of the function parametric domain.
  //! Warning: This domain it is not modified by the
  //! SetValue method
  Standard_EXPORT virtual void GetDomain(double& First, double& Last) const = 0;

  //! Returns the resolutions in the sub-space 2d <Index>
  //! This information is useful to find a good tolerance in
  //! 2d approximation.
  Standard_EXPORT virtual void Resolution(const int    Index,
                                          const double Tol,
                                          double&      TolU,
                                          double&      TolV) const;

  //! Is useful, if (me) have to run numerical
  //! algorithm to perform D0, D1 or D2
  //! The default implementation make nothing.
  Standard_EXPORT virtual void SetTolerance(const double Tol3d, const double Tol2d);

  //! Get the maximum Norm of the matrix-location part. It
  //! is usful to find a good Tolerance to approx M(t).
  Standard_EXPORT virtual double GetMaximalNorm() = 0;

  //! Get average value of M(t) and V(t) it is useful to
  //! make fast approximation of rational surfaces.
  Standard_EXPORT virtual void GetAverageLaw(gp_Mat& AM, gp_Vec& AV) = 0;

  //! Say if the Location Law, is an translation of Location
  //! The default implementation is " returns False ".
  Standard_EXPORT virtual bool IsTranslation(double& Error) const;

  //! Say if the Location Law, is a rotation of Location
  //! The default implementation is " returns False ".
  Standard_EXPORT virtual bool IsRotation(double& Error) const;

  Standard_EXPORT virtual void Rotation(gp_Pnt& Center) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_LocationLaw, Standard_Transient)
};

