#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_ProductCategory : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ProductCategory();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasAdescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT void UnSetDescription();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT bool HasDescription() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductCategory, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<TCollection_HAsciiString> description;
  bool                                  hasDescription;
};
