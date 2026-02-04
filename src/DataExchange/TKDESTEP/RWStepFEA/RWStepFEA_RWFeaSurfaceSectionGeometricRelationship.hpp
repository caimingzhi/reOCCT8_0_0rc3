#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_FeaSurfaceSectionGeometricRelationship;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for FeaSurfaceSectionGeometricRelationship
class RWStepFEA_RWFeaSurfaceSectionGeometricRelationship
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWFeaSurfaceSectionGeometricRelationship();

  //! Reads FeaSurfaceSectionGeometricRelationship
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                        data,
    const int                                                          num,
    occ::handle<Interface_Check>&                                      ach,
    const occ::handle<StepFEA_FeaSurfaceSectionGeometricRelationship>& ent) const;

  //! Writes FeaSurfaceSectionGeometricRelationship
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                               SW,
    const occ::handle<StepFEA_FeaSurfaceSectionGeometricRelationship>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_FeaSurfaceSectionGeometricRelationship>& ent,
                             Interface_EntityIterator& iter) const;
};

