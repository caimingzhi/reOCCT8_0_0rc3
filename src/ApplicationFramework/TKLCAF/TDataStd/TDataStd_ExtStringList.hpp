#pragma once

#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TCollection_ExtendedString;
class TDF_RelocationTable;

class TDataStd_ExtStringList : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_ExtStringList> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataStd_ExtStringList> Set(const TDF_Label&     label,
                                                                 const Standard_GUID& theGuid);

  Standard_EXPORT TDataStd_ExtStringList();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT int Extent() const;

  Standard_EXPORT void Prepend(const TCollection_ExtendedString& value);

  Standard_EXPORT void Append(const TCollection_ExtendedString& value);

  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT bool InsertBefore(const TCollection_ExtendedString& value,
                                    const TCollection_ExtendedString& before_value);

  Standard_EXPORT bool InsertBefore(const int                         index,
                                    const TCollection_ExtendedString& before_value);

  Standard_EXPORT bool InsertAfter(const TCollection_ExtendedString& value,
                                   const TCollection_ExtendedString& after_value);

  Standard_EXPORT bool InsertAfter(const int index, const TCollection_ExtendedString& after_value);

  Standard_EXPORT bool Remove(const TCollection_ExtendedString& value);

  Standard_EXPORT bool Remove(const int index);

  Standard_EXPORT void Clear();

  Standard_EXPORT const TCollection_ExtendedString& First() const;

  Standard_EXPORT const TCollection_ExtendedString& Last() const;

  Standard_EXPORT const NCollection_List<TCollection_ExtendedString>& List() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_ExtStringList, TDF_Attribute)

private:
  NCollection_List<TCollection_ExtendedString> myList;
  Standard_GUID                                myID;
};
