#pragma once

#include <Standard_Integer.hpp>
#include <Quantity_Color.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <MeshVS_PrsBuilder.hpp>
#include <MeshVS_DisplayModeFlags.hpp>
#include <MeshVS_BuilderPriority.hpp>
#include <TColStd_PackedMapOfInteger.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class MeshVS_Mesh;
class MeshVS_DataSource;
class Graphic3d_Texture2D;
class Graphic3d_ArrayOfPrimitives;

class MeshVS_NodalColorPrsBuilder : public MeshVS_PrsBuilder
{

public:
  Standard_EXPORT MeshVS_NodalColorPrsBuilder(
    const occ::handle<MeshVS_Mesh>&       Parent,
    const MeshVS_DisplayModeFlags&        Flags    = MeshVS_DMF_NodalColorDataPrs,
    const occ::handle<MeshVS_DataSource>& DS       = nullptr,
    const int                             Id       = -1,
    const MeshVS_BuilderPriority&         Priority = MeshVS_BP_NodalColor);

  Standard_EXPORT void Build(const occ::handle<Prs3d_Presentation>& Prs,
                             const TColStd_PackedMapOfInteger&      IDs,
                             TColStd_PackedMapOfInteger&            IDsToExclude,
                             const bool                             IsElement,
                             const int                              DisplayMode) const override;

  Standard_EXPORT const NCollection_DataMap<int, Quantity_Color>& GetColors() const;

  Standard_EXPORT void SetColors(const NCollection_DataMap<int, Quantity_Color>& Map);

  Standard_EXPORT bool HasColors() const;

  Standard_EXPORT bool GetColor(const int ID, Quantity_Color& theColor) const;

  Standard_EXPORT void SetColor(const int ID, const Quantity_Color& theColor);

  Standard_EXPORT void UseTexture(const bool theToUse);

  Standard_EXPORT bool IsUseTexture() const;

  Standard_EXPORT void SetColorMap(const NCollection_Sequence<Quantity_Color>& theColors);

  Standard_EXPORT const NCollection_Sequence<Quantity_Color>& GetColorMap() const;

  Standard_EXPORT void SetInvalidColor(const Quantity_Color& theInvalidColor);

  Standard_EXPORT Quantity_Color GetInvalidColor() const;

  Standard_EXPORT void SetTextureCoords(const NCollection_DataMap<int, double>& theMap);

  Standard_EXPORT const NCollection_DataMap<int, double>& GetTextureCoords() const;

  Standard_EXPORT void SetTextureCoord(const int theID, const double theCoord);

  Standard_EXPORT double GetTextureCoord(const int theID);

  Standard_EXPORT void AddVolumePrs(
    const occ::handle<NCollection_HArray1<NCollection_Sequence<int>>>& theTopo,
    const NCollection_Array1<int>&                                     theNodes,
    const NCollection_Array1<double>&                                  theCoords,
    const occ::handle<Graphic3d_ArrayOfPrimitives>&                    theArray,
    const bool                                                         theIsShaded,
    const int                                                          theNbColors,
    const int                                                          theNbTexColors,
    const double                                                       theColorRatio) const;

  DEFINE_STANDARD_RTTIEXT(MeshVS_NodalColorPrsBuilder, MeshVS_PrsBuilder)

private:
  Standard_EXPORT occ::handle<Graphic3d_Texture2D> CreateTexture() const;

  NCollection_DataMap<int, Quantity_Color> myNodeColorMap;
  bool                                     myUseTexture;
  NCollection_Sequence<Quantity_Color>     myTextureColorMap;
  NCollection_DataMap<int, double>         myTextureCoords;
  Quantity_Color                           myInvalidColor;
};
