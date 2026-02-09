#pragma once

#include <IntPatch_Intersection.hpp>
#include <GeomInt_LineConstructor.hpp>
#include <Standard_Integer.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Geom2d_Curve.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Vector.hpp>

class Geom_Surface;
class Geom_Curve;
class Geom2d_Curve;
class gp_Pnt2d;
class IntPatch_RLine;
class Bnd_Box2d;
class Adaptor3d_TopolTool;
class IntPatch_WLine;

class GeomInt_IntSS
{
public:
  DEFINE_STANDARD_ALLOC

  GeomInt_IntSS();

  GeomInt_IntSS(const occ::handle<Geom_Surface>& S1,
                const occ::handle<Geom_Surface>& S2,
                const double                     Tol,
                const bool                       Approx   = true,
                const bool                       ApproxS1 = false,
                const bool                       ApproxS2 = false);

  Standard_EXPORT void Perform(const occ::handle<Geom_Surface>& S1,
                               const occ::handle<Geom_Surface>& S2,
                               const double                     Tol,
                               const bool                       Approx   = true,
                               const bool                       ApproxS1 = false,
                               const bool                       ApproxS2 = false);

  void Perform(const occ::handle<GeomAdaptor_Surface>& HS1,
               const occ::handle<GeomAdaptor_Surface>& HS2,
               const double                            Tol,
               const bool                              Approx   = true,
               const bool                              ApproxS1 = false,
               const bool                              ApproxS2 = false);

  Standard_EXPORT void Perform(const occ::handle<Geom_Surface>& S1,
                               const occ::handle<Geom_Surface>& S2,
                               const double                     Tol,
                               const double                     U1,
                               const double                     V1,
                               const double                     U2,
                               const double                     V2,
                               const bool                       Approx   = true,
                               const bool                       ApproxS1 = false,
                               const bool                       ApproxS2 = false);

  void Perform(const occ::handle<GeomAdaptor_Surface>& HS1,
               const occ::handle<GeomAdaptor_Surface>& HS2,
               const double                            Tol,
               const double                            U1,
               const double                            V1,
               const double                            U2,
               const double                            V2,
               const bool                              Approx   = true,
               const bool                              ApproxS1 = false,
               const bool                              ApproxS2 = false);

  bool IsDone() const;

  double TolReached3d() const;

  double TolReached2d() const;

  int NbLines() const;

  Standard_EXPORT const occ::handle<Geom_Curve>& Line(const int Index) const;

