#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_GeneralModifier.hpp>
class IGESData_IGESWriter;
class IFSelect_ContextWrite;

class IGESSelect_FileModifier : public IFSelect_GeneralModifier
{

public:
  Standard_EXPORT virtual void Perform(IFSelect_ContextWrite& ctx,
                                       IGESData_IGESWriter&   writer) const = 0;

  DEFINE_STANDARD_RTTI_INLINE(IGESSelect_FileModifier, IFSelect_GeneralModifier)

protected:
  Standard_EXPORT IGESSelect_FileModifier();
};
