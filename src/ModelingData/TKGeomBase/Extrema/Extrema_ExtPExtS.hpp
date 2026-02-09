#pragma once

#include <Extrema_GenExtPS.hpp>
#include <Extrema_FuncPSNorm.hpp>
#include <Extrema_POnSurf.hpp>
#include <GeomAdaptor_SurfaceOfLinearExtrusion.hpp>
#include <gp_Ax2.hpp>
#include <gp_Vec.hpp>

class Extrema_ExtPExtS : public Standard_Transient
{

public:
  Standard_EXPORT Extrema_ExtPExtS();

  Standard_EXPORT Extrema_ExtPExtS(const gp_Pnt&                                            P,
                                   const occ::handle<GeomAdaptor_SurfaceOfLinearExtrusion>& S,
                                   const double                                             Umin,
                                   const double                                             Usup,
                                   const double                                             Vmin,
                                   const double                                             Vsup,
                                   const double                                             TolU,
                                   const double                                             TolV);

  Standard_EXPORT Extrema_ExtPExtS(const gp_Pnt&                                            P,
                                   const occ::handle<GeomAdaptor_SurfaceOfLinearExtrusion>& S,
                                   const double                                             TolU,
                                   const double                                             TolV);

  Standard_EXPORT void Initialize(const occ::handle<GeomAdaptor_SurfaceOfLinearExtrusion>& S,
                                  const double                                             Uinf,
                                  const double                                             Usup,
                                  const double                                             Vinf,
                                  const double                                             Vsup,
                                  const double                                             TolU,
                                  const double                                             TolV);

  Standard_EXPORT void Perform(const gp_Pnt& P);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

  DEFINE_STANDARD_RTTIEXT(Extrema_ExtPExtS, Standard_Transient)

private:
  Standard_EXPORT void MakePreciser(double&       U,
                                    const gp_Pnt& P,
                                    const bool    isMin,
                                    const gp_Ax2& OrtogSection) const;

  double                                            myuinf;
  double                                            myusup;
  double                                            mytolu;
  double                                            myvinf;
  double                                            myvsup;
  double                                            mytolv;
  Extrema_FuncPSNorm                                myF;
  occ::handle<Adaptor3d_Curve>                      myC;
  occ::handle<GeomAdaptor_SurfaceOfLinearExtrusion> myS;
  gp_Vec                                            myDirection;
  gp_Ax2                                            myPosition;
  Extrema_GenExtPS                                  myExtPS;
  bool                                              myIsAnalyticallyComputable;
  bool                                              myDone;
  int                                               myNbExt;
  double                                            mySqDist[4];
  Extrema_POnSurf                                   myPoint[4];
};
