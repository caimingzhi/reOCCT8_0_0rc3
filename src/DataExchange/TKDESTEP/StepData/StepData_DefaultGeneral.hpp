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

class StepData_DefaultGeneral : public StepData_GeneralModule
{

public:
  Standard_EXPORT StepData_DefaultGeneral();

  Standard_EXPORT void FillSharedCase(const int                              casenum,
                                      const occ::handle<Standard_Transient>& ent,
                                      Interface_EntityIterator&              iter) const override;

  Standard_EXPORT void CheckCase(const int                              casenum,
                                 const occ::handle<Standard_Transient>& ent,
                                 const Interface_ShareTool&             shares,
                                 occ::handle<Interface_Check>&          ach) const override;

  Standard_EXPORT bool NewVoid(const int CN, occ::handle<Standard_Transient>& entto) const override;

  Standard_EXPORT void CopyCase(const int                              casenum,
                                const occ::handle<Standard_Transient>& entfrom,
                                const occ::handle<Standard_Transient>& entto,
                                Interface_CopyTool&                    TC) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_DefaultGeneral, StepData_GeneralModule)
};
