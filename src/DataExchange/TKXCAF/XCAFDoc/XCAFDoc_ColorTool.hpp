#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFDoc_ColorType.hpp>
class XCAFDoc_ShapeTool;
class TDF_Label;
class Standard_GUID;
class Quantity_Color;
class Quantity_ColorRGBA;
class TopoDS_Shape;

class XCAFDoc_ColorTool : public TDataStd_GenericEmpty
{
public:
  Standard_EXPORT static bool AutoNaming();

  Standard_EXPORT static void SetAutoNaming(bool theIsAutoNaming);

public:
  Standard_EXPORT XCAFDoc_ColorTool();

  Standard_EXPORT static occ::handle<XCAFDoc_ColorTool> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT const occ::handle<XCAFDoc_ShapeTool>& ShapeTool();

  Standard_EXPORT bool IsColor(const TDF_Label& lab) const;

  Standard_EXPORT static bool GetColor(const TDF_Label& lab, Quantity_Color& col);

  Standard_EXPORT static bool GetColor(const TDF_Label& lab, Quantity_ColorRGBA& col);

  Standard_EXPORT bool FindColor(const Quantity_Color& col, TDF_Label& lab) const;

  Standard_EXPORT bool FindColor(const Quantity_ColorRGBA& col, TDF_Label& lab) const;

  Standard_EXPORT TDF_Label FindColor(const Quantity_Color& col) const;

  Standard_EXPORT TDF_Label FindColor(const Quantity_ColorRGBA& col) const;

  Standard_EXPORT TDF_Label AddColor(const Quantity_Color& col) const;

  Standard_EXPORT TDF_Label AddColor(const Quantity_ColorRGBA& col) const;

  Standard_EXPORT void RemoveColor(const TDF_Label& lab) const;

  Standard_EXPORT void GetColors(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT void SetColor(const TDF_Label&        L,
                                const TDF_Label&        colorL,
                                const XCAFDoc_ColorType type) const;

  Standard_EXPORT void SetColor(const TDF_Label&        L,
                                const Quantity_Color&   Color,
                                const XCAFDoc_ColorType type) const;

  Standard_EXPORT void SetColor(const TDF_Label&          L,
                                const Quantity_ColorRGBA& Color,
                                const XCAFDoc_ColorType   type) const;

  Standard_EXPORT void UnSetColor(const TDF_Label& L, const XCAFDoc_ColorType type) const;

  Standard_EXPORT bool IsSet(const TDF_Label& L, const XCAFDoc_ColorType type) const;

  Standard_EXPORT static bool GetColor(const TDF_Label&        L,
                                       const XCAFDoc_ColorType type,
                                       TDF_Label&              colorL);

  Standard_EXPORT static bool GetColor(const TDF_Label&        L,
                                       const XCAFDoc_ColorType type,
                                       Quantity_Color&         color);

  Standard_EXPORT static bool GetColor(const TDF_Label&        L,
                                       const XCAFDoc_ColorType type,
                                       Quantity_ColorRGBA&     color);

  Standard_EXPORT bool SetColor(const TopoDS_Shape&     S,
                                const TDF_Label&        colorL,
                                const XCAFDoc_ColorType type);

  Standard_EXPORT bool SetColor(const TopoDS_Shape&     S,
                                const Quantity_Color&   Color,
                                const XCAFDoc_ColorType type);

  Standard_EXPORT bool SetColor(const TopoDS_Shape&       S,
                                const Quantity_ColorRGBA& Color,
                                const XCAFDoc_ColorType   type);

  Standard_EXPORT bool UnSetColor(const TopoDS_Shape& S, const XCAFDoc_ColorType type);

  Standard_EXPORT bool IsSet(const TopoDS_Shape& S, const XCAFDoc_ColorType type);

  Standard_EXPORT bool GetColor(const TopoDS_Shape&     S,
                                const XCAFDoc_ColorType type,
                                TDF_Label&              colorL);

  Standard_EXPORT bool GetColor(const TopoDS_Shape&     S,
                                const XCAFDoc_ColorType type,
                                Quantity_Color&         color);

  Standard_EXPORT bool GetColor(const TopoDS_Shape&     S,
                                const XCAFDoc_ColorType type,
                                Quantity_ColorRGBA&     color);

  Standard_EXPORT static bool IsVisible(const TDF_Label& L);

  Standard_EXPORT void SetVisibility(const TDF_Label& shapeLabel, const bool isvisible = true);

  Standard_EXPORT bool IsColorByLayer(const TDF_Label& L) const;

  Standard_EXPORT void SetColorByLayer(const TDF_Label& shapeLabel,
                                       const bool       isColorByLayer = false);

  Standard_EXPORT bool SetInstanceColor(const TopoDS_Shape&     theShape,
                                        const XCAFDoc_ColorType type,
                                        const Quantity_Color&   color,
                                        const bool              isCreateSHUO = true);

  Standard_EXPORT bool SetInstanceColor(const TopoDS_Shape&       theShape,
                                        const XCAFDoc_ColorType   type,
                                        const Quantity_ColorRGBA& color,
                                        const bool                isCreateSHUO = true);

  Standard_EXPORT bool GetInstanceColor(const TopoDS_Shape&     theShape,
                                        const XCAFDoc_ColorType type,
                                        Quantity_Color&         color);

  Standard_EXPORT bool GetInstanceColor(const TopoDS_Shape&     theShape,
                                        const XCAFDoc_ColorType type,
                                        Quantity_ColorRGBA&     color);

  Standard_EXPORT bool IsInstanceVisible(const TopoDS_Shape& theShape);

  Standard_EXPORT bool ReverseChainsOfTreeNodes();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_ColorTool, TDataStd_GenericEmpty)

private:
  occ::handle<XCAFDoc_ShapeTool> myShapeTool;
};
