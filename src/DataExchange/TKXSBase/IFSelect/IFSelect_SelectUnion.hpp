#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectCombine.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

class IFSelect_SelectUnion : public IFSelect_SelectCombine
{

public:
  Standard_EXPORT IFSelect_SelectUnion();

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectUnion, IFSelect_SelectCombine)
};
