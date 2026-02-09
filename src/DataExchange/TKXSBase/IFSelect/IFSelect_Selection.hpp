#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_EntityIterator;
class Interface_Graph;
class IFSelect_SelectionIterator;
class TCollection_AsciiString;

class IFSelect_Selection : public Standard_Transient
{

public:
  Standard_EXPORT virtual Interface_EntityIterator RootResult(const Interface_Graph& G) const = 0;

  Standard_EXPORT Interface_EntityIterator UniqueResult(const Interface_Graph& G) const;

  Standard_EXPORT virtual Interface_EntityIterator CompleteResult(const Interface_Graph& G) const;

  Standard_EXPORT virtual void FillIterator(IFSelect_SelectionIterator& iter) const = 0;

  Standard_EXPORT virtual TCollection_AsciiString Label() const = 0;

  DEFINE_STANDARD_RTTIEXT(IFSelect_Selection, Standard_Transient)

protected:
  Standard_EXPORT virtual bool HasUniqueResult() const;
};
