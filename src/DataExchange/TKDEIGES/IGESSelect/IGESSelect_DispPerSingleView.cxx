

#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_PacketList.hpp>
#include <IFSelect_Selection.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_DispPerSingleView.hpp>
#include <IGESSelect_ViewSorter.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_DispPerSingleView, IFSelect_Dispatch)

IGESSelect_DispPerSingleView::IGESSelect_DispPerSingleView()
{
  thesorter = new IGESSelect_ViewSorter;
}

TCollection_AsciiString IGESSelect_DispPerSingleView::Label() const
{
  return TCollection_AsciiString("One File per single View or Drawing Frame");
}

void IGESSelect_DispPerSingleView::Packets(const Interface_Graph&    G,
                                           IFGraph_SubPartsIterator& packs) const
{
  if (FinalSelection().IsNull())
    return;
  Interface_EntityIterator list = FinalSelection()->UniqueResult(G);
  thesorter->SetModel(GetCasted(IGESData_IGESModel, G.Model()));
  thesorter->Clear();
  thesorter->AddList(list.Content());
  thesorter->SortSingleViews(true);
  occ::handle<IFSelect_PacketList> sets = thesorter->Sets(true);

  packs.SetLoad();
  int nb = sets->NbPackets();
  for (int i = 1; i <= nb; i++)
  {
    packs.AddPart();
    packs.GetFromIter(sets->Entities(i));
  }
}

bool IGESSelect_DispPerSingleView::CanHaveRemainder() const
{
  return true;
}

Interface_EntityIterator IGESSelect_DispPerSingleView::Remainder(const Interface_Graph& G) const
{
  if (thesorter->NbEntities() == 0)
  {
    Interface_EntityIterator list;
    if (FinalSelection().IsNull())
      return list;
    list = FinalSelection()->UniqueResult(G);
    thesorter->Clear();
    thesorter->Add(list.Content());
    thesorter->SortSingleViews(true);
  }
  return thesorter->Sets(true)->Duplicated(0, false);
}