  Standard_EXPORT bool HasLineOnS1(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& LineOnS1(const int Index) const;

  Standard_EXPORT bool HasLineOnS2(const int Index) const;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& LineOnS2(const int Index) const;

  int NbBoundaries() const;

  Standard_EXPORT const occ::handle<Geom_Curve>& Boundary(const int Index) const;

  int NbPoints() const;

  gp_Pnt Point(const int Index) const;

  Standard_EXPORT gp_Pnt2d Pnt2d(const int Index, const bool OnFirst) const;

  Standard_EXPORT void SetTolFixTangents(const double aTolCheck, const double aTolAngCheck);

  Standard_EXPORT void TolFixTangents(double& aTolCheck, double& aTolAngCheck);

  Standard_EXPORT static void TreatRLine(const occ::handle<IntPatch_RLine>&      theRL,
                                         const occ::handle<GeomAdaptor_Surface>& theHS1,
                                         const occ::handle<GeomAdaptor_Surface>& theHS2,
                                         occ::handle<Geom_Curve>&                theC3d,
                                         occ::handle<Geom2d_Curve>&              theC2d1,
                                         occ::handle<Geom2d_Curve>&              theC2d2,
                                         double&                                 theTolReached);

  Standard_EXPORT static void BuildPCurves(const double                     theFirst,
                                           const double                     theLast,
                                           const double                     theUmin,
                                           const double                     theUmax,
                                           const double                     theVmin,
                                           const double                     theVmax,
                                           double&                          theTol,
                                           const occ::handle<Geom_Surface>& theSurface,
                                           const occ::handle<Geom_Curve>&   theCurve,
                                           occ::handle<Geom2d_Curve>&       theCurve2d);

  Standard_EXPORT static void BuildPCurves(const double                     f,
                                           const double                     l,
                                           double&                          Tol,
                                           const occ::handle<Geom_Surface>& S,
                                           const occ::handle<Geom_Curve>&   C,
                                           occ::handle<Geom2d_Curve>&       C2d);

  Standard_EXPORT static void TrimILineOnSurfBoundaries(
    const occ::handle<Geom2d_Curve>& theC2d1,
    const occ::handle<Geom2d_Curve>& theC2d2,
    const Bnd_Box2d&                 theBound1,
    const Bnd_Box2d&                 theBound2,
    NCollection_Vector<double>&      theArrayOfParameters);

  Standard_EXPORT static occ::handle<Geom_Curve> MakeBSpline(const occ::handle<IntPatch_WLine>& WL,
                                                             const int ideb,
                                                             const int ifin);

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> MakeBSpline2d(
    const occ::handle<IntPatch_WLine>& theWLine,
    const int                          ideb,
    const int                          ifin,
    const bool                         onFirst);

protected:
  Standard_EXPORT void InternalPerform(const double Tol,
                                       const bool   Approx,
                                       const bool   ApproxS1,
                                       const bool   ApproxS2,
                                       const bool   useStart,
                                       const double U1,
                                       const double V1,
                                       const double U2,
                                       const double V2);

  Standard_EXPORT void MakeCurve(const int                               Ind,
                                 const occ::handle<Adaptor3d_TopolTool>& D1,
                                 const occ::handle<Adaptor3d_TopolTool>& D2,
                                 const double                            Tol,
                                 const bool                              Approx,
                                 const bool                              Approx1,
                                 const bool                              Approx2);

private:
  IntPatch_Intersection                           myIntersector;
  GeomInt_LineConstructor                         myLConstruct;
  occ::handle<GeomAdaptor_Surface>                myHS1;
  occ::handle<GeomAdaptor_Surface>                myHS2;
  int                                             myNbrestr;
  NCollection_Sequence<occ::handle<Geom_Curve>>   sline;
  NCollection_Sequence<occ::handle<Geom2d_Curve>> slineS1;
  NCollection_Sequence<occ::handle<Geom2d_Curve>> slineS2;
  double                                          myTolReached2d;
  double                                          myTolReached3d;
  double                                          myTolCheck;
  double                                          myTolAngCheck;
};

#include <IntPatch_Point.hpp>
#include <Geom_Surface.hpp>

inline GeomInt_IntSS::GeomInt_IntSS()
    : myNbrestr(0),
      myTolReached2d(0.0),
      myTolReached3d(0.0),
      myTolCheck(1.e-7),
      myTolAngCheck(1.e-6)
{
}

inline GeomInt_IntSS::GeomInt_IntSS(const occ::handle<Geom_Surface>& S1,
                                    const occ::handle<Geom_Surface>& S2,
                                    const double                     Tol,
                                    const bool                       Approx,
                                    const bool                       ApproxS1,
                                    const bool                       ApproxS2)
    : myNbrestr(0),
      myTolReached2d(0.0),
      myTolReached3d(0.0),
      myTolCheck(1.e-7),
      myTolAngCheck(1.e-6)
{
  Perform(S1, S2, Tol, Approx, ApproxS1, ApproxS2);
}

inline void GeomInt_IntSS::Perform(const occ::handle<GeomAdaptor_Surface>& HS1,
                                   const occ::handle<GeomAdaptor_Surface>& HS2,
                                   const double                            Tol,
                                   const bool                              Approx,
                                   const bool                              ApproxS1,
                                   const bool                              ApproxS2)
{
  myHS1 = HS1;
  myHS2 = HS2;
  InternalPerform(Tol, Approx, ApproxS1, ApproxS2, false, 0., 0., 0., 0.);
}

inline void GeomInt_IntSS::Perform(const occ::handle<GeomAdaptor_Surface>& HS1,
                                   const occ::handle<GeomAdaptor_Surface>& HS2,
                                   const double                            Tol,
                                   const double                            U1,
                                   const double                            V1,
                                   const double                            U2,
                                   const double                            V2,
                                   const bool                              Approx,
                                   const bool                              ApproxS1,
                                   const bool                              ApproxS2)
{
  myHS1 = HS1;
  myHS2 = HS2;
  InternalPerform(Tol, Approx, ApproxS1, ApproxS2, true, U1, V1, U2, V2);
}

inline bool GeomInt_IntSS::IsDone() const
{
  return myIntersector.IsDone();
}

inline double GeomInt_IntSS::TolReached2d() const
{
  return myTolReached2d;
}

inline double GeomInt_IntSS::TolReached3d() const
{
  return myTolReached3d;
}

inline int GeomInt_IntSS::NbLines() const
{
  return sline.Length() - myNbrestr;
}

inline int GeomInt_IntSS::NbBoundaries() const
{
  StdFail_NotDone_Raise_if(!myIntersector.IsDone(), "GeomInt_IntSS::NbBoundaries() - no result");
  return myNbrestr;
}

inline int GeomInt_IntSS::NbPoints() const
{
  return myIntersector.NbPnts();
}

inline gp_Pnt GeomInt_IntSS::Point(const int Index) const
{
  return myIntersector.Point(Index).Value();
}
