#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_AlignedCurve3dElementCoordinateSystem;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for AlignedCurve3dElementCoordinateSystem
class RWStepFEA_RWAlignedCurve3dElementCoordinateSystem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWAlignedCurve3dElementCoordinateSystem();

  //! Reads AlignedCurve3dElementCoordinateSystem
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                       data,
    const int                                                         num,
    occ::handle<Interface_Check>&                                     ach,
    const occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>& ent) const;

  //! Writes AlignedCurve3dElementCoordinateSystem
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                              SW,
    const occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>& ent,
                             Interface_EntityIterator& iter) const;
};

