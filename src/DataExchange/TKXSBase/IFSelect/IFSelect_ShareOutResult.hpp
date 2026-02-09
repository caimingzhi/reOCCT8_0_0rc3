#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Interface_Graph.hpp>
#include <IFGraph_SubPartsIterator.hpp>
class IFSelect_ShareOut;
class IFSelect_Dispatch;
class Interface_InterfaceModel;
class IFSelect_PacketList;
class Interface_EntityIterator;
class TCollection_AsciiString;

class IFSelect_ShareOutResult
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFSelect_ShareOutResult(const occ::handle<IFSelect_ShareOut>&        sho,
                                          const occ::handle<Interface_InterfaceModel>& mod);

  Standard_EXPORT IFSelect_ShareOutResult(const occ::handle<IFSelect_ShareOut>& sho,
                                          const Interface_Graph&                G);

  Standard_EXPORT IFSelect_ShareOutResult(const occ::handle<IFSelect_Dispatch>&        disp,
                                          const occ::handle<Interface_InterfaceModel>& mod);

  Standard_EXPORT IFSelect_ShareOutResult(const occ::handle<IFSelect_Dispatch>& disp,
                                          const Interface_Graph&                G);

  Standard_EXPORT occ::handle<IFSelect_ShareOut> ShareOut() const;

  Standard_EXPORT const Interface_Graph& Graph() const;

  Standard_EXPORT void Reset();

  Standard_EXPORT void Evaluate();

  Standard_EXPORT occ::handle<IFSelect_PacketList> Packets(const bool complete = true);

  Standard_EXPORT int NbPackets();

  Standard_EXPORT void Prepare();

  Standard_EXPORT bool More();

  Standard_EXPORT void Next();

  Standard_EXPORT void NextDispatch();

  Standard_EXPORT occ::handle<IFSelect_Dispatch> Dispatch() const;

  Standard_EXPORT int DispatchRank() const;

  Standard_EXPORT void PacketsInDispatch(int& numpack, int& nbpacks) const;

  Standard_EXPORT Interface_EntityIterator PacketRoot();

  Standard_EXPORT Interface_EntityIterator PacketContent();

  Standard_EXPORT TCollection_AsciiString FileName() const;

protected:
  Interface_Graph          thegraph;
  IFGraph_SubPartsIterator thedispres;

private:
  occ::handle<IFSelect_ShareOut> theshareout;
  occ::handle<IFSelect_Dispatch> thedispatch;
  bool                           theeval;
  int                            thedispnum;
  int                            thepacknum;
  int                            thepackdisp;
  int                            thenbindisp;
  NCollection_Sequence<int>      thedisplist;
};
