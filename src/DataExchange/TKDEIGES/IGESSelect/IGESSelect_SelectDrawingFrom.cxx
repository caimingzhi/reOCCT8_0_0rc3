

#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESSelect_SelectDrawingFrom.hpp>
#include <IGESSelect_ViewSorter.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectDrawingFrom, IFSelect_SelectDeduct)

IGESSelect_SelectDrawingFrom::IGESSelect_SelectDrawingFrom() = default;

bool IGESSelect_SelectDrawingFrom::HasUniqueResult() const
{
  return true;
}

Interface_EntityIterator IGESSelect_SelectDrawingFrom::RootResult(const Interface_Graph& G) const
{
  occ::handle<IGESSelect_ViewSorter> sorter = new IGESSelect_ViewSorter;
  sorter->SetModel(GetCasted(IGESData_IGESModel, G.Model()));
  sorter->Clear();
  sorter->AddList(InputResult(G).Content());
  sorter->SortDrawings(G);
  Interface_EntityIterator list;
  int                      nb = sorter->NbSets(true);
  for (int i = 1; i <= nb; i++)
    list.GetOneItem(sorter->SetItem(i, true));
  return list;
}

TCollection_AsciiString IGESSelect_SelectDrawingFrom::Label() const
{
  return TCollection_AsciiString("Drawings attached");
}
