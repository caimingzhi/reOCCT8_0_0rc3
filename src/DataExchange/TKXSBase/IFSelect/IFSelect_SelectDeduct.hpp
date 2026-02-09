#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
class IFSelect_SelectPointed;
class Interface_EntityIterator;
class Interface_Graph;
class IFSelect_SelectionIterator;

class IFSelect_SelectDeduct : public IFSelect_Selection
{

public:
  Standard_EXPORT void SetInput(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT occ::handle<IFSelect_Selection> Input() const;

  Standard_EXPORT bool HasInput() const;

  Standard_EXPORT bool HasAlternate() const;

  Standard_EXPORT occ::handle<IFSelect_SelectPointed>& Alternate();

  Standard_EXPORT Interface_EntityIterator InputResult(const Interface_Graph& G) const;

  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectDeduct, IFSelect_Selection)

private:
  occ::handle<IFSelect_Selection>     thesel;
  occ::handle<IFSelect_SelectPointed> thealt;
};
