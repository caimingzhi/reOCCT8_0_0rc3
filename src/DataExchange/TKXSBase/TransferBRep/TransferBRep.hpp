#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
#include <TopAbs_Orientation.hpp>
#include <TransferBRep_TransferResultInfo.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Shape;
class Transfer_Binder;
class Transfer_TransientProcess;
class Standard_Transient;
class Transfer_FinderProcess;
class TransferBRep_ShapeMapper;
class Message_Printer;
class Message_Msg;
class TransferBRep_TransferResultInfo;
class Interface_CheckIterator;
class Interface_InterfaceModel;

class TransferBRep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static TopoDS_Shape ShapeResult(const occ::handle<Transfer_Binder>& binder);

  Standard_EXPORT static TopoDS_Shape ShapeResult(const occ::handle<Transfer_TransientProcess>& TP,
                                                  const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT static void SetShapeResult(const occ::handle<Transfer_TransientProcess>& TP,
                                             const occ::handle<Standard_Transient>&        ent,
                                             const TopoDS_Shape&                           result);

  Standard_EXPORT static occ::handle<NCollection_HSequence<TopoDS_Shape>> Shapes(
    const occ::handle<Transfer_TransientProcess>& TP,
    const bool                                    rootsonly = true);

  Standard_EXPORT static occ::handle<NCollection_HSequence<TopoDS_Shape>> Shapes(
    const occ::handle<Transfer_TransientProcess>&                              TP,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT static TopAbs_Orientation ShapeState(
    const occ::handle<Transfer_FinderProcess>& FP,
    const TopoDS_Shape&                        shape);

  Standard_EXPORT static occ::handle<Transfer_Binder> ResultFromShape(
    const occ::handle<Transfer_FinderProcess>& FP,
    const TopoDS_Shape&                        shape);

  Standard_EXPORT static occ::handle<Standard_Transient> TransientFromShape(
    const occ::handle<Transfer_FinderProcess>& FP,
    const TopoDS_Shape&                        shape);

  Standard_EXPORT static void SetTransientFromShape(const occ::handle<Transfer_FinderProcess>& FP,
                                                    const TopoDS_Shape&                    shape,
                                                    const occ::handle<Standard_Transient>& result);

  Standard_EXPORT static occ::handle<TransferBRep_ShapeMapper> ShapeMapper(
    const occ::handle<Transfer_FinderProcess>& FP,
    const TopoDS_Shape&                        shape);

  Standard_EXPORT static void TransferResultInfo(
    const occ::handle<Transfer_TransientProcess>&                                     TP,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>&        EntityTypes,
    occ::handle<NCollection_HSequence<occ::handle<TransferBRep_TransferResultInfo>>>& InfoSeq);

  Standard_EXPORT static void TransferResultInfo(
    const occ::handle<Transfer_FinderProcess>&                                        FP,
    const occ::handle<NCollection_HSequence<int>>&                                    ShapeTypes,
    occ::handle<NCollection_HSequence<occ::handle<TransferBRep_TransferResultInfo>>>& InfoSeq);

  Standard_EXPORT static void PrintResultInfo(
    const occ::handle<Message_Printer>&                 Printer,
    const Message_Msg&                                  Header,
    const occ::handle<TransferBRep_TransferResultInfo>& ResultInfo,
    const bool                                          printEmpty = true);

  Standard_EXPORT static Interface_CheckIterator BRepCheck(const TopoDS_Shape& shape,
                                                           const int           lev = 1);

  Standard_EXPORT static Interface_CheckIterator ResultCheckList(
    const Interface_CheckIterator&               chl,
    const occ::handle<Transfer_FinderProcess>&   FP,
    const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    Checked(const Interface_CheckIterator& chl, const bool alsoshapes = false);

  Standard_EXPORT static occ::handle<NCollection_HSequence<TopoDS_Shape>> CheckedShapes(
    const Interface_CheckIterator& chl);

  Standard_EXPORT static Interface_CheckIterator CheckObject(
    const Interface_CheckIterator&         chl,
    const occ::handle<Standard_Transient>& obj);
};
