#include <IGESGraph_NominalSize.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_NominalSize, IGESData_IGESEntity)

IGESGraph_NominalSize::IGESGraph_NominalSize() = default;

void IGESGraph_NominalSize::Init(const int                                    nbProps,
                                 const double                                 aNominalSizeValue,
                                 const occ::handle<TCollection_HAsciiString>& aNominalSizeName,
                                 const occ::handle<TCollection_HAsciiString>& aStandardName)
{
  theNbPropertyValues = nbProps;
  theNominalSizeValue = aNominalSizeValue;
  theNominalSizeName  = aNominalSizeName;
  theStandardName     = aStandardName;
  InitTypeAndForm(406, 13);
}

int IGESGraph_NominalSize::NbPropertyValues() const
{
  return theNbPropertyValues;
}

double IGESGraph_NominalSize::NominalSizeValue() const
{
  return theNominalSizeValue;
}

occ::handle<TCollection_HAsciiString> IGESGraph_NominalSize::NominalSizeName() const
{
  return theNominalSizeName;
}

bool IGESGraph_NominalSize::HasStandardName() const
{
  return (!theStandardName.IsNull());
}

occ::handle<TCollection_HAsciiString> IGESGraph_NominalSize::StandardName() const
{
  return theStandardName;
}
