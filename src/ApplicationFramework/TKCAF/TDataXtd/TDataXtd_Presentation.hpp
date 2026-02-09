#pragma once

#include <Standard.hpp>
#include <Standard_GUID.hpp>

#include <gp_Pnt.hpp>
#include <TDF_Attribute.hpp>
#include <Quantity_NameOfColor.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>

class TDF_Label;
class TDF_RelocationTable;

class TDataXtd_Presentation : public TDF_Attribute
{
public:
  Standard_EXPORT TDataXtd_Presentation();

  Standard_EXPORT static occ::handle<TDataXtd_Presentation> Set(const TDF_Label&     theLabel,
                                                                const Standard_GUID& theDriverId);

  Standard_EXPORT static void Unset(const TDF_Label& theLabel);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& anAttribute) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocTationable) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TDataXtd_Presentation, TDF_Attribute)

public:
  Standard_EXPORT Standard_GUID GetDriverGUID() const;

  Standard_EXPORT void SetDriverGUID(const Standard_GUID& theGUID);

  Standard_EXPORT bool IsDisplayed() const;

  Standard_EXPORT bool HasOwnMaterial() const;

  Standard_EXPORT bool HasOwnTransparency() const;

  Standard_EXPORT bool HasOwnColor() const;

  Standard_EXPORT bool HasOwnWidth() const;

  Standard_EXPORT bool HasOwnMode() const;

  Standard_EXPORT bool HasOwnSelectionMode() const;

  Standard_EXPORT void SetDisplayed(const bool theIsDisplayed);

  Standard_EXPORT void SetMaterialIndex(const int theMaterialIndex);

  Standard_EXPORT void SetTransparency(const double theValue);

  Standard_EXPORT void SetColor(const Quantity_NameOfColor theColor);

  Standard_EXPORT void SetWidth(const double theWidth);

  Standard_EXPORT void SetMode(const int theMode);

  Standard_EXPORT int GetNbSelectionModes() const;

  Standard_EXPORT void SetSelectionMode(const int  theSelectionMode,
                                        const bool theTransaction = true);
  Standard_EXPORT void AddSelectionMode(const int  theSelectionMode,
                                        const bool theTransaction = true);

  Standard_EXPORT int MaterialIndex() const;

  Standard_EXPORT double Transparency() const;

  Standard_EXPORT Quantity_NameOfColor Color() const;

  Standard_EXPORT double Width() const;

  Standard_EXPORT int Mode() const;

  Standard_EXPORT int SelectionMode(const int index = 1) const;

  Standard_EXPORT void UnsetMaterial();

  Standard_EXPORT void UnsetTransparency();

  Standard_EXPORT void UnsetColor();

  Standard_EXPORT void UnsetWidth();

  Standard_EXPORT void UnsetMode();

  Standard_EXPORT void UnsetSelectionMode();

public:
  Standard_EXPORT static Quantity_NameOfColor getColorNameFromOldEnum(int theOld);

  Standard_EXPORT static int getOldColorNameFromNewEnum(Quantity_NameOfColor theNew);

private:
  Standard_GUID         myDriverGUID;
  Quantity_NameOfColor  myColor;
  int                   myMaterialIndex;
  int                   myMode;
  NCollection_List<int> mySelectionModes;
  double                myTransparency;
  double                myWidth;
  bool                  myIsDisplayed;
  bool                  myHasOwnColor;
  bool                  myHasOwnMaterial;
  bool                  myHasOwnTransparency;
  bool                  myHasOwnWidth;
  bool                  myHasOwnMode;
  bool                  myHasOwnSelectionMode;

  bool HasSelectionMode(const int theSelectionMode) const;
};
