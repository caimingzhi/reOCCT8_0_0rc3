#pragma once

#include <ShapeProcess.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <DESTEP_Parameters.hpp>
#include <STEPControl_StepModelType.hpp>
#include <Standard_Integer.hpp>
#include <Message_ProgressRange.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

#include <unordered_map>

struct DE_ShapeFixParameters;
class XSControl_WorkSession;
class StepData_StepModel;
class TopoDS_Shape;
class Transfer_ActorOfFinderProcess;

class STEPControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPControl_Writer();

  Standard_EXPORT STEPControl_Writer(const occ::handle<XSControl_WorkSession>& WS,
                                     const bool                                scratch = true);

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT void UnsetTolerance();

  Standard_EXPORT void SetWS(const occ::handle<XSControl_WorkSession>& WS,
                             const bool                                scratch = true);

  Standard_EXPORT occ::handle<XSControl_WorkSession> WS() const;

  Standard_EXPORT occ::handle<StepData_StepModel> Model(const bool newone = false);

  Standard_EXPORT IFSelect_ReturnStatus
    Transfer(const TopoDS_Shape&             sh,
             const STEPControl_StepModelType mode,
             const bool                      compgraph   = true,
             const Message_ProgressRange&    theProgress = Message_ProgressRange());

  Standard_EXPORT IFSelect_ReturnStatus
    Transfer(const TopoDS_Shape&             sh,
             const STEPControl_StepModelType mode,
             const DESTEP_Parameters&        theParams,
             const bool                      compgraph   = true,
             const Message_ProgressRange&    theProgress = Message_ProgressRange());

  Standard_EXPORT IFSelect_ReturnStatus Write(const char* theFileName);

  Standard_EXPORT IFSelect_ReturnStatus WriteStream(std::ostream& theOStream);

  Standard_EXPORT void PrintStatsTransfer(const int what, const int mode = 0) const;

  Standard_EXPORT void CleanDuplicateEntities();

  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  Standard_EXPORT const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const;

  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  Standard_EXPORT const XSAlgo_ShapeProcessor::ProcessingFlags& GetShapeProcessFlags() const;

private:
  occ::handle<Transfer_ActorOfFinderProcess> GetActor() const;

  void InitializeMissingParameters();

private:
  occ::handle<XSControl_WorkSession> thesession;
};
