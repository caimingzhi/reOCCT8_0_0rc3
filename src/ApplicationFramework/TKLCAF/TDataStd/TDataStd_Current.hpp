#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_RelocationTable;

class TDataStd_Current : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static void Set(const TDF_Label& L);

  Standard_EXPORT static TDF_Label Get(const TDF_Label& acces);

  Standard_EXPORT static bool Has(const TDF_Label& acces);

  Standard_EXPORT TDataStd_Current();

  Standard_EXPORT void SetLabel(const TDF_Label& current);

  Standard_EXPORT TDF_Label GetLabel() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Current, TDF_Attribute)

private:
  TDF_Label myLabel;
};
