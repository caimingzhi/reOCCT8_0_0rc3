#pragma once


#include <NCollection_UBTree.hpp>
#include <Bnd_Box.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

#include <ShapeExtend.hpp>
#include <ShapeExtend_Status.hpp>
#include <TopoDS_Vertex.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>

class ShapeAnalysis_BoxBndTreeSelector : public NCollection_UBTree<int, Bnd_Box>::Selector
{
public:
  ShapeAnalysis_BoxBndTreeSelector(occ::handle<NCollection_HArray1<TopoDS_Shape>> theSeq,
                                   bool                                           theShared)
      : mySeq(theSeq),
        myShared(theShared),
        myNb(0),
        myTol(1e-7),
        myMin3d(1e-7),
        myArrIndices(1, 2),
        myStatus(ShapeExtend::EncodeStatus(ShapeExtend_OK))
  {
    myArrIndices.Init(0);
  }

  void DefineBoxes(const Bnd_Box& theFBox, const Bnd_Box& theLBox)
  {
    myFBox = theFBox;
    myLBox = theLBox;
    myArrIndices.Init(0);
  }

  void DefineVertexes(TopoDS_Vertex theVf, TopoDS_Vertex theVl)
  {
    myFVertex = theVf;
    myLVertex = theVl;
    myStatus  = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  }

  void DefinePnt(const gp_Pnt& theFPnt, const gp_Pnt& theLPnt)
  {
    myFPnt   = theFPnt;
    myLPnt   = theLPnt;
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  }

  int GetNb() { return myNb; }

  void SetNb(int theNb) { myNb = theNb; }

  void LoadList(int elem) { myList.Add(elem); }

  void SetStop() { myStop = false; }

  void SetTolerance(double theTol)
  {
    myTol    = theTol;
    myMin3d  = theTol;
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
  }

  bool ContWire(int nbWire) { return myList.Contains(nbWire); }

  inline bool LastCheckStatus(const ShapeExtend_Status theStatus) const
  {
    return ShapeExtend::DecodeStatus(myStatus, theStatus);
  }

  bool Reject(const Bnd_Box& theBnd) const override;
  bool Accept(const int&) override;

private:
  Bnd_Box                                        myFBox;
  Bnd_Box                                        myLBox;
  occ::handle<NCollection_HArray1<TopoDS_Shape>> mySeq;
  bool                                           myShared;
  int                                            myNb;
  TopoDS_Vertex                                  myFVertex;
  TopoDS_Vertex                                  myLVertex;
  gp_Pnt                                         myFPnt;
  gp_Pnt                                         myLPnt;
  NCollection_Map<int>                           myList;
  double                                         myTol;
  double                                         myMin3d;
  NCollection_Array1<int>                        myArrIndices;
  int                                            myStatus;
};

