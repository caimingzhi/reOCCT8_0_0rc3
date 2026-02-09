

#include <IFGraph_Compare.hpp>
#include <IFSelect_SelectDiff.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectDiff, IFSelect_SelectControl)

IFSelect_SelectDiff::IFSelect_SelectDiff() = default;

Interface_EntityIterator IFSelect_SelectDiff::RootResult(const Interface_Graph& G) const
{
  IFGraph_Compare GC(G);
  GC.GetFromIter(MainInput()->RootResult(G), true);
  if (HasSecondInput())
    GC.GetFromIter(SecondInput()->RootResult(G), false);
  return GC.FirstOnly();
}

bool IFSelect_SelectDiff::HasUniqueResult() const
{
  return true;
}

TCollection_AsciiString IFSelect_SelectDiff::Label() const
{
  return TCollection_AsciiString("Differences");
}
