

#include <IFSelect_AppliedModifiers.hpp>
#include <IFSelect_ContextModif.hpp>
#include <IFSelect_ContextWrite.hpp>
#include <IFSelect_GeneralModifier.hpp>
#include <IFSelect_ModelCopier.hpp>
#include <IFSelect_Modifier.hpp>
#include <IFSelect_Selection.hpp>
#include <IFSelect_ShareOut.hpp>
#include <IFSelect_ShareOutResult.hpp>
#include <IFSelect_WorkLibrary.hpp>
#include <Interface_Check.hpp>
#include <Interface_CheckIterator.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IFSelect_ModelCopier, Standard_Transient)

IFSelect_ModelCopier::IFSelect_ModelCopier() = default;

void IFSelect_ModelCopier::SetShareOut(const occ::handle<IFSelect_ShareOut>& sho)
{
  theshareout = sho;
}

void IFSelect_ModelCopier::ClearResult()
{
  thefilemodels.Clear();
  thefilenames.Clear();
  theapplieds.Clear();
  theremain.Nullify();
}

bool IFSelect_ModelCopier::AddFile(const TCollection_AsciiString&               filename,
                                   const occ::handle<Interface_InterfaceModel>& content)
{
  int nb = thefilenames.Length();
  for (int i = 1; i <= nb; i++)
  {
    if (filename.IsEmpty())
      continue;
    if (thefilenames(i).IsEqual(filename))
      return false;
  }
  occ::handle<IFSelect_AppliedModifiers> nulapplied;
  thefilenames.Append(filename);
  thefilemodels.Append(content);
  theapplieds.Append(nulapplied);
  return true;
}

bool IFSelect_ModelCopier::NameFile(const int num, const TCollection_AsciiString& filename)
{
  int nb = thefilenames.Length();
  if (num <= 0 || num > nb)
    return false;
  for (int i = 1; i <= nb; i++)
  {
    if (filename.IsEmpty())
      continue;
    if (thefilenames(i).IsEqual(filename))
      return false;
  }
  thefilenames.SetValue(num, filename);
  return true;
}

bool IFSelect_ModelCopier::ClearFile(const int num)
{
  int nb = thefilenames.Length();
  if (num <= 0 || num > nb)
    return false;
  thefilenames.ChangeValue(num).Clear();
  return true;
}

bool IFSelect_ModelCopier::SetAppliedModifiers(
  const int                                     num,
  const occ::handle<IFSelect_AppliedModifiers>& applied)
{
  int nb = theapplieds.Length();
  if (num <= 0 || num > nb)
    return false;
  theapplieds.SetValue(num, applied);
  return true;
}

bool IFSelect_ModelCopier::ClearAppliedModifiers(const int num)
{
  int nb = theapplieds.Length();
  if (num <= 0 || num > nb)
    return false;
  theapplieds.ChangeValue(num).Nullify();
  return true;
}

Interface_CheckIterator IFSelect_ModelCopier::Copy(IFSelect_ShareOutResult&                 eval,
                                                   const occ::handle<IFSelect_WorkLibrary>& WL,
                                                   const occ::handle<Interface_Protocol>& protocol)
{
  Interface_CopyTool TC(eval.Graph().Model(), protocol);
  return Copying(eval, WL, protocol, TC);
}

Interface_CheckIterator IFSelect_ModelCopier::Copying(
  IFSelect_ShareOutResult&                 eval,
  const occ::handle<IFSelect_WorkLibrary>& WL,
  const occ::handle<Interface_Protocol>&   protocol,
  Interface_CopyTool&                      TC)
{
  Message::SendInfo() << "** WorkSession : Copying split data before sending" << std::endl;
  const Interface_Graph&  G = eval.Graph();
  Interface_CheckIterator checks;
  theshareout = eval.ShareOut();
  theremain   = new NCollection_HArray1<int>(0, G.Size());
  theremain->Init(0);
  for (eval.Evaluate(); eval.More(); eval.Next())
  {
    occ::handle<Interface_InterfaceModel> model;
    TCollection_AsciiString               filename = eval.FileName();
    int                                   dispnum  = eval.DispatchRank();
    int                                   numod, nbmod;
    eval.PacketsInDispatch(numod, nbmod);
    occ::handle<IFSelect_AppliedModifiers> curapp;
    CopiedModel(G,
                WL,
                protocol,
                eval.PacketRoot(),
                filename,
                dispnum,
                numod,
                TC,
                model,
                curapp,
                checks);

    AddFile(filename, model);
    theapplieds.SetValue(theapplieds.Length(), curapp);
  }
  theshareout->SetLastRun(theshareout->NbDispatches());
  checks.SetName("X-STEP WorkSession : Split Copy (no Write)");
  return checks;
}

