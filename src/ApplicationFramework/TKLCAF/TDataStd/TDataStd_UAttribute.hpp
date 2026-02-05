#pragma once

#include <Standard.hpp>

#include <Standard_GUID.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TDF_RelocationTable;
class TDF_DataSet;

class TDataStd_UAttribute : public TDF_Attribute
{

public:
  //! api class methods
  //! =============
  //! Find, or create, a UAttribute attribute with <LocalID> as Local GUID.
  //! The UAttribute attribute is returned.
  //! UAttribute methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_UAttribute> Set(const TDF_Label&     label,
                                                              const Standard_GUID& LocalID);

  Standard_EXPORT TDataStd_UAttribute();

  Standard_EXPORT void SetID(const Standard_GUID& LocalID) override;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_UAttribute, TDF_Attribute)

private:
  Standard_GUID myID;
};
