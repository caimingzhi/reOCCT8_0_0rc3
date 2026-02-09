

#include <IGESData_ViewKindEntity.hpp>
#include <IGESSelect_SelectFromSingleView.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectFromSingleView, IFSelect_SelectDeduct)

IGESSelect_SelectFromSingleView::IGESSelect_SelectFromSingleView() = default;

Interface_EntityIterator IGESSelect_SelectFromSingleView::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator list;
  Interface_EntityIterator views = InputResult(G);
  if (views.NbEntities() == 0)
    return list;
  int nb = G.Size();
  int i;
  for (i = 1; i <= nb; i++)
  {

    DeclareAndCast(IGESData_IGESEntity, igesent, G.Entity(i));
    if (igesent.IsNull())
      continue;
    int nv = G.EntityNumber(igesent->View());
    if (nv > 0 && nv <= nb)
      list.GetOneItem(igesent);
  }
  return list;
}

TCollection_AsciiString IGESSelect_SelectFromSingleView::Label() const
{
  return TCollection_AsciiString("Entities attached to a single View");
}
