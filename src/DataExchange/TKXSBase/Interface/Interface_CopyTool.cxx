

#include <Interface_CopyControl.hpp>
#include <Interface_CopyMap.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_InterfaceError.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ReportEntity.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_HAsciiString.hpp>

Interface_CopyTool::Interface_CopyTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                       const Interface_GeneralLib&                  lib)
    : thelib(lib),
      thelst(amodel->NbEntities())
{
  thelst.Init(false);
  themod = amodel;
  themap = new Interface_CopyMap(amodel);
  therep = new Interface_CopyMap(amodel);
  thelev = 0;
  theimp = false;
}

Interface_CopyTool::Interface_CopyTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                       const occ::handle<Interface_Protocol>&       protocol)
    : thelib(protocol),
      thelst(amodel->NbEntities())
{
  thelst.Init(false);
  themod = amodel;
  themap = new Interface_CopyMap(amodel);
  therep = new Interface_CopyMap(amodel);
  thelev = 0;
  theimp = false;
}

Interface_CopyTool::Interface_CopyTool(const occ::handle<Interface_InterfaceModel>& amodel)
    : thelib(Interface_Protocol::Active()),
      thelst(amodel->NbEntities())
{
  if (Interface_Protocol::Active().IsNull())
    throw Interface_InterfaceError("Interface CopyTool : Create with Active Protocol undefined");

  thelst.Init(false);
  themod = amodel;
  themap = new Interface_CopyMap(amodel);
  therep = new Interface_CopyMap(amodel);
  thelev = 0;
  theimp = false;
}

occ::handle<Interface_InterfaceModel> Interface_CopyTool::Model() const
{
  return themod;
}

void Interface_CopyTool::SetControl(const occ::handle<Interface_CopyControl>& othermap)
{
  themap = othermap;
}

occ::handle<Interface_CopyControl> Interface_CopyTool::Control() const
{
  return themap;
}

void Interface_CopyTool::Clear()
{
  themap->Clear();
  therep->Clear();
  thelev = 0;
  theimp = false;
  therts.Clear();
  ClearLastFlags();
}

bool Interface_CopyTool::NewVoid(const occ::handle<Standard_Transient>& entfrom,
                                 occ::handle<Standard_Transient>&       entto)
{
  if (entfrom == theent)
  {
    if (themdu.IsNull())
      return false;
    return themdu->NewVoid(theCN, entto);
  }
  theent   = entfrom;
  bool res = thelib.Select(entfrom, themdu, theCN);
  if (res)
    res = themdu->NewVoid(theCN, entto);
  if (!res)
    res = themdu->NewCopiedCase(theCN, entfrom, entto, *this);

  return res;
}

bool Interface_CopyTool::Copy(const occ::handle<Standard_Transient>& entfrom,
                              occ::handle<Standard_Transient>&       entto,
                              const bool                             mapped,
                              const bool                             errstat)
{
  bool res = true;
  if (entfrom == theent)
  {
    if (themdu.IsNull())
      res = false;
  }
  else
  {
    theent = entfrom;
    res    = thelib.Select(entfrom, themdu, theCN);
  }
  if (!res)
  {

    if (entfrom.IsNull())
      return res;
    if (entfrom->DynamicType() == STANDARD_TYPE(TCollection_HAsciiString))
    {
      entto = new TCollection_HAsciiString(
        occ::down_cast<TCollection_HAsciiString>(entfrom)->ToCString());
      res = true;
    }
    return res;
  }

  res = NewVoid(entfrom, entto);
  if (mapped)
    themap->Bind(entfrom, entto);

  if (!errstat)
    themdu->CopyCase(theCN, entfrom, entto, *this);
  return res;
}

void Interface_CopyTool::Implied(const occ::handle<Standard_Transient>& entfrom,
                                 const occ::handle<Standard_Transient>& entto)
{
  occ::handle<Interface_GeneralModule> module;
  int                                  CN;
  if (thelib.Select(entfrom, module, CN))
    module->RenewImpliedCase(CN, entfrom, entto, *this);
}

