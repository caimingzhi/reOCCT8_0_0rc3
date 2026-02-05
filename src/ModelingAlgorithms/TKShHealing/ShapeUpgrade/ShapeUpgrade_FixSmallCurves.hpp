#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <ShapeUpgrade_Tool.hpp>
#include <Standard_Real.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeUpgrade_SplitCurve3d;
class ShapeUpgrade_SplitCurve2d;
class Geom_Curve;
class Geom2d_Curve;

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_FixSmallCurves : public ShapeUpgrade_Tool
{

public:
  Standard_EXPORT ShapeUpgrade_FixSmallCurves();

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge, const TopoDS_Face& theFace);

  Standard_EXPORT virtual bool Approx(occ::handle<Geom_Curve>&   Curve3d,
                                      occ::handle<Geom2d_Curve>& Curve2d,
                                      occ::handle<Geom2d_Curve>& Curve2dR,
                                      double&                    First,
                                      double&                    Last);

  //! Sets the tool for splitting 3D curves.
  Standard_EXPORT void SetSplitCurve3dTool(
    const occ::handle<ShapeUpgrade_SplitCurve3d>& splitCurve3dTool);

  //! Sets the tool for splitting pcurves.
  Standard_EXPORT void SetSplitCurve2dTool(
    const occ::handle<ShapeUpgrade_SplitCurve2d>& splitCurve2dTool);

  //! Queries the status of last call to Perform
  //! OK   :
  //! DONE1:
  //! DONE2:
  //! FAIL1:
  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_FixSmallCurves, ShapeUpgrade_Tool)

protected:
  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitCurve3d> GetSplitCurve3dTool() const;

  //! Returns the tool for splitting pcurves.
  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitCurve2d> GetSplitCurve2dTool() const;

  int                                    myStatus;
  occ::handle<ShapeUpgrade_SplitCurve3d> mySplitCurve3dTool;
  occ::handle<ShapeUpgrade_SplitCurve2d> mySplitCurve2dTool;
  TopoDS_Edge                            myEdge;
  TopoDS_Face                            myFace;
};
