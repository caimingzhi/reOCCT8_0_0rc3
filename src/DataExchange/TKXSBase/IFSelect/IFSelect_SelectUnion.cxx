

#include <IFGraph_Cumulate.hpp>
#include <IFSelect_SelectUnion.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectUnion, IFSelect_SelectCombine)

IFSelect_SelectUnion::IFSelect_SelectUnion() = default;

Interface_EntityIterator IFSelect_SelectUnion::RootResult(const Interface_Graph& G) const
{
  IFGraph_Cumulate GC(G);
  int              nb = NbInputs();
  for (int i = 1; i <= nb; i++)
    GC.GetFromIter(Input(i)->RootResult(G));
  return GC.Result();
}

TCollection_AsciiString IFSelect_SelectUnion::Label() const
{
  return TCollection_AsciiString("Union (OR)");
}
