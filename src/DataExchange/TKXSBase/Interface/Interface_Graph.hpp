#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_BitMap.hpp>
#include <Interface_InterfaceModel.hpp>

#include <TCollection_HAsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_List.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

class Interface_GeneralLib;
class Interface_Protocol;
class Interface_GTool;
class Standard_Transient;
class Interface_EntityIterator;

#ifdef Status
  #undef Status
#endif

class Interface_Graph
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_Graph(const occ::handle<Interface_InterfaceModel>& amodel,
                                  const Interface_GeneralLib&                  lib,
                                  const bool                                   theModeStats = true);

  Standard_EXPORT Interface_Graph(const occ::handle<Interface_InterfaceModel>& amodel,
                                  const occ::handle<Interface_Protocol>&       protocol,
                                  const bool                                   theModeStats = true);

  Standard_EXPORT Interface_Graph(const occ::handle<Interface_InterfaceModel>& amodel,
                                  const occ::handle<Interface_GTool>&          gtool,
                                  const bool                                   theModeStats = true);

  Standard_EXPORT Interface_Graph(const occ::handle<Interface_InterfaceModel>& amodel,
                                  const bool                                   theModeStats = true);

  Standard_EXPORT Interface_Graph(const Interface_Graph& agraph, const bool copied = false);

  Standard_EXPORT Interface_Graph& operator=(const Interface_Graph& theOther);

  Standard_EXPORT void Reset();

  Standard_EXPORT void ResetStatus();

  Standard_EXPORT int Size() const;

  Standard_EXPORT int NbStatuses() const;

  Standard_EXPORT int EntityNumber(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT bool IsPresent(const int num) const;

  Standard_EXPORT bool IsPresent(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Entity(const int num) const;

  Standard_EXPORT int Status(const int num) const;

  Standard_EXPORT void SetStatus(const int num, const int stat);

  Standard_EXPORT void RemoveItem(const int num);

  Standard_EXPORT void ChangeStatus(const int oldstat, const int newstat);

  Standard_EXPORT void RemoveStatus(const int stat);

  Standard_EXPORT const Interface_BitMap& BitMap() const;

  Standard_EXPORT Interface_BitMap& CBitMap();

  Standard_EXPORT const occ::handle<Interface_InterfaceModel>& Model() const;

  Standard_EXPORT void GetFromModel();

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent,
                                     const bool                             shared,
                                     const int                              newstat = 0);

  Standard_EXPORT void GetFromEntity(const occ::handle<Standard_Transient>& ent,
                                     const bool                             shared,
                                     const int                              newstat,
                                     const int                              overlapstat,
                                     const bool                             cumul);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter, const int newstat);

  Standard_EXPORT void GetFromIter(const Interface_EntityIterator& iter,
                                   const int                       newstat,
                                   const int                       overlapstat,
                                   const bool                      cumul);

  Standard_EXPORT void GetFromGraph(const Interface_Graph& agraph);

  Standard_EXPORT void GetFromGraph(const Interface_Graph& agraph, const int stat);

  Standard_EXPORT bool HasShareErrors(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> GetShareds(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT Interface_EntityIterator
    Shareds(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT Interface_EntityIterator
    Sharings(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> GetSharings(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT Interface_EntityIterator
    TypedSharings(const occ::handle<Standard_Transient>& ent,
                  const occ::handle<Standard_Type>&      type) const;

  Standard_EXPORT Interface_EntityIterator RootEntities() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<NCollection_List<int>>>& SharingTable()
    const;

  Standard_EXPORT bool ModeStat() const;

protected:
  Standard_EXPORT void InitStats();

  occ::handle<Interface_InterfaceModel>                   themodel;
  TCollection_AsciiString                                 thepresents;
  occ::handle<NCollection_HArray1<int>>                   thestats;
  occ::handle<NCollection_HArray1<NCollection_List<int>>> thesharings;

private:
  Standard_EXPORT void Evaluate();

  Interface_BitMap theflags;
};
