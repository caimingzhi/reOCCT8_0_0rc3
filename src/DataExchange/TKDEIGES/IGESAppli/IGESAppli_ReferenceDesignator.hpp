#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESAppli_ReferenceDesignator : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_ReferenceDesignator();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const occ::handle<TCollection_HAsciiString>& aText);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> RefDesignatorText() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_ReferenceDesignator, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  occ::handle<TCollection_HAsciiString> theRefDesigText;
};
