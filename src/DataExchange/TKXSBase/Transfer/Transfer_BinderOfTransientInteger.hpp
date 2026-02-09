#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>

class Transfer_BinderOfTransientInteger : public Transfer_SimpleBinderOfTransient
{

public:
  Standard_EXPORT Transfer_BinderOfTransientInteger();

  Standard_EXPORT void SetInteger(const int value);

  Standard_EXPORT int Integer() const;

  DEFINE_STANDARD_RTTIEXT(Transfer_BinderOfTransientInteger, Transfer_SimpleBinderOfTransient)

private:
  int theintval;
};
