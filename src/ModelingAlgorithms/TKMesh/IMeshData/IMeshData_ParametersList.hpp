#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class IMeshData_ParametersList : public Standard_Transient
{
public:
  ~IMeshData_ParametersList() override = default;

  Standard_EXPORT virtual double& GetParameter(const int theIndex) = 0;

  Standard_EXPORT virtual int ParametersNb() const = 0;

  Standard_EXPORT virtual void Clear(const bool isKeepEndPoints) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_ParametersList, Standard_Transient)

protected:
  IMeshData_ParametersList() {}

  Standard_EXPORT virtual void removeParameter(const int theIndex) = 0;
};
