#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_ParametricCurve3dElementCoordinateDirection;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ParametricCurve3dElementCoordinateDirection
class RWStepFEA_RWParametricCurve3dElementCoordinateDirection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWParametricCurve3dElementCoordinateDirection();

  //! Reads ParametricCurve3dElementCoordinateDirection
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                             data,
    const int                                                               num,
    occ::handle<Interface_Check>&                                           ach,
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& ent) const;

  //! Writes ParametricCurve3dElementCoordinateDirection
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                    SW,
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(
    const occ::handle<StepFEA_ParametricCurve3dElementCoordinateDirection>& ent,
    Interface_EntityIterator&                                               iter) const;
};
