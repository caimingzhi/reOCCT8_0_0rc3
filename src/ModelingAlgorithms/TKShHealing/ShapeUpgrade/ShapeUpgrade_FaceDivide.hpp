#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_Tool.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeUpgrade_SplitSurface;
class ShapeUpgrade_WireDivide;

#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_FaceDivide : public ShapeUpgrade_Tool
{

public:
  Standard_EXPORT ShapeUpgrade_FaceDivide();

  Standard_EXPORT ShapeUpgrade_FaceDivide(const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Face& F);

  Standard_EXPORT void SetSurfaceSegmentMode(const bool Segment);

  Standard_EXPORT virtual bool Perform(const double theArea = 0.);

  Standard_EXPORT virtual bool SplitSurface(const double theArea = 0.);

  Standard_EXPORT virtual bool SplitCurves();

  Standard_EXPORT TopoDS_Shape Result() const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT void SetSplitSurfaceTool(
    const occ::handle<ShapeUpgrade_SplitSurface>& splitSurfaceTool);

  Standard_EXPORT void SetWireDivideTool(
    const occ::handle<ShapeUpgrade_WireDivide>& wireDivideTool);

  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitSurface> GetSplitSurfaceTool() const;

  Standard_EXPORT virtual occ::handle<ShapeUpgrade_WireDivide> GetWireDivideTool() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_FaceDivide, ShapeUpgrade_Tool)

protected:
  TopoDS_Face  myFace;
  TopoDS_Shape myResult;
  bool         mySegmentMode;
  int          myStatus;

private:
  occ::handle<ShapeUpgrade_SplitSurface> mySplitSurfaceTool;
  occ::handle<ShapeUpgrade_WireDivide>   myWireDivideTool;
};
