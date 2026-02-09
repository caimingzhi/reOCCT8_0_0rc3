

#include <IFGraph_AllShared.hpp>
#include <IFSelect_PacketList.hpp>
#include <IFSelect_ShareOut.hpp>
#include <IFSelect_ShareOutResult.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_GraphContent.hpp>
#include <Interface_InterfaceModel.hpp>
#include <TCollection_AsciiString.hpp>

IFSelect_ShareOutResult::IFSelect_ShareOutResult(
  const occ::handle<IFSelect_ShareOut>&        sho,
  const occ::handle<Interface_InterfaceModel>& amodel)
    : thegraph(amodel),
      thedispres(amodel, false)
{
  theshareout = sho;
  theeval     = false;
}

IFSelect_ShareOutResult::IFSelect_ShareOutResult(const occ::handle<IFSelect_ShareOut>& sho,
                                                 const Interface_Graph&                G)
    : thegraph(G),
      thedispres(G, false)
{
  theshareout = sho;
  theeval     = false;
}

IFSelect_ShareOutResult::IFSelect_ShareOutResult(
  const occ::handle<IFSelect_Dispatch>&        disp,
  const occ::handle<Interface_InterfaceModel>& amodel)
    : thegraph(amodel),
      thedispres(amodel, false)
{
  thedispatch = disp;
  theeval     = false;
}

IFSelect_ShareOutResult::IFSelect_ShareOutResult(const occ::handle<IFSelect_Dispatch>& disp,
                                                 const Interface_Graph&                G)
    : thegraph(G),
      thedispres(G, false)
{
  thedispatch = disp;
  theeval     = false;
}

occ::handle<IFSelect_ShareOut> IFSelect_ShareOutResult::ShareOut() const
{
  return theshareout;
}

const Interface_Graph& IFSelect_ShareOutResult::Graph() const
{
  return thegraph;
}

void IFSelect_ShareOutResult::Reset()
{
  theeval = false;
}

void IFSelect_ShareOutResult::Evaluate()
{
  if (theeval)
    return;
  Prepare();
  theeval = true;
}

occ::handle<IFSelect_PacketList> IFSelect_ShareOutResult::Packets(const bool complete)
{
  Evaluate();
  occ::handle<IFSelect_PacketList> list = new IFSelect_PacketList(thegraph.Model());
  Interface_EntityIterator         iter;
  for (; More(); Next())
  {
    list->AddPacket();
    if (complete)
      list->AddList(PacketContent().Content());
    else
      list->AddList(PacketRoot().Content());
  }
  return list;
}

int IFSelect_ShareOutResult::NbPackets()
{
  Evaluate();
  return thedispres.NbParts();
}

void IFSelect_ShareOutResult::Prepare()
{
  thedisplist.Clear();

  thedispres.Reset();
  IFGraph_AllShared              A(thegraph);
  occ::handle<IFSelect_Dispatch> disp = thedispatch;
  int                            nb = 1, first = 1;
  if (!theshareout.IsNull())
  {
    nb    = theshareout->NbDispatches();
    first = theshareout->LastRun() + 1;
  }
  int i;
  for (i = first; i <= nb; i++)
  {
    if (!theshareout.IsNull())
      disp = theshareout->Dispatch(i);
    if (disp->FinalSelection().IsNull())
      continue;
    IFGraph_SubPartsIterator packs(thegraph, false);
    disp->Packets(thegraph, packs);
    for (packs.Start(); packs.More(); packs.Next())
    {
      Interface_EntityIterator iter = packs.Entities();
      if (iter.NbEntities() == 0)
        continue;
      thedispres.AddPart();
      thedispres.GetFromIter(iter);
      A.ResetData();
      A.GetFromIter(iter);
      thedisplist.Append(i);
    }
  }
  thedispnum = thepacknum = 1;
  thepackdisp             = 1;
  thenbindisp             = 0;
  for (i = thepacknum; i <= thedisplist.Length(); i++)
  {
    if (thedisplist.Value(i) != thedispnum)
      break;
    thenbindisp++;
  }
}

bool IFSelect_ShareOutResult::More()
{
  return thedispres.More();
}

void IFSelect_ShareOutResult::Next()
{
  thedispres.Next();
  thepacknum++;
  int dispnum;
  if (thepacknum <= thedisplist.Length())
    dispnum = thedisplist.Value(thepacknum);
  else
  {
    thenbindisp = 0;
#if !defined No_Exception

#endif
    return;
  }
  if (thedispnum == dispnum)
    thepackdisp++;
  else
  {
    thedispnum  = dispnum;
    thepackdisp = 1;
    thenbindisp = 0;
    for (int i = thepacknum; i <= thedisplist.Length(); i++)
    {
      if (thedisplist.Value(i) != thedispnum)
        break;
      thenbindisp++;
    }
    if (!theshareout.IsNull())
      thedispatch = theshareout->Dispatch(thedispnum);
  }
}

void IFSelect_ShareOutResult::NextDispatch()
{
  for (; thepacknum <= thedisplist.Length(); thepacknum++)
  {
    thedispres.Next();
    if (thedispnum != thedisplist.Value(thepacknum))
    {
      thedispnum = thedisplist.Value(thepacknum);

      thepackdisp = 1;
      thenbindisp = 0;
      for (int i = thepacknum; i <= thedisplist.Length(); i++)
      {
        if (thedisplist.Value(i) != thedispnum)
          break;
        thenbindisp++;
      }
      if (!theshareout.IsNull())
        thedispatch = theshareout->Dispatch(thedispnum);
      return;
    }
  }
  thepacknum = thedisplist.Length() + 1;
  thedispnum = thepackdisp = thenbindisp = 0;
}

occ::handle<IFSelect_Dispatch> IFSelect_ShareOutResult::Dispatch() const
{
  return thedispatch;
}

int IFSelect_ShareOutResult::DispatchRank() const
{
  return thedispnum;
}

void IFSelect_ShareOutResult::PacketsInDispatch(int& numpack, int& nbpacks) const
{
  numpack = thepackdisp;
  nbpacks = thenbindisp;
}

Interface_EntityIterator IFSelect_ShareOutResult::PacketRoot()
{
  return thedispres.Entities();
}

Interface_EntityIterator IFSelect_ShareOutResult::PacketContent()
{

  Interface_EntityIterator iter = thedispres.Entities();
  Interface_Graph          G(thegraph);

  for (iter.Start(); iter.More(); iter.Next())
    G.GetFromEntity(iter.Value(), true);
  Interface_GraphContent GC(G);
  return GC.Result();
}

TCollection_AsciiString IFSelect_ShareOutResult::FileName() const
{
  int nd = DispatchRank();
  int np, nbp;
  PacketsInDispatch(np, nbp);
  return theshareout->FileName(nd, np, nbp);
}
