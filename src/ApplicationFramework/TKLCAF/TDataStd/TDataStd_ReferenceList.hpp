#pragma once


#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;
class TDF_DataSet;

//! Contains a list of references.
class TDataStd_ReferenceList : public TDF_Attribute
{

public:
  //! Static methods
  //! ==============
  //! Returns the ID of the list of references (labels) attribute.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds or creates a list of reference values (labels) attribute.
  Standard_EXPORT static occ::handle<TDataStd_ReferenceList> Set(const TDF_Label& label);

  //! Finds or creates a list of reference values (labels) attribute with explicit user defined
  //! <guid>.
  Standard_EXPORT static occ::handle<TDataStd_ReferenceList> Set(const TDF_Label&     label,
                                                                 const Standard_GUID& theGuid);

  Standard_EXPORT TDataStd_ReferenceList();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT int Extent() const;

  Standard_EXPORT void Prepend(const TDF_Label& value);

  Standard_EXPORT void Append(const TDF_Label& value);

  //! Sets the explicit GUID (user defined) for the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  //! Inserts the <value> before the first meet of <before_value>.
  Standard_EXPORT bool InsertBefore(const TDF_Label& value, const TDF_Label& before_value);

  //! Inserts the label before the <index> position.
  //! The indices start with 1 .. Extent().
  Standard_EXPORT bool InsertBefore(const int index, const TDF_Label& before_value);

  //! Inserts the <value> after the first meet of <after_value>.
  Standard_EXPORT bool InsertAfter(const TDF_Label& value, const TDF_Label& after_value);

  //! Inserts the label after the <index> position.
  //! The indices start with 1 .. Extent().
  Standard_EXPORT bool InsertAfter(const int index, const TDF_Label& after_value);

  //! Removes the first meet of the <value>.
  Standard_EXPORT bool Remove(const TDF_Label& value);

  //! Removes a label at "index" position.
  Standard_EXPORT bool Remove(const int index);

  Standard_EXPORT void Clear();

  Standard_EXPORT const TDF_Label& First() const;

  Standard_EXPORT const TDF_Label& Last() const;

  Standard_EXPORT const NCollection_List<TDF_Label>& List() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_ReferenceList, TDF_Attribute)

private:
  NCollection_List<TDF_Label> myList;
  Standard_GUID               myID;
};

