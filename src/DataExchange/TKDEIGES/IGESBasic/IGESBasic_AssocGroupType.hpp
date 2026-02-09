#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESBasic_AssocGroupType : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_AssocGroupType();

  Standard_EXPORT void Init(const int                                    nbDataFields,
                            const int                                    aType,
                            const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT int NbData() const;

  Standard_EXPORT int AssocType() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_AssocGroupType, IGESData_IGESEntity)

private:
  int                                   theNbData;
  int                                   theType;
  occ::handle<TCollection_HAsciiString> theName;
};
