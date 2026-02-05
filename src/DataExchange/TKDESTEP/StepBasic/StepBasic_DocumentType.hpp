#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_DocumentType : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DocumentType();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& apdt);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ProductDataType() const;

  Standard_EXPORT void SetProductDataType(const occ::handle<TCollection_HAsciiString>& apdt);

  DEFINE_STANDARD_RTTIEXT(StepBasic_DocumentType, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> thepdt;
};
