#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MoniTool_SignText.hpp>
class TCollection_AsciiString;
class Standard_Transient;
class Interface_InterfaceModel;

class Interface_SignType : public MoniTool_SignText
{

public:
  Standard_EXPORT TCollection_AsciiString
    Text(const occ::handle<Standard_Transient>& ent,
         const occ::handle<Standard_Transient>& context) const override;

  Standard_EXPORT virtual const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const = 0;

  Standard_EXPORT static const char* ClassName(const char* typnam);

  DEFINE_STANDARD_RTTIEXT(Interface_SignType, MoniTool_SignText)
};
