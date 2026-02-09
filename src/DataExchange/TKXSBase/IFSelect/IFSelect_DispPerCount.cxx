

#include <IFGraph_SCRoots.hpp>
#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_DispPerCount.hpp>
#include <IFSelect_IntParam.hpp>
#include <IFSelect_Selection.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_DispPerCount, IFSelect_Dispatch)

IFSelect_DispPerCount::IFSelect_DispPerCount() = default;

occ::handle<IFSelect_IntParam> IFSelect_DispPerCount::Count() const
{
  return thecount;
}

void IFSelect_DispPerCount::SetCount(const occ::handle<IFSelect_IntParam>& pcount)
{
  thecount = pcount;
}

int IFSelect_DispPerCount::CountValue() const
{
  int pcount = 0;
  if (!thecount.IsNull())
    pcount = thecount->Value();
  if (pcount <= 0)
    pcount = 1;
  return pcount;
}

TCollection_AsciiString IFSelect_DispPerCount::Label() const
{
  TCollection_AsciiString lab(CountValue());
  lab.Insert(1, "One File per ");
  lab.AssignCat(" Entities");
  return lab;
}

bool IFSelect_DispPerCount::LimitedMax(const int nbent, int& pcount) const
{
  pcount = 1 + nbent / CountValue();
  return true;
}

void IFSelect_DispPerCount::Packets(const Interface_Graph& G, IFGraph_SubPartsIterator& packs) const
{

  int pcount = CountValue();

  IFGraph_SCRoots roots(G, false);
  roots.SetLoad();
  roots.GetFromIter(FinalSelection()->UniqueResult(G));

  int i = 0;
  for (roots.Start(); roots.More(); roots.Next())
  {
    if (i == 0)
      packs.AddPart();
    i++;
    if (i >= pcount)
      i = 0;
    packs.GetFromIter(roots.Entities());
  }
}
