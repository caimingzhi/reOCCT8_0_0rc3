#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
class IFSelect_IntParam;
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

class IFSelect_SelectEntityNumber : public IFSelect_SelectBase
{

public:
  Standard_EXPORT IFSelect_SelectEntityNumber();

  Standard_EXPORT void SetNumber(const occ::handle<IFSelect_IntParam>& num);

  Standard_EXPORT occ::handle<IFSelect_IntParam> Number() const;

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectEntityNumber, IFSelect_SelectBase)

private:
  occ::handle<IFSelect_IntParam> thenum;
};
