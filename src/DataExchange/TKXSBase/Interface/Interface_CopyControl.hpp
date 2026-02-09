#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

class Interface_CopyControl : public Standard_Transient
{

public:
  Standard_EXPORT virtual void Clear() = 0;

  Standard_EXPORT virtual void Bind(const occ::handle<Standard_Transient>& ent,
                                    const occ::handle<Standard_Transient>& res) = 0;

  Standard_EXPORT virtual bool Search(const occ::handle<Standard_Transient>& ent,
                                      occ::handle<Standard_Transient>&       res) const = 0;

  DEFINE_STANDARD_RTTIEXT(Interface_CopyControl, Standard_Transient)
};
