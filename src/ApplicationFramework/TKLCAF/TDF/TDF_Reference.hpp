#pragma once


#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_RelocationTable;
class TDF_DataSet;

//! This attribute is used to store in the framework a
//! reference to an other label.
class TDF_Reference : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDF_Reference> Set(const TDF_Label& I,
                                                        const TDF_Label& Origin);

  Standard_EXPORT void Set(const TDF_Label& Origin);

  Standard_EXPORT TDF_Label Get() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& DS) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT TDF_Reference();

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDF_Reference, TDF_Attribute)

private:
  TDF_Label myOrigin;
};

