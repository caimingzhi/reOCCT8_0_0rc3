#pragma once

#include <Standard.hpp>

#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

class TDataStd_RealList : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_RealList> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataStd_RealList> Set(const TDF_Label&     label,
                                                            const Standard_GUID& theGuid);

  Standard_EXPORT TDataStd_RealList();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT int Extent() const;

  Standard_EXPORT void Prepend(const double value);

  Standard_EXPORT void Append(const double value);

  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT bool InsertBefore(const double value, const double before_value);

  Standard_EXPORT bool InsertBeforeByIndex(const int index, const double before_value);

  Standard_EXPORT bool InsertAfter(const double value, const double after_value);

  Standard_EXPORT bool InsertAfterByIndex(const int index, const double after_value);

  Standard_EXPORT bool Remove(const double value);

  Standard_EXPORT bool RemoveByIndex(const int index);

  Standard_EXPORT void Clear();

  Standard_EXPORT double First() const;

  Standard_EXPORT double Last() const;

  Standard_EXPORT const NCollection_List<double>& List() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_RealList, TDF_Attribute)

private:
  NCollection_List<double> myList;
  Standard_GUID            myID;
};
