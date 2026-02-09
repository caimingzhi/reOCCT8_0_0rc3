#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ProjLib_Projector.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Geom2d_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAbs_CurveType.hpp>

class gp_Pnt2d;
class gp_Vec2d;

class ProjLib_CompProjectedCurve : public Adaptor2d_Curve2d
{
  DEFINE_STANDARD_RTTIEXT(ProjLib_CompProjectedCurve, Adaptor2d_Curve2d)
public:
  Standard_EXPORT ProjLib_CompProjectedCurve();

  Standard_EXPORT ProjLib_CompProjectedCurve(const occ::handle<Adaptor3d_Surface>& S,
                                             const occ::handle<Adaptor3d_Curve>&   C,
                                             const double                          TolU,
                                             const double                          TolV);

  Standard_EXPORT ProjLib_CompProjectedCurve(const occ::handle<Adaptor3d_Surface>& S,
                                             const occ::handle<Adaptor3d_Curve>&   C,
                                             const double                          TolU,
                                             const double                          TolV,
                                             const double                          MaxDist);

  Standard_EXPORT ProjLib_CompProjectedCurve(const double                          Tol3d,
                                             const occ::handle<Adaptor3d_Surface>& S,
                                             const occ::handle<Adaptor3d_Curve>&   C,
                                             const double                          MaxDist = -1.0);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ShallowCopy() const override;

  Standard_EXPORT void Init();

  Standard_EXPORT void Perform();

  Standard_EXPORT void SetTol3d(const double theTol3d);

  Standard_EXPORT void SetContinuity(const GeomAbs_Shape theContinuity);

  Standard_EXPORT void SetMaxDegree(const int theMaxDegree);

  Standard_EXPORT void SetMaxSeg(const int theMaxSeg);

  Standard_EXPORT void SetProj2d(const bool theProj2d);

  Standard_EXPORT void SetProj3d(const bool theProj3d);

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT void Load(const occ::handle<Adaptor3d_Curve>& C);

  Standard_EXPORT const occ::handle<Adaptor3d_Surface>& GetSurface() const;

  Standard_EXPORT const occ::handle<Adaptor3d_Curve>& GetCurve() const;

  Standard_EXPORT void GetTolerance(double& TolU, double& TolV) const;

  Standard_EXPORT int NbCurves() const;

  Standard_EXPORT void Bounds(const int Index, double& Udeb, double& Ufin) const;

  Standard_EXPORT bool IsSinglePnt(const int Index, gp_Pnt2d& P) const;

  Standard_EXPORT bool IsUIso(const int Index, double& U) const;

  Standard_EXPORT bool IsVIso(const int Index, double& V) const;

  Standard_EXPORT gp_Pnt2d Value(const double U) const override;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> Trim(const double FirstParam,
                                                      const double LastParam,
                                                      const double Tol) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT double MaxDistance(const int Index) const;

  Standard_EXPORT const occ::handle<
    NCollection_HSequence<occ::handle<NCollection_HSequence<gp_Pnt>>>>&
    GetSequence() const;

  Standard_EXPORT GeomAbs_CurveType GetType() const override;

  Standard_EXPORT bool ResultIsPoint(const int theIndex) const;

  Standard_EXPORT double GetResult2dUApproxError(const int theIndex) const;

  Standard_EXPORT double GetResult2dVApproxError(const int theIndex) const;

  Standard_EXPORT double GetResult3dApproxError(const int theIndex) const;

  Standard_EXPORT occ::handle<Geom2d_Curve> GetResult2dC(const int theIndex) const;

  Standard_EXPORT occ::handle<Geom_Curve> GetResult3dC(const int theIndex) const;

  Standard_EXPORT gp_Pnt2d GetResult2dP(const int theIndex) const;

  Standard_EXPORT gp_Pnt GetResult3dP(const int theIndex) const;

  bool GetProj2d() const { return myProj2d; }

  bool GetProj3d() const { return myProj3d; }

private:
  Standard_EXPORT void UpdateTripleByTrapCriteria(gp_Pnt& thePoint) const;

  Standard_EXPORT void BuildIntervals(const GeomAbs_Shape S) const;

private:
  occ::handle<Adaptor3d_Surface>                                                 mySurface;
  occ::handle<Adaptor3d_Curve>                                                   myCurve;
  int                                                                            myNbCurves;
  occ::handle<NCollection_HSequence<occ::handle<NCollection_HSequence<gp_Pnt>>>> mySequence;
  occ::handle<NCollection_HArray1<bool>>                                         myUIso;
  occ::handle<NCollection_HArray1<bool>>                                         myVIso;
  occ::handle<NCollection_HArray1<bool>>                                         mySnglPnts;
  occ::handle<NCollection_HArray1<double>>                                       myMaxDistance;
  occ::handle<NCollection_HArray1<double>>                                       myTabInt;
  double                                                                         myTol3d;
  GeomAbs_Shape                                                                  myContinuity;
  int                                                                            myMaxDegree;
  int                                                                            myMaxSeg;
  bool                                                                           myProj2d;
  bool                                                                           myProj3d;
  double                                                                         myMaxDist;
  double                                                                         myTolU;
  double                                                                         myTolV;

  occ::handle<NCollection_HArray1<bool>>                      myResultIsPoint;
  occ::handle<NCollection_HArray1<double>>                    myResult2dUApproxError;
  occ::handle<NCollection_HArray1<double>>                    myResult2dVApproxError;
  occ::handle<NCollection_HArray1<double>>                    myResult3dApproxError;
  occ::handle<NCollection_HArray1<gp_Pnt>>                    myResult3dPoint;
  occ::handle<NCollection_HArray1<gp_Pnt2d>>                  myResult2dPoint;
  occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>>   myResult3dCurve;
  occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> myResult2dCurve;
};
