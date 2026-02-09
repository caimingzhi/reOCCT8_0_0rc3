#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_NameEntity.hpp>
class TCollection_HAsciiString;

class IGESBasic_Name : public IGESData_NameEntity
{

public:
  Standard_EXPORT IGESBasic_Name();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Value() const override;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_Name, IGESData_NameEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theName;
};
