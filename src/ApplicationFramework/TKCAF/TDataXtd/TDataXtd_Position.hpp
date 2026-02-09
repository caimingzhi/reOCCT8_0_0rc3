#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Pnt.hpp>
#include <TDF_Attribute.hpp>
class TDF_Label;
class Standard_GUID;
class TDF_RelocationTable;

class TDataXtd_Position : public TDF_Attribute
{

public:
  Standard_EXPORT static void Set(const TDF_Label& aLabel, const gp_Pnt& aPos);

  Standard_EXPORT static occ::handle<TDataXtd_Position> Set(const TDF_Label& aLabel);

  Standard_EXPORT static bool Get(const TDF_Label& aLabel, gp_Pnt& aPos);

  Standard_EXPORT TDataXtd_Position();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocTationable) const override;

  Standard_EXPORT const gp_Pnt& GetPosition() const;

  Standard_EXPORT void SetPosition(const gp_Pnt& aPos);

  DEFINE_STANDARD_RTTIEXT(TDataXtd_Position, TDF_Attribute)

private:
  gp_Pnt myPosition;
};
