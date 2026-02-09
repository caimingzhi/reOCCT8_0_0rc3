#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepCheck_Status.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <BRepCheck_Result.hpp>
class TopoDS_Wire;
class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Edge;

class BRepCheck_Wire : public BRepCheck_Result
{

public:
  Standard_EXPORT BRepCheck_Wire(const TopoDS_Wire& W);

  Standard_EXPORT void InContext(const TopoDS_Shape& ContextShape) override;

  Standard_EXPORT void Minimum() override;

  Standard_EXPORT void Blind() override;

  Standard_EXPORT BRepCheck_Status Closed(const bool Update = false);

  Standard_EXPORT BRepCheck_Status Closed2d(const TopoDS_Face& F, const bool Update = false);

  Standard_EXPORT BRepCheck_Status Orientation(const TopoDS_Face& F, const bool Update = false);

  Standard_EXPORT BRepCheck_Status SelfIntersect(const TopoDS_Face& F,
                                                 TopoDS_Edge&       E1,
                                                 TopoDS_Edge&       E2,
                                                 const bool         Update = false);

  Standard_EXPORT bool GeometricControls() const;

  Standard_EXPORT void GeometricControls(const bool B);

  Standard_EXPORT void SetStatus(const BRepCheck_Status theStatus);

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Wire, BRepCheck_Result)

private:
  bool             myCdone;
  BRepCheck_Status myCstat;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
       myMapVE;
  bool myGctrl;
};
