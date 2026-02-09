#pragma once

#include <Standard_Type.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>

class TopoDS_Shape;
class XCAFDoc_ShapeTool;
class XCAFDoc_VisMaterial;

class XCAFDoc_VisMaterialTool : public TDF_Attribute
{
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_VisMaterialTool, TDF_Attribute)
public:
  Standard_EXPORT static occ::handle<XCAFDoc_VisMaterialTool> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

public:
  Standard_EXPORT XCAFDoc_VisMaterialTool();

  Standard_EXPORT TDF_Label BaseLabel() const { return Label(); }

  Standard_EXPORT const occ::handle<XCAFDoc_ShapeTool>& ShapeTool();

  bool IsMaterial(const TDF_Label& theLabel) const { return !GetMaterial(theLabel).IsNull(); }

  Standard_EXPORT static occ::handle<XCAFDoc_VisMaterial> GetMaterial(const TDF_Label& theMatLabel);

  Standard_EXPORT TDF_Label AddMaterial(const occ::handle<XCAFDoc_VisMaterial>& theMat,
                                        const TCollection_AsciiString&          theName) const;

  Standard_EXPORT TDF_Label AddMaterial(const TCollection_AsciiString& theName) const;

  Standard_EXPORT void RemoveMaterial(const TDF_Label& theLabel) const;

  Standard_EXPORT void GetMaterials(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT void SetShapeMaterial(const TDF_Label& theShapeLabel,
                                        const TDF_Label& theMaterialLabel) const;

  Standard_EXPORT void UnSetShapeMaterial(const TDF_Label& theShapeLabel) const;

  Standard_EXPORT bool IsSetShapeMaterial(const TDF_Label& theLabel) const;

  Standard_EXPORT static bool GetShapeMaterial(const TDF_Label& theShapeLabel,
                                               TDF_Label&       theMaterialLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_VisMaterial> GetShapeMaterial(
    const TDF_Label& theShapeLabel);

  Standard_EXPORT bool SetShapeMaterial(const TopoDS_Shape& theShape,
                                        const TDF_Label&    theMaterialLabel);

  Standard_EXPORT bool UnSetShapeMaterial(const TopoDS_Shape& theShape);

  Standard_EXPORT bool IsSetShapeMaterial(const TopoDS_Shape& theShape);

  Standard_EXPORT bool GetShapeMaterial(const TopoDS_Shape& theShape, TDF_Label& theMaterialLabel);

  Standard_EXPORT occ::handle<XCAFDoc_VisMaterial> GetShapeMaterial(const TopoDS_Shape& theShape);

public:
  const Standard_GUID& ID() const override { return GetID(); }

  void Restore(const occ::handle<TDF_Attribute>&) override {}

  occ::handle<TDF_Attribute> NewEmpty() const override { return new XCAFDoc_VisMaterialTool(); }

  void Paste(const occ::handle<TDF_Attribute>&,
             const occ::handle<TDF_RelocationTable>&) const override
  {
  }

private:
  occ::handle<XCAFDoc_ShapeTool> myShapeTool;
};
