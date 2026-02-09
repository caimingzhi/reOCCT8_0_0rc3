#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class Geom_Curve;
class Geom_Surface;
class Geom2d_Curve;
class Geom2dAdaptor_Curve;
class gp_Lin2d;
class gp_Pnt;
class gp_Pnt2d;
class gp_Vec2d;

class GeomLib_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool Parameter(const occ::handle<Geom_Curve>& Curve,
                                        const gp_Pnt&                  Point,
                                        const double                   MaxDist,
                                        double&                        U);

  Standard_EXPORT static bool Parameters(const occ::handle<Geom_Surface>& Surface,
                                         const gp_Pnt&                    Point,
                                         const double                     MaxDist,
                                         double&                          U,
                                         double&                          V);

  Standard_EXPORT static bool Parameter(const occ::handle<Geom2d_Curve>& Curve,
                                        const gp_Pnt2d&                  Point,
                                        const double                     MaxDist,
                                        double&                          U);

  Standard_EXPORT static double ComputeDeviation(const Geom2dAdaptor_Curve& theCurve,
                                                 const double               theFPar,
                                                 const double               theLPar,
                                                 const double               theStartParameter,
                                                 const int                  theNbIters    = 100,
                                                 double* const              thePrmOnCurve = nullptr,
                                                 gp_Pnt2d* const            thePtOnCurve  = nullptr,
                                                 gp_Vec2d* const theVecCurvLine           = nullptr,
                                                 gp_Lin2d* const theLine = nullptr);

  Standard_EXPORT static double ComputeDeviation(const Geom2dAdaptor_Curve& theCurve,
                                                 const double               theFPar,
                                                 const double               theLPar,
                                                 const int                  theNbSubIntervals,
                                                 const int                  theNbIters = 10,
                                                 double* const thePrmOnCurve           = nullptr);
};
