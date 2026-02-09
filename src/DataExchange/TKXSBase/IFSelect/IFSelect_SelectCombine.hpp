#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Selection.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
class IFSelect_SelectionIterator;

class IFSelect_SelectCombine : public IFSelect_Selection
{

public:
  Standard_EXPORT int NbInputs() const;

  Standard_EXPORT occ::handle<IFSelect_Selection> Input(const int num) const;

  Standard_EXPORT int InputRank(const occ::handle<IFSelect_Selection>& sel) const;

  Standard_EXPORT void Add(const occ::handle<IFSelect_Selection>& sel, const int atnum = 0);

  Standard_EXPORT bool Remove(const occ::handle<IFSelect_Selection>& sel);

  Standard_EXPORT bool Remove(const int num);

  Standard_EXPORT void FillIterator(IFSelect_SelectionIterator& iter) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectCombine, IFSelect_Selection)

protected:
  Standard_EXPORT IFSelect_SelectCombine();

  Standard_EXPORT bool HasUniqueResult() const override;

private:
  NCollection_Sequence<occ::handle<IFSelect_Selection>> thelist;
};
