#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MoniTool_SignText.hpp>
class TCollection_AsciiString;
class Standard_Transient;

class MoniTool_SignShape : public MoniTool_SignText
{

public:
  Standard_EXPORT MoniTool_SignShape();

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT TCollection_AsciiString
    Text(const occ::handle<Standard_Transient>& ent,
         const occ::handle<Standard_Transient>& context) const override;

  DEFINE_STANDARD_RTTIEXT(MoniTool_SignShape, MoniTool_SignText)
};
