#pragma once

#include <NCollection_Sequence.hpp>
#include <NCollection_UBTreeFiller.hpp>
#include <NCollection_UBTree.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <Geom_Line.hpp>
#include <Bnd_Box.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Precision.hpp>

// Typedef to reduce code complexity.

// Class representing tree selector for point object.
class BRepClass3d_BndBoxTreeSelectorPoint : public NCollection_UBTree<int, Bnd_Box>::Selector
{
public:
  BRepClass3d_BndBoxTreeSelectorPoint(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapOfShape)
      : myMapOfShape(theMapOfShape)
  {
  }

  bool Reject(const Bnd_Box& theBox) const override { return (theBox.IsOut(myP)); }

  bool Accept(const int& theObj) override;

  // Sets current point for boxes-point collisions.
  void SetCurrentPoint(const gp_Pnt& theP) { myP = theP; }

private:
  BRepClass3d_BndBoxTreeSelectorPoint(const BRepClass3d_BndBoxTreeSelectorPoint&) = delete;
  BRepClass3d_BndBoxTreeSelectorPoint& operator=(const BRepClass3d_BndBoxTreeSelectorPoint&) =
    delete;

private:
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&
         myMapOfShape; // shapes (vertices + edges)
  gp_Pnt myP;
};

// Class representing tree selector for line object.
class BRepClass3d_BndBoxTreeSelectorLine : public NCollection_UBTree<int, Bnd_Box>::Selector
{
public:
  struct EdgeParam
  {
    TopoDS_Edge myE;
    double      myParam;  // par on myE
    double      myLParam; // par on line
  };

  struct VertParam
  {
    TopoDS_Vertex myV;
    double        myLParam; // par on line
  };

public:
  BRepClass3d_BndBoxTreeSelectorLine(
    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapOfShape)
      : myMapOfShape(theMapOfShape),
        myIsValid(true)
  {
  }

  bool Reject(const Bnd_Box& theBox) const override { return (theBox.IsOut(myL)); }

  bool Accept(const int& theObj) override;

  // Sets current line for boxes-line collisions
  void SetCurrentLine(const gp_Lin& theL, const double theMaxParam)
  {
    myL = theL;
    myLC.Load(new Geom_Line(theL), -Precision::PConfusion(), theMaxParam);
  }

  void GetEdgeParam(const int i, TopoDS_Edge& theOutE, double& theOutParam, double& outLParam) const
  {
    const EdgeParam& EP = myEP.Value(i);
    theOutE             = EP.myE;
    theOutParam         = EP.myParam;
    outLParam           = EP.myLParam;
  }

  void GetVertParam(const int i, TopoDS_Vertex& theOutV, double& outLParam) const
  {
    const VertParam& VP = myVP.Value(i);
    theOutV             = VP.myV;
    outLParam           = VP.myLParam;
  }

  int GetNbEdgeParam() const { return myEP.Length(); }

  int GetNbVertParam() const { return myVP.Length(); }

  void ClearResults()
  {
    myEP.Clear();
    myVP.Clear();
    myIsValid = true;
  }

  //! Returns TRUE if correct classification is possible
  bool IsCorrect() const { return myIsValid; }

private:
  BRepClass3d_BndBoxTreeSelectorLine(const BRepClass3d_BndBoxTreeSelectorLine&)            = delete;
  BRepClass3d_BndBoxTreeSelectorLine& operator=(const BRepClass3d_BndBoxTreeSelectorLine&) = delete;

private:
  const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>&
                                  myMapOfShape; // shapes (vertices + edges)
  gp_Lin                          myL;
  NCollection_Sequence<EdgeParam> myEP; // output result (edge vs line)
  NCollection_Sequence<VertParam> myVP; // output result (vertex vs line)
  GeomAdaptor_Curve               myLC;
  bool                            myIsValid;
};
