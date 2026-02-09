#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <ShapeExtend_Status.hpp>

class ShapeFix_Wireframe : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_Wireframe();

  Standard_EXPORT ShapeFix_Wireframe(const TopoDS_Shape& shape);

  Standard_EXPORT virtual void ClearStatuses();

  Standard_EXPORT void Load(const TopoDS_Shape& shape);

  Standard_EXPORT bool FixWireGaps();

  Standard_EXPORT bool FixSmallEdges();

  Standard_EXPORT bool CheckSmallEdges(
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theSmallEdges,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      theEdgeToFaces,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                            theFaceWithSmall,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMultyEdges);

  Standard_EXPORT bool MergeSmallEdges(
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theSmallEdges,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
      theEdgeToFaces,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                            theFaceWithSmall,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& theMultyEdges,
    const bool                                              theModeDrop   = false,
    const double                                            theLimitAngle = -1);

  bool StatusWireGaps(const ShapeExtend_Status status) const;

  bool StatusSmallEdges(const ShapeExtend_Status status) const;

  TopoDS_Shape Shape();

  bool& ModeDropSmallEdges();

  void SetLimitAngle(const double theLimitAngle);

  double LimitAngle() const;

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Wireframe, ShapeFix_Root)

protected:
  TopoDS_Shape myShape;

private:
  bool   myModeDrop;
  double myLimitAngle;
  int    myStatusWireGaps;
  int    myStatusSmallEdges;
};

#include <ShapeExtend.hpp>

inline bool ShapeFix_Wireframe::StatusWireGaps(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusWireGaps, status);
}

inline bool ShapeFix_Wireframe::StatusSmallEdges(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusSmallEdges, status);
}

inline TopoDS_Shape ShapeFix_Wireframe::Shape()
{
  return myShape;
}

inline bool& ShapeFix_Wireframe::ModeDropSmallEdges()
{
  return myModeDrop;
}

inline void ShapeFix_Wireframe::SetLimitAngle(const double theLimitAngle)
{
  myLimitAngle = theLimitAngle;
}

inline double ShapeFix_Wireframe::LimitAngle() const
{
  return myLimitAngle;
}
