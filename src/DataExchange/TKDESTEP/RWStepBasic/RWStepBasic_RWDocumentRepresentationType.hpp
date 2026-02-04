#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_DocumentRepresentationType;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for DocumentRepresentationType
class RWStepBasic_RWDocumentRepresentationType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWDocumentRepresentationType();

  //! Reads DocumentRepresentationType
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&              data,
                                const int                                                num,
                                occ::handle<Interface_Check>&                            ach,
                                const occ::handle<StepBasic_DocumentRepresentationType>& ent) const;

  //! Writes DocumentRepresentationType
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                     SW,
    const occ::handle<StepBasic_DocumentRepresentationType>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_DocumentRepresentationType>& ent,
                             Interface_EntityIterator&                                iter) const;
};

