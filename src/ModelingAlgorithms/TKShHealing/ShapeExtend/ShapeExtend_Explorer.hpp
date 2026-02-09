#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;

class ShapeExtend_Explorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeExtend_Explorer();

  Standard_EXPORT TopoDS_Shape
    CompoundFromSeq(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqval) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> SeqFromCompound(
    const TopoDS_Shape& comp,
    const bool          expcomp) const;

  Standard_EXPORT void ListFromSeq(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqval,
                                   NCollection_List<TopoDS_Shape>&                         lisval,
                                   const bool clear = true) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> SeqFromList(
    const NCollection_List<TopoDS_Shape>& lisval) const;

  Standard_EXPORT TopAbs_ShapeEnum ShapeType(const TopoDS_Shape& shape, const bool compound) const;

  Standard_EXPORT TopoDS_Shape SortedCompound(const TopoDS_Shape&    shape,
                                              const TopAbs_ShapeEnum type,
                                              const bool             explore,
                                              const bool             compound) const;

  Standard_EXPORT void DispatchList(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& list,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       vertices,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       edges,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       wires,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       faces,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       shells,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       solids,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       compsols,
    occ::handle<NCollection_HSequence<TopoDS_Shape>>&       compounds) const;
};
