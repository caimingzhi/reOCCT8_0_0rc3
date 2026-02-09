#pragma once

#include <NCollection_DataMap.hpp>
#include <Precision.hpp>
#include <TColStd_PackedMapOfInteger.hpp>

#include <BRepExtrema_ProximityValueTool.hpp>
#include <BRepExtrema_TriangleSet.hpp>
#include <BRepExtrema_OverlapTool.hpp>

class BRepExtrema_ShapeProximity
{

public:
  Standard_EXPORT BRepExtrema_ShapeProximity(const double theTolerance = Precision::Infinite());

  Standard_EXPORT BRepExtrema_ShapeProximity(const TopoDS_Shape& theShape1,
                                             const TopoDS_Shape& theShape2,
                                             const double theTolerance = Precision::Infinite());

public:
  double Tolerance() const { return myTolerance; }

  void SetTolerance(const double theTolerance) { myTolerance = theTolerance; }

  double Proximity() const { return Tolerance(); }

  Standard_EXPORT bool LoadShape1(const TopoDS_Shape& theShape1);

  Standard_EXPORT bool LoadShape2(const TopoDS_Shape& theShape2);

  void SetNbSamples1(const int theNbSamples) { myNbSamples1 = theNbSamples; }

  void SetNbSamples2(const int theNbSamples) { myNbSamples2 = theNbSamples; }

  Standard_EXPORT void Perform();

  bool IsDone() const { return myOverlapTool.IsDone() || myProxValTool.IsDone(); }

  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapSubShapes1() const
  {
    return myOverlapTool.OverlapSubShapes1();
  }

  const NCollection_DataMap<int, TColStd_PackedMapOfInteger>& OverlapSubShapes2() const
  {
    return myOverlapTool.OverlapSubShapes2();
  }

  const TopoDS_Shape& GetSubShape1(const int theID) const { return myShapeList1.Value(theID); }

  const TopoDS_Shape& GetSubShape2(const int theID) const { return myShapeList2.Value(theID); }

  const occ::handle<BRepExtrema_TriangleSet>& ElementSet1() const { return myElementSet1; }

  const occ::handle<BRepExtrema_TriangleSet>& ElementSet2() const { return myElementSet2; }

  const gp_Pnt& ProximityPoint1() const { return myProxPoint1; }

  const gp_Pnt& ProximityPoint2() const { return myProxPoint2; }

  const ProxPnt_Status& ProxPntStatus1() const { return myProxPntStatus1; }

  const ProxPnt_Status& ProxPntStatus2() const { return myProxPntStatus2; }

private:
  double myTolerance;

  bool myIsInitS1;

  bool myIsInitS2;

  NCollection_Vector<TopoDS_Shape> myShapeList1;

  NCollection_Vector<TopoDS_Shape> myShapeList2;

  occ::handle<BRepExtrema_TriangleSet> myElementSet1;

  occ::handle<BRepExtrema_TriangleSet> myElementSet2;

  int myNbSamples1;

  int myNbSamples2;

  gp_Pnt myProxPoint1;

  gp_Pnt myProxPoint2;

  ProxPnt_Status myProxPntStatus1, myProxPntStatus2;

  BRepExtrema_OverlapTool myOverlapTool;

  BRepExtrema_ProximityValueTool myProxValTool;
};
