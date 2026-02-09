#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Quantity_NameOfColor.hpp>
#include <Graphic3d_NameOfMaterial.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <TDataXtd_Presentation.hpp>
#include <AIS_InteractiveContext.hpp>

class AIS_InteractiveObject;
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;
class TDF_AttributeDelta;

class TPrsStd_AISPresentation : public TDF_Attribute
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TPrsStd_AISPresentation> Set(const TDF_Label&     L,
                                                                  const Standard_GUID& driver);

  Standard_EXPORT static void Unset(const TDF_Label& L);

  Standard_EXPORT static occ::handle<TPrsStd_AISPresentation> Set(
    const occ::handle<TDF_Attribute>& master);

  Standard_EXPORT TPrsStd_AISPresentation();

  Standard_EXPORT void SetDisplayed(const bool B);

  Standard_EXPORT void Display(const bool update = false);

  Standard_EXPORT void Erase(const bool remove = false);

  Standard_EXPORT void Update();

  Standard_EXPORT Standard_GUID GetDriverGUID() const;

  Standard_EXPORT void SetDriverGUID(const Standard_GUID& guid);

  Standard_EXPORT bool IsDisplayed() const;

  Standard_EXPORT occ::handle<AIS_InteractiveObject> GetAIS() const;

  Standard_EXPORT Graphic3d_NameOfMaterial Material() const;

  Standard_EXPORT void SetMaterial(const Graphic3d_NameOfMaterial aName);

  Standard_EXPORT bool HasOwnMaterial() const;

  Standard_EXPORT void UnsetMaterial();

  Standard_EXPORT void SetTransparency(const double aValue = 0.6);

  Standard_EXPORT double Transparency() const;

  Standard_EXPORT bool HasOwnTransparency() const;

  Standard_EXPORT void UnsetTransparency();

  Standard_EXPORT Quantity_NameOfColor Color() const;

  Standard_EXPORT void SetColor(const Quantity_NameOfColor aColor);

  Standard_EXPORT bool HasOwnColor() const;

  Standard_EXPORT void UnsetColor();

  Standard_EXPORT double Width() const;

  Standard_EXPORT void SetWidth(const double aWidth);

  Standard_EXPORT bool HasOwnWidth() const;

  Standard_EXPORT void UnsetWidth();

  Standard_EXPORT int Mode() const;

  Standard_EXPORT void SetMode(const int theMode);

  Standard_EXPORT bool HasOwnMode() const;

  Standard_EXPORT void UnsetMode();

  Standard_EXPORT int GetNbSelectionModes() const;
  Standard_EXPORT int SelectionMode(const int index = 1) const;

  Standard_EXPORT void SetSelectionMode(const int  theSelectionMode,
                                        const bool theTransaction = true);
  Standard_EXPORT void AddSelectionMode(const int  theSelectionMode,
                                        const bool theTransaction = true);

  Standard_EXPORT bool HasOwnSelectionMode() const;

  Standard_EXPORT void UnsetSelectionMode();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> BackupCopy() const override;

  Standard_EXPORT void AfterAddition() override;

  Standard_EXPORT void BeforeRemoval() override;

  Standard_EXPORT void BeforeForget() override;

  Standard_EXPORT void AfterResume() override;

  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                  const bool                             forceIt = false) override;

  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(TPrsStd_AISPresentation, TDF_Attribute)

protected:
  Standard_EXPORT virtual occ::handle<TDataXtd_Presentation> getData() const;

private:
  occ::handle<AIS_InteractiveContext> getAISContext() const;

  void ActivateSelectionMode();

  Standard_EXPORT void AISUpdate();

  Standard_EXPORT void AISDisplay();

  Standard_EXPORT void AISErase(const bool remove = false);

private:
  occ::handle<AIS_InteractiveObject> myAIS;
};
