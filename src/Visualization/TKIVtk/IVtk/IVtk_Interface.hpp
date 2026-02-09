#pragma once

#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

class IVtk_Interface : public Standard_Transient
{

public:
  typedef occ::handle<IVtk_Interface> Handle;
  DEFINE_STANDARD_RTTIEXT(IVtk_Interface, Standard_Transient)

  ~IVtk_Interface() override = default;
};
