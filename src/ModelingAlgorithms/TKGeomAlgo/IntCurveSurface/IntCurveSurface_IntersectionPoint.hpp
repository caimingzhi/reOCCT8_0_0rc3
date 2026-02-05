#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>

//! Definition of an interserction point between a
//! curve and a surface.
class IntCurveSurface_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty Constructor.
  Standard_EXPORT IntCurveSurface_IntersectionPoint();

  //! Create an IntersectionPoint.
  Standard_EXPORT IntCurveSurface_IntersectionPoint(const gp_Pnt&                           P,
                                                    const double                            USurf,
                                                    const double                            VSurf,
                                                    const double                            UCurv,
                                                    const IntCurveSurface_TransitionOnCurve TrCurv);

  //! Set the fields of the current IntersectionPoint.
  Standard_EXPORT void SetValues(const gp_Pnt&                           P,
                                 const double                            USurf,
                                 const double                            VSurf,
                                 const double                            UCurv,
                                 const IntCurveSurface_TransitionOnCurve TrCurv);

  //! Get the fields of the current IntersectionPoint.
  Standard_EXPORT void Values(gp_Pnt&                            P,
                              double&                            USurf,
                              double&                            VSurf,
                              double&                            UCurv,
                              IntCurveSurface_TransitionOnCurve& TrCurv) const;

  //! returns the geometric point.
  const gp_Pnt& Pnt() const;

  //! returns the U parameter on the surface.
  double U() const;

  //! returns the V parameter on the surface.
  double V() const;

  //! returns the parameter on the curve.
  double W() const;

  //! returns the Transition of the point.
  IntCurveSurface_TransitionOnCurve Transition() const;

  //! Dump all the fields.
  Standard_EXPORT void Dump() const;

private:
  gp_Pnt                            myP;
  double                            myUSurf;
  double                            myVSurf;
  double                            myUCurv;
  IntCurveSurface_TransitionOnCurve myTrOnCurv;
};

inline const gp_Pnt& IntCurveSurface_IntersectionPoint::Pnt() const
{
  return (myP);
}

inline double IntCurveSurface_IntersectionPoint::U() const
{
  return (myUSurf);
}

inline double IntCurveSurface_IntersectionPoint::V() const
{
  return (myVSurf);
}

inline double IntCurveSurface_IntersectionPoint::W() const
{
  return (myUCurv);
}

inline IntCurveSurface_TransitionOnCurve IntCurveSurface_IntersectionPoint::Transition() const
{
  return (myTrOnCurv);
}
