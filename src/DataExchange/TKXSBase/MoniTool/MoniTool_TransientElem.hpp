#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <MoniTool_Element.hpp>
#include <Standard_CString.hpp>

class MoniTool_TransientElem : public MoniTool_Element
{

public:
  Standard_EXPORT MoniTool_TransientElem(const occ::handle<Standard_Transient>& akey);

  Standard_EXPORT const occ::handle<Standard_Transient>& Value() const;

  Standard_EXPORT bool Equates(const occ::handle<MoniTool_Element>& other) const override;

  Standard_EXPORT occ::handle<Standard_Type> ValueType() const override;

  Standard_EXPORT const char* ValueTypeName() const override;

  DEFINE_STANDARD_RTTIEXT(MoniTool_TransientElem, MoniTool_Element)

private:
  occ::handle<Standard_Transient> theval;
};
