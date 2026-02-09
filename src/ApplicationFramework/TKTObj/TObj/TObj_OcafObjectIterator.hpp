#pragma once

#include <TObj_LabelIterator.hpp>

class TObj_OcafObjectIterator : public TObj_LabelIterator
{
public:
  Standard_EXPORT TObj_OcafObjectIterator(const TDF_Label&                  theLabel,
                                          const occ::handle<Standard_Type>& theType      = nullptr,
                                          const bool                        theRecursive = false,
                                          const bool theAllSubChildren                   = false);

protected:
  Standard_EXPORT void MakeStep() override;

protected:
  occ::handle<Standard_Type> myType;

  bool myAllSubChildren;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_OcafObjectIterator, TObj_LabelIterator)
};

#ifdef _MSC_VER
  #pragma once
#endif
