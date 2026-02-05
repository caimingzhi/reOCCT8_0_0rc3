#include <IGESAppli_ReferenceDesignator.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_ReferenceDesignator, IGESData_IGESEntity)

IGESAppli_ReferenceDesignator::IGESAppli_ReferenceDesignator() = default;

void IGESAppli_ReferenceDesignator::Init(const int                                    nbPropVal,
                                         const occ::handle<TCollection_HAsciiString>& aText)
{
  theRefDesigText     = aText;
  theNbPropertyValues = nbPropVal;
  InitTypeAndForm(406, 7);
}

int IGESAppli_ReferenceDesignator::NbPropertyValues() const
{
  return theNbPropertyValues;
}

occ::handle<TCollection_HAsciiString> IGESAppli_ReferenceDesignator::RefDesignatorText() const
{
  return theRefDesigText;
}
