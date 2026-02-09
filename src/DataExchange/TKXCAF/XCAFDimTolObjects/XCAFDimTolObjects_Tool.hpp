#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XCAFDoc_DimTolTool.hpp>
#include <TDocStd_Document.hpp>
#include <Standard_Boolean.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_DataMap.hpp>
#include <XCAFDimTolObjects_GeomToleranceObject.hpp>
#include <XCAFDimTolObjects_DatumObject.hpp>

class XCAFDimTolObjects_GeomToleranceObject;
class XCAFDimTolObjects_DimensionObject;

class XCAFDimTolObjects_DatumObject;
class TDocStd_Document;
class TopoDS_Shape;

class XCAFDimTolObjects_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XCAFDimTolObjects_Tool(const occ::handle<TDocStd_Document>& theDoc);

  Standard_EXPORT void GetDimensions(
    NCollection_Sequence<occ::handle<XCAFDimTolObjects_DimensionObject>>&
      theDimensionObjectSequence) const;

  Standard_EXPORT bool GetRefDimensions(
    const TopoDS_Shape&                                                   theShape,
    NCollection_Sequence<occ::handle<XCAFDimTolObjects_DimensionObject>>& theDimensions) const;

  Standard_EXPORT void GetGeomTolerances(
    NCollection_Sequence<occ::handle<XCAFDimTolObjects_GeomToleranceObject>>&
      theGeomToleranceObjectSequence,
    NCollection_Sequence<occ::handle<XCAFDimTolObjects_DatumObject>>& theDatumObjectSequence,
    NCollection_DataMap<occ::handle<XCAFDimTolObjects_GeomToleranceObject>,
                        occ::handle<XCAFDimTolObjects_DatumObject>>&  theMap) const;

  Standard_EXPORT bool GetRefGeomTolerances(
    const TopoDS_Shape& theShape,
    NCollection_Sequence<occ::handle<XCAFDimTolObjects_GeomToleranceObject>>&
      theGeomToleranceObjectSequence,
    NCollection_Sequence<occ::handle<XCAFDimTolObjects_DatumObject>>& theDatumObjectSequence,
    NCollection_DataMap<occ::handle<XCAFDimTolObjects_GeomToleranceObject>,
                        occ::handle<XCAFDimTolObjects_DatumObject>>&  theMap) const;

  Standard_EXPORT bool GetRefDatum(const TopoDS_Shape&                         theShape,
                                   occ::handle<XCAFDimTolObjects_DatumObject>& theDatum) const;

private:
  occ::handle<XCAFDoc_DimTolTool> myDimTolTool;
};