occ::handle<Standard_Transient> Interface_CopyTool::Transferred(
  const occ::handle<Standard_Transient>& ent)
{
  occ::handle<Standard_Transient> res;
  if (ent.IsNull())
    return res;
  int nument = themod->Number(ent);

  if (nument == 0 && thelev > 100)
    throw Interface_InterfaceError(
      "CopyTool : Transferred, Entity is not contained in Starting Model");
  if (!themap->Search(ent, res))
  {

    if (!Copy(ent, res, (nument != 0), themod->IsRedefinedContent(nument)))
      return res;

    thelev++;
    if (nument != 0)
      thelst.SetTrue(nument);
    occ::handle<Interface_ReportEntity> rep;
    if (nument != 0)
      rep = themod->ReportEntity(nument);
    if (!rep.IsNull())
    {

      if (rep->IsUnknown())
        therep->Bind(ent, new Interface_ReportEntity(res));
      else
      {
        occ::handle<Standard_Transient> contfrom, contto;
        contfrom                                  = rep->Content();
        occ::handle<Interface_ReportEntity> repto = new Interface_ReportEntity(rep->Check(), res);
        if (!contfrom.IsNull())
        {
          if (contfrom == ent)
            contto = res;
          else
            Copy(contfrom, contto, themod->Contains(contfrom), false);
          repto->SetContent(contto);
        }
        therep->Bind(ent, repto);
      }
    }

    thelev--;
  }
  if (thelev == 0 && nument > 0)
    therts.Append(nument);
  return res;
}

void Interface_CopyTool::Bind(const occ::handle<Standard_Transient>& ent,
                              const occ::handle<Standard_Transient>& res)
{
  int num = themod->Number(ent);
  themap->Bind(ent, res);
  thelst.SetTrue(num);
}

bool Interface_CopyTool::Search(const occ::handle<Standard_Transient>& ent,
                                occ::handle<Standard_Transient>&       res) const
{
  return themap->Search(ent, res);
}

void Interface_CopyTool::ClearLastFlags()
{
  thelst.Init(false);
}

int Interface_CopyTool::LastCopiedAfter(const int                        numfrom,
                                        occ::handle<Standard_Transient>& ent,
                                        occ::handle<Standard_Transient>& res) const
{
  int nb = thelst.Length();
  for (int num = numfrom + 1; num <= nb; num++)
  {
    if (thelst.Value(num))
    {
      ent = themod->Value(num);
      if (themap->Search(ent, res))
        return num;
    }
  }
  return 0;
}

void Interface_CopyTool::TransferEntity(const occ::handle<Standard_Transient>& ent)
{
  occ::handle<Standard_Transient> res = Transferred(ent);
}

void Interface_CopyTool::RenewImpliedRefs()
{
  if (theimp)
    return;
  theimp = true;

  int nb = themod->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> ent = themod->Value(i);
    occ::handle<Standard_Transient> res;
    if (!themap->Search(ent, res))
      continue;

    occ::handle<Standard_Transient> aRep;
    if (!therep->Search(ent, aRep))
    {
      Implied(ent, res);
    }
    else
    {
      occ::handle<Interface_ReportEntity> rep = occ::down_cast<Interface_ReportEntity>(aRep);
      if (!rep.IsNull() && !rep->HasNewContent())
        Implied(ent, res);
    }
  }
}

void Interface_CopyTool::FillModel(const occ::handle<Interface_InterfaceModel>& bmodel)
{

  bmodel->Clear();
  bmodel->GetFromAnother(themod);

  Interface_EntityIterator list = CompleteResult(true);
  bmodel->GetFromTransfer(list);

  RenewImpliedRefs();
}

Interface_EntityIterator Interface_CopyTool::CompleteResult(const bool withreports) const
{
  Interface_EntityIterator iter;
  int                      nb = themod->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> ent = themod->Value(i);
    occ::handle<Standard_Transient> res;
    if (!themap->Search(ent, res))
      continue;
    if (withreports)
    {
      occ::handle<Standard_Transient> rep;
      if (therep->Search(ent, rep))
        res = rep;
    }
    iter.GetOneItem(res);
  }
  return iter;
}

Interface_EntityIterator Interface_CopyTool::RootResult(const bool withreports) const
{
  Interface_EntityIterator iter;
  int                      nb = therts.Length();
  for (int i = 1; i <= nb; i++)
  {
    int                             j   = therts.Value(i);
    occ::handle<Standard_Transient> ent = themod->Value(j);
    occ::handle<Standard_Transient> res;
    if (!themap->Search(ent, res))
      continue;
    if (withreports)
    {
      occ::handle<Standard_Transient> rep;
      if (therep->Search(ent, rep))
        res = rep;
    }
    iter.GetOneItem(res);
  }
  return iter;
}

Interface_CopyTool::~Interface_CopyTool() = default;
