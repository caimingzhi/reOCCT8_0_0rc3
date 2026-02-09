#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRep_Builder.hpp>
#include <GeomTools_SurfaceSet.hpp>
#include <GeomTools_CurveSet.hpp>
#include <GeomTools_Curve2dSet.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopTools_ShapeSet.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <TopAbs_ShapeEnum.hpp>

class TopoDS_Shape;

class BRepTools_ShapeSet : public TopTools_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepTools_ShapeSet(const bool theWithTriangles = true,
                                     const bool theWithNormals   = false);

  Standard_EXPORT BRepTools_ShapeSet(const BRep_Builder& theBuilder,
                                     const bool          theWithTriangles = true,
                                     const bool          theWithNormals   = false);

  Standard_EXPORT ~BRepTools_ShapeSet() override;

  bool IsWithTriangles() const { return myWithTriangles; }

  bool IsWithNormals() const { return myWithNormals; }

  void SetWithTriangles(const bool theWithTriangles) { myWithTriangles = theWithTriangles; }

  void SetWithNormals(const bool theWithNormals) { myWithNormals = theWithNormals; }

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void AddGeometry(const TopoDS_Shape& S) override;

  Standard_EXPORT void DumpGeometry(Standard_OStream& OS) const override;

  Standard_EXPORT void WriteGeometry(
    Standard_OStream&            OS,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  Standard_EXPORT void ReadGeometry(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  Standard_EXPORT void DumpGeometry(const TopoDS_Shape& S, Standard_OStream& OS) const override;

  Standard_EXPORT void WriteGeometry(const TopoDS_Shape& S, Standard_OStream& OS) const override;

  Standard_EXPORT void ReadGeometry(const TopAbs_ShapeEnum T,
                                    Standard_IStream&      IS,
                                    TopoDS_Shape&          S) override;

  Standard_EXPORT void AddShapes(TopoDS_Shape& S1, const TopoDS_Shape& S2) override;

  Standard_EXPORT void Check(const TopAbs_ShapeEnum T, TopoDS_Shape& S) override;

  Standard_EXPORT void ReadPolygon3D(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void WritePolygon3D(
    Standard_OStream&            OS,
    const bool                   Compact     = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  Standard_EXPORT void DumpPolygon3D(Standard_OStream& OS) const;

  Standard_EXPORT void ReadTriangulation(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void WriteTriangulation(
    Standard_OStream&            OS,
    const bool                   Compact     = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  Standard_EXPORT void DumpTriangulation(Standard_OStream& OS) const;

  Standard_EXPORT void ReadPolygonOnTriangulation(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void WritePolygonOnTriangulation(
    Standard_OStream&            OS,
    const bool                   Compact     = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  Standard_EXPORT void DumpPolygonOnTriangulation(Standard_OStream& OS) const;

private:
  BRep_Builder                                            myBuilder;
  GeomTools_SurfaceSet                                    mySurfaces;
  GeomTools_CurveSet                                      myCurves;
  GeomTools_Curve2dSet                                    myCurves2d;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myPolygons2D;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myPolygons3D;
  NCollection_IndexedDataMap<occ::handle<Poly_Triangulation>,

                             bool>
    myTriangulations;

  NCollection_IndexedMap<occ::handle<Standard_Transient>> myNodes;
  bool                                                    myWithTriangles;
  bool                                                    myWithNormals;
};
