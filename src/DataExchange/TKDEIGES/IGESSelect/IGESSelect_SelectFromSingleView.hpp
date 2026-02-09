#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectDeduct.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

class IGESSelect_SelectFromSingleView : public IFSelect_SelectDeduct
{

public:
  Standard_EXPORT IGESSelect_SelectFromSingleView();

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectFromSingleView, IFSelect_SelectDeduct)
};
