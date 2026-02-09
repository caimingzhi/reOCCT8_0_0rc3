#pragma once

#include <GeomAdaptor_Surface.hpp>
#include <GeomInt_LineConstructor.hpp>
#include <IntPatch_Intersection.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <NCollection_List.hpp>
#include <IntTools_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <IntTools_PntOn2Faces.hpp>
#include <TopoDS_Face.hpp>

class IntTools_Context;
class Adaptor3d_TopolTool;

class IntTools_FaceFace
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_FaceFace();

  Standard_EXPORT void SetParameters(const bool   ApproxCurves,
                                     const bool   ComputeCurveOnS1,
                                     const bool   ComputeCurveOnS2,
                                     const double ApproximationTolerance);

  Standard_EXPORT void Perform(const TopoDS_Face& F1,
                               const TopoDS_Face& F2,
                               const bool         theToRunParallel = false);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT const NCollection_Sequence<IntTools_Curve>& Lines() const;

  Standard_EXPORT const NCollection_Sequence<IntTools_PntOn2Faces>& Points() const;

  Standard_EXPORT const TopoDS_Face& Face1() const;

  Standard_EXPORT const TopoDS_Face& Face2() const;

  Standard_EXPORT bool TangentFaces() const;

  Standard_EXPORT void PrepareLines3D(const bool bToSplit = true);

  Standard_EXPORT void SetList(NCollection_List<IntSurf_PntOn2S>& ListOfPnts);

  Standard_EXPORT void SetContext(const occ::handle<IntTools_Context>& aContext);

  Standard_EXPORT void SetFuzzyValue(const double theFuzz);

  Standard_EXPORT double FuzzyValue() const;

  Standard_EXPORT const occ::handle<IntTools_Context>& Context() const;

protected:
  Standard_EXPORT void MakeCurve(const int                               Index,
                                 const occ::handle<Adaptor3d_TopolTool>& D1,
                                 const occ::handle<Adaptor3d_TopolTool>& D2,
                                 const double                            theToler);

  Standard_EXPORT void ComputeTolReached3d(const bool theToRunParallel);

protected:
  bool                                       myIsDone;
  IntPatch_Intersection                      myIntersector;
  GeomInt_LineConstructor                    myLConstruct;
  occ::handle<GeomAdaptor_Surface>           myHS1;
  occ::handle<GeomAdaptor_Surface>           myHS2;
  int                                        myNbrestr;
  bool                                       myApprox;
  bool                                       myApprox1;
  bool                                       myApprox2;
  double                                     myTolApprox;
  double                                     myTolF1;
  double                                     myTolF2;
  double                                     myTol;
  double                                     myFuzzyValue;
  NCollection_Sequence<IntTools_Curve>       mySeqOfCurve;
  bool                                       myTangentFaces;
  TopoDS_Face                                myFace1;
  TopoDS_Face                                myFace2;
  NCollection_Sequence<IntTools_PntOn2Faces> myPnts;
  NCollection_List<IntSurf_PntOn2S>          myListOfPnts;
  occ::handle<IntTools_Context>              myContext;
};
