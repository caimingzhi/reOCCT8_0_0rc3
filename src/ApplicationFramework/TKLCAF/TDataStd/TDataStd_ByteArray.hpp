#pragma once

#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;
class TDF_DeltaOnModification;

class TDataStd_ByteArray : public TDF_Attribute
{
  friend class TDataStd_DeltaOnModificationOfByteArray;
  DEFINE_STANDARD_RTTIEXT(TDataStd_ByteArray, TDF_Attribute)
public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_ByteArray> Set(const TDF_Label& label,
                                                             const int        lower,
                                                             const int        upper,
                                                             const bool       isDelta = false);

  Standard_EXPORT static occ::handle<TDataStd_ByteArray> Set(const TDF_Label&     label,
                                                             const Standard_GUID& theGuid,
                                                             const int            lower,
                                                             const int            upper,
                                                             const bool           isDelta = false);

  Standard_EXPORT void Init(const int lower, const int upper);

  Standard_EXPORT void SetValue(const int index, const uint8_t value);

  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT uint8_t Value(const int Index) const;

  uint8_t operator()(const int Index) const { return Value(Index); }

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  const occ::handle<NCollection_HArray1<uint8_t>>& InternalArray() const { return myValue; }

  Standard_EXPORT void ChangeArray(const occ::handle<NCollection_HArray1<uint8_t>>& newArray,
                                   const bool isCheckItems = true);

  bool GetDelta() const { return myIsDelta; }

  void SetDelta(const bool isDelta) { myIsDelta = isDelta; }

  Standard_EXPORT TDataStd_ByteArray();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& OS) const override;

  Standard_EXPORT occ::handle<TDF_DeltaOnModification> DeltaOnModification(
    const occ::handle<TDF_Attribute>& anOldAttribute) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  void RemoveArray() { myValue.Nullify(); }

private:
  occ::handle<NCollection_HArray1<uint8_t>> myValue;
  bool                                      myIsDelta;
  Standard_GUID                             myID;
};
