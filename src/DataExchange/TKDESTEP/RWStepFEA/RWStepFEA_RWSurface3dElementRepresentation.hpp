#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_Surface3dElementRepresentation;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for Surface3dElementRepresentation
class RWStepFEA_RWSurface3dElementRepresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWSurface3dElementRepresentation();

  //! Reads Surface3dElementRepresentation
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                data,
    const int                                                  num,
    occ::handle<Interface_Check>&                              ach,
    const occ::handle<StepFEA_Surface3dElementRepresentation>& ent) const;

  //! Writes Surface3dElementRepresentation
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                       SW,
    const occ::handle<StepFEA_Surface3dElementRepresentation>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_Surface3dElementRepresentation>& ent,
                             Interface_EntityIterator&                                  iter) const;
};

