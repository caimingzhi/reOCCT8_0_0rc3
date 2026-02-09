#pragma once

#include <BRepExtrema_ProximityDistTool.hpp>
#include <BRepExtrema_TriangleSet.hpp>
#include <NCollection_CellFilter.hpp>
#include <Precision.hpp>

typedef NCollection_Vector<gp_XYZ> VectorOfPoint;

class BRepExtrema_VertexInspector : public NCollection_CellFilter_InspectorXYZ
{
public:
  typedef int Target;

  BRepExtrema_VertexInspector()
      : myTol(Precision::SquareConfusion()),
        myIsNeedAdd(true)
  {
  }

  void Add(const gp_XYZ& thePnt) { myPoints.Append(thePnt); }

  void SetTol(const double theTol) { myTol = theTol; }

  void SetCurrent(const gp_XYZ& theCurPnt)
  {
    myCurrent   = theCurPnt;
    myIsNeedAdd = true;
  }

  bool IsNeedAdd() { return myIsNeedAdd; }

  Standard_EXPORT NCollection_CellFilter_Action Inspect(const int theTarget);

private:
  double        myTol;
  bool          myIsNeedAdd;
  VectorOfPoint myPoints;
  gp_XYZ        myCurrent;
};

typedef typename BRepExtrema_ProximityDistTool::ProxPnt_Status ProxPnt_Status;

class BRepExtrema_ProximityValueTool
{

public:
  Standard_EXPORT BRepExtrema_ProximityValueTool();

  Standard_EXPORT BRepExtrema_ProximityValueTool(
    const occ::handle<BRepExtrema_TriangleSet>& theSet1,
    const occ::handle<BRepExtrema_TriangleSet>& theSet2,
    const NCollection_Vector<TopoDS_Shape>&     theShapeList1,
    const NCollection_Vector<TopoDS_Shape>&     theShapeList2);

public:
  Standard_EXPORT void LoadTriangleSets(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                                        const occ::handle<BRepExtrema_TriangleSet>& theSet2);

  Standard_EXPORT void LoadShapeLists(const NCollection_Vector<TopoDS_Shape>& theShapeList1,
                                      const NCollection_Vector<TopoDS_Shape>& theShapeList2);

  Standard_EXPORT void SetNbSamplePoints(const int theSamples1 = 0, const int theSamples2 = 0);

  Standard_EXPORT void Perform(double& theTolerance);

  bool IsDone() const { return myIsDone; }

  void MarkDirty() { myIsDone = false; }

  double Distance() const { return myDistance; }

  void ProximityPoints(gp_Pnt& thePoint1, gp_Pnt& thePoint2) const
  {
    thePoint1 = myPnt1;
    thePoint2 = myPnt2;
  }

  void ProximityPointsStatus(ProxPnt_Status& thePointStatus1, ProxPnt_Status& thePointStatus2) const
  {
    thePointStatus1 = myPntStatus1;
    thePointStatus2 = myPntStatus2;
  }

private:
  bool getInfoForRefinement(const TopoDS_Shape& theShapes,
                            TopAbs_ShapeEnum&   theShapeType,
                            int&                theNbNodes,
                            double&             theStep);

  double computeProximityDist(const occ::handle<BRepExtrema_TriangleSet>& theSet1,
                              const int                                   theNbSamples1,
                              const BVH_Array3d&                          theAddVertices1,
                              const NCollection_Vector<ProxPnt_Status>&   theAddStatus1,
                              const occ::handle<BRepExtrema_TriangleSet>& theSet2,
                              const NCollection_Vector<TopoDS_Shape>&     theShapeList1,
                              const NCollection_Vector<TopoDS_Shape>&     theShapeList2,
                              BVH_Vec3d&                                  thePoint1,
                              BVH_Vec3d&                                  thePoint2,
                              ProxPnt_Status&                             thePointStatus1,
                              ProxPnt_Status&                             thePointStatus2) const;

  bool getShapesAdditionalVertices();

  bool getEdgeAdditionalVertices(const TopoDS_Edge&                  theEdge,
                                 const double                        theStep,
                                 BVH_Array3d&                        theAddVertices,
                                 NCollection_Vector<ProxPnt_Status>& theAddStatuses);

  bool getFaceAdditionalVertices(const TopoDS_Face&                  theFace,
                                 const double                        theStep,
                                 BVH_Array3d&                        theAddVertices,
                                 NCollection_Vector<ProxPnt_Status>& theAddStatuses);

  void doRecurTrgSplit(const gp_Pnt (&theTrg)[3],
                       const ProxPnt_Status (&theEdgesStatus)[3],
                       const double                        theTol,
                       const double                        theStep,
                       BVH_Array3d&                        theAddVertices,
                       NCollection_Vector<ProxPnt_Status>& theAddStatuses);

private:
  occ::handle<BRepExtrema_TriangleSet> mySet1;

  occ::handle<BRepExtrema_TriangleSet> mySet2;

  NCollection_Vector<TopoDS_Shape> myShapeList1;

  NCollection_Vector<TopoDS_Shape> myShapeList2;

  TopoDS_Shape myShape1;

  TopoDS_Shape myShape2;

  BVH_Array3d myAddVertices1;
  BVH_Array3d myAddVertices2;

  NCollection_Vector<ProxPnt_Status> myAddStatus1;
  NCollection_Vector<ProxPnt_Status> myAddStatus2;

  bool myIsInitS1;
  bool myIsInitS2;

  bool myIsRefinementRequired1;
  bool myIsRefinementRequired2;

  int myNbNodes1;
  int myNbNodes2;

  double myStep1;
  double myStep2;

  NCollection_CellFilter<BRepExtrema_VertexInspector> myCells;
  BRepExtrema_VertexInspector                         myInspector;

  TopAbs_ShapeEnum myShapeType1;
  TopAbs_ShapeEnum myShapeType2;

  double myDistance;
  bool   myIsDone;

  int myNbSamples1;
  int myNbSamples2;

  gp_Pnt myPnt1, myPnt2;

  ProxPnt_Status myPntStatus1, myPntStatus2;
};
