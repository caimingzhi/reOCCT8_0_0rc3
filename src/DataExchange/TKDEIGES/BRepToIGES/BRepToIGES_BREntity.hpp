#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Message_ProgressRange.hpp>

class IGESData_IGESModel;
class Transfer_FinderProcess;
class IGESData_IGESEntity;
class TopoDS_Shape;
class Standard_Transient;

class BRepToIGES_BREntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepToIGES_BREntity();

  Standard_EXPORT void Init();

  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  Standard_EXPORT occ::handle<IGESData_IGESModel> GetModel() const;

  Standard_EXPORT double GetUnit() const;

  Standard_EXPORT void SetTransferProcess(const occ::handle<Transfer_FinderProcess>& TP);

  Standard_EXPORT occ::handle<Transfer_FinderProcess> GetTransferProcess() const;

  Standard_EXPORT virtual occ::handle<IGESData_IGESEntity> TransferShape(
    const TopoDS_Shape&          start,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void AddFail(const TopoDS_Shape& start, const char* amess);

  Standard_EXPORT void AddWarning(const TopoDS_Shape& start, const char* amess);

  Standard_EXPORT void AddFail(const occ::handle<Standard_Transient>& start, const char* amess);

  Standard_EXPORT void AddWarning(const occ::handle<Standard_Transient>& start, const char* amess);

  Standard_EXPORT bool HasShapeResult(const TopoDS_Shape& start) const;

  Standard_EXPORT occ::handle<Standard_Transient> GetShapeResult(const TopoDS_Shape& start) const;

  Standard_EXPORT void SetShapeResult(const TopoDS_Shape&                    start,
                                      const occ::handle<Standard_Transient>& result);

  Standard_EXPORT bool HasShapeResult(const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT occ::handle<Standard_Transient> GetShapeResult(
    const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT void SetShapeResult(const occ::handle<Standard_Transient>& start,
                                      const occ::handle<Standard_Transient>& result);

  Standard_EXPORT bool GetConvertSurfaceMode() const;

  Standard_EXPORT bool GetPCurveMode() const;

  Standard_EXPORT virtual ~BRepToIGES_BREntity();

private:
  occ::handle<IGESData_IGESModel>     TheModel;
  double                              TheUnitFactor;
  bool                                myConvSurface;
  bool                                myPCurveMode;
  occ::handle<Transfer_FinderProcess> TheMap;
};
