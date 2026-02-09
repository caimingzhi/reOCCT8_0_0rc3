#pragma once

#include <Standard_Transient.hpp>

template <class ParametersListPtrType>
class IMeshData_ParametersListArrayAdaptor : public Standard_Transient
{
public:
  IMeshData_ParametersListArrayAdaptor(const ParametersListPtrType& theParameters)
      : myParameters(theParameters)
  {
  }

  ~IMeshData_ParametersListArrayAdaptor() override = default;

  int Lower() const { return 0; }

  int Upper() const { return myParameters->ParametersNb() - 1; }

  double Value(const int theIndex) const { return myParameters->GetParameter(theIndex); }

private:
  IMeshData_ParametersListArrayAdaptor(
    const IMeshData_ParametersListArrayAdaptor<ParametersListPtrType>& theOther) = delete;

  void operator=(const IMeshData_ParametersListArrayAdaptor<ParametersListPtrType>& theOther) =
    delete;

  const ParametersListPtrType myParameters;
};
