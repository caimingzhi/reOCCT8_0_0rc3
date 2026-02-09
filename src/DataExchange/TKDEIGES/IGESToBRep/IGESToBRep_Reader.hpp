#pragma once

#include <Message_ProgressRange.hpp>
#include <ShapeProcess.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

struct DE_ShapeFixParameters;
class IGESData_IGESModel;
class IGESToBRep_Actor;
class Transfer_TransientProcess;
class TopoDS_Shape;

class IGESToBRep_Reader
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT IGESToBRep_Reader();

  Standard_EXPORT int LoadFile(const char* filename);

  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  Standard_EXPORT occ::handle<IGESData_IGESModel> Model() const;

  Standard_EXPORT void SetTransientProcess(const occ::handle<Transfer_TransientProcess>& TP);

  Standard_EXPORT occ::handle<Transfer_TransientProcess> TransientProcess() const;

  Standard_EXPORT occ::handle<IGESToBRep_Actor> Actor() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT bool Check(const bool withprint) const;

  Standard_EXPORT void TransferRoots(
    const bool                   onlyvisible = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const int                    num,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double UsedTolerance() const;

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT TopoDS_Shape Shape(const int num = 1) const;

  Standard_EXPORT TopoDS_Shape OneShape() const;

  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  inline const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const
  {
    return myShapeProcParams;
  }

  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  inline const ShapeProcess::OperationsFlags& GetShapeProcessFlags() const
  {
    return myShapeProcFlags.first;
  }

private:
  void InitializeMissingParameters();

private:
  occ::handle<IGESData_IGESModel>        theModel;
  bool                                   theDone;
  NCollection_Sequence<TopoDS_Shape>     theShapes;
  occ::handle<IGESToBRep_Actor>          theActor;
  occ::handle<Transfer_TransientProcess> theProc;

  XSAlgo_ShapeProcessor::ParameterMap    myShapeProcParams;
  XSAlgo_ShapeProcessor::ProcessingFlags myShapeProcFlags;
};
