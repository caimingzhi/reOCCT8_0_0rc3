#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopOpeBRepBuild_LoopSet.hpp>
#include <TopOpeBRepBuild_BlockIterator.hpp>
#include <TopOpeBRepBuild_BlockBuilder.hpp>
#include <TopOpeBRepBuild_FaceAreaBuilder.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
class TopOpeBRepBuild_WireEdgeSet;
class TopoDS_Shape;
class TopOpeBRepBuild_ShapeSet;

class TopOpeBRepBuild_FaceBuilder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_FaceBuilder();

  //! Create a FaceBuilder to build the faces on
  //! the shapes (wires, blocks of edge) described by <LS>.
  Standard_EXPORT TopOpeBRepBuild_FaceBuilder(TopOpeBRepBuild_WireEdgeSet& ES,
                                              const TopoDS_Shape&          F,
                                              const bool                   ForceClass = false);

  Standard_EXPORT void InitFaceBuilder(TopOpeBRepBuild_WireEdgeSet& ES,
                                       const TopoDS_Shape&          F,
                                       const bool                   ForceClass);

  //! Removes are non 3d-closed wires.
  //! Fills up maps <mapVVsameG> and <mapVon1Edge>, in order to
  //! correct 3d-closed but unclosed (topologic connexity) wires.
  //! modifies myBlockBuilder
  Standard_EXPORT void DetectUnclosedWire(
    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapVVsameG,
    NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapVon1Edge);

  //! Using the given maps, change the topology of the 3d-closed
  //! wires, in order to get closed wires.
  Standard_EXPORT void CorrectGclosedWire(
    const NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapVVref,
    const NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
      mapVon1Edge);

  //! Removes edges appearing twice (FORWARD,REVERSED) with a bounding
  //! vertex not connected to any other edge.
  //! mapE contains edges found.
  //! modifies myBlockBuilder.
  Standard_EXPORT void DetectPseudoInternalEdge(
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& mapE);

  //! return myFace
  Standard_EXPORT const TopoDS_Shape& Face() const;

  Standard_EXPORT int InitFace();

  Standard_EXPORT bool MoreFace() const;

  Standard_EXPORT void NextFace();

  Standard_EXPORT int InitWire();

  Standard_EXPORT bool MoreWire() const;

  Standard_EXPORT void NextWire();

  Standard_EXPORT bool IsOldWire() const;

  //! Returns current wire
  //! This wire may be :
  //! * an old wire OldWire(), which has not been reconstructed;
  //! * a new wire made of edges described by ...NewEdge() methods.
  Standard_EXPORT const TopoDS_Shape& OldWire() const;

  //! Iterates on myBlockIterator until finding a valid element
  Standard_EXPORT void FindNextValidElement();

  Standard_EXPORT int InitEdge();

  Standard_EXPORT bool MoreEdge() const;

  Standard_EXPORT void NextEdge();

  //! Returns current new edge of current new wire.
  Standard_EXPORT const TopoDS_Shape& Edge() const;

  Standard_EXPORT int EdgeConnexity(const TopoDS_Shape& E) const;

  Standard_EXPORT int AddEdgeWire(const TopoDS_Shape& E, TopoDS_Shape& W) const;

private:
  Standard_EXPORT void MakeLoops(TopOpeBRepBuild_ShapeSet& SS);

  TopoDS_Face                                                     myFace;
  TopOpeBRepBuild_LoopSet                                         myLoopSet;
  TopOpeBRepBuild_BlockIterator                                   myBlockIterator;
  TopOpeBRepBuild_BlockBuilder                                    myBlockBuilder;
  TopOpeBRepBuild_FaceAreaBuilder                                 myFaceAreaBuilder;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> myMOSI;
};
