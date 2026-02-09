#pragma once

#include <Standard.hpp>

#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

class TDataStd_BooleanList : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_BooleanList> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataStd_BooleanList> Set(const TDF_Label&     label,
                                                               const Standard_GUID& theGuid);

  Standard_EXPORT TDataStd_BooleanList();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT int Extent() const;

  Standard_EXPORT void Prepend(const bool value);

  Standard_EXPORT void Append(const bool value);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool First() const;

  Standard_EXPORT bool Last() const;

  Standard_EXPORT const NCollection_List<uint8_t>& List() const;

  Standard_EXPORT bool InsertBefore(const int index, const bool before_value);

  Standard_EXPORT bool InsertAfter(const int index, const bool after_value);

  Standard_EXPORT bool Remove(const int index);

  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_BooleanList, TDF_Attribute)

private:
  NCollection_List<uint8_t> myList;
  Standard_GUID             myID;
};
