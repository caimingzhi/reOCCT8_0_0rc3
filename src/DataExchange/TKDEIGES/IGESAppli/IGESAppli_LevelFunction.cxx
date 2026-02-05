#include <IGESAppli_LevelFunction.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_LevelFunction, IGESData_IGESEntity)

IGESAppli_LevelFunction::IGESAppli_LevelFunction() = default;

void IGESAppli_LevelFunction::Init(const int                                    nbPropVal,
                                   const int                                    aCode,
                                   const occ::handle<TCollection_HAsciiString>& aFuncDescrip)
{
  theNbPropertyValues = nbPropVal;
  theFuncDescripCode  = aCode;
  theFuncDescrip      = aFuncDescrip;
  InitTypeAndForm(406, 3);
}

int IGESAppli_LevelFunction::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESAppli_LevelFunction::FuncDescriptionCode() const
{
  return theFuncDescripCode;
}

occ::handle<TCollection_HAsciiString> IGESAppli_LevelFunction::FuncDescription() const
{
  return theFuncDescrip;
}
