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

//! This class provides the intersection of
//! face's underlying surfaces.
class IntTools_FaceFace
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT IntTools_FaceFace();

  //! Modifier
  Standard_EXPORT void SetParameters(const bool   ApproxCurves,
                                     const bool   ComputeCurveOnS1,
                                     const bool   ComputeCurveOnS2,
                                     const double ApproximationTolerance);

  //! Intersects underliing surfaces of F1 and F2
  //! Use sum of tolerance of F1 and F2 as intersection
  //! criteria
  Standard_EXPORT void Perform(const TopoDS_Face& F1,
                               const TopoDS_Face& F2,
                               const bool         theToRunParallel = false);

  //! Returns True if the intersection was successful
  Standard_EXPORT bool IsDone() const;

  //! Returns sequence of 3d curves as result of intersection
  Standard_EXPORT const NCollection_Sequence<IntTools_Curve>& Lines() const;

  //! Returns sequence of 3d curves as result of intersection
  Standard_EXPORT const NCollection_Sequence<IntTools_PntOn2Faces>& Points() const;

  //! Returns first of processed faces
  Standard_EXPORT const TopoDS_Face& Face1() const;

  //! Returns second of processed faces
  Standard_EXPORT const TopoDS_Face& Face2() const;

  //! Returns True if faces are tangent
  Standard_EXPORT bool TangentFaces() const;

  //! Provides post-processing the result lines.
  //! @param[in] bToSplit  split the closed 3D-curves on parts when TRUE,
  //!                      remain untouched otherwise
  Standard_EXPORT void PrepareLines3D(const bool bToSplit = true);

  Standard_EXPORT void SetList(NCollection_List<IntSurf_PntOn2S>& ListOfPnts);

  //! Sets the intersection context
  Standard_EXPORT void SetContext(const occ::handle<IntTools_Context>& aContext);

  //! Sets the Fuzzy value
  Standard_EXPORT void SetFuzzyValue(const double theFuzz);

  //! Returns Fuzzy value
  Standard_EXPORT double FuzzyValue() const;

  //! Gets the intersection context
  Standard_EXPORT const occ::handle<IntTools_Context>& Context() const;

protected:
  //! Creates curves from the IntPatch_Line.
  Standard_EXPORT void MakeCurve(const int                               Index,
                                 const occ::handle<Adaptor3d_TopolTool>& D1,
                                 const occ::handle<Adaptor3d_TopolTool>& D2,
                                 const double                            theToler);

  //! Computes the valid tolerance for the intersection curves
  //! as a maximal deviation between 3D curve and 2D curves on faces.
  //! If there are no 2D curves the maximal deviation between 3D curves
  //! and surfaces is computed.
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
