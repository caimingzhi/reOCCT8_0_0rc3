#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectControl.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

class IFSelect_SelectDiff : public IFSelect_SelectControl
{

public:
  Standard_EXPORT IFSelect_SelectDiff();

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectDiff, IFSelect_SelectControl)

protected:
  Standard_EXPORT bool HasUniqueResult() const override;
};
