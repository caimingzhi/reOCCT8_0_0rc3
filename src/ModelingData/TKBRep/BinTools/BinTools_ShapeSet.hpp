#pragma once

#include <BinTools_ShapeSetBase.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <BinTools_LocationSet.hpp>
#include <BRep_Builder.hpp>
#include <BinTools_SurfaceSet.hpp>
#include <BinTools_CurveSet.hpp>
#include <BinTools_Curve2dSet.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>

class BinTools_ShapeSet : public BinTools_ShapeSetBase
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinTools_ShapeSet();

  Standard_EXPORT ~BinTools_ShapeSet() override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT int Add(const TopoDS_Shape& S);

  Standard_EXPORT const TopoDS_Shape& Shape(const int I);

  Standard_EXPORT int Index(const TopoDS_Shape& S) const;

  Standard_EXPORT const BinTools_LocationSet& Locations() const;

  Standard_EXPORT BinTools_LocationSet& ChangeLocations();

  Standard_EXPORT int NbShapes() const;

  Standard_EXPORT void Write(
    Standard_OStream&            OS,
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void Read(
    Standard_IStream&            IS,
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT void Write(const TopoDS_Shape& S, Standard_OStream& OS) override;

  Standard_EXPORT virtual void WriteGeometry(
    Standard_OStream&            OS,
    const Message_ProgressRange& theRange = Message_ProgressRange()) const;

  Standard_EXPORT virtual void ReadGeometry(
    Standard_IStream&            IS,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT virtual void ReadFlagsAndSubs(TopoDS_Shape&          S,
                                                const TopAbs_ShapeEnum T,
                                                Standard_IStream&      IS,
                                                const int              NbShapes);

  Standard_EXPORT virtual void ReadSubs(TopoDS_Shape& S, Standard_IStream& IS, const int NbShapes);

  Standard_EXPORT void Read(Standard_IStream&, TopoDS_Shape&) override {};

  Standard_EXPORT virtual void WriteShape(const TopoDS_Shape& S, Standard_OStream& OS) const;

  Standard_EXPORT virtual void ReadShape(const TopAbs_ShapeEnum T,
                                         Standard_IStream&      IS,
                                         TopoDS_Shape&          S);

  Standard_EXPORT virtual void AddShape(const TopoDS_Shape& S);

  Standard_EXPORT virtual void AddShapes(TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT void ReadPolygon3D(
    Standard_IStream&            IS,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT void WritePolygon3D(
    Standard_OStream&            OS,
    const Message_ProgressRange& theRange = Message_ProgressRange()) const;

  Standard_EXPORT void ReadTriangulation(
    Standard_IStream&            IS,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT void WriteTriangulation(
    Standard_OStream&            OS,
    const Message_ProgressRange& theRange = Message_ProgressRange()) const;

  Standard_EXPORT void ReadPolygonOnTriangulation(
    Standard_IStream&            IS,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT void WritePolygonOnTriangulation(
    Standard_OStream&            OS,
    const Message_ProgressRange& theRange = Message_ProgressRange()) const;

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myShapes;
  BinTools_LocationSet                                          myLocations;
  BRep_Builder                                                  myBuilder;
  BinTools_SurfaceSet                                           mySurfaces;
  BinTools_CurveSet                                             myCurves;
  BinTools_Curve2dSet                                           myCurves2d;
  NCollection_IndexedMap<occ::handle<Poly_Polygon2D>>           myPolygons2D;
  NCollection_IndexedMap<occ::handle<Poly_Polygon3D>>           myPolygons3D;
  NCollection_IndexedDataMap<occ::handle<Poly_Triangulation>,

                             bool>
    myTriangulations;

  NCollection_IndexedMap<occ::handle<Poly_PolygonOnTriangulation>> myNodes;
};
