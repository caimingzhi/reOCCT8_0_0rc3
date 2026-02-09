#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Interface_CheckStatus.hpp>
#include <Message_ProgressRange.hpp>

class XSControl_Controller;
class Interface_InterfaceModel;
class Interface_HGraph;
class Transfer_ActorOfTransientProcess;
class Transfer_TransientProcess;
class Transfer_ResultFromModel;
class TopoDS_Shape;
class Interface_CheckIterator;
class Interface_Graph;

class XSControl_TransferReader : public Standard_Transient
{
public:
  XSControl_TransferReader() = default;

  Standard_EXPORT void SetController(const occ::handle<XSControl_Controller>& theControl);

  void SetActor(const occ::handle<Transfer_ActorOfTransientProcess>& theActor)
  {
    myActor = theActor;
  }

  Standard_EXPORT occ::handle<Transfer_ActorOfTransientProcess> Actor();

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& theModel);

  Standard_EXPORT void SetGraph(const occ::handle<Interface_HGraph>& theGraph);

  const occ::handle<Interface_InterfaceModel>& Model() const { return myModel; }

  Standard_EXPORT void SetContext(const char*                            theName,
                                  const occ::handle<Standard_Transient>& theCtx);

  Standard_EXPORT bool GetContext(const char*                       theName,
                                  const occ::handle<Standard_Type>& theType,
                                  occ::handle<Standard_Transient>&  theCtx) const;

  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>& Context()
  {
    return myContext;
  }

  void SetFileName(const char* theName) { myFileName = theName; }

  const char* FileName() const { return myFileName.ToCString(); }

  Standard_EXPORT void Clear(const int theMode);

  const occ::handle<Transfer_TransientProcess>& TransientProcess() const { return myTP; }

  void SetTransientProcess(const occ::handle<Transfer_TransientProcess>& theTP) { myTP = theTP; }

  Standard_EXPORT bool RecordResult(const occ::handle<Standard_Transient>& theEnt);

  Standard_EXPORT bool IsRecorded(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT bool HasResult(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> RecordedList()
    const;

  Standard_EXPORT bool Skip(const occ::handle<Standard_Transient>& theEnt);

  Standard_EXPORT bool IsSkipped(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT bool IsMarked(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT occ::handle<Transfer_ResultFromModel> FinalResult(
    const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT const char* FinalEntityLabel(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT int FinalEntityNumber(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT occ::handle<Transfer_ResultFromModel> ResultFromNumber(const int theNum) const;

  Standard_EXPORT occ::handle<Standard_Transient> TransientResult(
    const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT TopoDS_Shape ShapeResult(const occ::handle<Standard_Transient>& theEnt) const;

  Standard_EXPORT bool ClearResult(const occ::handle<Standard_Transient>& theEnt,
                                   const int                              theMode);

  Standard_EXPORT occ::handle<Standard_Transient> EntityFromResult(
    const occ::handle<Standard_Transient>& theRes,
    const int                              theMode = 0) const;

  Standard_EXPORT occ::handle<Standard_Transient> EntityFromShapeResult(
    const TopoDS_Shape& theRes,
    const int           theMode = 0) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    EntitiesFromShapeList(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& theRes,
                          const int theMode = 0) const;

  Standard_EXPORT Interface_CheckIterator CheckList(const occ::handle<Standard_Transient>& theEnt,
                                                    const int theLevel = 0) const;

  Standard_EXPORT bool HasChecks(const occ::handle<Standard_Transient>& theEnt,
                                 const bool                             FailsOnly) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> CheckedList(
    const occ::handle<Standard_Transient>& theEnt,
    const Interface_CheckStatus            WithCheck = Interface_CheckAny,
    const bool                             theResult = true) const;

  Standard_EXPORT bool BeginTransfer();

  Standard_EXPORT bool Recognize(const occ::handle<Standard_Transient>& theEnt);

  Standard_EXPORT int TransferOne(
    const occ::handle<Standard_Transient>& theEnt,
    const bool                             theRec      = true,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  Standard_EXPORT int TransferList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theList,
    const bool                                                                 theRec = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT int TransferRoots(
    const Interface_Graph&       theGraph,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void TransferClear(const occ::handle<Standard_Transient>& theEnt,
                                     const int                              theLevel = 0);

  Standard_EXPORT void PrintStats(Standard_OStream& theStream,
                                  const int         theWhat,
                                  const int         theMode = 0) const;

  Standard_EXPORT Interface_CheckIterator LastCheckList() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  LastTransferList(const bool theRoots) const;

  Standard_EXPORT const occ::handle<NCollection_HSequence<TopoDS_Shape>>& ShapeResultList(
    const bool theRec);

  Standard_EXPORT static void PrintStatsProcess(const occ::handle<Transfer_TransientProcess>& theTP,
                                                const int theWhat,
                                                const int theMode = 0);

  Standard_EXPORT static void PrintStatsOnList(
    const occ::handle<Transfer_TransientProcess>&                              theTP,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theList,
    const int                                                                  theWhat,
    const int                                                                  theMode = 0);

  DEFINE_STANDARD_RTTIEXT(XSControl_TransferReader, Standard_Transient)

private:
  occ::handle<XSControl_Controller>                                             myController;
  TCollection_AsciiString                                                       myFileName;
  occ::handle<Interface_InterfaceModel>                                         myModel;
  occ::handle<Interface_HGraph>                                                 myGraph;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> myContext;
  occ::handle<Transfer_ActorOfTransientProcess>                                 myActor;
  occ::handle<Transfer_TransientProcess>                                        myTP;
  NCollection_DataMap<int, occ::handle<Standard_Transient>>                     myResults;
  occ::handle<NCollection_HSequence<TopoDS_Shape>>                              myShapeResult;
};
