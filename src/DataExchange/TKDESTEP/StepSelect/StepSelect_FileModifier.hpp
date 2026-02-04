#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_GeneralModifier.hpp>
class StepData_StepWriter;
class IFSelect_ContextWrite;

class StepSelect_FileModifier : public IFSelect_GeneralModifier
{

public:
  //! Perform the action specific to each class of File Modifier
  //! <ctx> is the ContextWrite, which brings : the model, the
  //! protocol, the file name, plus the object AppliedModifiers
  //! (not used here) and the CheckList
  //! Remark that the model has to be casted for specific access
  //!
  //! <writer> is the Writer and is specific to each norm, on which
  //! to act
  Standard_EXPORT virtual void Perform(IFSelect_ContextWrite& ctx,
                                       StepData_StepWriter&   writer) const = 0;

  DEFINE_STANDARD_RTTI_INLINE(StepSelect_FileModifier, IFSelect_GeneralModifier)

protected:
  //! Sets a File Modifier to keep the graph of dependences
  //! unchanges (because it works on the model already produced)
  Standard_EXPORT StepSelect_FileModifier();
};

