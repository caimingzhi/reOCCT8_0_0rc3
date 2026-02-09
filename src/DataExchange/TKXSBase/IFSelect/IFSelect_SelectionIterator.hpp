#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_Selection.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IFSelect_Selection;

class IFSelect_SelectionIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFSelect_SelectionIterator();

  Standard_EXPORT IFSelect_SelectionIterator(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT void AddFromIter(IFSelect_SelectionIterator& iter);

  Standard_EXPORT void AddItem(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT void AddList(const NCollection_Sequence<occ::handle<IFSelect_Selection>>& list);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<IFSelect_Selection>& Value() const;

private:
  int                                                                 thecurr;
  occ::handle<NCollection_HSequence<occ::handle<IFSelect_Selection>>> thelist;
};
