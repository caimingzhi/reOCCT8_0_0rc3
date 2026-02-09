#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_HSequence.hpp>
class XCAFDoc_ShapeTool;
class TDF_Label;
class Standard_GUID;
class TCollection_ExtendedString;
class TopoDS_Shape;

class XCAFDoc_LayerTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_LayerTool();

  Standard_EXPORT static occ::handle<XCAFDoc_LayerTool> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT const occ::handle<XCAFDoc_ShapeTool>& ShapeTool();

  Standard_EXPORT bool IsLayer(const TDF_Label& lab) const;

  Standard_EXPORT bool GetLayer(const TDF_Label& lab, TCollection_ExtendedString& aLayer) const;

  Standard_EXPORT bool FindLayer(const TCollection_ExtendedString& aLayer, TDF_Label& lab) const;

  Standard_EXPORT TDF_Label FindLayer(const TCollection_ExtendedString& aLayer,
                                      const bool theToFindWithProperty = false,
                                      const bool theToFindVisible      = true) const;

  Standard_EXPORT TDF_Label AddLayer(const TCollection_ExtendedString& theLayer) const;

  Standard_EXPORT TDF_Label AddLayer(const TCollection_ExtendedString& theLayer,
                                     const bool                        theToFindVisible) const;

  Standard_EXPORT void RemoveLayer(const TDF_Label& lab) const;

  Standard_EXPORT void GetLayerLabels(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT void SetLayer(const TDF_Label& L,
                                const TDF_Label& LayerL,
                                const bool       shapeInOneLayer = false) const;

  Standard_EXPORT void SetLayer(const TDF_Label&                  L,
                                const TCollection_ExtendedString& aLayer,
                                const bool                        shapeInOneLayer = false) const;

  Standard_EXPORT void UnSetLayers(const TDF_Label& L) const;

  Standard_EXPORT bool UnSetOneLayer(const TDF_Label&                  L,
                                     const TCollection_ExtendedString& aLayer) const;

  Standard_EXPORT bool UnSetOneLayer(const TDF_Label& L, const TDF_Label& aLayerL) const;

  Standard_EXPORT bool IsSet(const TDF_Label& L, const TCollection_ExtendedString& aLayer) const;

  Standard_EXPORT bool IsSet(const TDF_Label& L, const TDF_Label& aLayerL) const;

  Standard_EXPORT bool GetLayers(
    const TDF_Label&                                                L,
    occ::handle<NCollection_HSequence<TCollection_ExtendedString>>& aLayerS);

  Standard_EXPORT bool GetLayers(const TDF_Label& L, NCollection_Sequence<TDF_Label>& aLayerLS);

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_ExtendedString>> GetLayers(
    const TDF_Label& L);

  Standard_EXPORT static void GetShapesOfLayer(const TDF_Label&                 theLayerL,
                                               NCollection_Sequence<TDF_Label>& theShLabels);

  Standard_EXPORT bool IsVisible(const TDF_Label& layerL) const;

  Standard_EXPORT void SetVisibility(const TDF_Label& layerL, const bool isvisible = true) const;

  Standard_EXPORT bool SetLayer(const TopoDS_Shape& Sh,
                                const TDF_Label&    LayerL,
                                const bool          shapeInOneLayer = false);

  Standard_EXPORT bool SetLayer(const TopoDS_Shape&               Sh,
                                const TCollection_ExtendedString& aLayer,
                                const bool                        shapeInOneLayer = false);

  Standard_EXPORT bool UnSetLayers(const TopoDS_Shape& Sh);

  Standard_EXPORT bool UnSetOneLayer(const TopoDS_Shape&               Sh,
                                     const TCollection_ExtendedString& aLayer);

  Standard_EXPORT bool UnSetOneLayer(const TopoDS_Shape& Sh, const TDF_Label& aLayerL);

  Standard_EXPORT bool IsSet(const TopoDS_Shape& Sh, const TCollection_ExtendedString& aLayer);

  Standard_EXPORT bool IsSet(const TopoDS_Shape& Sh, const TDF_Label& aLayerL);

  Standard_EXPORT bool GetLayers(
    const TopoDS_Shape&                                             Sh,
    occ::handle<NCollection_HSequence<TCollection_ExtendedString>>& aLayerS);

  Standard_EXPORT bool GetLayers(const TopoDS_Shape& Sh, NCollection_Sequence<TDF_Label>& aLayerLS);

  Standard_EXPORT occ::handle<NCollection_HSequence<TCollection_ExtendedString>> GetLayers(
    const TopoDS_Shape& Sh);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_LayerTool, TDataStd_GenericEmpty)

private:
  occ::handle<XCAFDoc_ShapeTool> myShapeTool;
};
