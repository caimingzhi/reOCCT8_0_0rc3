#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2d_Curve.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Face;
class TopoDS_Wire;
class Geom2d_Curve;

class BRepMAT2d_Explorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepMAT2d_Explorer();

  Standard_EXPORT BRepMAT2d_Explorer(const TopoDS_Face& aFace);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Perform(const TopoDS_Face& aFace);

  Standard_EXPORT int NumberOfContours() const;

  Standard_EXPORT int NumberOfCurves(const int IndexContour) const;

  Standard_EXPORT void Init(const int IndexContour);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<Geom2d_Curve> Value() const;

  Standard_EXPORT TopoDS_Shape Shape() const;

  Standard_EXPORT const NCollection_Sequence<occ::handle<Geom2d_Curve>>& Contour(
    const int IndexContour) const;

  Standard_EXPORT bool IsModified(const TopoDS_Shape& aShape) const;

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& aShape) const;

  Standard_EXPORT const NCollection_Sequence<bool>& GetIsClosed() const;

private:
  Standard_EXPORT void Add(const TopoDS_Wire& Spine,
                           const TopoDS_Face& aFace,
                           TopoDS_Face&       aNewFace);

  Standard_EXPORT void NewContour();

  Standard_EXPORT void Add(const occ::handle<Geom2d_Curve>& aCurve);

  NCollection_Sequence<NCollection_Sequence<occ::handle<Geom2d_Curve>>>           theCurves;
  int                                                                             current;
  int                                                                             currentContour;
  TopoDS_Shape                                                                    myShape;
  NCollection_Sequence<bool>                                                      myIsClosed;
  NCollection_IndexedDataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myModifShapes;
};
