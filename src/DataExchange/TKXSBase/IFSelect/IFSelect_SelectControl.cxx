

#include <IFSelect_SelectControl.hpp>
#include <IFSelect_Selection.hpp>
#include <IFSelect_SelectionIterator.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectControl, IFSelect_Selection)

occ::handle<IFSelect_Selection> IFSelect_SelectControl::MainInput() const
{
  return themain;
}

occ::handle<IFSelect_Selection> IFSelect_SelectControl::SecondInput() const
{
  return thesecond;
}

bool IFSelect_SelectControl::HasSecondInput() const
{
  return (!thesecond.IsNull());
}

void IFSelect_SelectControl::SetMainInput(const occ::handle<IFSelect_Selection>& sel)
{
  themain = sel;
}

void IFSelect_SelectControl::SetSecondInput(const occ::handle<IFSelect_Selection>& sel)
{
  thesecond = sel;
}

void IFSelect_SelectControl::FillIterator(IFSelect_SelectionIterator& iter) const
{
  iter.AddItem(themain);
  if (!thesecond.IsNull())
    iter.AddItem(thesecond);
}
