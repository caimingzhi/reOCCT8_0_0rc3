#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GeomPlate_CurveConstraint.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomPlate_PointConstraint.hpp>
#include <Plate_Plate.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Extrema_ExtPS.hpp>
#include <Adaptor3d_Curve.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <Geom2d_Curve.hpp>
class Geom_Surface;
class GeomPlate_Surface;
class GeomPlate_CurveConstraint;
class GeomPlate_PointConstraint;
class gp_Pnt2d;
class gp_Pnt;
class Geom2d_Curve;

class GeomPlate_BuildPlateSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomPlate_BuildPlateSurface(
    const occ::handle<NCollection_HArray1<int>>&                          NPoints,
    const occ::handle<NCollection_HArray1<occ::handle<Adaptor3d_Curve>>>& TabCurve,
    const occ::handle<NCollection_HArray1<int>>&                          Tang,
    const int                                                             Degree,
    const int                                                             NbIter      = 3,
    const double                                                          Tol2d       = 0.00001,
    const double                                                          Tol3d       = 0.0001,
    const double                                                          TolAng      = 0.01,
    const double                                                          TolCurv     = 0.1,
    const bool                                                            Anisotropie = false);

  Standard_EXPORT GeomPlate_BuildPlateSurface(const occ::handle<Geom_Surface>& Surf,
                                              const int                        Degree     = 3,
                                              const int                        NbPtsOnCur = 10,
                                              const int                        NbIter     = 3,
                                              const double                     Tol2d      = 0.00001,
                                              const double                     Tol3d      = 0.0001,
                                              const double                     TolAng     = 0.01,
                                              const double                     TolCurv    = 0.1,
                                              const bool                       Anisotropie = false);

  Standard_EXPORT GeomPlate_BuildPlateSurface(const int    Degree      = 3,
                                              const int    NbPtsOnCur  = 10,
                                              const int    NbIter      = 3,
                                              const double Tol2d       = 0.00001,
                                              const double Tol3d       = 0.0001,
                                              const double TolAng      = 0.01,
                                              const double TolCurv     = 0.1,
                                              const bool   Anisotropie = false);

  Standard_EXPORT void Init();

  Standard_EXPORT void LoadInitSurface(const occ::handle<Geom_Surface>& Surf);

  Standard_EXPORT void Add(const occ::handle<GeomPlate_CurveConstraint>& Cont);

  Standard_EXPORT void SetNbBounds(const int NbBounds);

  Standard_EXPORT void Add(const occ::handle<GeomPlate_PointConstraint>& Cont);

  Standard_EXPORT void Perform(const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<GeomPlate_CurveConstraint> CurveConstraint(const int order) const;

  Standard_EXPORT occ::handle<GeomPlate_PointConstraint> PointConstraint(const int order) const;

  Standard_EXPORT void Disc2dContour(const int nbp, NCollection_Sequence<gp_XY>& Seq2d);

  Standard_EXPORT void Disc3dContour(const int                     nbp,
                                     const int                     iordre,
                                     NCollection_Sequence<gp_XYZ>& Seq3d);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<GeomPlate_Surface> Surface() const;

  Standard_EXPORT occ::handle<Geom_Surface> SurfInit() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> Sense() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<Geom2d_Curve>>> Curves2d() const;

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> Order() const;

  Standard_EXPORT double G0Error() const;

  Standard_EXPORT double G1Error() const;

  Standard_EXPORT double G2Error() const;

  Standard_EXPORT double G0Error(const int Index);

  Standard_EXPORT double G1Error(const int Index);

  Standard_EXPORT double G2Error(const int Index);

private:
  Standard_EXPORT void EcartContraintesMil(const int                                 c,
                                           occ::handle<NCollection_HArray1<double>>& d,
                                           occ::handle<NCollection_HArray1<double>>& an,
                                           occ::handle<NCollection_HArray1<double>>& courb);

  Standard_EXPORT gp_Pnt2d ProjectPoint(const gp_Pnt& P);

  Standard_EXPORT occ::handle<Geom2d_Curve> ProjectCurve(const occ::handle<Adaptor3d_Curve>& Curv);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ProjectedCurve(occ::handle<Adaptor3d_Curve>& Curv);

  Standard_EXPORT void ComputeSurfInit(const Message_ProgressRange& theProgress);

  Standard_EXPORT void Intersect(
    occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntInter,
    occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntG1G1);

  Standard_EXPORT void Discretise(
    const occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntInter,
    const occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>& PntG1G1);

  Standard_EXPORT void LoadCurve(const int NbBoucle, const int OrderMax = 2);

  Standard_EXPORT void LoadPoint(const int NbBoucle, const int OrderMax = 2);

  Standard_EXPORT void CalculNbPtsInit();

  Standard_EXPORT bool VerifSurface(const int NbLoop);

  Standard_EXPORT void VerifPoints(double& dist, double& ang, double& curv) const;

  Standard_EXPORT bool CourbeJointive(const double tolerance);

  Standard_EXPORT double ComputeAnisotropie() const;

  Standard_EXPORT bool IsOrderG1() const;

  occ::handle<NCollection_HSequence<occ::handle<GeomPlate_CurveConstraint>>> myLinCont;
  occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>             myParCont;
  occ::handle<NCollection_HArray1<NCollection_Sequence<double>>>             myPlateCont;
  occ::handle<NCollection_HSequence<occ::handle<GeomPlate_PointConstraint>>> myPntCont;
  occ::handle<Geom_Surface>                                                  mySurfInit;
  occ::handle<Geom_Surface>                                                  myPlanarSurfInit;
  occ::handle<GeomPlate_Surface>                                             myGeomPlateSurface;
  Plate_Plate                                                                myPlate;
  Plate_Plate                                                                myPrevPlate;
  bool                                                                       myAnisotropie;
  occ::handle<NCollection_HArray1<int>>                                      mySense;
  int                                                                        myDegree;
  occ::handle<NCollection_HArray1<int>>                                      myInitOrder;
  double                                                                     myG0Error;
  double                                                                     myG1Error;
  double                                                                     myG2Error;
  int                                                                        myNbPtsOnCur;
  bool                                                                       mySurfInitIsGive;
  int                                                                        myNbIter;
  Extrema_ExtPS                                                              myProj;
  double                                                                     myTol2d;
  double                                                                     myTol3d;
  double                                                                     myTolAng;
  double                                                                     myTolU;
  double                                                                     myTolV;
  int                                                                        myNbBounds;
  bool                                                                       myIsLinear;
  bool                                                                       myFree;
};
