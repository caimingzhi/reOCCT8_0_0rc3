#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

//! Interface class representing list of parameters on curve.
class IMeshData_ParametersList : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshData_ParametersList() override = default;

  //! Returns parameter with the given index.
  Standard_EXPORT virtual double& GetParameter(const int theIndex) = 0;

  //! Returns number of parameters.
  Standard_EXPORT virtual int ParametersNb() const = 0;

  //! Clears parameters list.
  Standard_EXPORT virtual void Clear(const bool isKeepEndPoints) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_ParametersList, Standard_Transient)

protected:
  //! Constructor.
  IMeshData_ParametersList() {}

  //! Removes parameter with the given index.
  Standard_EXPORT virtual void removeParameter(const int theIndex) = 0;
};
