#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <BRepOffset_Interval.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <ChFiDS_TypeOfConcavity.hpp>
#include <NCollection_Map.hpp>

#include <Message_ProgressRange.hpp>

class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Face;
class TopoDS_Compound;

class BRepOffset_Analyse
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT BRepOffset_Analyse();

  Standard_EXPORT BRepOffset_Analyse(const TopoDS_Shape& theS, const double theAngle);

public:
  Standard_EXPORT void Perform(const TopoDS_Shape&          theS,
                               const double                 theAngle,
                               const Message_ProgressRange& theRange = Message_ProgressRange());

public:
  bool IsDone() const { return myDone; }

  Standard_EXPORT const NCollection_List<BRepOffset_Interval>& Type(const TopoDS_Edge& theE) const;

  Standard_EXPORT void Edges(const TopoDS_Vertex&            theV,
                             const ChFiDS_TypeOfConcavity    theType,
                             NCollection_List<TopoDS_Shape>& theL) const;

  Standard_EXPORT void Edges(const TopoDS_Face&              theF,
                             const ChFiDS_TypeOfConcavity    theType,
                             NCollection_List<TopoDS_Shape>& theL) const;

  Standard_EXPORT void TangentEdges(const TopoDS_Edge&              theEdge,
                                    const TopoDS_Vertex&            theVertex,
                                    NCollection_List<TopoDS_Shape>& theEdges) const;

  bool HasAncestor(const TopoDS_Shape& theS) const { return myAncestors.Contains(theS); }

  const NCollection_List<TopoDS_Shape>& Ancestors(const TopoDS_Shape& theS) const
  {
    return myAncestors.FindFromKey(theS);
  }

  Standard_EXPORT void Explode(NCollection_List<TopoDS_Shape>& theL,
                               const ChFiDS_TypeOfConcavity    theType) const;

  Standard_EXPORT void Explode(NCollection_List<TopoDS_Shape>& theL,
                               const ChFiDS_TypeOfConcavity    theType1,
                               const ChFiDS_TypeOfConcavity    theType2) const;

  Standard_EXPORT void AddFaces(const TopoDS_Face&                                      theFace,
                                TopoDS_Compound&                                        theCo,
                                NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap,
                                const ChFiDS_TypeOfConcavity theType) const;

  Standard_EXPORT void AddFaces(const TopoDS_Face&                                      theFace,
                                TopoDS_Compound&                                        theCo,
                                NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMap,
                                const ChFiDS_TypeOfConcavity                            theType1,
                                const ChFiDS_TypeOfConcavity theType2) const;

  void SetOffsetValue(const double theOffset) { myOffset = theOffset; }

  void SetFaceOffsetMap(
    const NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher>& theMap)
  {
    myFaceOffsetMap = theMap;
  }

  const NCollection_List<TopoDS_Shape>& NewFaces() const { return myNewFaces; }

  Standard_EXPORT TopoDS_Shape Generated(const TopoDS_Shape& theS) const;

  bool HasGenerated(const TopoDS_Shape& theS) const { return myGenerated.Seek(theS) != nullptr; }

  Standard_EXPORT const TopoDS_Edge& EdgeReplacement(const TopoDS_Face& theFace,
                                                     const TopoDS_Edge& theEdge) const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>* Descendants(
    const TopoDS_Shape& theS,
    const bool          theUpdate = false) const;

public:
  Standard_EXPORT void Clear();

private:
  Standard_EXPORT void TreatTangentFaces(const NCollection_List<TopoDS_Shape>& theEdges,
                                         const Message_ProgressRange&          theRange);

private:
  TopoDS_Shape myShape;
  double       myAngle;

  double                                                             myOffset;
  NCollection_DataMap<TopoDS_Shape, double, TopTools_ShapeMapHasher> myFaceOffsetMap;

  bool myDone;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<BRepOffset_Interval>, TopTools_ShapeMapHasher>
    myMapEdgeType;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myAncestors;
  NCollection_DataMap<TopoDS_Shape,
                      NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>,
                      TopTools_ShapeMapHasher>
    myReplacement;
  mutable NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myDescendants;

  NCollection_List<TopoDS_Shape> myNewFaces;

  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myGenerated;
};
