

#include <IFSelect_SelectExtract.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectExtract, IFSelect_SelectDeduct)

IFSelect_SelectExtract::IFSelect_SelectExtract()
{
  thesort = true;
}

bool IFSelect_SelectExtract::IsDirect() const
{
  return thesort;
}

void IFSelect_SelectExtract::SetDirect(const bool direct)
{
  thesort = direct;
}

Interface_EntityIterator IFSelect_SelectExtract::RootResult(const Interface_Graph& G) const
{
  Interface_EntityIterator iter;
  Interface_EntityIterator inputer = InputResult(G);
  int                      rank    = 0;
  for (inputer.Start(); inputer.More(); inputer.Next())
  {
    const occ::handle<Standard_Transient>& ent = inputer.Value();
    rank++;
    if (SortInGraph(rank, ent, G) == thesort)
      iter.GetOneItem(ent);
  }
  return iter;
}

bool IFSelect_SelectExtract::SortInGraph(const int                              rank,
                                         const occ::handle<Standard_Transient>& ent,
                                         const Interface_Graph&                 G) const
{
  return Sort(rank, ent, G.Model());
}

TCollection_AsciiString IFSelect_SelectExtract::Label() const
{
  TCollection_AsciiString labl;
  if (thesort)
    labl.AssignCat("Picked: ");
  if (!thesort)
    labl.AssignCat("Removed: ");
  labl.AssignCat(ExtractLabel());
  return labl;
}
