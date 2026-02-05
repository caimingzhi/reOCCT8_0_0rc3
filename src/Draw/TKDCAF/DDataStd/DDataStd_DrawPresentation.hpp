#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_Attribute.hpp>
class Draw_Drawable3D;
class TDF_Label;
class Standard_GUID;
class TDF_RelocationTable;
class TDF_AttributeDelta;

//! draw presentation of a label of a document
class DDataStd_DrawPresentation : public TDF_Attribute
{

public:
  //! api methods on draw presentation
  //! ================================
  Standard_EXPORT static bool HasPresentation(const TDF_Label& L);

  Standard_EXPORT static bool IsDisplayed(const TDF_Label& L);

  Standard_EXPORT static void Display(const TDF_Label& L);

  Standard_EXPORT static void Erase(const TDF_Label& L);

  //! attribute implementation
  //! ========================
  Standard_EXPORT static void Update(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT DDataStd_DrawPresentation();

  Standard_EXPORT void SetDisplayed(const bool status);

  Standard_EXPORT bool IsDisplayed() const;

  Standard_EXPORT void SetDrawable(const occ::handle<Draw_Drawable3D>& D);

  Standard_EXPORT occ::handle<Draw_Drawable3D> GetDrawable() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  //! call backs for viewer updating
  //! ==============================
  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT void AfterAddition() override;

  Standard_EXPORT void BeforeRemoval() override;

  Standard_EXPORT void BeforeForget() override;

  Standard_EXPORT void AfterResume() override;

  Standard_EXPORT bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                  const bool                             forceIt = false) override;

  //! update draw viewer according to delta
  //! private methods
  //! ===============
  Standard_EXPORT bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                 const bool                             forceIt = false) override;

  DEFINE_STANDARD_RTTIEXT(DDataStd_DrawPresentation, TDF_Attribute)

private:
  Standard_EXPORT void DrawBuild();

  Standard_EXPORT static void DrawDisplay(const TDF_Label&                              L,
                                          const occ::handle<DDataStd_DrawPresentation>& P);

  Standard_EXPORT static void DrawErase(const TDF_Label&                              L,
                                        const occ::handle<DDataStd_DrawPresentation>& P);

  bool                         isDisplayed;
  occ::handle<Draw_Drawable3D> myDrawable;
};
