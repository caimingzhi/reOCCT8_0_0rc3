#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_GeneralModule.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_EntityIterator;
class Interface_ShareTool;
class Interface_Check;
class Interface_CopyTool;
class TCollection_HAsciiString;

//! Defines General Services for StepAP214 Entities
//! (Share,Check,Copy; Trace already inherited)
//! Depends (for case numbers) of Protocol from StepAP214
class RWStepAP214_GeneralModule : public StepData_GeneralModule
{

public:
  //! Creates a GeneralModule
  Standard_HIDDEN RWStepAP214_GeneralModule();

  //! Specific filling of the list of Entities shared by an Entity
  //! <ent>, according to a Case Number <CN> (provided by StepAP214
  //! Protocol).
  Standard_HIDDEN void FillSharedCase(const int                              CN,
                                      const occ::handle<Standard_Transient>& ent,
                                      Interface_EntityIterator&              iter) const override;

  //! Specific Checking of an Entity <ent>
  Standard_HIDDEN void CheckCase(const int                              CN,
                                 const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             shares,
                                 occ::handle<Interface_Check>&          ach) const override;

  //! Specific Copy ("Deep") from <entfrom> to <entto> (same type)
  //! by using a CopyTool which provides its working Map.
  //! Use method Transferred from CopyTool to work
  Standard_HIDDEN void CopyCase(const int                              CN,
                                const occ::handle<Standard_Transient>& entfrom,
                                const occ::handle<Standard_Transient>& entto,
                                Interface_CopyTool&                    TC) const override;

  Standard_HIDDEN bool NewVoid(const int CN, occ::handle<Standard_Transient>& ent) const override;

  Standard_HIDDEN virtual int CategoryNumber(const int                              CN,
                                             const occ::handle<Standard_Transient>& ent,
                                             const Interface_ShareTool& shares) const override;

  //! Returns the name of a STEP Entity according to its type
  Standard_HIDDEN virtual occ::handle<TCollection_HAsciiString> Name(
    const int                              CN,
    const occ::handle<Standard_Transient>& ent,
    const Interface_ShareTool&             shares) const override;

  DEFINE_STANDARD_RTTIEXT(RWStepAP214_GeneralModule, StepData_GeneralModule)
};