Interface_CheckIterator IFSelect_ModelCopier::SendCopied(
  const occ::handle<IFSelect_WorkLibrary>& WL,
  const occ::handle<Interface_Protocol>&   protocol)
{
  Message::SendInfo() << "** WorkSession : Sending split data already copied" << std::endl;
  int                     nb = NbFiles();
  Interface_CheckIterator checks;
  if (nb > 0)
  {
    for (int i = 1; i <= nb; i++)
    {
      if (FileName(i).Length() == 0)
        continue;
      occ::handle<IFSelect_AppliedModifiers> curapp = theapplieds.Value(i);
      IFSelect_ContextWrite   ctx(FileModel(i), protocol, curapp, FileName(i).ToCString());
      bool                    res      = WL->WriteFile(ctx);
      Interface_CheckIterator checklst = ctx.CheckList();
      checks.Merge(checklst);

      if (!res)
      {
        char mess[100];
        Sprintf(mess, "Split Send (WriteFile) abandon on file n0.%d", i);
        checks.CCheck(0)->AddFail(mess);
        Message::SendInfo() << "  **  Sending File n0." << i << " has failed, abandon  **"
                            << std::endl;
        return checks;
      }
      AddSentFile(FileName(i).ToCString());
    }
    ClearResult();
  }
  checks.SetName("X-STEP WorkSession : Split Send (Copy+Write)");
  return checks;
}

Interface_CheckIterator IFSelect_ModelCopier::Send(IFSelect_ShareOutResult&                 eval,
                                                   const occ::handle<IFSelect_WorkLibrary>& WL,
                                                   const occ::handle<Interface_Protocol>& protocol)
{
  Interface_CopyTool TC(eval.Graph().Model(), protocol);
  return Sending(eval, WL, protocol, TC);
}

Interface_CheckIterator IFSelect_ModelCopier::Sending(
  IFSelect_ShareOutResult&                 eval,
  const occ::handle<IFSelect_WorkLibrary>& WL,
  const occ::handle<Interface_Protocol>&   protocol,
  Interface_CopyTool&                      TC)
{
  const Interface_Graph&  G = eval.Graph();
  Interface_CheckIterator checks;
  int                     i = 0;
  Message::SendInfo() << "** WorkSession : Copying then sending split data" << std::endl;
  theshareout = eval.ShareOut();
  theremain   = new NCollection_HArray1<int>(0, G.Size());
  theremain->Init(0);
  for (eval.Evaluate(); eval.More(); eval.Next())
  {
    i++;
    occ::handle<Interface_InterfaceModel> model;
    TCollection_AsciiString               filename = eval.FileName();
    int                                   dispnum  = eval.DispatchRank();
    int                                   numod, nbmod;
    eval.PacketsInDispatch(numod, nbmod);
    occ::handle<IFSelect_AppliedModifiers> curapp;
    CopiedModel(G,
                WL,
                protocol,
                eval.PacketRoot(),
                filename,
                dispnum,
                numod,
                TC,
                model,
                curapp,
                checks);
    IFSelect_ContextWrite   ctx(model, protocol, curapp, filename.ToCString());
    bool                    res      = WL->WriteFile(ctx);
    Interface_CheckIterator checklst = ctx.CheckList();
    checks.Merge(checklst);

    if (!res)
    {
      char mess[100];
      Sprintf(mess, "Split Send (WriteFile) abandon on file n0.%d", i);
      checks.CCheck(0)->AddFail(mess);
      Message::SendInfo() << "  **  Sending File " << filename << " has failed, abandon  **"
                          << std::endl;
      checks.SetName("X-STEP WorkSession : Split Send (only Write)");
      return checks;
    }
    AddSentFile(filename.ToCString());
  }
  theshareout->SetLastRun(theshareout->NbDispatches());
  checks.SetName("X-STEP WorkSession : Split Send (only Write)");
  return checks;
}

Interface_CheckIterator IFSelect_ModelCopier::SendAll(
  const char*                              filename,
  const Interface_Graph&                   G,
  const occ::handle<IFSelect_WorkLibrary>& WL,
  const occ::handle<Interface_Protocol>&   protocol)
{
  Interface_CheckIterator checks;
  checks.SetName("X-STEP WorkSession : Send All");
  Message::SendInfo() << "** WorkSession : Sending all data" << std::endl;
  const occ::handle<Interface_InterfaceModel>& model = G.Model();
  if (model.IsNull() || protocol.IsNull() || WL.IsNull())
    return checks;

  Interface_CopyTool TC(model, protocol);
  int                i, nb = model->NbEntities();
  for (i = 1; i <= nb; i++)
    TC.Bind(model->Value(i), model->Value(i));

  Interface_EntityIterator               pipo;
  occ::handle<Interface_InterfaceModel>  newmod;
  occ::handle<IFSelect_AppliedModifiers> applied;
  CopiedModel(G,
              WL,
              protocol,
              pipo,
              TCollection_AsciiString(filename),
              0,
              0,
              TC,
              newmod,
              applied,
              checks);

  IFSelect_ContextWrite   ctx(model, protocol, applied, filename);
  bool                    res      = WL->WriteFile(ctx);
  Interface_CheckIterator checklst = ctx.CheckList();
  checks.Merge(checklst);
  if (!res)
    checks.CCheck(0)->AddFail("SendAll (WriteFile) has failed");

  return checks;
}

