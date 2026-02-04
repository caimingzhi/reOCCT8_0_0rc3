#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDefs_AttributeDef;
class Standard_Transient;
class TCollection_HAsciiString;

//! defines IGES Attribute Table, Type <422> Form <0, 1>
//! in package IGESDefs
//! This class is used to represent an occurrence of
//! Attribute Table. This Class may be independent
//! or dependent or pointed at by other Entities.
class IGESDefs_AttributeTable : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_AttributeTable();

  //! This method is used to set the fields of the class
  //! AttributeTable
  //! - attributes : Attribute instances, created as
  //! (1,NbAttributes,1,NbRows)
  //! - NbRows = 1 is a particular case (Form 0)
  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray2<occ::handle<Standard_Transient>>>& attributes);

  //! Sets a Definition as Structure information
  //! (works by calling InitMisc)
  Standard_EXPORT void SetDefinition(const occ::handle<IGESDefs_AttributeDef>& def);

  //! Return the Structure information in Directory Entry,
  //! casted as an AttributeDef
  Standard_EXPORT occ::handle<IGESDefs_AttributeDef> Definition() const;

  //! returns Number of Rows. Remark that it is always 1 if Form = 0
  //! It means that the list of Attributes (by their number, and for each
  //! one its type and ValueCount) is repeated <NbRows> times
  Standard_EXPORT int NbRows() const;

  //! returns Number of Attributes
  Standard_EXPORT int NbAttributes() const;

  //! returns the Type of an Attribute, given its No. : it is read in the
  //! Definition.
  //! (1 : Integer, 2 : Real, 3 : String, 4 : Entity, 6 : Logical)
  Standard_EXPORT int DataType(const int Atnum) const;

  //! returns the Count of Value for an Attribute, given its No. :
  //! it is read in the Definition.
  Standard_EXPORT int ValueCount(const int Atnum) const;

  Standard_EXPORT occ::handle<Standard_Transient> AttributeList(const int Attribnum,
                                                                const int Rownum) const;

  //! Returns Attribute Value <AtNum, Rownum, rank ValNum> as an Integer
  //! Error if Indices out of Range, or no Value defined, or not an Integer
  Standard_EXPORT int AttributeAsInteger(const int AtNum, const int Rownum, const int ValNum) const;

  //! Returns Attribute Value <AtNum, Rownum, rank ValNum> as a Real
  //! Error if Indices out of Range, or no Value defined, or not a Real
  Standard_EXPORT double AttributeAsReal(const int AtNum, const int Rownum, const int ValNum) const;

  //! Returns Attribute Value <AtNum, Rownum, rank ValNum> as an Integer
  Standard_EXPORT occ::handle<TCollection_HAsciiString> AttributeAsString(const int AtNum,
                                                                          const int Rownum,
                                                                          const int ValNum) const;

  //! Returns Attribute Value <AtNum, Rownum, rank ValNum> as an Entity
  //! Error if Indices out of Range, or no Value defined, or not an Entity
  Standard_EXPORT occ::handle<IGESData_IGESEntity> AttributeAsEntity(const int AtNum,
                                                                     const int Rownum,
                                                                     const int ValNum) const;

  //! Returns Attribute Value <AtNum, Rownum, rank ValNum> as a Boolean
  //! Error if Indices out of Range, or no Value defined, or not a Logical
  Standard_EXPORT bool AttributeAsLogical(const int AtNum,
                                          const int Rownum,
                                          const int ValNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_AttributeTable, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray2<occ::handle<Standard_Transient>>> theAttributes;
};

