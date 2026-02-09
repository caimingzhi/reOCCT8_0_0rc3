#pragma once

#include <Adaptor3d_CurveOnSurface.hpp>
#include <Adaptor3d_Surface.hpp>

class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;

class Approx_SameParameter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_SameParameter(const occ::handle<Geom_Curve>&   C3D,
                                       const occ::handle<Geom2d_Curve>& C2D,
                                       const occ::handle<Geom_Surface>& S,
                                       const double                     Tol);

  Standard_EXPORT Approx_SameParameter(const occ::handle<Adaptor3d_Curve>&   C3D,
                                       const occ::handle<Geom2d_Curve>&      C2D,
                                       const occ::handle<Adaptor3d_Surface>& S,
                                       const double                          Tol);

  Standard_EXPORT Approx_SameParameter(const occ::handle<Adaptor3d_Curve>&   C3D,
                                       const occ::handle<Adaptor2d_Curve2d>& C2D,
                                       const occ::handle<Adaptor3d_Surface>& S,
                                       const double                          Tol);

  bool IsDone() const { return myDone; }

  double TolReached() const { return myTolReached; }

  bool IsSameParameter() const { return mySameParameter; }

  occ::handle<Geom2d_Curve> Curve2d() const { return myCurve2d; }

  occ::handle<Adaptor3d_Curve> Curve3d() const { return myC3d; }

  occ::handle<Adaptor3d_CurveOnSurface> CurveOnSurface() const { return myCurveOnSurface; }

private:
  struct Approx_SameParameter_Data
  {
    Adaptor3d_CurveOnSurface myCOnS;
    int                      myNbPnt;
    double*                  myPC3d;
    double*                  myPC2d;

    double* myNewPC3d;
    double* myNewPC2d;

    double myC3dPF;
    double myC3dPL;
    double myC2dPF;
    double myC2dPL;

    double myTol;

    void Swap(const int theNewNbPoints)
    {
      myNbPnt = theNewNbPoints;
      double* temp;

      temp      = myPC3d;
      myPC3d    = myNewPC3d;
      myNewPC3d = temp;

      temp      = myPC2d;
      myPC2d    = myNewPC2d;
      myNewPC2d = temp;
    }
  };

  Approx_SameParameter(const Approx_SameParameter&)            = delete;
  Approx_SameParameter& operator=(const Approx_SameParameter&) = delete;

  Standard_EXPORT void Build(const double Tol);

  bool BuildInitialDistribution(Approx_SameParameter_Data& theData) const;

  bool IncreaseInitialNbSamples(Approx_SameParameter_Data& theData) const;

  bool ComputeTangents(const Adaptor3d_CurveOnSurface& theCOnS,
                       double&                         theFirstTangent,
                       double&                         theLastTangent) const;

  bool CheckSameParameter(Approx_SameParameter_Data& theData, double& theSqDist) const;

  bool Interpolate(const Approx_SameParameter_Data& theData,
                   const double                     aTangFirst,
                   const double                     aTangLast,
                   NCollection_Array1<double>&      thePoles,
                   NCollection_Array1<double>&      theFlatKnots) const;

  bool IncreaseNbPoles(const NCollection_Array1<double>& thePoles,
                       const NCollection_Array1<double>& theFlatKnots,
                       Approx_SameParameter_Data&        theData,
                       double&                           theBestSqTol) const;

  static const int myNbSamples    = 22;
  static const int myMaxArraySize = 1000;
  const double     myDeltaMin;

  bool                                  mySameParameter;
  bool                                  myDone;
  double                                myTolReached;
  occ::handle<Geom2d_Curve>             myCurve2d;
  occ::handle<Adaptor2d_Curve2d>        myHCurve2d;
  occ::handle<Adaptor3d_Curve>          myC3d;
  occ::handle<Adaptor3d_Surface>        mySurf;
  occ::handle<Adaptor3d_CurveOnSurface> myCurveOnSurface;
};
