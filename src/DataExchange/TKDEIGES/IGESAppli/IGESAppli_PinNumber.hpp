#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESAppli_PinNumber : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PinNumber();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aValue);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> PinNumberVal() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PinNumber, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> thePinNumber;
};
