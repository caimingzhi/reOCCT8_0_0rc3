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

class BinTools_ShapeReader : public BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinTools_ShapeReader();

  Standard_EXPORT ~BinTools_ShapeReader() override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void Read(Standard_IStream& theStream, TopoDS_Shape& theShape) override;

  Standard_EXPORT const TopLoc_Location* ReadLocation(BinTools_IStream& theStream);

private:
  TopoDS_Shape ReadShape(BinTools_IStream& theStream);

  occ::handle<Geom_Curve> ReadCurve(BinTools_IStream& theStream);

  occ::handle<Geom2d_Curve> ReadCurve2d(BinTools_IStream& theStream);

  occ::handle<Geom_Surface> ReadSurface(BinTools_IStream& theStream);

  occ::handle<Poly_Polygon3D> ReadPolygon3d(BinTools_IStream& theStream);

  occ::handle<Poly_PolygonOnTriangulation> ReadPolygon(BinTools_IStream& theStream);

  occ::handle<Poly_Triangulation> ReadTriangulation(BinTools_IStream& theStream);

  NCollection_DataMap<uint64_t, TopoDS_Shape>                             myShapePos;
  NCollection_DataMap<uint64_t, TopLoc_Location>                          myLocationPos;
  NCollection_DataMap<uint64_t, occ::handle<Geom_Curve>>                  myCurvePos;
  NCollection_DataMap<uint64_t, occ::handle<Geom2d_Curve>>                myCurve2dPos;
  NCollection_DataMap<uint64_t, occ::handle<Geom_Surface>>                mySurfacePos;
  NCollection_DataMap<uint64_t, occ::handle<Poly_Polygon3D>>              myPolygon3dPos;
  NCollection_DataMap<uint64_t, occ::handle<Poly_PolygonOnTriangulation>> myPolygonPos;
  NCollection_DataMap<uint64_t, occ::handle<Poly_Triangulation>>          myTriangulationPos;
};
