#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepVisual_ExternallyDefinedCurveFont;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ExternallyDefinedCurveFont
class RWStepVisual_RWExternallyDefinedCurveFont
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepVisual_RWExternallyDefinedCurveFont();

  //! Reads ExternallyDefinedCurveFont
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&               data,
    const int                                                 num,
    occ::handle<Interface_Check>&                             ach,
    const occ::handle<StepVisual_ExternallyDefinedCurveFont>& ent) const;

  //! Writes ExternallyDefinedCurveFont
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                      SW,
    const occ::handle<StepVisual_ExternallyDefinedCurveFont>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepVisual_ExternallyDefinedCurveFont>& ent,
                             Interface_EntityIterator&                                 iter) const;
};

