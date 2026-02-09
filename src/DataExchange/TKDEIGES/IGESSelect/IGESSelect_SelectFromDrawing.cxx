

#include <IGESData_ViewKindEntity.hpp>
#include <IGESSelect_SelectFromDrawing.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectFromDrawing, IFSelect_SelectDeduct)

#define PourDrawing 404

IGESSelect_SelectFromDrawing::IGESSelect_SelectFromDrawing() = default;

Interface_EntityIterator IGESSelect_SelectFromDrawing::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator list, views;
  Interface_EntityIterator draws = InputResult(G);
  if (draws.NbEntities() == 0)
    return list;
  int nb = G.Size();
  int i;

  for (draws.Start(); draws.More(); draws.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, igesent, draws.Value());
    if (igesent.IsNull())
      continue;
    if (igesent->TypeNumber() != PourDrawing)
      continue;
    list.GetOneItem(igesent);
    Interface_EntityIterator someviews = G.Shareds(draws.Value());
    list.AddList(someviews.Content());
  }
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

TCollection_AsciiString IGESSelect_SelectFromDrawing::Label() const
{
  return TCollection_AsciiString("Entities attached to a Drawing");
}
