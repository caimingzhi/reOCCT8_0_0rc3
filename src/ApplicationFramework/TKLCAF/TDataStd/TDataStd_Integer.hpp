#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

class TDataStd_Integer : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_Integer> Set(const TDF_Label& label, const int value);

  Standard_EXPORT static occ::handle<TDataStd_Integer> Set(const TDF_Label&     label,
                                                           const Standard_GUID& guid,
                                                           const int            value);

  Standard_EXPORT void Set(const int V);

  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT int Get() const;

  Standard_EXPORT bool IsCaptured() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT TDataStd_Integer();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Integer, TDF_Attribute)

private:
  int           myValue;
  Standard_GUID myID;
};
