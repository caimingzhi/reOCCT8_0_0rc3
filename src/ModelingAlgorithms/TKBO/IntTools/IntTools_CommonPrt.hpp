#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <IntTools_Range.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
#include <gp_Pnt.hpp>

class IntTools_CommonPrt
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_CommonPrt();

  Standard_EXPORT IntTools_CommonPrt(const IntTools_CommonPrt& aCPrt);

  Standard_EXPORT IntTools_CommonPrt& Assign(const IntTools_CommonPrt& Other);

  IntTools_CommonPrt& operator=(const IntTools_CommonPrt& Other) { return Assign(Other); }

  Standard_EXPORT void SetEdge1(const TopoDS_Edge& anE);

  Standard_EXPORT void SetEdge2(const TopoDS_Edge& anE);

  Standard_EXPORT void SetType(const TopAbs_ShapeEnum aType);

  Standard_EXPORT void SetRange1(const IntTools_Range& aR);

  Standard_EXPORT void SetRange1(const double tf, const double tl);

  Standard_EXPORT void AppendRange2(const IntTools_Range& aR);

  Standard_EXPORT void AppendRange2(const double tf, const double tl);

  Standard_EXPORT void SetVertexParameter1(const double tV);

  Standard_EXPORT void SetVertexParameter2(const double tV);

  Standard_EXPORT const TopoDS_Edge& Edge1() const;

  Standard_EXPORT const TopoDS_Edge& Edge2() const;

  Standard_EXPORT TopAbs_ShapeEnum Type() const;

  Standard_EXPORT const IntTools_Range& Range1() const;

  Standard_EXPORT void Range1(double& tf, double& tl) const;

  Standard_EXPORT const NCollection_Sequence<IntTools_Range>& Ranges2() const;

  Standard_EXPORT NCollection_Sequence<IntTools_Range>& ChangeRanges2();

  Standard_EXPORT double VertexParameter1() const;

  Standard_EXPORT double VertexParameter2() const;

  Standard_EXPORT void Copy(IntTools_CommonPrt& anOther) const;

  Standard_EXPORT bool AllNullFlag() const;

  Standard_EXPORT void SetAllNullFlag(const bool aFlag);

  Standard_EXPORT void SetBoundingPoints(const gp_Pnt& aP1, const gp_Pnt& aP2);

  Standard_EXPORT void BoundingPoints(gp_Pnt& aP1, gp_Pnt& aP2) const;

private:
  TopoDS_Edge                          myEdge1;
  TopoDS_Edge                          myEdge2;
  TopAbs_ShapeEnum                     myType;
  IntTools_Range                       myRange1;
  double                               myVertPar1;
  double                               myVertPar2;
  NCollection_Sequence<IntTools_Range> myRanges2;
  bool                                 myAllNullFlag;
  gp_Pnt                               myPnt1;
  gp_Pnt                               myPnt2;
};
