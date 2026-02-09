

#include <IFSelect_PacketList.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_ViewKindEntity.hpp>
#include <IGESSelect_ViewSorter.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_ViewSorter, Standard_Transient)

#define PourDrawing 404

IGESSelect_ViewSorter::IGESSelect_ViewSorter() = default;

void IGESSelect_ViewSorter::SetModel(const occ::handle<IGESData_IGESModel>& model)
{
  themodel = model;
}

void IGESSelect_ViewSorter::Clear()
{
  int nb = themodel->NbEntities();
  if (nb < 100)
    nb = 100;
  themap.Clear();
  themap.ReSize(nb);
  theitems.Clear();
  theitems.ReSize(nb);
  thefinals.Clear();
  thefinals.ReSize(nb);
  theinditem.Clear();
  theindfin.Clear();
}

bool IGESSelect_ViewSorter::Add(const occ::handle<Standard_Transient>& ent)
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (!igesent.IsNull())
    return AddEntity(igesent);
  DeclareAndCast(NCollection_HSequence<occ::handle<Standard_Transient>>, list, ent);
  if (!list.IsNull())
  {
    AddList(list);
    return true;
  }
  DeclareAndCast(Interface_InterfaceModel, model, ent);
  if (!model.IsNull())
  {
    AddModel(model);
    return true;
  }
  return false;
}

bool IGESSelect_ViewSorter::AddEntity(const occ::handle<IGESData_IGESEntity>& igesent)
{

  if (igesent.IsNull())
    return false;
  if (themap.FindIndex(igesent))
    return false;
  themap.Add(igesent);

  occ::handle<IGESData_IGESEntity> view;
  if (igesent->TypeNumber() == PourDrawing)
    view = igesent;
  else
  {
    if (igesent->IsKind(STANDARD_TYPE(IGESData_ViewKindEntity)))
      view = igesent;
    else
      view = igesent->View();
  }

  int viewindex = 0;
  if (!view.IsNull())
  {
    viewindex = theitems.FindIndex(view);
    if (viewindex <= 0)
      viewindex = theitems.Add(view);
  }
  theinditem.Append(viewindex);
  theindfin.Append(0);
  return true;
}

void IGESSelect_ViewSorter::AddList(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list)
{
  int nb = list->Length();
  for (int i = 1; i <= nb; i++)
    Add(list->Value(i));
}

void IGESSelect_ViewSorter::AddModel(const occ::handle<Interface_InterfaceModel>& model)
{
  DeclareAndCast(IGESData_IGESModel, igesmod, model);
  if (igesmod.IsNull())
    return;
  int nb = igesmod->NbEntities();
  for (int i = 1; i <= nb; i++)
    AddEntity(igesmod->Entity(i));
}

int IGESSelect_ViewSorter::NbEntities() const
{
  return themap.Extent();
}

void IGESSelect_ViewSorter::SortSingleViews(const bool alsoframes)
{

  thefinals.Clear();
  int nb = theinditem.Length();

  for (int i = 1; i <= nb; i++)
  {
    int numitem    = theinditem.Value(i);
    int finalindex = 0;
    if (numitem > 0)
    {

      DeclareAndCast(IGESData_IGESEntity, item, theitems.FindKey(numitem));
      bool ok = false;
      if (alsoframes)
        ok = (item->TypeNumber() == PourDrawing);
      if (!ok)
      {
        DeclareAndCast(IGESData_ViewKindEntity, view, item);
        if (!view.IsNull())
          ok = view->IsSingle();
      }
      if (ok)
      {
        finalindex = thefinals.FindIndex(item);
        if (finalindex <= 0)
          finalindex = thefinals.Add(item);
      }
    }
    theindfin.SetValue(i, finalindex);
  }
}

void IGESSelect_ViewSorter::SortDrawings(const Interface_Graph& G)
{

  thefinals.Clear();
  int nb = theinditem.Length();

  for (int i = 1; i <= nb; i++)
  {
    int numitem    = theinditem.Value(i);
    int finalindex = 0;
    if (numitem > 0)
    {

      DeclareAndCast(IGESData_IGESEntity, item, theitems.FindKey(numitem));
      if (item.IsNull())
        continue;

      occ::handle<Standard_Transient> drawing;
      if (item->TypeNumber() == PourDrawing)
        drawing = item;
      else
      {
        Interface_EntityIterator list = G.Sharings(item);
        for (list.Start(); list.More(); list.Next())
        {
          DeclareAndCast(IGESData_IGESEntity, draw, list.Value());
          if (draw.IsNull())
            continue;
          if (draw->TypeNumber() == PourDrawing)
            drawing = draw;
        }
      }
      if (!drawing.IsNull())
      {
        finalindex = thefinals.FindIndex(drawing);
        if (finalindex <= 0)
          finalindex = thefinals.Add(drawing);
      }
    }
    theindfin.SetValue(i, finalindex);
  }
}

int IGESSelect_ViewSorter::NbSets(const bool final) const
{
  if (final)
    return thefinals.Extent();
  else
    return theitems.Extent();
}

occ::handle<IGESData_IGESEntity> IGESSelect_ViewSorter::SetItem(const int  num,
                                                                const bool final) const
{
  if (final)
    return GetCasted(IGESData_IGESEntity, thefinals.FindKey(num));
  else
    return GetCasted(IGESData_IGESEntity, theitems.FindKey(num));
}

occ::handle<IFSelect_PacketList> IGESSelect_ViewSorter::Sets(const bool final) const
{
  occ::handle<IFSelect_PacketList> list = new IFSelect_PacketList(themodel);
  int                              i, nb;
  nb      = (final ? theindfin.Length() : theinditem.Length());
  int nbs = NbSets(final);
  for (int num = 1; num <= nbs; num++)
  {
    list->AddPacket();
    if (final)
    {

      for (i = 1; i <= nb; i++)
      {
        if (theindfin.Value(i) != num)
          continue;
        list->Add(themap.FindKey(i));
      }
    }
    else
    {
      for (i = 1; i <= nb; i++)
      {
        if (theinditem.Value(i) != num)
          continue;
        list->Add(themap.FindKey(i));
      }
    }
  }
  return list;
}
