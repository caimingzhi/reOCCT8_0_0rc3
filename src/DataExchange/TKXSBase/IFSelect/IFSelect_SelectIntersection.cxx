

#include <IFGraph_Compare.hpp>
#include <IFSelect_SelectIntersection.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectIntersection, IFSelect_SelectCombine)

IFSelect_SelectIntersection::IFSelect_SelectIntersection() = default;

Interface_EntityIterator IFSelect_SelectIntersection::RootResult(const Interface_Graph& G) const
{
  IFGraph_Compare GC(G);
  int             nb = NbInputs();
  for (int i = 1; i <= nb; i++)
  {
    GC.GetFromIter(Input(i)->RootResult(G), (i == 1));
    if (i > 1 && i < nb)
    {
      Interface_EntityIterator comm = GC.Common();
      GC.ResetData();
      GC.GetFromIter(comm, true);
    }
  }
  return GC.Common();
}

TCollection_AsciiString IFSelect_SelectIntersection::Label() const
{
  return TCollection_AsciiString("Intersection (AND)");
}
