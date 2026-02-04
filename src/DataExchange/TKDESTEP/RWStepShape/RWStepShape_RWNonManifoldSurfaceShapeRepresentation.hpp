#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_NonManifoldSurfaceShapeRepresentation;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for NonManifoldSurfaceShapeRepresentation
class RWStepShape_RWNonManifoldSurfaceShapeRepresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepShape_RWNonManifoldSurfaceShapeRepresentation();

  //! Reads NonManifoldSurfaceShapeRepresentation
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                         data,
    const int                                                           num,
    occ::handle<Interface_Check>&                                       ach,
    const occ::handle<StepShape_NonManifoldSurfaceShapeRepresentation>& ent) const;

  //! Writes NonManifoldSurfaceShapeRepresentation
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                SW,
    const occ::handle<StepShape_NonManifoldSurfaceShapeRepresentation>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(
    const occ::handle<StepShape_NonManifoldSurfaceShapeRepresentation>& ent,
    Interface_EntityIterator&                                           iter) const;
};

