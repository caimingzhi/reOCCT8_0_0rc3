

#include <IFGraph_SCRoots.hpp>
#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_DispPerFiles.hpp>
#include <IFSelect_IntParam.hpp>
#include <IFSelect_Selection.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_DispPerFiles, IFSelect_Dispatch)

IFSelect_DispPerFiles::IFSelect_DispPerFiles() = default;

occ::handle<IFSelect_IntParam> IFSelect_DispPerFiles::Count() const
{
  return thecount;
}

void IFSelect_DispPerFiles::SetCount(const occ::handle<IFSelect_IntParam>& pcount)
{
  thecount = pcount;
}

int IFSelect_DispPerFiles::CountValue() const
{
  int pcount = 0;
  if (!thecount.IsNull())
    pcount = thecount->Value();
  if (pcount <= 0)
    pcount = 1;
  return pcount;
}

TCollection_AsciiString IFSelect_DispPerFiles::Label() const
{
  TCollection_AsciiString lab(CountValue());
  lab.Insert(1, "Maximum ");
  lab.AssignCat(" Files");
  return lab;
}

bool IFSelect_DispPerFiles::LimitedMax(const int, int& pcount) const
{
  pcount = CountValue();
  return true;
}

void IFSelect_DispPerFiles::Packets(const Interface_Graph& G, IFGraph_SubPartsIterator& packs) const
{

  int pcount = CountValue();

  IFGraph_SCRoots roots(G, false);
  roots.SetLoad();
  roots.GetFromIter(FinalSelection()->UniqueResult(G));

  roots.Start();
  int nb = roots.NbParts();
  if (pcount > 0)
    pcount = (nb - 1) / pcount + 1;

  int i = 0;
  for (; roots.More(); roots.Next())
  {
    if (i == 0)
      packs.AddPart();
    i++;
    if (i >= pcount)
      i = 0;
    packs.GetFromIter(roots.Entities());
  }
}
