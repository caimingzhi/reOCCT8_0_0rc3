#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Compound.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;

class ShapeAnalysis_FreeBounds
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_FreeBounds();

  Standard_EXPORT ShapeAnalysis_FreeBounds(const TopoDS_Shape& shape,
                                           const double        toler,
                                           const bool          splitclosed = false,
                                           const bool          splitopen   = true);

  Standard_EXPORT ShapeAnalysis_FreeBounds(const TopoDS_Shape& shape,
                                           const bool          splitclosed        = false,
                                           const bool          splitopen          = true,
                                           const bool          checkinternaledges = false);

  const TopoDS_Compound& GetClosedWires() const;

  const TopoDS_Compound& GetOpenWires() const;

  Standard_EXPORT static void ConnectEdgesToWires(
    occ::handle<NCollection_HSequence<TopoDS_Shape>>& edges,
    const double                                      toler,
    const bool                                        shared,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>& wires);

  Standard_EXPORT static void ConnectWiresToWires(
    occ::handle<NCollection_HSequence<TopoDS_Shape>>& iwires,
    const double                                      toler,
    const bool                                        shared,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>& owires);

  Standard_EXPORT static void ConnectWiresToWires(
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&                         iwires,
    const double                                                              toler,
    const bool                                                                shared,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&                         owires,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& vertices);

  Standard_EXPORT static void SplitWires(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& wires,
    const double                                            toler,
    const bool                                              shared,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       closed,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       open);

  Standard_EXPORT static void DispatchWires(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& wires,
    TopoDS_Compound&                                        closed,
    TopoDS_Compound&                                        open);

private:
  Standard_EXPORT void SplitWires();

  TopoDS_Compound myWires;
  TopoDS_Compound myEdges;
  double          myTolerance;
  bool            myShared;
  bool            mySplitClosed;
  bool            mySplitOpen;
};

inline const TopoDS_Compound& ShapeAnalysis_FreeBounds::GetClosedWires() const
{
  return myWires;
}

inline const TopoDS_Compound& ShapeAnalysis_FreeBounds::GetOpenWires() const
{
  return myEdges;
}
