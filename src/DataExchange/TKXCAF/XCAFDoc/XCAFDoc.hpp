#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TCollection_AsciiString.hpp>

#include <XCAFDoc_ColorType.hpp>
class TDF_Attribute;
class Standard_GUID;

class XCAFDoc
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static const Standard_GUID& AssemblyGUID();

  Standard_EXPORT static const Standard_GUID& ShapeRefGUID();

  Standard_EXPORT static const Standard_GUID& ColorRefGUID(const XCAFDoc_ColorType type);

  Standard_EXPORT static const Standard_GUID& DimTolRefGUID();

  Standard_EXPORT static const Standard_GUID& DimensionRefFirstGUID();

  Standard_EXPORT static const Standard_GUID& DimensionRefSecondGUID();

  Standard_EXPORT static const Standard_GUID& GeomToleranceRefGUID();

  Standard_EXPORT static const Standard_GUID& DatumRefGUID();

  Standard_EXPORT static const Standard_GUID& DatumTolRefGUID();

  Standard_EXPORT static const Standard_GUID& LayerRefGUID();

  Standard_EXPORT static const Standard_GUID& MaterialRefGUID();

  Standard_EXPORT static const Standard_GUID& VisMaterialRefGUID();

  Standard_EXPORT static const Standard_GUID& NoteRefGUID();

  Standard_EXPORT static const Standard_GUID& InvisibleGUID();

  Standard_EXPORT static const Standard_GUID& ColorByLayerGUID();

  Standard_EXPORT static const Standard_GUID& ExternRefGUID();

  Standard_EXPORT static const Standard_GUID& SHUORefGUID();

  Standard_EXPORT static const Standard_GUID& ViewRefGUID();

  Standard_EXPORT static const Standard_GUID& ViewRefShapeGUID();

  Standard_EXPORT static const Standard_GUID& ViewRefGDTGUID();

  Standard_EXPORT static const Standard_GUID& ViewRefPlaneGUID();

  Standard_EXPORT static const Standard_GUID& ViewRefNoteGUID();
  Standard_EXPORT static const Standard_GUID& ViewRefAnnotationGUID();

  Standard_EXPORT static const Standard_GUID& LockGUID();

  Standard_EXPORT static TCollection_AsciiString AttributeInfo(
    const occ::handle<TDF_Attribute>& theAtt);
};
