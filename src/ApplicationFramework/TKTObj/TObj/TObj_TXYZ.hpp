#pragma once

#include <gp_XYZ.hpp>
#include <TDF_Attribute.hpp>

class Standard_GUID;
class TDF_Label;

class TObj_TXYZ : public TDF_Attribute
{
public:
  Standard_EXPORT TObj_TXYZ();

  static Standard_EXPORT const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

public:
  static Standard_EXPORT occ::handle<TObj_TXYZ> Set(const TDF_Label& theLabel,
                                                    const gp_XYZ&    theXYZ);

public:
  Standard_EXPORT void Set(const gp_XYZ& theXYZ);

  Standard_EXPORT gp_XYZ Get() const;

public:
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

private:
  gp_XYZ myXYZ;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_TXYZ, TDF_Attribute)
};

#ifdef _MSC_VER
  #pragma once
#endif
