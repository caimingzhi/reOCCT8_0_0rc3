#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <gp_Dir.hpp>
#include <BRepFeat_StatusError.hpp>
#include <BRepFeat_Form.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class TopoDS_Face;
class TopoDS_Edge;

class BRepFeat_MakePrism : public BRepFeat_Form
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_MakePrism();

  BRepFeat_MakePrism(const TopoDS_Shape& Sbase,
                     const TopoDS_Shape& Pbase,
                     const TopoDS_Face&  Skface,
                     const gp_Dir&       Direction,
                     const int           Fuse,
                     const bool          Modify);

  Standard_EXPORT void Init(const TopoDS_Shape& Sbase,
                            const TopoDS_Shape& Pbase,
                            const TopoDS_Face&  Skface,
                            const gp_Dir&       Direction,
                            const int           Fuse,
                            const bool          Modify);

  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  Standard_EXPORT void Perform(const double Length);

  Standard_EXPORT void Perform(const TopoDS_Shape& Until);

  Standard_EXPORT void Perform(const TopoDS_Shape& From, const TopoDS_Shape& Until);

  Standard_EXPORT void PerformUntilEnd();

  Standard_EXPORT void PerformFromEnd(const TopoDS_Shape& FUntil);

  Standard_EXPORT void PerformThruAll();

  Standard_EXPORT void PerformUntilHeight(const TopoDS_Shape& Until, const double Length);

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& S) override;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() override;

private:
  TopoDS_Shape myPbase;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                mySlface;
  gp_Dir                                        myDir;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCurves;
  occ::handle<Geom_Curve>                       myBCurve;
  BRepFeat_StatusError                          myStatusError;
};

inline BRepFeat_MakePrism::BRepFeat_MakePrism()
    : myStatusError(BRepFeat_OK)
{
}

inline BRepFeat_MakePrism::BRepFeat_MakePrism(const TopoDS_Shape& Sbase,
                                              const TopoDS_Shape& Pbase,
                                              const TopoDS_Face&  Skface,
                                              const gp_Dir&       Direc,
                                              const int           Fuse,
                                              const bool          Modify)

{
  Init(Sbase, Pbase, Skface, Direc, Fuse, Modify);
}
