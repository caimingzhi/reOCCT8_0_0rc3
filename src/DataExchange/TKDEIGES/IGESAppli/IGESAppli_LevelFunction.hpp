#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESAppli_LevelFunction : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_LevelFunction();

  Standard_EXPORT void Init(const int                                    nbPropVal,
                            const int                                    aCode,
                            const occ::handle<TCollection_HAsciiString>& aFuncDescrip);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int FuncDescriptionCode() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> FuncDescription() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_LevelFunction, IGESData_IGESEntity)

private:
  int                                   theNbPropertyValues;
  int                                   theFuncDescripCode;
  occ::handle<TCollection_HAsciiString> theFuncDescrip;
};
