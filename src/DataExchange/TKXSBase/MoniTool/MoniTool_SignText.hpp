#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_AsciiString;

class MoniTool_SignText : public Standard_Transient
{

public:
  Standard_EXPORT virtual const char* Name() const = 0;

  Standard_EXPORT virtual TCollection_AsciiString TextAlone(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT virtual TCollection_AsciiString Text(
    const occ::handle<Standard_Transient>& ent,
    const occ::handle<Standard_Transient>& context) const = 0;

  DEFINE_STANDARD_RTTIEXT(MoniTool_SignText, Standard_Transient)
};
