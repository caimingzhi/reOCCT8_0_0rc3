

#include <IFGraph_SubPartsIterator.hpp>
#include <IFSelect_PacketList.hpp>
#include <IFSelect_Selection.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_DispPerDrawing.hpp>
#include <IGESSelect_ViewSorter.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_DispPerDrawing, IFSelect_Dispatch)

IGESSelect_DispPerDrawing::IGESSelect_DispPerDrawing()
{
  thesorter = new IGESSelect_ViewSorter;
}

TCollection_AsciiString IGESSelect_DispPerDrawing::Label() const
{
  return TCollection_AsciiString("One File per Drawing");
}

void IGESSelect_DispPerDrawing::Packets(const Interface_Graph&    G,
                                        IFGraph_SubPartsIterator& packs) const
{
  if (FinalSelection().IsNull())
    return;
  Interface_EntityIterator list = FinalSelection()->UniqueResult(G);
  thesorter->SetModel(GetCasted(IGESData_IGESModel, G.Model()));
  thesorter->Clear();
  thesorter->AddList(list.Content());
  thesorter->SortDrawings(G);
  occ::handle<IFSelect_PacketList> sets = thesorter->Sets(true);

  packs.SetLoad();
  int nb = sets->NbPackets();
  for (int i = 1; i <= nb; i++)
  {
    packs.AddPart();
    packs.GetFromIter(sets->Entities(i));
  }
}

bool IGESSelect_DispPerDrawing::CanHaveRemainder() const
{
  return true;
}

Interface_EntityIterator IGESSelect_DispPerDrawing::Remainder(const Interface_Graph& G) const
{
  if (thesorter->NbEntities() == 0)
  {
    Interface_EntityIterator list;
    if (FinalSelection().IsNull())
      return list;
    list = FinalSelection()->UniqueResult(G);
    thesorter->Clear();
    thesorter->AddList(list.Content());
    thesorter->SortDrawings(G);
  }
  return thesorter->Sets(true)->Duplicated(0, false);
}
