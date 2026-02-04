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

  //! Perform the intersection between the
  //! segment L and the loaded shape.
  //!
  //! PInf is the smallest parameter on the line
  //! PSup is the highest parameter on the line
  //!
  //! For an infinite line PInf and PSup can be
  //! +/- RealLast.
  Standard_EXPORT void Perform(const gp_Lin& L, const double PInf, const double PSup);

  //! Perform the intersection between the
  //! segment L and the loaded shape.
  //!
  //! PInf is the smallest parameter on the line
  //! PSup is the highest parameter on the line
  //!
  //! For an infinite line PInf and PSup can be
  //! +/- RealLast.
  Standard_EXPORT void PerformNearest(const gp_Lin& L, const double PInf, const double PSup);

  //! same method for a HCurve from Adaptor3d.
  //! PInf an PSup can also be -INF and +INF.
  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Curve>& HCu,
                               const double                        PInf,
                               const double                        PSup);

  //! True when the intersection has been computed.
  bool IsDone() const { return myIsDone; }

  //! Returns the number of the intersection points
  int NbPnt() const { return myIndexPt.Length(); }

  //! Returns the U parameter of the ith intersection point
  //! on the surface.
  double UParameter(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->UParameter(myIndexIntPnt(myIndexPt(I)));
  }

  //! Returns the V parameter of the ith intersection point
  //! on the surface.
  double VParameter(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->VParameter(myIndexIntPnt(myIndexPt(I)));
  }

  //! Returns the parameter of the ith intersection point
  //! on the line.
  double WParameter(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->WParameter(myIndexIntPnt(myIndexPt(I)));
  }

  //! Returns the geometric point of the ith intersection
  //! between the line and the surface.
  const gp_Pnt& Pnt(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->Pnt(myIndexIntPnt(myIndexPt(I)));
  }

  //! Returns the ith transition of the line on the surface.
  IntCurveSurface_TransitionOnCurve Transition(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->Transition(myIndexIntPnt(myIndexPt(I)));
  }

  //! Returns the ith state of the point on the face.
  //! The values can be either TopAbs_IN
  //! ( the point is in the face)
  //! or TopAbs_ON
  //! ( the point is on a boundary of the face).
  TopAbs_State State(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->State(myIndexIntPnt(myIndexPt(I)));
  }

  //! Returns the significant face used to determine
  //! the intersection.
  const TopoDS_Face& Face(const int I) const
  {
    occ::handle<IntCurvesFace_Intersector> anIntAdaptor = myIntersector(myIndexFace(myIndexPt(I)));
    return anIntAdaptor->Face();
  }

  //! Internal method. Sort the result on the Curve
  //! parameter.
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

