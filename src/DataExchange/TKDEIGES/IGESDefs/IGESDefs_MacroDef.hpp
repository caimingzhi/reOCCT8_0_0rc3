#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class TCollection_HAsciiString;

//! defines IGES Macro Definition Entity, Type <306> Form <0>
//! in package IGESDefs
//! This Class specifies the action of a specific MACRO.
//! After specification MACRO can be used as necessary
//! by means of MACRO class instance entity.
class IGESDefs_MacroDef : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_MacroDef();

  //! This method is used to set the fields of the class
  //! MacroDef
  //! - macro          : MACRO
  //! - entityTypeID   : Entity Type ID
  //! - langStatements : Language Statements
  //! - endMacro       : END MACRO
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                   macro,
    const int                                                                      entityTypeID,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& langStatements,
    const occ::handle<TCollection_HAsciiString>&                                   endMacro);

  //! returns the number of language statements
  Standard_EXPORT int NbStatements() const;

  //! returns the MACRO(Literal)
  Standard_EXPORT occ::handle<TCollection_HAsciiString> MACRO() const;

  //! returns the Entity Type ID
  Standard_EXPORT int EntityTypeID() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LanguageStatement(const int StatNum) const;

  //! returns the ENDM(Literal)
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ENDMACRO() const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_MacroDef, IGESData_IGESEntity)

private:
  occ::handle<TCollection_HAsciiString>                                   theMACRO;
  int                                                                     theEntityTypeID;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theLangStatements;
  occ::handle<TCollection_HAsciiString>                                   theENDMACRO;
};

