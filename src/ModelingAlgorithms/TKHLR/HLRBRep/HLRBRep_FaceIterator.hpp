#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopAbs_Orientation.hpp>
class HLRAlgo_WiresBlock;
class HLRAlgo_EdgesBlock;
class HLRBRep_FaceData;

class HLRBRep_FaceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_FaceIterator();

  Standard_EXPORT void InitEdge(HLRBRep_FaceData& fd);

  bool MoreEdge() const;

  Standard_EXPORT void NextEdge();

  bool BeginningOfWire() const;

  bool EndOfWire() const;

  void SkipWire();

  occ::handle<HLRAlgo_EdgesBlock> Wire() const;

  int Edge() const;

  TopAbs_Orientation Orientation() const;

  bool OutLine() const;

  bool Internal() const;

  bool Double() const;

  bool IsoLine() const;

private:
  int                             iWire;
  int                             nbWires;
  int                             iEdge;
  int                             nbEdges;
  occ::handle<HLRAlgo_WiresBlock> myWires;
  occ::handle<HLRAlgo_EdgesBlock> myEdges;
};

#include <HLRAlgo_WiresBlock.hpp>
#include <HLRAlgo_EdgesBlock.hpp>

inline bool HLRBRep_FaceIterator::MoreEdge() const
{
  return iWire <= nbWires;
}

inline bool HLRBRep_FaceIterator::BeginningOfWire() const
{
  return iEdge == 1;
}

inline bool HLRBRep_FaceIterator::EndOfWire() const
{
  return iEdge == nbEdges;
}

inline void HLRBRep_FaceIterator::SkipWire()
{
  iEdge = nbEdges;
  NextEdge();
}

inline occ::handle<HLRAlgo_EdgesBlock> HLRBRep_FaceIterator::Wire() const
{
  return myWires->Wire(iWire);
}

inline int HLRBRep_FaceIterator::Edge() const
{
  return myEdges->Edge(iEdge);
}

inline TopAbs_Orientation HLRBRep_FaceIterator::Orientation() const
{
  return myEdges->Orientation(iEdge);
}

inline bool HLRBRep_FaceIterator::OutLine() const
{
  return myEdges->OutLine(iEdge);
}

inline bool HLRBRep_FaceIterator::Internal() const
{
  return myEdges->Internal(iEdge);
}

inline bool HLRBRep_FaceIterator::Double() const
{
  return myEdges->Double(iEdge);
}

inline bool HLRBRep_FaceIterator::IsoLine() const
{
  return myEdges->IsoLine(iEdge);
}
