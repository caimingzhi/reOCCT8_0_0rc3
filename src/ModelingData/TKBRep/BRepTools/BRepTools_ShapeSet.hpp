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

//! Contains a Shape and all its subshapes, locations
//! and geometries.
//!
//! The topology is inherited from TopTools.
class BRepTools_ShapeSet : public TopTools_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Builds an empty ShapeSet.
  //! @param theWithTriangles flag to write triangulation data
  Standard_EXPORT BRepTools_ShapeSet(const bool theWithTriangles = true,
                                     const bool theWithNormals   = false);

  //! Builds an empty ShapeSet.
  //! @param theWithTriangles flag to write triangulation data
  Standard_EXPORT BRepTools_ShapeSet(const BRep_Builder& theBuilder,
                                     const bool          theWithTriangles = true,
                                     const bool          theWithNormals   = false);

  Standard_EXPORT ~BRepTools_ShapeSet() override;

  //! Return true if shape should be stored with triangles.
  bool IsWithTriangles() const { return myWithTriangles; }

  //! Return true if shape should be stored triangulation with normals.
  bool IsWithNormals() const { return myWithNormals; }

  //! Define if shape will be stored with triangles.
  //! Ignored (always written) if face defines only triangulation (no surface).
  void SetWithTriangles(const bool theWithTriangles) { myWithTriangles = theWithTriangles; }

  //! Define if shape will be stored triangulation with normals.
  //! Ignored (always written) if face defines only triangulation (no surface).
  void SetWithNormals(const bool theWithNormals) { myWithNormals = theWithNormals; }

  //! Clears the content of the set.
  Standard_EXPORT void Clear() override;

  //! Stores the geometry of <S>.
  Standard_EXPORT void AddGeometry(const TopoDS_Shape& S) override;

  //! Dumps the geometry of me on the stream <OS>.
  Standard_EXPORT void DumpGeometry(Standard_OStream& OS) const override;

  //! Writes the geometry of me on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT void WriteGeometry(
    Standard_OStream&            OS,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  //! Reads the geometry of me from the stream <IS>.
  Standard_EXPORT void ReadGeometry(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) override;

  //! Dumps the geometry of <S> on the stream <OS>.
  Standard_EXPORT void DumpGeometry(const TopoDS_Shape& S, Standard_OStream& OS) const override;

  //! Writes the geometry of <S> on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT void WriteGeometry(const TopoDS_Shape& S, Standard_OStream& OS) const override;

  //! Reads the geometry of a shape of type <T> from the
  //! stream <IS> and returns it in <S>.
  Standard_EXPORT void ReadGeometry(const TopAbs_ShapeEnum T,
                                    Standard_IStream&      IS,
                                    TopoDS_Shape&          S) override;

  //! Inserts the shape <S2> in the shape <S1>. This
  //! method must be redefined to use the correct
  //! builder.
  Standard_EXPORT void AddShapes(TopoDS_Shape& S1, const TopoDS_Shape& S2) override;

  Standard_EXPORT void Check(const TopAbs_ShapeEnum T, TopoDS_Shape& S) override;

  //! Reads the 3d polygons of me
  //! from the stream <IS>.
  Standard_EXPORT void ReadPolygon3D(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Writes the 3d polygons
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT void WritePolygon3D(
    Standard_OStream&            OS,
    const bool                   Compact     = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  //! Dumps the 3d polygons
  //! on the stream <OS>.
  Standard_EXPORT void DumpPolygon3D(Standard_OStream& OS) const;

  //! Reads the triangulation of me
  //! from the stream <IS>.
  Standard_EXPORT void ReadTriangulation(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Writes the triangulation
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT void WriteTriangulation(
    Standard_OStream&            OS,
    const bool                   Compact     = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  //! Dumps the triangulation
  //! on the stream <OS>.
  Standard_EXPORT void DumpTriangulation(Standard_OStream& OS) const;

  //! Reads the polygons on triangulation of me
  //! from the stream <IS>.
  Standard_EXPORT void ReadPolygonOnTriangulation(
    Standard_IStream&            IS,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Writes the polygons on triangulation
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT void WritePolygonOnTriangulation(
    Standard_OStream&            OS,
    const bool                   Compact     = true,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  //! Dumps the polygons on triangulation
  //! on the stream <OS>.
  Standard_EXPORT void DumpPolygonOnTriangulation(Standard_OStream& OS) const;

private:
  BRep_Builder                                            myBuilder;
  GeomTools_SurfaceSet                                    mySurfaces;
  GeomTools_CurveSet                                      myCurves;
  GeomTools_Curve2dSet                                    myCurves2d;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myPolygons2D;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myPolygons3D;
  NCollection_IndexedDataMap<occ::handle<Poly_Triangulation>,
                             // clang-format off
                             bool> myTriangulations; //!< Contains a boolean flag with information
                                                                 //!  to save normals for triangulation
  // clang-format on
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myNodes;
  bool                                                    myWithTriangles;
  bool                                                    myWithNormals;
};

