#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

enum BRepLib_WireError
{
  BRepLib_WireDone,
  BRepLib_EmptyWire,
  BRepLib_DisconnectedWire,
  BRepLib_NonManifoldWire
};

#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <BRepLib_MakeShape.hpp>
#include <NCollection_List.hpp>
#include <Bnd_Box.hpp>
#include <NCollection_UBTree.hpp>

class TopoDS_Wire;

class BRepLib_MakeWire : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_MakeWire();

  Standard_EXPORT BRepLib_MakeWire(const TopoDS_Edge& E);

  Standard_EXPORT BRepLib_MakeWire(const TopoDS_Edge& E1, const TopoDS_Edge& E2);

  Standard_EXPORT BRepLib_MakeWire(const TopoDS_Edge& E1,
                                   const TopoDS_Edge& E2,
                                   const TopoDS_Edge& E3);

  Standard_EXPORT BRepLib_MakeWire(const TopoDS_Edge& E1,
                                   const TopoDS_Edge& E2,
                                   const TopoDS_Edge& E3,
                                   const TopoDS_Edge& E4);

  Standard_EXPORT BRepLib_MakeWire(const TopoDS_Wire& W);

  Standard_EXPORT BRepLib_MakeWire(const TopoDS_Wire& W, const TopoDS_Edge& E);

  Standard_EXPORT void Add(const TopoDS_Edge& E);

  Standard_EXPORT void Add(const TopoDS_Wire& W);

  Standard_EXPORT void Add(const NCollection_List<TopoDS_Shape>& L);

  Standard_EXPORT BRepLib_WireError Error() const;

  Standard_EXPORT const TopoDS_Wire& Wire();
  Standard_EXPORT                    operator TopoDS_Wire();

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT const TopoDS_Vertex& Vertex() const;

private:
  class BRepLib_BndBoxVertexSelector : public NCollection_UBTree<int, Bnd_Box>::Selector
  {
  public:
    BRepLib_BndBoxVertexSelector(
      const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& theMapOfShape)
        : myMapOfShape(theMapOfShape),
          myTolP(0.0),
          myVInd(0)
    {
    }

    bool Reject(const Bnd_Box& theBox) const override { return theBox.IsOut(myVBox); }

    bool Accept(const int& theObj) override;

    void SetCurrentVertex(const gp_Pnt& theP, double theTol, int theVInd);

    const NCollection_List<int>& GetResultInds() const { return myResultInd; }

    void ClearResInds() { myResultInd.Clear(); }

  private:
    BRepLib_BndBoxVertexSelector(const BRepLib_BndBoxVertexSelector&)            = delete;
    BRepLib_BndBoxVertexSelector& operator=(const BRepLib_BndBoxVertexSelector&) = delete;

    const NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& myMapOfShape;
    gp_Pnt                                                               myP;
    double                                                               myTolP;
    int                                                                  myVInd;
    Bnd_Box                                                              myVBox;
    NCollection_List<int>                                                myResultInd;
  };

  void CollectCoincidentVertices(const NCollection_List<TopoDS_Shape>&              theL,
                                 NCollection_List<NCollection_List<TopoDS_Vertex>>& theGrVL);

  void CreateNewVertices(
    const NCollection_List<NCollection_List<TopoDS_Vertex>>&                  theGrVL,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theO2NV);

  void CreateNewListOfEdges(
    const NCollection_List<TopoDS_Shape>&                                           theL,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theO2NV,
    NCollection_List<TopoDS_Shape>&                                                 theNewEList);

  void Add(const TopoDS_Edge& E, bool IsCheckGeometryProximity);

private:
  BRepLib_WireError                                             myError;
  TopoDS_Edge                                                   myEdge;
  TopoDS_Vertex                                                 myVertex;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myVertices;
  TopoDS_Vertex                                                 FirstVertex;
  TopoDS_Vertex                                                 VF;
  TopoDS_Vertex                                                 VL;
};
