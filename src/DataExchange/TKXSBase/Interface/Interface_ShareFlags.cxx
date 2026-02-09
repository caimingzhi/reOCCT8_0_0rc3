

#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GTool.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ReportEntity.hpp>
#include <Interface_ShareFlags.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Transient.hpp>

Interface_ShareFlags::Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel,
                                           const Interface_GeneralLib&                  lib)
    : theflags(amodel->NbEntities())
{
  occ::handle<Interface_GTool> gtool;
  themodel = amodel;
  Evaluate(lib, gtool);
}

Interface_ShareFlags::Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel,
                                           const occ::handle<Interface_GTool>&          gtool)
    : theflags(amodel->NbEntities())
{
  themodel = amodel;
  Evaluate(gtool->Lib(), gtool);
}

Interface_ShareFlags::Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel,
                                           const occ::handle<Interface_Protocol>&       protocol)
    : theflags(amodel->NbEntities())
{
  occ::handle<Interface_GTool> gtool;
  themodel = amodel;
  Evaluate(Interface_GeneralLib(protocol), gtool);
}

Interface_ShareFlags::Interface_ShareFlags(const occ::handle<Interface_InterfaceModel>& amodel)
    : theflags(amodel->NbEntities())
{
  occ::handle<Interface_GTool> gtool = themodel->GTool();
  gtool->Reservate(amodel->NbEntities());
  themodel = amodel;
  Evaluate(gtool->Lib(), gtool);
}

Interface_ShareFlags::Interface_ShareFlags(const Interface_Graph& agraph)
    : theflags(agraph.Model()->NbEntities())
{
  themodel = agraph.Model();
  int nb   = themodel->NbEntities();
  if (nb == 0)
    return;
  theroots = new NCollection_HSequence<occ::handle<Standard_Transient>>();
  for (int i = 1; i <= nb; i++)
  {

    occ::handle<Standard_Transient>                                     ent = themodel->Value(i);
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> list =
      agraph.GetSharings(ent);

    if (!list.IsNull() && list->Length() > 0)
      theflags.SetTrue(i);
    else
      theroots->Append(ent);
  }
}

void Interface_ShareFlags::Evaluate(const Interface_GeneralLib&         lib,
                                    const occ::handle<Interface_GTool>& gtool)
{
  bool patool = gtool.IsNull();
  int  nb     = themodel->NbEntities();
  if (nb == 0)
    return;
  theroots = new NCollection_HSequence<occ::handle<Standard_Transient>>();
  int i;
  for (i = 1; i <= nb; i++)
  {

    occ::handle<Standard_Transient> ent = themodel->Value(i);
    if (themodel->IsRedefinedContent(i))
      ent = themodel->ReportEntity(i)->Content();

    Interface_EntityIterator             iter;
    occ::handle<Interface_GeneralModule> module;
    int                                  CN;
    if (patool)
    {
      if (lib.Select(ent, module, CN))
        module->FillShared(themodel, CN, ent, iter);
    }
    else
    {
      if (gtool->Select(ent, module, CN))
        module->FillShared(themodel, CN, ent, iter);
    }

    for (iter.Start(); iter.More(); iter.Next())
    {
      int num = themodel->Number(iter.Value());
      theflags.SetTrue(num);
    }
  }
  for (i = 1; i <= nb; i++)
  {
    if (!theflags.Value(i))
      theroots->Append(themodel->Value(i));
  }
}

occ::handle<Interface_InterfaceModel> Interface_ShareFlags::Model() const
{
  return themodel;
}

bool Interface_ShareFlags::IsShared(const occ::handle<Standard_Transient>& ent) const
{
  int num = themodel->Number(ent);
  if (num == 0 || num > themodel->NbEntities())
    throw Standard_DomainError("Interface ShareFlags : IsShared");
  return theflags.Value(num);
}

Interface_EntityIterator Interface_ShareFlags::RootEntities() const
{
  Interface_EntityIterator iter(theroots);
  return iter;
}

int Interface_ShareFlags::NbRoots() const
{
  return (theroots.IsNull() ? 0 : theroots->Length());
}

occ::handle<Standard_Transient> Interface_ShareFlags::Root(const int num) const
{
  return theroots->Value(num);
}
