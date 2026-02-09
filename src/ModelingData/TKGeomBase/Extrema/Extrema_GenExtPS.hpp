#pragma once

#include <Bnd_Sphere.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Extrema_POnSurfParams.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_UBTreeFiller.hpp>
#include <NCollection_Handle.hpp>
#include <Extrema_FuncPSNorm.hpp>
#include <Extrema_ExtFlag.hpp>
#include <Extrema_ExtAlgo.hpp>

class Adaptor3d_Surface;

class Extrema_GenExtPS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenExtPS();

  Standard_EXPORT ~Extrema_GenExtPS();

  Standard_EXPORT Extrema_GenExtPS(const gp_Pnt&            P,
                                   const Adaptor3d_Surface& S,
                                   const int                NbU,
                                   const int                NbV,
                                   const double             TolU,
                                   const double             TolV,
                                   const Extrema_ExtFlag    F = Extrema_ExtFlag_MINMAX,
                                   const Extrema_ExtAlgo    A = Extrema_ExtAlgo_Grad);

  Standard_EXPORT Extrema_GenExtPS(const gp_Pnt&            P,
                                   const Adaptor3d_Surface& S,
                                   const int                NbU,
                                   const int                NbV,
                                   const double             Umin,
                                   const double             Usup,
                                   const double             Vmin,
                                   const double             Vsup,
                                   const double             TolU,
                                   const double             TolV,
                                   const Extrema_ExtFlag    F = Extrema_ExtFlag_MINMAX,
                                   const Extrema_ExtAlgo    A = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const int                NbU,
                                  const int                NbV,
                                  const double             TolU,
                                  const double             TolV);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const int                NbU,
                                  const int                NbV,
                                  const double             Umin,
                                  const double             Usup,
                                  const double             Vmin,
                                  const double             Vsup,
                                  const double             TolU,
                                  const double             TolV);

  Standard_EXPORT void Perform(const gp_Pnt& P);

  Standard_EXPORT void SetFlag(const Extrema_ExtFlag F);

  Standard_EXPORT void SetAlgo(const Extrema_ExtAlgo A);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

private:
  Standard_EXPORT void BuildTree();

  Standard_EXPORT void FindSolution(const gp_Pnt& P, const Extrema_POnSurfParams& theParams);

  Standard_EXPORT void GetGridPoints(const Adaptor3d_Surface& theSurf);

  Standard_EXPORT void BuildGrid(const gp_Pnt& thePoint);

  Standard_EXPORT const Extrema_POnSurfParams& ComputeEdgeParameters(
    const bool                   IsUEdge,
    const Extrema_POnSurfParams& theParam0,
    const Extrema_POnSurfParams& theParam1,
    const gp_Pnt&                thePoints,
    const double                 theDiffTol);

private:
  Extrema_GenExtPS(const Extrema_GenExtPS&)            = delete;
  Extrema_GenExtPS& operator=(const Extrema_GenExtPS&) = delete;

private:
  bool   myDone;
  bool   myInit;
  double myumin;
  double myusup;
  double myvmin;
  double myvsup;
  int    myusample;
  int    myvsample;
  double mytolu;
  double mytolv;

  NCollection_Array2<Extrema_POnSurfParams>               myPoints;
  NCollection_Handle<NCollection_UBTree<int, Bnd_Sphere>> mySphereUBTree;
  occ::handle<NCollection_HArray1<Bnd_Sphere>>            mySphereArray;
  Extrema_FuncPSNorm                                      myF;
  const Adaptor3d_Surface*                                myS;
  Extrema_ExtFlag                                         myFlag;
  Extrema_ExtAlgo                                         myAlgo;
  occ::handle<NCollection_HArray1<double>>                myUParams;
  occ::handle<NCollection_HArray1<double>>                myVParams;
  NCollection_Array2<Extrema_POnSurfParams>               myFacePntParams;
  NCollection_Array2<Extrema_POnSurfParams>               myUEdgePntParams;
  NCollection_Array2<Extrema_POnSurfParams>               myVEdgePntParams;
  Extrema_POnSurfParams                                   myGridParam;
};
