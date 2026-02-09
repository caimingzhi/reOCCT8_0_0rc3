#pragma once

#include <GeomAdaptor_SurfaceOfRevolution.hpp>
#include <gp_Ax2.hpp>
#include <Extrema_GenExtPS.hpp>
#include <Extrema_POnSurf.hpp>

class Extrema_ExtPRevS : public Standard_Transient
{

public:
  Standard_EXPORT Extrema_ExtPRevS();

  Standard_EXPORT Extrema_ExtPRevS(const gp_Pnt&                                       P,
                                   const occ::handle<GeomAdaptor_SurfaceOfRevolution>& S,
                                   const double                                        Umin,
                                   const double                                        Usup,
                                   const double                                        Vmin,
                                   const double                                        Vsup,
                                   const double                                        TolU,
                                   const double                                        TolV);

  Standard_EXPORT Extrema_ExtPRevS(const gp_Pnt&                                       P,
                                   const occ::handle<GeomAdaptor_SurfaceOfRevolution>& S,
                                   const double                                        TolU,
                                   const double                                        TolV);

  Standard_EXPORT void Initialize(const occ::handle<GeomAdaptor_SurfaceOfRevolution>& S,
                                  const double                                        Umin,
                                  const double                                        Usup,
                                  const double                                        Vmin,
                                  const double                                        Vsup,
                                  const double                                        TolU,
                                  const double                                        TolV);

  Standard_EXPORT void Perform(const gp_Pnt& P);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

  DEFINE_STANDARD_RTTIEXT(Extrema_ExtPRevS, Standard_Transient)

private:
  occ::handle<GeomAdaptor_SurfaceOfRevolution> myS;
  double                                       myvinf;
  double                                       myvsup;
  double                                       mytolv;
  gp_Ax2                                       myPosition;
  Extrema_GenExtPS                             myExtPS;
  bool                                         myIsAnalyticallyComputable;
  bool                                         myDone;
  int                                          myNbExt;
  double                                       mySqDist[8];
  Extrema_POnSurf                              myPoint[8];
};
