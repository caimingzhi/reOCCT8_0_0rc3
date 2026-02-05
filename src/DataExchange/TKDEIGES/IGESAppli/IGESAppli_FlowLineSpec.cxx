#include <IGESAppli_FlowLineSpec.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_FlowLineSpec, IGESData_IGESEntity)

IGESAppli_FlowLineSpec::IGESAppli_FlowLineSpec() = default;

void IGESAppli_FlowLineSpec::Init(
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& allProperties)
{
  if (allProperties->Lower() != 1)
    throw Standard_DimensionMismatch("IGESAppli_FlowLineSpec : Init");
  theNameAndModifiers = allProperties;
  InitTypeAndForm(406, 14);
}

int IGESAppli_FlowLineSpec::NbPropertyValues() const
{
  return theNameAndModifiers->Length();
}

occ::handle<TCollection_HAsciiString> IGESAppli_FlowLineSpec::FlowLineName() const
{
  return theNameAndModifiers->Value(1);
}

occ::handle<TCollection_HAsciiString> IGESAppli_FlowLineSpec::Modifier(const int Index) const
{
  return theNameAndModifiers->Value(Index);
}
