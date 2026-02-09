#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>

class IntCurveSurface_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_IntersectionPoint();

  Standard_EXPORT IntCurveSurface_IntersectionPoint(const gp_Pnt&                           P,
                                                    const double                            USurf,
                                                    const double                            VSurf,
                                                    const double                            UCurv,
                                                    const IntCurveSurface_TransitionOnCurve TrCurv);

  Standard_EXPORT void SetValues(const gp_Pnt&                           P,
                                 const double                            USurf,
                                 const double                            VSurf,
                                 const double                            UCurv,
                                 const IntCurveSurface_TransitionOnCurve TrCurv);

  Standard_EXPORT void Values(gp_Pnt&                            P,
                              double&                            USurf,
                              double&                            VSurf,
                              double&                            UCurv,
                              IntCurveSurface_TransitionOnCurve& TrCurv) const;

  const gp_Pnt& Pnt() const;

  double U() const;

  double V() const;

  double W() const;

  IntCurveSurface_TransitionOnCurve Transition() const;

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
