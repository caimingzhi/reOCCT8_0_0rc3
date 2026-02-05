#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepShape_EdgeCurve;
class StepData_StepWriter;
class Interface_EntityIterator;
class Interface_ShareTool;

//! Read & Write Module for EdgeCurve
//! Check added by CKY , 7-OCT-1996
class RWStepShape_RWEdgeCurve
{
public:
  DEFINE_STANDARD_ALLOC

public:
  RWStepShape_RWEdgeCurve() = default;

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& theStepData,
                                const int                                   theRecordID,
                                occ::handle<Interface_Check>&               theMessageTool,
                                const occ::handle<StepShape_EdgeCurve>&     theEdgeCurve) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                    theStepWriter,
                                 const occ::handle<StepShape_EdgeCurve>& theEdgeCurve) const;

  Standard_HIDDEN void Share(const occ::handle<StepShape_EdgeCurve>& theEdgeCurve,
                             Interface_EntityIterator&               theSharedEntitiesIt) const;

  Standard_HIDDEN void Check(const occ::handle<StepShape_EdgeCurve>& theEdgeCurve,
                             const Interface_ShareTool&              theShareTool,
                             occ::handle<Interface_Check>&           theMessageTool) const;
};
