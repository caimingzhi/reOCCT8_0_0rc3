#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Transfer_Finder.hpp>
class TopoDS_Shape;
class TopTools_ShapeMapHasher;
class TransferBRep_ShapeInfo;
class Transfer_Finder;

class TransferBRep_ShapeMapper : public Transfer_Finder
{

public:
  //! Creates a Mapper with a Value. This Value can then not be
  //! changed. It is used by the Hasher to compute the HashCode,
  //! which will then be stored for an immediate reading.
  Standard_EXPORT TransferBRep_ShapeMapper(const TopoDS_Shape& akey);

  //! Returns the contained value
  Standard_EXPORT const TopoDS_Shape& Value() const;

  //! Specific test of equality : defined as False if <other> has
  //! not the same true Type, else contents are compared (by
  //! C++ operator ==)
  Standard_EXPORT bool Equates(const occ::handle<Transfer_Finder>& other) const override;

  //! Returns the Type of the Value. By default, returns the
  //! DynamicType of <me>, but can be redefined
  Standard_EXPORT occ::handle<Standard_Type> ValueType() const override;

  //! Returns the name of the Type of the Value. Default is name
  //! of ValueType, unless it is for a non-handled object
  Standard_EXPORT const char* ValueTypeName() const override;

  DEFINE_STANDARD_RTTI_INLINE(TransferBRep_ShapeMapper, Transfer_Finder)

private:
  TopoDS_Shape theval;
};
