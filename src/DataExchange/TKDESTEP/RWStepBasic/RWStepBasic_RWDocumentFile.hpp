#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_DocumentFile;
class StepData_StepWriter;
class Interface_EntityIterator;

class RWStepBasic_RWDocumentFile
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepBasic_RWDocumentFile();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepBasic_DocumentFile>&  ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                       SW,
                                 const occ::handle<StepBasic_DocumentFile>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepBasic_DocumentFile>& ent,
                             Interface_EntityIterator&                  iter) const;
};
