#pragma once

#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>
class TDF_Label;
class TDF_RelocationTable;

class TDataStd_BooleanArray : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_BooleanArray> Set(const TDF_Label& label,
                                                                const int        lower,
                                                                const int        upper);

  Standard_EXPORT static occ::handle<TDataStd_BooleanArray> Set(const TDF_Label&     label,
                                                                const Standard_GUID& theGuid,
                                                                const int            lower,
                                                                const int            upper);

  Standard_EXPORT void Init(const int lower, const int upper);

  Standard_EXPORT void SetValue(const int index, const bool value);

  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT bool Value(const int Index) const;

  bool operator()(const int Index) const { return Value(Index); }

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<uint8_t>>& InternalArray() const;

  Standard_EXPORT void SetInternalArray(const occ::handle<NCollection_HArray1<uint8_t>>& values);

  Standard_EXPORT TDataStd_BooleanArray();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& OS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_BooleanArray, TDF_Attribute)

private:
  occ::handle<NCollection_HArray1<uint8_t>> myValues;
  int                                       myLower;
  int                                       myUpper;
  Standard_GUID                             myID;
};
