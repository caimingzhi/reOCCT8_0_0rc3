

#include <IGESBasic_GroupWithoutBackP.hpp>
#include <IGESSelect_SelectBypassGroup.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectBypassGroup, IFSelect_SelectExplore)

#define TypePourGroup 402

IGESSelect_SelectBypassGroup::IGESSelect_SelectBypassGroup(const int level)
    : IFSelect_SelectExplore(level)
{
}

bool IGESSelect_SelectBypassGroup::Explore(const int,
                                           const occ::handle<Standard_Transient>& ent,
                                           const Interface_Graph&,
                                           Interface_EntityIterator& explored) const
{
  DeclareAndCast(IGESBasic_Group, gr, ent);
  if (gr.IsNull())
    return true;

  int i, nb = gr->NbEntities();
  for (i = 1; i <= nb; i++)
    explored.AddItem(gr->Entity(i));
  return true;
}

TCollection_AsciiString IGESSelect_SelectBypassGroup::ExploreLabel() const
{
  return TCollection_AsciiString("Content of Groups");
}
