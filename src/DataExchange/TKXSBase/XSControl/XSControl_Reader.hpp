#pragma once

#include <DE_ShapeFixParameters.hpp>
#include <ShapeProcess.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_CString.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <IFSelect_PrintCount.hpp>
#include <Message_ProgressRange.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

class XSControl_WorkSession;
class Interface_InterfaceModel;
class Standard_Transient;
class Transfer_ActorOfTransientProcess;
class TopoDS_Shape;

class XSControl_Reader
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XSControl_Reader();

  Standard_EXPORT XSControl_Reader(const char* norm);

  Standard_EXPORT XSControl_Reader(const occ::handle<XSControl_WorkSession>& WS,
                                   const bool                                scratch = true);

  virtual ~XSControl_Reader() = default;

  Standard_EXPORT bool SetNorm(const char* norm);

  Standard_EXPORT void SetWS(const occ::handle<XSControl_WorkSession>& WS,
                             const bool                                scratch = true);

  Standard_EXPORT occ::handle<XSControl_WorkSession> WS() const;

  Standard_EXPORT virtual IFSelect_ReturnStatus ReadFile(const char* filename);

  Standard_EXPORT virtual IFSelect_ReturnStatus ReadStream(const char*   theName,
                                                           std::istream& theIStream);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> GiveList(
    const char* first  = "",
    const char* second = "");

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> GiveList(
    const char*                            first,
    const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT virtual int NbRootsForTransfer();

  Standard_EXPORT occ::handle<Standard_Transient> RootForTransfer(const int num = 1);

  Standard_EXPORT bool TransferOneRoot(
    const int                    num         = 1,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool TransferOne(
    const int                    num,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool TransferEntity(
    const occ::handle<Standard_Transient>& start,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  Standard_EXPORT int TransferList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT int TransferRoots(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void ClearShapes();

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT TopoDS_Shape Shape(const int num = 1) const;

  Standard_EXPORT TopoDS_Shape OneShape() const;

  Standard_EXPORT void PrintCheckLoad(const bool failsonly, const IFSelect_PrintCount mode) const;

  Standard_EXPORT void PrintCheckLoad(Standard_OStream&         theStream,
                                      const bool                failsonly,
                                      const IFSelect_PrintCount mode) const;

  Standard_EXPORT void PrintCheckTransfer(const bool                failsonly,
                                          const IFSelect_PrintCount mode) const;

  Standard_EXPORT void PrintCheckTransfer(Standard_OStream&         theStream,
                                          const bool                failsonly,
                                          const IFSelect_PrintCount mode) const;

  Standard_EXPORT void PrintStatsTransfer(const int what, const int mode = 0) const;

  Standard_EXPORT void PrintStatsTransfer(Standard_OStream& theStream,
                                          const int         what,
                                          const int         mode = 0) const;

  Standard_EXPORT void GetStatsTransfer(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    int&                                                                       nbMapped,
    int&                                                                       nbWithResult,
    int&                                                                       nbWithFail) const;

  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  Standard_EXPORT const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const;

  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  Standard_EXPORT const XSAlgo_ShapeProcessor::ProcessingFlags& GetShapeProcessFlags() const;

protected:
  Standard_EXPORT NCollection_Sequence<TopoDS_Shape>& Shapes();

  virtual DE_ShapeFixParameters GetDefaultShapeFixParameters() const
  {
    return DE_ShapeFixParameters();
  }

  virtual ShapeProcess::OperationsFlags GetDefaultShapeProcessFlags() const
  {
    return ShapeProcess::OperationsFlags();
  }

private:
  occ::handle<Transfer_ActorOfTransientProcess> GetActor() const;

  void InitializeMissingParameters();

protected:
  bool                                                  therootsta;
  NCollection_Sequence<occ::handle<Standard_Transient>> theroots;

private:
  occ::handle<XSControl_WorkSession> thesession;
  NCollection_Sequence<TopoDS_Shape> theshapes;
};
