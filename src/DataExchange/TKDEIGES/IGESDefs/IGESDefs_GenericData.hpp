#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Real.hpp>
class TCollection_HAsciiString;
class Standard_Transient;

//! defines IGES Generic Data, Type <406> Form <27>
//! in package IGESDefs
//! Used to communicate information defined by the system
//! operator while creating the model. The information is
//! system specific and does not map into one of the
//! predefined properties or associativities. Properties
//! and property values can be defined by multiple
//! instances of this property.
class IGESDefs_GenericData : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDefs_GenericData();

  //! This method is used to set the fields of the class
  //! GenericData
  //! - nbPropVal : Number of property values
  //! - aName     : Property Name
  //! - allTypes  : Property Types
  //! - allValues : Property Values
  Standard_EXPORT void Init(
    const int                                                                nbPropVal,
    const occ::handle<TCollection_HAsciiString>&                             aName,
    const occ::handle<NCollection_HArray1<int>>&                             allTypes,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& allValues);

  //! returns the number of property values
  Standard_EXPORT int NbPropertyValues() const;

  //! returns property name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! returns the number of TYPE/VALUE pairs
  Standard_EXPORT int NbTypeValuePairs() const;

  //! returns the Index'th property value data type
  //! raises exception if Index <= 0 or Index > NbTypeValuePairs()
  Standard_EXPORT int Type(const int Index) const;

  //! HArray1OfInteger (length 1), HArray1OfReal (length 1) for
  //! Integer, Real, Boolean (= Integer 0/1),
  //! HAsciiString for String (the value itself),
  //! IGESEntity for Entity (the value itself)
  Standard_EXPORT occ::handle<Standard_Transient> Value(const int Index) const;

  //! Returns Attribute Value <AttrNum, rank ValueNum> as an Integer
  //! Error if Index out of Range, or not an Integer
  Standard_EXPORT int ValueAsInteger(const int ValueNum) const;

  //! Returns Attribute Value <AttrNum, rank ValueNum> as a Real
  //! Error if Index out of Range, or not a Real
  Standard_EXPORT double ValueAsReal(const int ValueNum) const;

  //! Returns Attribute Value <AttrNum, rank ValueNum> as an Integer
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ValueAsString(const int ValueNum) const;

  //! Returns Attribute Value <AttrNum, rank ValueNum> as an Entity
  //! Error if Index out of Range, or not a Entity
  Standard_EXPORT occ::handle<IGESData_IGESEntity> ValueAsEntity(const int ValueNum) const;

  //! Returns Attribute Value <AttrNum, rank ValueNum> as a Boolean
  //! Error if Index out of Range, or not a Logical
  Standard_EXPORT bool ValueAsLogical(const int ValueNum) const;

  DEFINE_STANDARD_RTTIEXT(IGESDefs_GenericData, IGESData_IGESEntity)

private:
  int                                                               theNbPropertyValues;
  occ::handle<TCollection_HAsciiString>                             theName;
  occ::handle<NCollection_HArray1<int>>                             theTypes;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> theValues;
};
