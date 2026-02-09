#include <IFSelect_PacketList.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_InterfaceError.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_PacketList, Standard_Transient)

IFSelect_PacketList::IFSelect_PacketList(const occ::handle<Interface_InterfaceModel>& model)
    : thedupls(0, model->NbEntities()),
      thepacks(100),
      theflags(0, model->NbEntities()),
      thename("Packets")
{
  themodel = model;
  thelast  = 0;
  thebegin = false;
  thedupls.Init(0);
  theflags.Init(0);
}

void IFSelect_PacketList::SetName(const char* name)
{
  thename.Clear();
  thename.AssignCat(name);
}

const char* IFSelect_PacketList::Name() const
{
  return thename.ToCString();
}

occ::handle<Interface_InterfaceModel> IFSelect_PacketList::Model() const
{
  return themodel;
}

void IFSelect_PacketList::AddPacket()
{
  int nbl = thepacks.NbEntities();
  int nbe = theflags.Upper();
  for (int i = 1; i <= nbe; i++)
    theflags.SetValue(i, 0);

  if (thelast >= nbl)
    thepacks.SetNbEntities(nbl * 2);

  if (!thebegin)
    thelast++;
  thepacks.SetNumber(thelast);
  thebegin = false;
}

void IFSelect_PacketList::Add(const occ::handle<Standard_Transient>& ent)
{
  int num = themodel->Number(ent);
  if (num == 0)
    throw Interface_InterfaceError("PacketList:Add, Entity not in Model");
  if (thelast == 0)
    throw Interface_InterfaceError("PacketList:Add, no Packet yet added");
  if (theflags(num) != 0)
    return;
  theflags(num) = 1;
  thedupls(num)++;
  thepacks.Add(num);
  thebegin = false;
}

void IFSelect_PacketList::AddList(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list)
{
  if (list.IsNull())
    return;
  int i, nb = list->Length();
  thepacks.Reservate(nb + 1);
  for (i = 1; i <= nb; i++)
    Add(list->Value(i));
}

int IFSelect_PacketList::NbPackets() const
{
  return (thebegin ? thelast - 1 : thelast);
}

int IFSelect_PacketList::NbEntities(const int numpack) const
{
  if (numpack <= 0 || numpack > NbPackets())
    return 0;
  Interface_IntList lisi(thepacks, false);
  lisi.SetNumber(numpack);
  return lisi.Length();
}

Interface_EntityIterator IFSelect_PacketList::Entities(const int numpack) const
{
  Interface_EntityIterator list;
  if (numpack <= 0 || numpack > NbPackets())
    return list;
  Interface_IntList lisi(thepacks, false);
  lisi.SetNumber(numpack);
  int i, nb = lisi.Length();
  for (i = 1; i <= nb; i++)
    list.AddItem(themodel->Value(lisi.Value(i)));
  return list;
}

int IFSelect_PacketList::HighestDuplicationCount() const
{
  int i, nb = themodel->NbEntities();
  int high = 0;
  for (i = 1; i <= nb; i++)
  {
    int j = thedupls.Value(i);
    if (j > high)
      high = j;
  }
  return high;
}

int IFSelect_PacketList::NbDuplicated(const int newcount, const bool andmore) const
{
  int i, nb = themodel->NbEntities();
  int nbdu = 0;

  for (i = 1; i <= nb; i++)
  {
    int j = thedupls.Value(i);
    if (j == newcount || (j > newcount && andmore))
      nbdu++;
  }
  return nbdu;
}

Interface_EntityIterator IFSelect_PacketList::Duplicated(const int  newcount,
                                                         const bool andmore) const
{
  int                      nb = themodel->NbEntities();
  Interface_EntityIterator list;

  int i;
  for (i = 1; i <= nb; i++)
  {
    int j = thedupls.Value(i);
    if (j == newcount || (j > newcount && andmore))
      list.AddItem(themodel->Value(i));
  }
  return list;
}
