#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <MoniTool_AttrList.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

//! a Element allows to map any kind of object as a Key for a Map.
//! This works by defining, for a Hash Code, that of the real Key,
//! not of the Element which acts only as an intermediate.
//! When a Map asks for the HashCode of a Element, this one returns
//! the code it has determined at creation time
class MoniTool_Element : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT MoniTool_Element();

  //! Returns the HashCode which has been stored by SetHashCode
  //! (remark that HashCode could be deferred then be defined by
  //! sub-classes, the result is the same)
  Standard_EXPORT size_t GetHashCode() const;

  //! Specific testof equality : to be defined by each sub-class,
  //! must be False if Elements have not the same true Type, else
  //! their contents must be compared
  Standard_EXPORT virtual bool Equates(const occ::handle<MoniTool_Element>& other) const = 0;

  //! Returns the Type of the Value. By default, returns the
  //! DynamicType of <me>, but can be redefined
  Standard_EXPORT virtual occ::handle<Standard_Type> ValueType() const;

  //! Returns the name of the Type of the Value. Default is name
  //! of ValueType, unless it is for a non-handled object
  Standard_EXPORT virtual const char* ValueTypeName() const;

  //! Returns (readonly) the Attribute List
  Standard_EXPORT const MoniTool_AttrList& ListAttr() const;

  //! Returns (modifiable) the Attribute List
  Standard_EXPORT MoniTool_AttrList& ChangeAttr();

  DEFINE_STANDARD_RTTIEXT(MoniTool_Element, Standard_Transient)

protected:
  //! Stores the HashCode which corresponds to the Value given to
  //! create the Mapper
  Standard_EXPORT void SetHashCode(const size_t code);

private:
  size_t            thecode;
  MoniTool_AttrList theattrib;
};

