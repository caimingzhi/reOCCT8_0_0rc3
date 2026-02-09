#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;

class IGESGraph_DrawingUnits : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_DrawingUnits();

  Standard_EXPORT void Init(const int                                    nbProps,
                            const int                                    aFlag,
                            const occ::handle<TCollection_HAsciiString>& aUnit);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int Flag() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Unit() const;

  Standard_EXPORT double UnitValue() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_DrawingUnits, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  int                                   theFlag;
  occ::handle<TCollection_HAsciiString> theUnit;
};
