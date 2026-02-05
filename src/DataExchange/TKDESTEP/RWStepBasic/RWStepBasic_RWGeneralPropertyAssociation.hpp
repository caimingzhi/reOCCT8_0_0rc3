#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_GeneralProperty;
class StepData_StepWriter;
class Interface_EntityIterator;

class StepBasic_GeneralPropertyAssociation;

//! Read & Write tool for GeneralPropertyAssociation
class RWStepBasic_RWGeneralPropertyAssociation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWGeneralPropertyAssociation();

  //! Reads GeneralPropertyAssociation
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&              theData,
    const int                                                theNum,
    occ::handle<Interface_Check>&                            theAch,
    const occ::handle<StepBasic_GeneralPropertyAssociation>& theEnt) const;

  //! Writes GeneralPropertyAssociation
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                     theSW,
    const occ::handle<StepBasic_GeneralPropertyAssociation>& theEnt) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_GeneralPropertyAssociation>& theEnt,
                             Interface_EntityIterator& theIter) const;
};
