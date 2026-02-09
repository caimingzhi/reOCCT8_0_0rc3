

#include <IGESBasic_SingularSubfigure.hpp>
#include <IGESBasic_SubfigureDef.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESDraw_CircArraySubfigure.hpp>
#include <IGESDraw_NetworkSubfigure.hpp>
#include <IGESDraw_NetworkSubfigureDef.hpp>
#include <IGESDraw_RectArraySubfigure.hpp>
#include <IGESSelect_SelectBypassSubfigure.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectBypassSubfigure, IFSelect_SelectExplore)

IGESSelect_SelectBypassSubfigure::IGESSelect_SelectBypassSubfigure(const int level)
    : IFSelect_SelectExplore(level)
{
}

bool IGESSelect_SelectBypassSubfigure::Explore(const int,
                                               const occ::handle<Standard_Transient>& ent,
                                               const Interface_Graph&,
                                               Interface_EntityIterator& explored) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  int igt = igesent->TypeNumber();

  if (igt == 308)
  {
    DeclareAndCast(IGESBasic_SubfigureDef, subf, ent);
    if (subf.IsNull())
      return true;
    int i, nb = subf->NbEntities();
    for (i = 1; i <= nb; i++)
      explored.AddItem(subf->AssociatedEntity(i));
    return true;
  }
  if (igt == 408)
  {
    DeclareAndCast(IGESBasic_SingularSubfigure, subf, ent);
    explored.AddItem(subf->Subfigure());
  }

  if (igt == 320)
  {
    DeclareAndCast(IGESDraw_NetworkSubfigureDef, subf, ent);
    if (subf.IsNull())
      return true;
    int i, nb = subf->NbEntities();
    for (i = 1; i <= nb; i++)
      explored.AddItem(subf->Entity(i));
    return true;
  }
  if (igt == 420)
  {
    DeclareAndCast(IGESDraw_NetworkSubfigure, subf, ent);
    explored.AddItem(subf->SubfigureDefinition());
  }

  if (igt == 412)
  {
    DeclareAndCast(IGESDraw_RectArraySubfigure, subf, ent);
    explored.AddItem(subf->BaseEntity());
  }
  if (igt == 414)
  {
    DeclareAndCast(IGESDraw_CircArraySubfigure, subf, ent);
    explored.AddItem(subf->BaseEntity());
  }

  return true;
}

TCollection_AsciiString IGESSelect_SelectBypassSubfigure::ExploreLabel() const
{
  return TCollection_AsciiString("Content of Subfigures");
}
