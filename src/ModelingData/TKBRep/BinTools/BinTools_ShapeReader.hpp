#pragma once

#include <BinTools_ShapeSetBase.hpp>
#include <BinTools_IStream.hpp>
#include <NCollection_DataMap.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>

class Geom_Curve;
class Geom_Surface;
class Geom2d_Curve;
class Poly_Polygon3D;
class Poly_PolygonOnTriangulation;
class Poly_Triangulation;

//! Reads topology from IStream in binary format without grouping of objects by types
//! and using relative positions in a file as references.
class BinTools_ShapeReader : public BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initializes a shape reader.
  Standard_EXPORT BinTools_ShapeReader();

  Standard_EXPORT ~BinTools_ShapeReader() override;

  //! Clears the content of the set.
  Standard_EXPORT void Clear() override;

  //! Reads the shape from stream using previously restored shapes and objects by references.
  Standard_EXPORT void Read(Standard_IStream& theStream, TopoDS_Shape& theShape) override;

  //! Reads location from the stream.
  Standard_EXPORT const TopLoc_Location* ReadLocation(BinTools_IStream& theStream);

private:
  //! Reads the shape from stream using previously restored shapes and objects by references.
  TopoDS_Shape ReadShape(BinTools_IStream& theStream);
  //! Reads curve from the stream.
  occ::handle<Geom_Curve> ReadCurve(BinTools_IStream& theStream);
  //! Reads curve2d from the stream.
  occ::handle<Geom2d_Curve> ReadCurve2d(BinTools_IStream& theStream);
  //! Reads surface from the stream.
  occ::handle<Geom_Surface> ReadSurface(BinTools_IStream& theStream);
  //! Reads ploygon3d from the stream.
  occ::handle<Poly_Polygon3D> ReadPolygon3d(BinTools_IStream& theStream);
  //! Reads polygon on triangulation from the stream.
  occ::handle<Poly_PolygonOnTriangulation> ReadPolygon(BinTools_IStream& theStream);
  //! Reads triangulation from the stream.
  occ::handle<Poly_Triangulation> ReadTriangulation(BinTools_IStream& theStream);

  /// position of the shape previously restored
  NCollection_DataMap<uint64_t, TopoDS_Shape>                             myShapePos;
  NCollection_DataMap<uint64_t, TopLoc_Location>                          myLocationPos;
  NCollection_DataMap<uint64_t, occ::handle<Geom_Curve>>                  myCurvePos;
  NCollection_DataMap<uint64_t, occ::handle<Geom2d_Curve>>                myCurve2dPos;
  NCollection_DataMap<uint64_t, occ::handle<Geom_Surface>>                mySurfacePos;
  NCollection_DataMap<uint64_t, occ::handle<Poly_Polygon3D>>              myPolygon3dPos;
  NCollection_DataMap<uint64_t, occ::handle<Poly_PolygonOnTriangulation>> myPolygonPos;
  NCollection_DataMap<uint64_t, occ::handle<Poly_Triangulation>>          myTriangulationPos;
};
