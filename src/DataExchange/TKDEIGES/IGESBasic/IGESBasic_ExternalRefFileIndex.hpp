#pragma once


#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;

//! defines ExternalRefFileIndex, Type <402> Form <12>
//! in package IGESBasic
//! Contains a list of the symbolic names used by the
//! referencing files and the DE pointers to the
//! corresponding definitions within the referenced file
class IGESBasic_ExternalRefFileIndex : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESBasic_ExternalRefFileIndex();

  //! This method is used to set the fields of the class
  //! ExternalRefFileIndex
  //! - aNameArray  : External Reference Entity symbolic names
  //! - allEntities : External Reference Entities
  //! raises exception if array lengths are not equal
  //! if size of aNameArray is not equal to size of allEntities
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& aNameArray,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>&      allEntities);

  //! returns number of index entries
  Standard_EXPORT int NbEntries() const;

  //! returns the External Reference Entity symbolic name
  //! raises exception if Index <= 0 or Index > NbEntries()
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(const int Index) const;

  //! returns the internal entity
  //! raises exception if Index <= 0 or Index > NbEntries()
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Entity(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_ExternalRefFileIndex, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theNames;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>      theEntities;
};

