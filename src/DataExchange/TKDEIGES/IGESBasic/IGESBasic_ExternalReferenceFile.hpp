#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

//! defines ExternalReferenceFile, Type <406> Form <12>
//! in package IGESBasic
//! References definitions residing in another file
class IGESBasic_ExternalReferenceFile : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalReferenceFile();

  //! This method is used to set the fields of the class
  //! ExternalReferenceFile
  //! - aNameArray : External Reference File Names
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aNameArray);

  //! returns number of External Reference File Names
  Standard_EXPORT int NbListEntries() const;

  //! returns External Reference File Name
  //! raises exception if Index <= 0 or Index > NbListEntries()
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalReferenceFile, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNames;
};
