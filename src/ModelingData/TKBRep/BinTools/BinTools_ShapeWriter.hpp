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

class BinTools_ShapeWriter : public BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinTools_ShapeWriter();

  Standard_EXPORT ~BinTools_ShapeWriter() override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void Write(const TopoDS_Shape& theShape, Standard_OStream& theStream) override;

  Standard_EXPORT virtual void WriteLocation(BinTools_OStream&      theStream,
                                             const TopLoc_Location& theLocation);

private:
  virtual void WriteShape(BinTools_OStream& theStream, const TopoDS_Shape& theShape);

  void WriteCurve(BinTools_OStream& theStream, const occ::handle<Geom_Curve>& theCurve);

  void WriteCurve(BinTools_OStream& theStream, const occ::handle<Geom2d_Curve>& theCurve);

  void WriteSurface(BinTools_OStream& theStream, const occ::handle<Geom_Surface>& theSurface);

  void WritePolygon(BinTools_OStream& theStream, const occ::handle<Poly_Polygon3D>& thePolygon);

  void WritePolygon(BinTools_OStream&                               theStream,
                    const occ::handle<Poly_PolygonOnTriangulation>& thePolygon);

  void WriteTriangulation(BinTools_OStream&                      theStream,
                          const occ::handle<Poly_Triangulation>& theTriangulation,
                          const bool                             theNeedToWriteNormals);

  NCollection_DataMap<TopoDS_Shape, uint64_t, TopTools_ShapeMapHasher>    myShapePos;
  NCollection_DataMap<TopLoc_Location, uint64_t>                          myLocationPos;
  NCollection_DataMap<occ::handle<Geom_Curve>, uint64_t>                  myCurvePos;
  NCollection_DataMap<occ::handle<Geom2d_Curve>, uint64_t>                myCurve2dPos;
  NCollection_DataMap<occ::handle<Geom_Surface>, uint64_t>                mySurfacePos;
  NCollection_DataMap<occ::handle<Poly_Polygon3D>, uint64_t>              myPolygon3dPos;
  NCollection_DataMap<occ::handle<Poly_PolygonOnTriangulation>, uint64_t> myPolygonPos;
  NCollection_DataMap<occ::handle<Poly_Triangulation>, uint64_t>          myTriangulationPos;
};
