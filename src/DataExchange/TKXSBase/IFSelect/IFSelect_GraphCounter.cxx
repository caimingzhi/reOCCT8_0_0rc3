

#include <IFSelect_GraphCounter.hpp>
#include <IFSelect_SelectDeduct.hpp>
#include <IFSelect_SelectPointed.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_GraphCounter, IFSelect_SignCounter)

IFSelect_GraphCounter::IFSelect_GraphCounter(const bool withmap, const bool withlist)
    : IFSelect_SignCounter(withmap, withlist)
{
}

occ::handle<IFSelect_SelectDeduct> IFSelect_GraphCounter::Applied() const
{
  return theapplied;
}

void IFSelect_GraphCounter::SetApplied(const occ::handle<IFSelect_SelectDeduct>& applied)
{
  theapplied = applied;
}

void IFSelect_GraphCounter::AddWithGraph(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
  const Interface_Graph&                                                     graph)
{
  if (theapplied.IsNull())
  {
    AddList(list, graph.Model());
    return;
  }
  if (list.IsNull())
    return;
  int i, nb = list->Length();
  for (i = 1; i <= nb; i++)
  {
    char                            val[12];
    occ::handle<Standard_Transient> ent = list->Value(i);
    theapplied->Alternate()->SetEntity(ent);
    Interface_EntityIterator iter = theapplied->UniqueResult(graph);
    int                      n    = iter.NbEntities();
    switch (n)
    {
      case 0:
        Add(ent, "0");
        break;
      case 1:
        Add(ent, "1");
        break;
      case 2:
        Add(ent, "2");
        break;
      case 3:
        Add(ent, "3");
        break;
      case 4:
        Add(ent, "4");
        break;
      case 5:
        Add(ent, "5");
        break;
      case 6:
        Add(ent, "6");
        break;
      case 7:
        Add(ent, "7");
        break;
      case 8:
        Add(ent, "8");
        break;
      case 9:
        Add(ent, "9");
        break;
      default:
        Sprintf(val, "%d", n);
        Add(ent, val);
        break;
    }
  }
}
