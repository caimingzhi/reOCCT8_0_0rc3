#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_CharacterizedObject;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for CharacterizedObject
class RWStepBasic_RWCharacterizedObject
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWCharacterizedObject();

  //! Reads CharacterizedObject
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&       data,
                                const int                                         num,
                                occ::handle<Interface_Check>&                     ach,
                                const occ::handle<StepBasic_CharacterizedObject>& ent) const;

  //! Writes CharacterizedObject
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                              SW,
                                 const occ::handle<StepBasic_CharacterizedObject>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_CharacterizedObject>& ent,
                             Interface_EntityIterator&                         iter) const;
};
