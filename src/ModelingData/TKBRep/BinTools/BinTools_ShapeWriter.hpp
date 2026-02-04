#pragma once


#include <BinTools_ShapeSetBase.hpp>
#include <BinTools_OStream.hpp>
#include <NCollection_DataMap.hpp>
#include <TopTools_ShapeMapHasher.hpp>

class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;
class Poly_Polygon3D;
class Poly_PolygonOnTriangulation;
class Poly_Triangulation;

//! Writes topology in OStream in binary format without grouping of objects by types
//! and using relative positions in a file as references.
class BinTools_ShapeWriter : public BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  //! Builds an empty ShapeSet.
  //! Parameter <theWithTriangles> is added for XML Persistence
  Standard_EXPORT BinTools_ShapeWriter();

  Standard_EXPORT ~BinTools_ShapeWriter() override;

  //! Clears the content of the set.
  Standard_EXPORT void Clear() override;

  //! Writes the shape to stream using previously stored shapes and objects to refer them.
  Standard_EXPORT void Write(const TopoDS_Shape& theShape, Standard_OStream& theStream) override;

  //! Writes location to the stream (all the needed sub-information or reference if it is already
  //! used).
  Standard_EXPORT virtual void WriteLocation(BinTools_OStream&      theStream,
                                             const TopLoc_Location& theLocation);

private:
  //! Writes shape to the stream (all the needed sub-information or reference if it is already
  //! used).
  virtual void WriteShape(BinTools_OStream& theStream, const TopoDS_Shape& theShape);
  //! Writes curve to the stream (all the needed sub-information or reference if it is already
  //! used).
  void WriteCurve(BinTools_OStream& theStream, const occ::handle<Geom_Curve>& theCurve);
  //! Writes curve2d to the stream (all the needed sub-information or reference if it is already
  //! used).
  void WriteCurve(BinTools_OStream& theStream, const occ::handle<Geom2d_Curve>& theCurve);
  //! Writes surface to the stream.
  void WriteSurface(BinTools_OStream& theStream, const occ::handle<Geom_Surface>& theSurface);
  //! Writes ploygon3d to the stream.
  void WritePolygon(BinTools_OStream& theStream, const occ::handle<Poly_Polygon3D>& thePolygon);
  //! Writes polygon on triangulation to the stream.
  void WritePolygon(BinTools_OStream&                               theStream,
                    const occ::handle<Poly_PolygonOnTriangulation>& thePolygon);
  //! Writes triangulation to the stream.
  void WriteTriangulation(BinTools_OStream&                      theStream,
                          const occ::handle<Poly_Triangulation>& theTriangulation,
                          const bool                             theNeedToWriteNormals);

  /// position of the shape previously stored
  NCollection_DataMap<TopoDS_Shape, uint64_t, TopTools_ShapeMapHasher>    myShapePos;
  NCollection_DataMap<TopLoc_Location, uint64_t>                          myLocationPos;
  NCollection_DataMap<occ::handle<Geom_Curve>, uint64_t>                  myCurvePos;
  NCollection_DataMap<occ::handle<Geom2d_Curve>, uint64_t>                myCurve2dPos;
  NCollection_DataMap<occ::handle<Geom_Surface>, uint64_t>                mySurfacePos;
  NCollection_DataMap<occ::handle<Poly_Polygon3D>, uint64_t>              myPolygon3dPos;
  NCollection_DataMap<occ::handle<Poly_PolygonOnTriangulation>, uint64_t> myPolygonPos;
  NCollection_DataMap<occ::handle<Poly_Triangulation>, uint64_t>          myTriangulationPos;
};

