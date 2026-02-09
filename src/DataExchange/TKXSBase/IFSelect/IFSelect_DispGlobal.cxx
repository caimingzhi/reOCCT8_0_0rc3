

#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_DispGlobal.hpp>
#include <IFSelect_Selection.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_DispGlobal, IFSelect_Dispatch)

IFSelect_DispGlobal::IFSelect_DispGlobal() = default;

TCollection_AsciiString IFSelect_DispGlobal::Label() const
{
  return TCollection_AsciiString("One File for All Input");
}

bool IFSelect_DispGlobal::LimitedMax(const int, int& pcount) const
{
  pcount = 1;
  return true;
}

void IFSelect_DispGlobal::Packets(const Interface_Graph& G, IFGraph_SubPartsIterator& packs) const
{
  packs.AddPart();
  packs.GetFromIter(FinalSelection()->UniqueResult(G));
}