Interface_CheckIterator IFSelect_ModelCopier::SendSelected(
  const char*                              filename,
  const Interface_Graph&                   G,
  const occ::handle<IFSelect_WorkLibrary>& WL,
  const occ::handle<Interface_Protocol>&   protocol,
  const Interface_EntityIterator&          list)
{
  Interface_CheckIterator checks;
  checks.SetName("X-STEP WorkSession : Send Selected");
  Message::SendInfo() << "** WorkSession : Sending selected data" << std::endl;
  const occ::handle<Interface_InterfaceModel>& original = G.Model();
  if (original.IsNull() || protocol.IsNull() || WL.IsNull())
    return checks;
  occ::handle<Interface_InterfaceModel> newmod = original->NewEmptyModel();
  Interface_CopyTool                    TC(original, protocol);
  TC.FillModel(newmod);

  Interface_GeneralLib lib(protocol);
  for (list.Start(); list.More(); list.Next())
  {
    newmod->AddWithRefs(list.Value(), lib);
  }
  int i, nb = newmod->NbEntities();
  for (i = 1; i <= nb; i++)
    TC.Bind(newmod->Value(i), newmod->Value(i));
  if (theremain.IsNull())
  {
    theremain = new NCollection_HArray1<int>(0, G.Size());
    theremain->Init(0);
  }

  Interface_EntityIterator               pipo;
  occ::handle<IFSelect_AppliedModifiers> applied;
  CopiedModel(G,
              WL,
              protocol,
              pipo,
              TCollection_AsciiString(filename),
              0,
              0,
              TC,
              newmod,
              applied,
              checks);

  occ::handle<Standard_Transient> ent1, ent2;
  for (int ic = TC.LastCopiedAfter(0, ent1, ent2); ic > 0; ic = TC.LastCopiedAfter(ic, ent1, ent2))
  {
    if (ic <= theremain->Upper())
      theremain->SetValue(ic, theremain->Value(ic) + 1);
  }
  IFSelect_ContextWrite   ctx(newmod, protocol, applied, filename);
  bool                    res      = WL->WriteFile(ctx);
  Interface_CheckIterator checklst = ctx.CheckList();
  checks.Merge(checklst);
  if (!res)
    checks.CCheck(0)->AddFail("SendSelected (WriteFile) has failed");

  return checks;
}

void IFSelect_ModelCopier::CopiedModel(const Interface_Graph&                   G,
                                       const occ::handle<IFSelect_WorkLibrary>& WL,
                                       const occ::handle<Interface_Protocol>&   protocol,
                                       const Interface_EntityIterator&          tocopy,
                                       const TCollection_AsciiString&           filename,
                                       const int                                dispnum,
                                       const int,
                                       Interface_CopyTool&                     TC,
                                       occ::handle<Interface_InterfaceModel>&  newmod,
                                       occ::handle<IFSelect_AppliedModifiers>& applied,
                                       Interface_CheckIterator&                checks) const
{

  applied.Nullify();
  const occ::handle<Interface_InterfaceModel>& original = G.Model();
  if (dispnum > 0)
  {
    newmod = original->NewEmptyModel();
    TC.Clear();
    WL->CopyModel(original, newmod, tocopy, TC);

    occ::handle<Standard_Transient> ent1, ent2;

    for (int ic = TC.LastCopiedAfter(0, ent1, ent2); ic > 0;
         ic     = TC.LastCopiedAfter(ic, ent1, ent2))
    {
      if (ic <= theremain->Upper())
        theremain->SetValue(ic, theremain->Value(ic) + 1);
    }
  }
  else if (newmod.IsNull())
    newmod = original;

  int nbmod = 0;
  if (!theshareout.IsNull())
    nbmod = theshareout->NbModifiers(true);
  int i;
  for (i = 1; i <= nbmod; i++)
  {
    occ::handle<IFSelect_Modifier> unmod = theshareout->ModelModifier(i);

    if (dispnum > 0)
      if (!unmod->Applies(theshareout->Dispatch(dispnum)))
        continue;
    IFSelect_ContextModif ctx(G, TC, filename.ToCString());

    occ::handle<IFSelect_Selection> sel = unmod->Selection();
    if (!sel.IsNull())
    {
      Interface_EntityIterator entiter = sel->UniqueResult(G);
      ctx.Select(entiter);
    }
    if (ctx.IsForNone())
      continue;
    unmod->Perform(ctx, newmod, protocol, TC);
    Interface_CheckIterator checklst = ctx.CheckList();
    checks.Merge(checklst);
  }

  nbmod = 0;
  if (!theshareout.IsNull())
    nbmod = theshareout->NbModifiers(false);
  if (nbmod == 0)
    return;
  applied = new IFSelect_AppliedModifiers(nbmod, newmod->NbEntities());
  for (i = 1; i <= nbmod; i++)
  {
    occ::handle<IFSelect_GeneralModifier> unmod = theshareout->GeneralModifier(false, i);

    if (dispnum > 0)
      if (!unmod->Applies(theshareout->Dispatch(dispnum)))
        continue;

    occ::handle<IFSelect_Selection> sel = unmod->Selection();
    if (sel.IsNull())
      applied->AddModif(unmod);
    else
    {
      Interface_EntityIterator        list = sel->UniqueResult(G);
      occ::handle<Standard_Transient> newent;

      for (list.Start(); list.More(); list.Next())
      {
        if (TC.Search(list.Value(), newent))
          applied->AddNum(newmod->Number(newent));
      }
    }
  }
}

