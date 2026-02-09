

#include <IFSelect_ContextModif.hpp>
#include <IFSelect_GeneralModifier.hpp>
#include <IFSelect_Selection.hpp>
#include <Interface_Check.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_CopyControl.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>

IFSelect_ContextModif::IFSelect_ContextModif(const Interface_Graph&    graph,
                                             const Interface_CopyTool& TC,
                                             const char*               filename)
    : thegraf(graph, false),
      thefile(filename),
      thelist(graph.Size(), ' ')
{
  themap  = TC.Control();
  thesel  = false;
  thecurr = thecurt                  = 0;
  int                             nb = thelist.Length();
  occ::handle<Standard_Transient> newent;
  for (int i = 1; i <= nb; i++)
  {
    if (themap->Search(graph.Entity(i), newent))
      thelist.SetValue(i, '1');
  }
}

IFSelect_ContextModif::IFSelect_ContextModif(const Interface_Graph& graph, const char* filename)
    : thegraf(graph, false),
      thefile(filename),
      thelist(graph.Size(), ' ')
{
  thesel  = false;
  thecurr = thecurt                  = 0;
  int                             nb = thelist.Length();
  occ::handle<Standard_Transient> newent;
  for (int i = 1; i <= nb; i++)
    thelist.SetValue(i, '1');
}

void IFSelect_ContextModif::Select(Interface_EntityIterator& list)
{
  thesel = true;
  int nb = thelist.Length();
  for (int i = 1; i <= nb; i++)
    thelist.SetValue(i, ' ');
  for (list.Start(); list.More(); list.Next())
  {
    occ::handle<Standard_Transient> start, newent;
    start   = list.Value();
    int num = thegraf.EntityNumber(start);
    if (num > nb || num < 0)
      num = 0;
    if (themap.IsNull() && num > 0)
      thelist.SetValue(num, '1');
    else if (themap->Search(start, newent))
    {
      if (num > 0)
        thelist.SetValue(num, '1');
    }
  }
}

const Interface_Graph& IFSelect_ContextModif::OriginalGraph() const
{
  return thegraf;
}

occ::handle<Interface_InterfaceModel> IFSelect_ContextModif::OriginalModel() const
{
  return thegraf.Model();
}

void IFSelect_ContextModif::SetProtocol(const occ::handle<Interface_Protocol>& prot)
{
  theprot = prot;
}

occ::handle<Interface_Protocol> IFSelect_ContextModif::Protocol() const
{
  return theprot;
}

bool IFSelect_ContextModif::HasFileName() const
{
  return (thefile.Length() > 0);
}

const char* IFSelect_ContextModif::FileName() const
{
  return thefile.ToCString();
}

occ::handle<Interface_CopyControl> IFSelect_ContextModif::Control() const
{
  return themap;
}

bool IFSelect_ContextModif::IsForNone() const
{
  if (!thesel)
    return false;
  int nb = thelist.Length();
  for (int i = 1; i <= nb; i++)
  {
    if (thelist.Value(i) != ' ')
      return false;
  }
  return true;
}

bool IFSelect_ContextModif::IsForAll() const
{
  return (!thesel);
}

bool IFSelect_ContextModif::IsTransferred(const occ::handle<Standard_Transient>& ent) const
{
  if (themap.IsNull())
    return true;
  occ::handle<Standard_Transient> newent;
  return themap->Search(ent, newent);
}

bool IFSelect_ContextModif::IsSelected(const occ::handle<Standard_Transient>& ent) const
{

  int num = thegraf.EntityNumber(ent);
  if (num == 0)
    return false;
  return (thelist.Value(num) != ' ');
}

Interface_EntityIterator IFSelect_ContextModif::SelectedOriginal() const
{
  Interface_EntityIterator list;
  int                      nb = thelist.Length();
  for (int i = 1; i <= nb; i++)
  {
    if (thelist.Value(i) != ' ')
      list.GetOneItem(thegraf.Entity(i));
  }
  return list;
}

Interface_EntityIterator IFSelect_ContextModif::SelectedResult() const
{
  Interface_EntityIterator list;
  int                      nb = thelist.Length();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> newent;
    if (themap.IsNull())
      newent = thegraf.Entity(i);
    else if (thelist.Value(i) != ' ')
      themap->Search(thegraf.Entity(i), newent);
    if (!newent.IsNull())
      list.GetOneItem(newent);
  }
  return list;
}

