#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <MoniTool_AttrList.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class MoniTool_Element : public Standard_Transient
{

public:
  Standard_EXPORT MoniTool_Element();

  Standard_EXPORT size_t GetHashCode() const;

  Standard_EXPORT virtual bool Equates(const occ::handle<MoniTool_Element>& other) const = 0;

  Standard_EXPORT virtual occ::handle<Standard_Type> ValueType() const;

  Standard_EXPORT virtual const char* ValueTypeName() const;

  Standard_EXPORT const MoniTool_AttrList& ListAttr() const;

  Standard_EXPORT MoniTool_AttrList& ChangeAttr();

  DEFINE_STANDARD_RTTIEXT(MoniTool_Element, Standard_Transient)

protected:
  Standard_EXPORT void SetHashCode(const size_t code);

private:
  size_t            thecode;
  MoniTool_AttrList theattrib;
};
