#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectBase.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class TCollection_AsciiString;

class IFSelect_SelectModelEntities : public IFSelect_SelectBase
{

public:
  Standard_EXPORT IFSelect_SelectModelEntities();

  Standard_EXPORT Interface_EntityIterator RootResult(const Interface_Graph& G) const override;

  Standard_EXPORT Interface_EntityIterator CompleteResult(const Interface_Graph& G) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectModelEntities, IFSelect_SelectBase)
};