void IFSelect_ModelCopier::CopiedRemaining(const Interface_Graph&                   G,
                                           const occ::handle<IFSelect_WorkLibrary>& WL,
                                           Interface_CopyTool&                      TC,
                                           occ::handle<Interface_InterfaceModel>&   newmod)
{
  const occ::handle<Interface_InterfaceModel>& original = G.Model();

  newmod = original->NewEmptyModel();
  TC.Clear();
  Interface_EntityIterator tocopy;
  int                      nb = G.Size();
  theremain                   = new NCollection_HArray1<int>(0, nb + 1);
  theremain->Init(0);
  for (int i = 1; i <= nb; i++)
  {
    if (G.Status(i) == 0)
      tocopy.AddItem(original->Value(i));
    else
      theremain->SetValue(i, -1);
  }
  WL->CopyModel(original, newmod, tocopy, TC);

  if (newmod->NbEntities() == 0)
    newmod.Nullify();
  else
  {

    occ::handle<Standard_Transient> ent1, ent2;
    for (int ic = TC.LastCopiedAfter(0, ent1, ent2); ic > 0;
         ic     = TC.LastCopiedAfter(ic, ent1, ent2))
    {
      if (ic <= theremain->Upper())
        theremain->SetValue(ic, 1);
    }

#ifdef MISOPOINT
    std::cout << " Remaining Model : " << newmod->NbEntities() << " Entities" << std::endl;
    int ne = 0;
    for (i = 1; i <= nb; i++)
    {
      if (theremain->Value(i) == 0)
      {
        if (ne == 0)
          std::cout << " Refractory : ";
        ne++;
        std::cout << " " << i;
      }
    }
    if (ne > 0)
      std::cout << "  -- " << ne << " Entities" << std::endl;
    else
      std::cout << "  -- Remaining data complete" << std::endl;
#endif
  }
}

bool IFSelect_ModelCopier::SetRemaining(Interface_Graph& CG) const
{
  int nb = CG.Size();
  if (theremain.IsNull())
    return (nb == 0);
  if (nb != theremain->Upper())
    return false;
  for (int i = 1; i <= nb; i++)
  {
    if (CG.Status(i) >= 0)
      CG.SetStatus(i, CG.Status(i) + theremain->Value(i));
  }
  theremain->Init(0);
  return true;
}

int IFSelect_ModelCopier::NbFiles() const
{
  return thefilemodels.Length();
}

TCollection_AsciiString IFSelect_ModelCopier::FileName(const int num) const
{
  return thefilenames.Value(num);
}

occ::handle<Interface_InterfaceModel> IFSelect_ModelCopier::FileModel(const int num) const
{
  return thefilemodels.Value(num);
}

occ::handle<IFSelect_AppliedModifiers> IFSelect_ModelCopier::AppliedModifiers(const int num) const
{
  return theapplieds.Value(num);
}

void IFSelect_ModelCopier::BeginSentFiles(const occ::handle<IFSelect_ShareOut>& sho,
                                          const bool                            record)
{
  thesentfiles.Nullify();
  if (record)
    thesentfiles = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();

  if (sho.IsNull())
    return;
  int lastrun = sho->LastRun();
  sho->ClearResult(true);
  sho->SetLastRun(lastrun);
}

void IFSelect_ModelCopier::AddSentFile(const char* filename)
{
  if (!thesentfiles.IsNull())
    thesentfiles->Append(new TCollection_HAsciiString(filename));
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> IFSelect_ModelCopier::
  SentFiles() const
{
  return thesentfiles;
}
