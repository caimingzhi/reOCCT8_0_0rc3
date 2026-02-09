#pragma once

#include <TObj_LabelIterator.hpp>

class TObj_ReferenceIterator : public TObj_LabelIterator
{
public:
  Standard_EXPORT TObj_ReferenceIterator(const TDF_Label&                  theLabel,
                                         const occ::handle<Standard_Type>& theType      = nullptr,
                                         const bool                        theRecursive = true);

protected:
  Standard_EXPORT void MakeStep() override;

  occ::handle<Standard_Type> myType;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_ReferenceIterator, TObj_LabelIterator)
};

#ifdef _MSC_VER
  #pragma once
#endif
