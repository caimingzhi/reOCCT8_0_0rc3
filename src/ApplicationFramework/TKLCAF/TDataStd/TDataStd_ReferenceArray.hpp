#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_RelocationTable;
class TDF_DataSet;

class TDataStd_ReferenceArray : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_ReferenceArray> Set(const TDF_Label& label,
                                                                  const int        lower,
                                                                  const int        upper);

  Standard_EXPORT static occ::handle<TDataStd_ReferenceArray> Set(const TDF_Label&     label,
                                                                  const Standard_GUID& theGuid,
                                                                  const int            lower,
                                                                  const int            upper);

  Standard_EXPORT void Init(const int lower, const int upper);

  Standard_EXPORT void SetValue(const int index, const TDF_Label& value);

  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT TDF_Label Value(const int Index) const;

  TDF_Label operator()(const int Index) const { return Value(Index); }

  Standard_EXPORT int Lower() const;

  Standard_EXPORT int Upper() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT const occ::handle<NCollection_HArray1<TDF_Label>>& InternalArray() const;

  Standard_EXPORT void SetInternalArray(const occ::handle<NCollection_HArray1<TDF_Label>>& values,
                                        const bool isCheckItems = true);

  Standard_EXPORT TDataStd_ReferenceArray();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_ReferenceArray, TDF_Attribute)

private:
  occ::handle<NCollection_HArray1<TDF_Label>> myArray;
  Standard_GUID                               myID;
};
