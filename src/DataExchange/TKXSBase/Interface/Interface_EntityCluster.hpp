#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_EntityIterator;

class Interface_EntityCluster : public Standard_Transient
{

public:
  Standard_EXPORT Interface_EntityCluster();

  Standard_EXPORT Interface_EntityCluster(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT Interface_EntityCluster(const occ::handle<Interface_EntityCluster>& ec);

  Standard_EXPORT Interface_EntityCluster(const occ::handle<Standard_Transient>&      ant,
                                          const occ::handle<Interface_EntityCluster>& ec);

  Standard_EXPORT void Append(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT bool Remove(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT bool Remove(const int num);

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Value(const int num) const;

  Standard_EXPORT void SetValue(const int num, const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT void FillIterator(Interface_EntityIterator& iter) const;

  Standard_EXPORT ~Interface_EntityCluster() override;

  friend class Interface_EntityList;

  DEFINE_STANDARD_RTTIEXT(Interface_EntityCluster, Standard_Transient)

private:
  Standard_EXPORT bool IsLocalFull() const;

  Standard_EXPORT int NbLocal() const;

  Standard_EXPORT bool HasNext() const;

  Standard_EXPORT occ::handle<Interface_EntityCluster> Next() const;

  occ::handle<Standard_Transient>      theents[4];
  occ::handle<Interface_EntityCluster> thenext;
};
