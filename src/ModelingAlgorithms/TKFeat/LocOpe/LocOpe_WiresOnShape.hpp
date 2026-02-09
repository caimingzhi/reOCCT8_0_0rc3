#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Compound;
class TopoDS_Edge;
class TopoDS_Vertex;

class LocOpe_WiresOnShape : public Standard_Transient
{

public:
  Standard_EXPORT LocOpe_WiresOnShape(const TopoDS_Shape& S);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT bool Add(const NCollection_Sequence<TopoDS_Shape>& theEdges);

  void SetCheckInterior(const bool ToCheckInterior);

  Standard_EXPORT void Bind(const TopoDS_Wire& W, const TopoDS_Face& F);

  Standard_EXPORT void Bind(const TopoDS_Compound& Comp, const TopoDS_Face& F);

  Standard_EXPORT void Bind(const TopoDS_Edge& E, const TopoDS_Face& F);

  Standard_EXPORT void Bind(const TopoDS_Edge& EfromW, const TopoDS_Edge& EonFace);

  Standard_EXPORT void BindAll();

  bool IsDone() const;

  Standard_EXPORT void InitEdgeIterator();

  Standard_EXPORT bool MoreEdge();

  Standard_EXPORT TopoDS_Edge Edge();

  Standard_EXPORT TopoDS_Face OnFace();

  Standard_EXPORT bool OnEdge(TopoDS_Edge& E);

  Standard_EXPORT void NextEdge();

  Standard_EXPORT bool OnVertex(const TopoDS_Vertex& Vwire, TopoDS_Vertex& Vshape);

  Standard_EXPORT bool OnEdge(const TopoDS_Vertex& V, TopoDS_Edge& E, double& P);

  Standard_EXPORT bool OnEdge(const TopoDS_Vertex& V,
                              const TopoDS_Edge&   EdgeFrom,
                              TopoDS_Edge&         E,
                              double&              P);

  bool IsFaceWithSection(const TopoDS_Shape& aFace) const;

  DEFINE_STANDARD_RTTIEXT(LocOpe_WiresOnShape, Standard_Transient)

private:
  TopoDS_Shape                                                                    myShape;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMapEF;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>                   myFacesWithSection;
  bool                                                                     myCheckInterior;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
  bool                                                                     myDone;
  int                                                                      myIndex;
};

inline void LocOpe_WiresOnShape::SetCheckInterior(const bool ToCheckInterior)
{
  myCheckInterior = ToCheckInterior;
}

inline bool LocOpe_WiresOnShape::IsDone() const
{
  return myDone;
}

inline bool LocOpe_WiresOnShape::IsFaceWithSection(const TopoDS_Shape& aFace) const
{
  return (myFacesWithSection.Contains(aFace));
}
