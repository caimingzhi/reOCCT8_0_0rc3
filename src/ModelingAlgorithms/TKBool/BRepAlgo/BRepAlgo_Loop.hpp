#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <BRepAlgo_Image.hpp>
class TopoDS_Edge;

class BRepAlgo_Loop
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_Loop();

  Standard_EXPORT void Init(const TopoDS_Face& F);

  Standard_EXPORT void AddEdge(TopoDS_Edge& E, const NCollection_List<TopoDS_Shape>& LV);

  Standard_EXPORT void AddConstEdge(const TopoDS_Edge& E);

  Standard_EXPORT void AddConstEdges(const NCollection_List<TopoDS_Shape>& LE);

  Standard_EXPORT void SetImageVV(const BRepAlgo_Image& theImageVV);

  Standard_EXPORT void Perform();

  Standard_EXPORT void UpdateVEmap(NCollection_IndexedDataMap<TopoDS_Shape,
                                                              NCollection_List<TopoDS_Shape>,
                                                              TopTools_ShapeMapHasher>& theVEmap);

  Standard_EXPORT void CutEdge(const TopoDS_Edge&                    E,
                               const NCollection_List<TopoDS_Shape>& VonE,
                               NCollection_List<TopoDS_Shape>&       NE) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewWires() const;

  Standard_EXPORT void WiresToFaces();

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewFaces() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& NewEdges(const TopoDS_Edge& E) const;

  Standard_EXPORT void GetVerticesForSubstitute(
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& VerVerMap) const;

  Standard_EXPORT void VerticesForSubstitute(
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& VerVerMap);

  void SetTolConf(const double theTolConf) { myTolConf = theTolConf; }

  double GetTolConf() const { return myTolConf; }

private:
  TopoDS_Face                    myFace;
  NCollection_List<TopoDS_Shape> myConstEdges;
  NCollection_List<TopoDS_Shape> myEdges;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                 myVerOnEdges;
  NCollection_List<TopoDS_Shape> myNewWires;
  NCollection_List<TopoDS_Shape> myNewFaces;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                                           myCutEdges;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVerticesForSubstitute;
  BRepAlgo_Image                                                           myImageVV;
  double                                                                   myTolConf;
};
