#pragma once

#include <Standard.hpp>

#include <Interface_IntList.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Interface_InterfaceModel;
class Interface_EntityIterator;

class IFSelect_PacketList : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_PacketList(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void SetName(const char* name);

  Standard_EXPORT const char* Name() const;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void AddPacket();

  Standard_EXPORT void Add(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void AddList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT int NbPackets() const;

  Standard_EXPORT int NbEntities(const int numpack) const;

  Standard_EXPORT Interface_EntityIterator Entities(const int numpack) const;

  Standard_EXPORT int HighestDuplicationCount() const;

  Standard_EXPORT int NbDuplicated(const int count, const bool andmore) const;

  Standard_EXPORT Interface_EntityIterator Duplicated(const int count, const bool andmore) const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_PacketList, Standard_Transient)

private:
  occ::handle<Interface_InterfaceModel> themodel;
  NCollection_Array1<int>               thedupls;
  Interface_IntList                     thepacks;
  NCollection_Array1<int>               theflags;
  int                                   thelast;
  bool                                  thebegin;
  TCollection_AsciiString               thename;
};
