#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_GeneralLib.hpp>
#include <Interface_ReaderLib.hpp>
#include <Interface_FileReaderTool.hpp>
#include <Standard_Integer.hpp>
class StepData_FileRecognizer;
class StepData_StepReaderData;
class StepData_Protocol;
class Interface_Check;
class Standard_Transient;
class Interface_InterfaceModel;

class StepData_StepReaderTool : public Interface_FileReaderTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_StepReaderTool(const occ::handle<StepData_StepReaderData>& reader,
                                          const occ::handle<StepData_Protocol>&       protocol);

  Standard_EXPORT void Prepare(const bool optimize = true);

  Standard_EXPORT void Prepare(const occ::handle<StepData_FileRecognizer>& reco,
                               const bool                                  optimize = true);

  Standard_EXPORT bool Recognize(const int                        num,
                                 occ::handle<Interface_Check>&    ach,
                                 occ::handle<Standard_Transient>& ent) override;

  Standard_EXPORT void PrepareHeader(const occ::handle<StepData_FileRecognizer>& reco);

  Standard_EXPORT void BeginRead(const occ::handle<Interface_InterfaceModel>& amodel) override;

  Standard_EXPORT bool AnalyseRecord(const int                              num,
                                     const occ::handle<Standard_Transient>& anent,
                                     occ::handle<Interface_Check>&          acheck) override;

  Standard_EXPORT void EndRead(const occ::handle<Interface_InterfaceModel>& amodel) override;

private:
  occ::handle<StepData_FileRecognizer> thereco;
  Interface_GeneralLib                 theglib;
  Interface_ReaderLib                  therlib;
};
