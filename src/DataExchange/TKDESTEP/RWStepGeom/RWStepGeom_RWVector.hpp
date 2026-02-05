#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepGeom_Vector;
class StepData_StepWriter;
class Interface_EntityIterator;
class Interface_ShareTool;

//! Read & Write Module for Vector
//! Check added by CKY , 7-OCT-1996
class RWStepGeom_RWVector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepGeom_RWVector();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepGeom_Vector>&         ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                SW,
                                 const occ::handle<StepGeom_Vector>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepGeom_Vector>& ent,
                             Interface_EntityIterator&           iter) const;

  Standard_HIDDEN void Check(const occ::handle<StepGeom_Vector>& ent,
                             const Interface_ShareTool&          shares,
                             occ::handle<Interface_Check>&       ach) const;
};
