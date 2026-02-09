

#include <IFSelect_SelectExplore.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedMap.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectExplore, IFSelect_SelectDeduct)

IFSelect_SelectExplore::IFSelect_SelectExplore(const int level)
    : thelevel(level)
{
}

int IFSelect_SelectExplore::Level() const
{
  return thelevel;
}

Interface_EntityIterator IFSelect_SelectExplore::RootResult(const Interface_Graph& G) const
{

  int                                                     nb = G.Size();
  NCollection_IndexedMap<occ::handle<Standard_Transient>> entrees(nb);
  NCollection_IndexedMap<occ::handle<Standard_Transient>> result(nb);

  int                      i, j, level = 1, ilev = 0;
  Interface_EntityIterator input;
  input = InputResult(G);
  for (input.Start(); input.More(); input.Next())
    i = entrees.Add(input.Value());
  ilev = entrees.Extent();

  for (i = 1; i <= nb; i++)
  {
    if (i > entrees.Extent())
      break;
    if (i > ilev)
    {
      level++;
      if (level > thelevel && thelevel > 0)
        break;
      ilev = entrees.Extent();
    }
    occ::handle<Standard_Transient> ent = entrees.FindKey(i);
    if (ent.IsNull())
      continue;
    Interface_EntityIterator exp;
    if (!Explore(level, ent, G, exp))
      continue;

    if (exp.NbEntities() == 0)
    {
      j = result.Add(ent);
      continue;
    }
    else if (level == thelevel)
    {
      for (exp.Start(); exp.More(); exp.Next())
        j = result.Add(exp.Value());
    }
    else
    {
      for (exp.Start(); exp.More(); exp.Next())
        j = entrees.Add(exp.Value());
    }
  }

  Interface_EntityIterator res;
  nb = result.Extent();
  for (j = 1; j <= nb; j++)
    res.AddItem(result.FindKey(j));
  return res;
}

TCollection_AsciiString IFSelect_SelectExplore::Label() const
{
  TCollection_AsciiString labl;
  if (thelevel == 0)
    labl.AssignCat("(Recursive)");
  else if (thelevel > 0)
  {
    char lab[30];
    Sprintf(lab, "(Level %d)", thelevel);
    labl.AssignCat(lab);
  }
  labl.AssignCat(ExploreLabel());
  return labl;
}
