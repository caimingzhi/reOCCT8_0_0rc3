#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class IGESData_IGESModel;
class IGESData_IGESEntity;
class Interface_InterfaceModel;
class Interface_Graph;
class IFSelect_PacketList;

class IGESSelect_ViewSorter : public Standard_Transient
{

public:
  Standard_EXPORT IGESSelect_ViewSorter();

  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool Add(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT bool AddEntity(const occ::handle<IGESData_IGESEntity>& igesent);

  Standard_EXPORT void AddList(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list);

  Standard_EXPORT void AddModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT void SortSingleViews(const bool alsoframes);

  Standard_EXPORT void SortDrawings(const Interface_Graph& G);

  Standard_EXPORT int NbSets(const bool final) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> SetItem(const int num, const bool final) const;

  Standard_EXPORT occ::handle<IFSelect_PacketList> Sets(const bool final) const;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_ViewSorter, Standard_Transient)

private:
  occ::handle<IGESData_IGESModel>                         themodel;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> themap;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> theitems;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> thefinals;
  NCollection_Sequence<int>                               theinditem;
  NCollection_Sequence<int>                               theindfin;
};
