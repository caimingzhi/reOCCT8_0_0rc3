#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Face;
class TopoDS_Shape;

class BOPAlgo_WireEdgeSet
{
public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_WireEdgeSet();
  virtual ~BOPAlgo_WireEdgeSet();

  BOPAlgo_WireEdgeSet(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  void Clear();

  void SetFace(const TopoDS_Face& aF);

  const TopoDS_Face& Face() const;

  void AddStartElement(const TopoDS_Shape& sS);

  const NCollection_List<TopoDS_Shape>& StartElements() const;

  void AddShape(const TopoDS_Shape& sS);

  const NCollection_List<TopoDS_Shape>& Shapes() const;

protected:
  TopoDS_Face                    myFace;
  NCollection_List<TopoDS_Shape> myStartShapes;
  NCollection_List<TopoDS_Shape> myShapes;
};

inline BOPAlgo_WireEdgeSet::BOPAlgo_WireEdgeSet() = default;

inline BOPAlgo_WireEdgeSet::BOPAlgo_WireEdgeSet(
  const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myStartShapes(theAllocator),
      myShapes(theAllocator)
{
}

inline BOPAlgo_WireEdgeSet::~BOPAlgo_WireEdgeSet() = default;

inline void BOPAlgo_WireEdgeSet::Clear()
{
  myStartShapes.Clear();
  myShapes.Clear();
}

inline void BOPAlgo_WireEdgeSet::SetFace(const TopoDS_Face& aF)
{
  myFace = aF;
}

inline const TopoDS_Face& BOPAlgo_WireEdgeSet::Face() const
{
  return myFace;
}

inline void BOPAlgo_WireEdgeSet::AddStartElement(const TopoDS_Shape& aE)
{
  myStartShapes.Append(aE);
}

inline const NCollection_List<TopoDS_Shape>& BOPAlgo_WireEdgeSet::StartElements() const
{
  return myStartShapes;
}

inline void BOPAlgo_WireEdgeSet::AddShape(const TopoDS_Shape& aW)
{
  myShapes.Append(aW);
}

inline const NCollection_List<TopoDS_Shape>& BOPAlgo_WireEdgeSet::Shapes() const
{
  return myShapes;
}
