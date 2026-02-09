#pragma once

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>
#include <MeshVS_PrsBuilder.hpp>
#include <MeshVS_DisplayModeFlags.hpp>
#include <MeshVS_BuilderPriority.hpp>

class MeshVS_Mesh;
class Quantity_Color;
class MeshVS_DataSource;
class TCollection_AsciiString;

class MeshVS_TextPrsBuilder : public MeshVS_PrsBuilder
{

public:
  Standard_EXPORT MeshVS_TextPrsBuilder(
    const occ::handle<MeshVS_Mesh>&       Parent,
    const double                          Height,
    const Quantity_Color&                 Color,
    const MeshVS_DisplayModeFlags&        Flags    = MeshVS_DMF_TextDataPrs,
    const occ::handle<MeshVS_DataSource>& DS       = nullptr,
    const int                             Id       = -1,
    const MeshVS_BuilderPriority&         Priority = MeshVS_BP_Text);

  Standard_EXPORT void Build(const occ::handle<Prs3d_Presentation>& Prs,
                             const TColStd_PackedMapOfInteger&      IDs,
                             TColStd_PackedMapOfInteger&            IDsToExclude,
                             const bool                             IsElement,
                             const int                              theDisplayMode) const override;

  Standard_EXPORT const NCollection_DataMap<int, TCollection_AsciiString>& GetTexts(
    const bool IsElement) const;

  Standard_EXPORT void SetTexts(const bool                                               IsElement,
                                const NCollection_DataMap<int, TCollection_AsciiString>& Map);

  Standard_EXPORT bool HasTexts(const bool IsElement) const;

  Standard_EXPORT bool GetText(const bool               IsElement,
                               const int                ID,
                               TCollection_AsciiString& Text) const;

  Standard_EXPORT void SetText(const bool                     IsElement,
                               const int                      ID,
                               const TCollection_AsciiString& Text);

  DEFINE_STANDARD_RTTIEXT(MeshVS_TextPrsBuilder, MeshVS_PrsBuilder)

private:
  NCollection_DataMap<int, TCollection_AsciiString> myNodeTextMap;
  NCollection_DataMap<int, TCollection_AsciiString> myElemTextMap;
};
