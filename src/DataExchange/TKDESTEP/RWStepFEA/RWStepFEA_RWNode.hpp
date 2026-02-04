#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_Node;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for Node
class RWStepFEA_RWNode
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWNode();

  //! Reads Node
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepFEA_Node>&            ent) const;

  //! Writes Node
  Standard_HIDDEN void WriteStep(StepData_StepWriter&             SW,
                                 const occ::handle<StepFEA_Node>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_Node>& ent,
                             Interface_EntityIterator&        iter) const;
};

