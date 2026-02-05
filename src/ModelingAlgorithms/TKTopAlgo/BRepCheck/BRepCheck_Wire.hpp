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

  //! if <ContextShape> is a face, consequently checks
  //! SelfIntersect(), Closed(), Orientation() and
  //! Closed2d until faulty is found
  Standard_EXPORT void InContext(const TopoDS_Shape& ContextShape) override;

  //! checks that the wire is not empty and "connex".
  //! Called by constructor
  Standard_EXPORT void Minimum() override;

  //! Does nothing
  Standard_EXPORT void Blind() override;

  //! Checks if the oriented edges of the wire give a
  //! closed wire. If the wire is closed, returns
  //! BRepCheck_NoError. Warning: if the first and
  //! last edge are infinite, the wire will be
  //! considered as a closed one. If <Update> is set to
  //! true, registers the status in the list.
  //! May return (and registers):
  //! **BRepCheck_NotConnected, if wire is not
  //! topologically closed
  //! **BRepCheck_RedundantEdge, if an edge is in wire
  //! more than 3 times or in case of 2 occurrences if
  //! not with FORWARD and REVERSED orientation.
  //! **BRepCheck_NoError
  Standard_EXPORT BRepCheck_Status Closed(const bool Update = false);

  //! Checks if edges of the wire give a wire closed in
  //! 2d space.
  //! Returns BRepCheck_NoError, or BRepCheck_NotClosed
  //! If <Update> is set to true, registers the
  //! status in the list.
  Standard_EXPORT BRepCheck_Status Closed2d(const TopoDS_Face& F, const bool Update = false);

  //! Checks if the oriented edges of the wire are
  //! correctly oriented. An internal call is made to
  //! the method Closed. If no face exists, call the
  //! method with a null face (TopoDS_face()). If
  //! <Update> is set to true, registers the
  //! status in the list.
  //! May return (and registers):
  //! BRepCheck_InvalidDegeneratedFlag,
  //! BRepCheck_BadOrientationOfSubshape,
  //! BRepCheck_NotClosed,
  //! BRepCheck_NoError
  Standard_EXPORT BRepCheck_Status Orientation(const TopoDS_Face& F, const bool Update = false);

  //! Checks if the wire intersect itself on the face
  //! <F>. <E1> and <E2> are the first intersecting
  //! edges found. <E2> may be a null edge when a
  //! self-intersecting edge is found.If <Update> is set
  //! to true, registers the status in the
  //! list.
  //! May return (and register):
  //! BRepCheck_EmptyWire,
  //! BRepCheck_SelfIntersectingWire,
  //! BRepCheck_NoCurveOnSurface,
  //! BRepCheck_NoError
  Standard_EXPORT BRepCheck_Status SelfIntersect(const TopoDS_Face& F,
                                                 TopoDS_Edge&       E1,
                                                 TopoDS_Edge&       E2,
                                                 const bool         Update = false);

  //! report SelfIntersect() check would be (is) done
  Standard_EXPORT bool GeometricControls() const;

  //! set SelfIntersect() to be checked
  Standard_EXPORT void GeometricControls(const bool B);

  //! Sets status of Wire;
  Standard_EXPORT void SetStatus(const BRepCheck_Status theStatus);

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Wire, BRepCheck_Result)

private:
  bool             myCdone;
  BRepCheck_Status myCstat;
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
       myMapVE;
  bool myGctrl;
};
