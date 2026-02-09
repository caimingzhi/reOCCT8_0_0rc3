#pragma once

#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <TDataStd_RealEnum.hpp>
#include <TDF_DerivedAttribute.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TDF_RelocationTable;

class TDataStd_Real : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataStd_Real> Set(const TDF_Label& label, const double value);

  Standard_EXPORT static occ::handle<TDataStd_Real> Set(const TDF_Label&     label,
                                                        const Standard_GUID& guid,
                                                        const double         value);

  Standard_EXPORT TDataStd_Real();

  Standard_DEPRECATED(
    "TDataStd_Real::SetDimension() is deprecated. Please avoid usage of this method.")
  Standard_EXPORT void SetDimension(const TDataStd_RealEnum DIM);

  Standard_DEPRECATED(
    "TDataStd_Real::GetDimension() is deprecated. Please avoid usage of this method.")
  Standard_EXPORT TDataStd_RealEnum GetDimension() const;

  Standard_EXPORT void Set(const double V);

  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  Standard_EXPORT void SetID() override;

  Standard_EXPORT double Get() const;

  Standard_EXPORT bool IsCaptured() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TDataStd_Real, TDF_Attribute)

protected:
  double myValue;

  TDataStd_RealEnum myDimension;
  Standard_GUID     myID;
};
