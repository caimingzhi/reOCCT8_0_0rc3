#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
#include <Message_ProgressRange.hpp>

class Interface_Protocol;
class Transfer_ActorOfTransientProcess;
class Interface_InterfaceModel;
class Transfer_TransientProcess;
class Interface_CheckIterator;
class TopoDS_Shape;
class Standard_Transient;

class TransferBRep_Reader
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TransferBRep_Reader();

  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& protocol);

  Standard_EXPORT virtual occ::handle<Interface_Protocol> Protocol() const;

  Standard_EXPORT void SetActor(const occ::handle<Transfer_ActorOfTransientProcess>& actor);

  Standard_EXPORT virtual occ::handle<Transfer_ActorOfTransientProcess> Actor() const;

  Standard_EXPORT void SetFileStatus(const int status);

  Standard_EXPORT int FileStatus() const;

  Standard_EXPORT bool FileNotFound() const;

  Standard_EXPORT bool SyntaxError() const;

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT bool CheckStatusModel(const bool withprint) const;

  Standard_EXPORT Interface_CheckIterator CheckListModel() const;

  Standard_EXPORT bool& ModeNewTransfer();

  Standard_EXPORT bool BeginTransfer();

  Standard_EXPORT void EndTransfer();

  Standard_EXPORT virtual void PrepareTransfer();

  Standard_EXPORT virtual void TransferRoots(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual bool Transfer(
    const int                    num,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT virtual void TransferList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> Shapes() const;

  Standard_EXPORT const TopoDS_Shape& Shape(const int num = 1) const;

  Standard_EXPORT TopoDS_Shape ShapeResult(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT TopoDS_Shape OneShape() const;

  Standard_EXPORT int NbTransients() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Transients()
    const;

  Standard_EXPORT occ::handle<Standard_Transient> Transient(const int num = 1) const;

  Standard_EXPORT bool CheckStatusResult(const bool withprints) const;

  Standard_EXPORT Interface_CheckIterator CheckListResult() const;

  Standard_EXPORT occ::handle<Transfer_TransientProcess> TransientProcess() const;

  Standard_EXPORT virtual ~TransferBRep_Reader();

protected:
  bool                                   theDone;
  occ::handle<Transfer_TransientProcess> theProc;

private:
  occ::handle<Interface_Protocol>                                     theProto;
  occ::handle<Transfer_ActorOfTransientProcess>                       theActor;
  occ::handle<Interface_InterfaceModel>                               theModel;
  int                                                                 theFilest;
  bool                                                                theNewpr;
  occ::handle<NCollection_HSequence<TopoDS_Shape>>                    theShapes;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> theTransi;
};
