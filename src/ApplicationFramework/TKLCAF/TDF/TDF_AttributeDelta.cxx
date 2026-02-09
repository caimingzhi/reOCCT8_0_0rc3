#include <TDF_AttributeDelta.hpp>

#include <Standard_Dump.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDF_AttributeDelta, Standard_Transient)

TDF_AttributeDelta::TDF_AttributeDelta(const occ::handle<TDF_Attribute>& anAttribute)
    : myAttribute(anAttribute),
      myLabel(anAttribute->Label())
{
}

TDF_Label TDF_AttributeDelta::Label() const
{
  return myLabel;
}

occ::handle<TDF_Attribute> TDF_AttributeDelta::Attribute() const
{
  return myAttribute;
}

Standard_GUID TDF_AttributeDelta::ID() const
{
  return myAttribute->ID();
}

Standard_OStream& TDF_AttributeDelta::Dump(Standard_OStream& OS) const
{
  static TCollection_AsciiString entry;
  TDF_Tool::Entry(Label(), entry);
  OS << this->DynamicType()->Name() << " at " << entry;
  OS << " on " << Attribute()->DynamicType()->Name();
  return OS;
}

void TDF_AttributeDelta::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAttribute.get())

  TCollection_AsciiString aStrForTDF_Label;
  TDF_Tool::Entry(myLabel, aStrForTDF_Label);
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, aStrForTDF_Label)
}
