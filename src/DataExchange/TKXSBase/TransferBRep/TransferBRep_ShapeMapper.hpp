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
  Standard_EXPORT TransferBRep_ShapeMapper(const TopoDS_Shape& akey);

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT bool Equates(const occ::handle<Transfer_Finder>& other) const override;

  Standard_EXPORT occ::handle<Standard_Type> ValueType() const override;

  Standard_EXPORT const char* ValueTypeName() const override;

  DEFINE_STANDARD_RTTI_INLINE(TransferBRep_ShapeMapper, Transfer_Finder)

private:
  TopoDS_Shape theval;
};
