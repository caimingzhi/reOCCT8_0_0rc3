#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <UnitsMethods_LengthUnit.hpp>

class Standard_GUID;
class TDF_Label;
class TDocStd_Document;
class XCAFDoc_ShapeTool;
class XCAFDoc_ColorTool;
class XCAFDoc_ClippingPlaneTool;
class XCAFDoc_LayerTool;
class XCAFDoc_DimTolTool;
class XCAFDoc_MaterialTool;
class XCAFDoc_NotesTool;
class XCAFDoc_ViewTool;
class XCAFDoc_VisMaterialTool;

class XCAFDoc_DocumentTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_DocumentTool> Set(const TDF_Label& L,
                                                               const bool       IsAcces = true);

  Standard_EXPORT static bool IsXCAFDocument(const occ::handle<TDocStd_Document>& Doc);

  Standard_EXPORT static TDF_Label DocLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label ShapesLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label ColorsLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label LayersLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label DGTsLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label MaterialsLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label ViewsLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label ClippingPlanesLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label NotesLabel(const TDF_Label& acces);

  Standard_EXPORT static TDF_Label VisMaterialLabel(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_ShapeTool> ShapeTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckShapeTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_ColorTool> ColorTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckColorTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_VisMaterialTool> VisMaterialTool(
    const TDF_Label& theLabel);

  Standard_EXPORT static bool CheckVisMaterialTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_LayerTool> LayerTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckLayerTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_DimTolTool> DimTolTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckDimTolTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_MaterialTool> MaterialTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckMaterialTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_ViewTool> ViewTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckViewTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_ClippingPlaneTool> ClippingPlaneTool(
    const TDF_Label& acces);

  Standard_EXPORT static bool CheckClippingPlaneTool(const TDF_Label& theAcces);

  Standard_EXPORT static occ::handle<XCAFDoc_NotesTool> NotesTool(const TDF_Label& acces);

  Standard_EXPORT static bool CheckNotesTool(const TDF_Label& theAcces);

  Standard_EXPORT static bool GetLengthUnit(const occ::handle<TDocStd_Document>& theDoc,
                                            double&                              theResut,
                                            const UnitsMethods_LengthUnit        theBaseUnit);

  Standard_EXPORT static bool GetLengthUnit(const occ::handle<TDocStd_Document>& theDoc,
                                            double&                              theResut);

  Standard_EXPORT static void SetLengthUnit(const occ::handle<TDocStd_Document>& theDoc,
                                            const double                         theUnitValue);

  Standard_EXPORT static void SetLengthUnit(const occ::handle<TDocStd_Document>& theDoc,
                                            const double                         theUnitValue,
                                            const UnitsMethods_LengthUnit        theBaseUnit);

public:
  Standard_EXPORT XCAFDoc_DocumentTool();

  Standard_EXPORT void Init() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT bool AfterRetrieval(const bool forceIt = false) override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_DocumentTool, TDataStd_GenericEmpty)
};
