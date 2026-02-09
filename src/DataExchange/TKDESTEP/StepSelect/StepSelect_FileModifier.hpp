#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_GeneralModifier.hpp>
class StepData_StepWriter;
class IFSelect_ContextWrite;

class StepSelect_FileModifier : public IFSelect_GeneralModifier
{

public:
  Standard_EXPORT virtual void Perform(IFSelect_ContextWrite& ctx,
                                       StepData_StepWriter&   writer) const = 0;

  DEFINE_STANDARD_RTTI_INLINE(StepSelect_FileModifier, IFSelect_GeneralModifier)

protected:
  Standard_EXPORT StepSelect_FileModifier();
};
