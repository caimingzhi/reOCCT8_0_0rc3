#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

class IGESDefs_MacroDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_MacroDef();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                   macro,
    const int                                                                      entityTypeID,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& langStatements,
    const occ::handle<TCollection_HAsciiString>&                                   endMacro);

  Standard_EXPORT int NbStatements() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> MACRO() const;

  Standard_EXPORT int EntityTypeID() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LanguageStatement(const int StatNum) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ENDMACRO() const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_MacroDef, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString>                                   theMACRO;
  int                                                                     theEntityTypeID;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theLangStatements;
  occ::handle<TCollection_HAsciiString>                                   theENDMACRO;
};
