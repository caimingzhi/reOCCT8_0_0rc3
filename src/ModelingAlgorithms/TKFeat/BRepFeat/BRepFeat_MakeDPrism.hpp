#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Real.hpp>
#include <BRepFeat_StatusError.hpp>
#include <BRepFeat_Form.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class TopoDS_Shape;
class TopoDS_Edge;

class BRepFeat_MakeDPrism : public BRepFeat_Form
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_MakeDPrism(const TopoDS_Shape& Sbase,
                      const TopoDS_Face&  Pbase,
                      const TopoDS_Face&  Skface,
                      const double        Angle,
                      const int           Fuse,
                      const bool          Modify)
  {
    Init(Sbase, Pbase, Skface, Angle, Fuse, Modify);
  }

  BRepFeat_MakeDPrism()
      : myAngle(RealLast()),
        myStatusError(BRepFeat_OK)
  {
  }

  Standard_EXPORT void Init(const TopoDS_Shape& Sbase,
                            const TopoDS_Face&  Pbase,
                            const TopoDS_Face&  Skface,
                            const double        Angle,
                            const int           Fuse,
                            const bool          Modify);

  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  Standard_EXPORT void Perform(const double Height);

  Standard_EXPORT void Perform(const TopoDS_Shape& Until);

  Standard_EXPORT void Perform(const TopoDS_Shape& From, const TopoDS_Shape& Until);

  Standard_EXPORT void PerformUntilEnd();

  Standard_EXPORT void PerformFromEnd(const TopoDS_Shape& FUntil);

  Standard_EXPORT void PerformThruAll();

  Standard_EXPORT void PerformUntilHeight(const TopoDS_Shape& Until, const double Height);

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& S) override;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() override;

  Standard_EXPORT void BossEdges(const int sig);

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& TopEdges();

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& LatEdges();

private:
  TopoDS_Face myPbase;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                mySlface;
  double                                        myAngle;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCurves;
  occ::handle<Geom_Curve>                       myBCurve;
  NCollection_List<TopoDS_Shape>                myTopEdges;
  NCollection_List<TopoDS_Shape>                myLatEdges;
  BRepFeat_StatusError                          myStatusError;
};
