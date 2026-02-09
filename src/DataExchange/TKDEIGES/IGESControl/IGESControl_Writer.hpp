#pragma once

#include <ShapeProcess.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <IGESData_BasicEditor.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <Standard_OStream.hpp>
#include <Message_ProgressRange.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

struct DE_ShapeFixParameters;
class Transfer_FinderProcess;
class IGESData_IGESModel;
class TopoDS_Shape;
class Standard_Transient;
class IGESData_IGESEntity;

class IGESControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT IGESControl_Writer();

  Standard_EXPORT IGESControl_Writer(const char* theUnit, const int theModecr = 0);

  Standard_EXPORT IGESControl_Writer(const occ::handle<IGESData_IGESModel>& theModel,
                                     const int                              theModecr = 0);

  const occ::handle<IGESData_IGESModel>& Model() const { return myModel; }

  const occ::handle<Transfer_FinderProcess>& TransferProcess() const { return myTP; }

  void SetTransferProcess(const occ::handle<Transfer_FinderProcess>& TP) { myTP = TP; }

  Standard_EXPORT bool AddShape(const TopoDS_Shape&          sh,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool AddGeom(const occ::handle<Standard_Transient>& geom);

  Standard_EXPORT bool AddEntity(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT void ComputeModel();

  Standard_EXPORT bool Write(Standard_OStream& S, const bool fnes = false);

  Standard_EXPORT bool Write(const char* file, const bool fnes = false);

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
  occ::handle<Transfer_FinderProcess> myTP;
  occ::handle<IGESData_IGESModel>     myModel;
  IGESData_BasicEditor                myEditor;
  int                                 myWriteMode;
  bool                                myIsComputed;

  XSAlgo_ShapeProcessor::ParameterMap    myShapeProcParams;
  XSAlgo_ShapeProcessor::ProcessingFlags myShapeProcFlags;
};
