#pragma once

#include <Standard_Integer.hpp>
#include <Quantity_Color.hpp>
#include <NCollection_DataMap.hpp>
#include <MeshVS_TwoColors.hpp>
#include <MeshVS_PrsBuilder.hpp>
#include <MeshVS_DisplayModeFlags.hpp>
#include <MeshVS_BuilderPriority.hpp>

class MeshVS_Mesh;
class MeshVS_DataSource;
class Quantity_Color;

class MeshVS_ElementalColorPrsBuilder : public MeshVS_PrsBuilder
{

public:
  Standard_EXPORT MeshVS_ElementalColorPrsBuilder(
    const occ::handle<MeshVS_Mesh>&       Parent,
    const MeshVS_DisplayModeFlags&        Flags    = MeshVS_DMF_ElementalColorDataPrs,
    const occ::handle<MeshVS_DataSource>& DS       = nullptr,
    const int                             Id       = -1,
    const MeshVS_BuilderPriority&         Priority = MeshVS_BP_ElemColor);

  Standard_EXPORT void Build(const occ::handle<Prs3d_Presentation>& Prs,
                             const TColStd_PackedMapOfInteger&      IDs,
                             TColStd_PackedMapOfInteger&            IDsToExclude,
                             const bool                             IsElement,
                             const int                              DisplayMode) const override;

  Standard_EXPORT const NCollection_DataMap<int, Quantity_Color>& GetColors1() const;

  Standard_EXPORT void SetColors1(const NCollection_DataMap<int, Quantity_Color>& Map);

  Standard_EXPORT bool HasColors1() const;

  Standard_EXPORT bool GetColor1(const int ID, Quantity_Color& theColor) const;

  Standard_EXPORT void SetColor1(const int ID, const Quantity_Color& theColor);

  Standard_EXPORT const NCollection_DataMap<int, MeshVS_TwoColors>& GetColors2() const;

  Standard_EXPORT void SetColors2(const NCollection_DataMap<int, MeshVS_TwoColors>& Map);

  Standard_EXPORT bool HasColors2() const;

  Standard_EXPORT bool GetColor2(const int ID, MeshVS_TwoColors& theColor) const;

  Standard_EXPORT bool GetColor2(const int       ID,
                                 Quantity_Color& theColor1,
                                 Quantity_Color& theColor2) const;

  Standard_EXPORT void SetColor2(const int ID, const MeshVS_TwoColors& theTwoColors);

  Standard_EXPORT void SetColor2(const int             ID,
                                 const Quantity_Color& theColor1,
                                 const Quantity_Color& theColor2);

  DEFINE_STANDARD_RTTIEXT(MeshVS_ElementalColorPrsBuilder, MeshVS_PrsBuilder)

private:
  NCollection_DataMap<int, Quantity_Color>   myElemColorMap1;
  NCollection_DataMap<int, MeshVS_TwoColors> myElemColorMap2;
};
