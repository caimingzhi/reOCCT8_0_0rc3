#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_GeneralModule.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_EntityIterator;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;

//! Specific features for General Services adapted to STEP
class StepData_GeneralModule : public Interface_GeneralModule
{

public:
  //! Specific filling of the list of Entities shared by an Entity
  //! <ent>. Can use the internal utility method Share, below
  Standard_EXPORT void FillSharedCase(const int                              casenum,
                                      const occ::handle<Standard_Transient>& ent,
                                      Interface_EntityIterator& iter) const override = 0;

  //! Specific Checking of an Entity <ent>
  Standard_EXPORT void CheckCase(const int                              casenum,
                                 const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             shares,
                                 occ::handle<Interface_Check>&          ach) const override = 0;

  //! Specific Copy ("Deep") from <entfrom> to <entto> (same type)
  //! by using a TransferControl which provides its working Map.
  //! Use method Transferred from TransferControl to work
  //! Specific Copying of Implied References
  //! A Default is provided which does nothing (must current case !)
  //! Already copied references (by CopyFrom) must remain unchanged
  //! Use method Search from TransferControl to work
  Standard_EXPORT void CopyCase(const int                              casenum,
                                const occ::handle<Standard_Transient>& entfrom,
                                const occ::handle<Standard_Transient>& entto,
                                Interface_CopyTool&                    TC) const override = 0;

  DEFINE_STANDARD_RTTIEXT(StepData_GeneralModule, Interface_GeneralModule)
};