int IFSelect_ContextModif::SelectedCount() const
{
  int nb = thelist.Length();
  int ns = 0;
  for (int i = 1; i <= nb; i++)
  {
    if (thelist.Value(i) != ' ')
      ns++;
  }
  return ns;
}

void IFSelect_ContextModif::Start()
{
  thecurr = thecurt = 0;
  Next();
}

bool IFSelect_ContextModif::More() const
{
  return (thecurr > 0);
}

void IFSelect_ContextModif::Next()
{
  int nb = thelist.Length();

  for (int i = thecurr + 1; i <= nb; i++)
  {
    if (thelist.Value(i) != ' ')
    {
      thecurr = i;
      thecurt++;
      return;
    }
  }
  thecurr = thecurt = 0;
}

occ::handle<Standard_Transient> IFSelect_ContextModif::ValueOriginal() const
{
  if (thecurr <= 0)
    throw Standard_NoSuchObject("IFSelect_ContextModif");
  return thegraf.Entity(thecurr);
}

occ::handle<Standard_Transient> IFSelect_ContextModif::ValueResult() const
{
  if (thecurr <= 0)
    throw Standard_NoSuchObject("IFSelect_ContextModif");
  occ::handle<Standard_Transient> ent, newent;
  ent = thegraf.Entity(thecurr);
  if (themap.IsNull())
    newent = ent;
  else
    themap->Search(ent, newent);
  return newent;
}

void IFSelect_ContextModif::TraceModifier(const occ::handle<IFSelect_GeneralModifier>& modif)
{
  if (modif.IsNull())
    return;

  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  sout << "---   Run Modifier:" << std::endl;
  occ::handle<IFSelect_Selection> sel = modif->Selection();
  if (!sel.IsNull())
    sout << "      Selection:" << sel->Label();
  else
    sout << "  (no Selection)";

  int ne = 0, nb = thelist.Length();
  for (int i = 1; i <= nb; i++)
  {
    if (thelist.Value(i) != ' ')
      ne++;
  }
  if (nb == ne)
    sout << "  All Model (" << nb << " Entities)" << std::endl;
  else
    sout << "  Entities,Total:" << nb << " Concerned:" << ne << std::endl;
}

void IFSelect_ContextModif::Trace(const char* mess)
{

  if (thecurr <= 0)
    return;
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  if (ValueOriginal() == ValueResult())
    sout << "--  ContextModif. Entity  n0 " << thecurr << std::endl;
  else
    sout << "--  ContextModif. Entity in Original, n0 " << thecurr << " in Result, n0 " << thecurt
         << std::endl;
  if (mess[0] != '\0')
    sout << "--  Message:" << mess << std::endl;
}

void IFSelect_ContextModif::AddCheck(const occ::handle<Interface_Check>& check)
{
  if (check->NbFails() + check->NbWarnings() == 0)
    return;
  const occ::handle<Standard_Transient>& ent = check->Entity();
  int                                    num = thegraf.EntityNumber(ent);
  if (num == 0 && !ent.IsNull())
    num = -1;
  thechek.Add(check, num);
}

void IFSelect_ContextModif::AddWarning(const occ::handle<Standard_Transient>& start,
                                       const char*                            mess,
                                       const char*                            orig)
{
  thechek.CCheck(thegraf.EntityNumber(start))->AddWarning(mess, orig);
}

void IFSelect_ContextModif::AddFail(const occ::handle<Standard_Transient>& start,
                                    const char*                            mess,
                                    const char*                            orig)
{
  thechek.CCheck(thegraf.EntityNumber(start))->AddFail(mess, orig);
}

occ::handle<Interface_Check> IFSelect_ContextModif::CCheck(const int num)
{
  occ::handle<Interface_Check> ach = thechek.CCheck(num);
  if (num > 0 && num <= thegraf.Size())
    ach->SetEntity(thegraf.Entity(num));
  return ach;
}

occ::handle<Interface_Check> IFSelect_ContextModif::CCheck(
  const occ::handle<Standard_Transient>& ent)
{
  int num = thegraf.EntityNumber(ent);
  if (num == 0)
    num = -1;
  occ::handle<Interface_Check>& ach = thechek.CCheck(num);
  ach->SetEntity(ent);
  return ach;
}

Interface_CheckIterator IFSelect_ContextModif::CheckList() const
{
  return thechek;
}
