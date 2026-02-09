#pragma once

#include <Standard.hpp>

#include <Standard_Boolean.hpp>
#include <TDF_Attribute.hpp>
#include <TColStd_HPackedMapOfInteger.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;
class TDF_DeltaOnModification;

class TDataStd_IntPackedMap : public TDF_Attribute
{
  friend class TDataStd_DeltaOnModificationOfIntPackedMap;
  DEFINE_STANDARD_RTTIEXT(TDataStd_IntPackedMap, TDF_Attribute)
public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_IntPackedMap> Set(const TDF_Label& label,
                                                                const bool       isDelta = false);

  Standard_EXPORT TDataStd_IntPackedMap();

  Standard_EXPORT bool ChangeMap(const occ::handle<TColStd_HPackedMapOfInteger>& theMap);

  Standard_EXPORT bool ChangeMap(const TColStd_PackedMapOfInteger& theMap);

  const TColStd_PackedMapOfInteger& GetMap() const { return myMap->Map(); }

  const occ::handle<TColStd_HPackedMapOfInteger>& GetHMap() const { return myMap; }

  Standard_EXPORT bool Clear();

  Standard_EXPORT bool Add(const int theKey);

  Standard_EXPORT bool Remove(const int theKey);

  Standard_EXPORT bool Contains(const int theKey) const;

  int Extent() const { return myMap->Map().Extent(); }

  bool IsEmpty() const { return myMap->Map().IsEmpty(); }

  bool GetDelta() const { return myIsDelta; }

  void SetDelta(const bool isDelta) { myIsDelta = isDelta; }

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT occ::handle<TDF_DeltaOnModification> DeltaOnModification(
    const occ::handle<TDF_Attribute>& anOldAttribute) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  void RemoveMap() { myMap.Nullify(); }

private:
  occ::handle<TColStd_HPackedMapOfInteger> myMap;
  bool                                     myIsDelta;
};
