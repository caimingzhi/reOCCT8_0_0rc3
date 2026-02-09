#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Wire.hpp>
#include <BRepFeat_Form.hpp>
#include <Standard_Integer.hpp>
class Geom_Curve;
class TopoDS_Edge;

class BRepFeat_MakePipe : public BRepFeat_Form
{
public:
  DEFINE_STANDARD_ALLOC

  BRepFeat_MakePipe();

  BRepFeat_MakePipe(const TopoDS_Shape& Sbase,
                    const TopoDS_Shape& Pbase,
                    const TopoDS_Face&  Skface,
                    const TopoDS_Wire&  Spine,
                    const int           Fuse,
                    const bool          Modify);

  Standard_EXPORT void Init(const TopoDS_Shape& Sbase,
                            const TopoDS_Shape& Pbase,
                            const TopoDS_Face&  Skface,
                            const TopoDS_Wire&  Spine,
                            const int           Fuse,
                            const bool          Modify);

  Standard_EXPORT void Add(const TopoDS_Edge& E, const TopoDS_Face& OnFace);

  Standard_EXPORT void Perform();

  Standard_EXPORT void Perform(const TopoDS_Shape& Until);

  Standard_EXPORT void Perform(const TopoDS_Shape& From, const TopoDS_Shape& Until);

  Standard_EXPORT void Curves(NCollection_Sequence<occ::handle<Geom_Curve>>& S) override;

  Standard_EXPORT occ::handle<Geom_Curve> BarycCurve() override;

private:
  TopoDS_Shape myPbase;
  TopoDS_Face  mySkface;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                mySlface;
  TopoDS_Wire                                   mySpine;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCurves;
  occ::handle<Geom_Curve>                       myBCurve;
};

inline BRepFeat_MakePipe::BRepFeat_MakePipe() = default;

inline BRepFeat_MakePipe::BRepFeat_MakePipe(const TopoDS_Shape& Sbase,
                                            const TopoDS_Shape& Pbase,
                                            const TopoDS_Face&  Skface,
                                            const TopoDS_Wire&  Spine,
                                            const int           Fuse,
                                            const bool          Modify)

{
  Init(Sbase, Pbase, Skface, Spine, Fuse, Modify);
}
