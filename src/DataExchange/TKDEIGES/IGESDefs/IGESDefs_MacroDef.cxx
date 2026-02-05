#include <IGESDefs_MacroDef.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_MacroDef, IGESData_IGESEntity)

IGESDefs_MacroDef::IGESDefs_MacroDef() = default;

void IGESDefs_MacroDef::Init(
  const occ::handle<TCollection_HAsciiString>&                                   macro,
  const int                                                                      entityTypeID,
  const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& langStatements,
  const occ::handle<TCollection_HAsciiString>&                                   endMacro)
{
  if (langStatements->Lower() != 1)
    throw Standard_DimensionMismatch("IGESDefs_MacroDef : Init");
  theMACRO          = macro;
  theEntityTypeID   = entityTypeID;
  theLangStatements = langStatements;
  theENDMACRO       = endMacro;
  InitTypeAndForm(306, 0);
}

int IGESDefs_MacroDef::NbStatements() const
{
  return theLangStatements->Length();
}

occ::handle<TCollection_HAsciiString> IGESDefs_MacroDef::MACRO() const
{
  return theMACRO;
}

int IGESDefs_MacroDef::EntityTypeID() const
{
  return theEntityTypeID;
}

occ::handle<TCollection_HAsciiString> IGESDefs_MacroDef::LanguageStatement(const int StatNum) const
{
  return theLangStatements->Value(StatNum);
}

occ::handle<TCollection_HAsciiString> IGESDefs_MacroDef::ENDMACRO() const
{
  return theENDMACRO;
}
