

#include <IFGraph_SCRoots.hpp>
#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_DispPerOne.hpp>
#include <IFSelect_Selection.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_DispPerOne, IFSelect_Dispatch)

IFSelect_DispPerOne::IFSelect_DispPerOne() = default;

TCollection_AsciiString IFSelect_DispPerOne::Label() const
{
  return TCollection_AsciiString("One File per Input Entity");
}

bool IFSelect_DispPerOne::LimitedMax(const int nbent, int& pcount) const
{
  pcount = nbent;
  return true;
}

void IFSelect_DispPerOne::Packets(const Interface_Graph& G, IFGraph_SubPartsIterator& packs) const
{
  IFGraph_SCRoots packsc(G, false);
  packsc.SetLoad();
  packsc.GetFromIter(FinalSelection()->UniqueResult(G));

  packs.GetParts(packsc);
}
