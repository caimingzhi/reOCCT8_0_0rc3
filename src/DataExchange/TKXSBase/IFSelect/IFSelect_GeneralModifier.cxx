

#include <IFSelect_Dispatch.hpp>
#include <IFSelect_GeneralModifier.hpp>
#include <IFSelect_Selection.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_GeneralModifier, Standard_Transient)

IFSelect_GeneralModifier::IFSelect_GeneralModifier(const bool maychangegraph)
{
  thechgr = maychangegraph;
}

bool IFSelect_GeneralModifier::MayChangeGraph() const
{
  return thechgr;
}

void IFSelect_GeneralModifier::SetDispatch(const occ::handle<IFSelect_Dispatch>& disp)
{
  thedisp = disp;
}

occ::handle<IFSelect_Dispatch> IFSelect_GeneralModifier::Dispatch() const
{
  return thedisp;
}

bool IFSelect_GeneralModifier::Applies(const occ::handle<IFSelect_Dispatch>& disp) const
{
  if (thedisp.IsNull())
    return true;
  if (thedisp != disp)
    return false;
  return true;
}

void IFSelect_GeneralModifier::SetSelection(const occ::handle<IFSelect_Selection>& sel)
{
  thesel = sel;
}

void IFSelect_GeneralModifier::ResetSelection()
{
  thesel.Nullify();
}

bool IFSelect_GeneralModifier::HasSelection() const
{
  return !thesel.IsNull();
}

occ::handle<IFSelect_Selection> IFSelect_GeneralModifier::Selection() const
{
  return thesel;
}
