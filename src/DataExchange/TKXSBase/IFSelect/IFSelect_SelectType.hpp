#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectAnyType.hpp>
class TCollection_AsciiString;

class IFSelect_SelectType : public IFSelect_SelectAnyType
{

public:
  Standard_EXPORT IFSelect_SelectType();

  Standard_EXPORT IFSelect_SelectType(const occ::handle<Standard_Type>& atype);

  Standard_EXPORT void SetType(const occ::handle<Standard_Type>& atype);

  Standard_EXPORT occ::handle<Standard_Type> TypeForMatch() const override;

  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectType, IFSelect_SelectAnyType)

private:
  occ::handle<Standard_Type> thetype;
};
