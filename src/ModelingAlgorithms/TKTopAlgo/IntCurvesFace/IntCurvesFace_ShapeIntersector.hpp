#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Real.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <IntCurvesFace_Intersector.hpp>
#include <TopAbs_State.hpp>

class Adaptor3d_Curve;
class TopoDS_Shape;
class gp_Lin;
class gp_Pnt;
class TopoDS_Face;

class IntCurvesFace_ShapeIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurvesFace_ShapeIntersector();

  Standard_EXPORT void Load(const TopoDS_Shape& Sh, const double Tol);

  Standard_EXPORT void Perform(const gp_Lin& L, const double PInf, const double PSup);

  Standard_EXPORT void PerformNearest(const gp_Lin& L, const double PInf, const double PSup);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>& HCu,
                               const double                        PInf,
                               const double                        PSup);

  bool IsDone() const { return myIsDone; }

  int NbPnt() const { return myIndexPt.Length(); }

  double UParameter(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->UParameter(myIndexIntPnt(myIndexPt(I)));
  }

  double VParameter(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->VParameter(myIndexIntPnt(myIndexPt(I)));
  }

  double WParameter(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->WParameter(myIndexIntPnt(myIndexPt(I)));
  }

  const gp_Pnt& Pnt(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->Pnt(myIndexIntPnt(myIndexPt(I)));
  }

  IntCurveSurface_TransitionOnCurve Transition(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->Transition(myIndexIntPnt(myIndexPt(I)));
  }

  TopAbs_State State(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->State(myIndexIntPnt(myIndexPt(I)));
  }

  const TopoDS_Face& Face(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->Face();
  }

  Standard_EXPORT void SortResult();

  Standard_EXPORT virtual ~IntCurvesFace_ShapeIntersector();

private:
  bool                                                         myIsDone;
  int                                                          myNbFaces;
  NCollection_Array1<int>                                      myPtrNums;
  NCollection_Array1<int>                                      myPtrIndexNums;
  NCollection_Sequence<occ::handle<IntCurvesFace_Intersector>> myIntersector;
  NCollection_Sequence<int>                                    myIndexPt;
  NCollection_Sequence<int>                                    myIndexFace;
  NCollection_Sequence<int>                                    myIndexIntPnt;
  NCollection_Sequence<double>                                 myIndexPar;
};
