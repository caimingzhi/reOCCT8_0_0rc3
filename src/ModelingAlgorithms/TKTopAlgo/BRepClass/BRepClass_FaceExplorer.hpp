#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

#include <TopAbs_Orientation.hpp>
#include <TopoDS_Face.hpp>
#include <TopExp_Explorer.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;
class gp_Lin2d;
class BRepClass_Edge;

class BRepClass_FaceExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_FaceExplorer(const TopoDS_Face& F);

  Standard_EXPORT bool CheckPoint(gp_Pnt2d& thePoint);

  Standard_EXPORT bool Reject(const gp_Pnt2d& P) const;

  Standard_EXPORT bool Segment(const gp_Pnt2d& P, gp_Lin2d& L, double& Par);

  Standard_EXPORT bool OtherSegment(const gp_Pnt2d& P, gp_Lin2d& L, double& Par);

  Standard_EXPORT void InitWires();

  bool MoreWires() const;

  void NextWire();

  Standard_EXPORT bool RejectWire(const gp_Lin2d& L, const double Par) const;

  Standard_EXPORT void InitEdges();

  bool MoreEdges() const;

  void NextEdge();

  Standard_EXPORT bool RejectEdge(const gp_Lin2d& L, const double Par) const;

  Standard_EXPORT void CurrentEdge(BRepClass_Edge& E, TopAbs_Orientation& Or) const;

  double MaxTolerance() const { return myMaxTolerance; }

  void SetMaxTolerance(const double theValue) { myMaxTolerance = theValue; }

  bool UseBndBox() const { return myUseBndBox; }

  void SetUseBndBox(const bool theValue) { myUseBndBox = theValue; }

protected:
  Standard_EXPORT void ComputeFaceBounds();

private:
  TopoDS_Face     myFace;
  TopExp_Explorer myWExplorer;
  TopExp_Explorer myEExplorer;
  int             myCurEdgeInd;
  double          myCurEdgePar;
  double          myMaxTolerance;
  bool            myUseBndBox;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myMapVE;

  double myUMin;
  double myUMax;
  double myVMin;
  double myVMax;
};

inline bool BRepClass_FaceExplorer::MoreWires() const
{
  return myWExplorer.More();
}

inline void BRepClass_FaceExplorer::NextWire()
{
  myWExplorer.Next();
}

inline bool BRepClass_FaceExplorer::MoreEdges() const
{
  return myEExplorer.More();
}

inline void BRepClass_FaceExplorer::NextEdge()
{
  myEExplorer.Next();
}
