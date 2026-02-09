#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <Standard_Integer.hpp>
#include <ShapeUpgrade_Tool.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeUpgrade_SplitCurve3d;
class ShapeUpgrade_SplitCurve2d;
class ShapeUpgrade_EdgeDivide;
class ShapeAnalysis_TransferParameters;
class ShapeUpgrade_FixSmallCurves;
class Geom_Surface;
class TopoDS_Edge;
class TopLoc_Location;

#ifdef Status
  #undef Status
#endif

class ShapeUpgrade_WireDivide : public ShapeUpgrade_Tool
{

public:
  Standard_EXPORT ShapeUpgrade_WireDivide();

  Standard_EXPORT void Init(const TopoDS_Wire& W, const TopoDS_Face& F);

  Standard_EXPORT void Init(const TopoDS_Wire& W, const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Load(const TopoDS_Wire& W);

  Standard_EXPORT void Load(const TopoDS_Edge& E);

  Standard_EXPORT void SetFace(const TopoDS_Face& F);

  Standard_EXPORT void SetSurface(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void SetSurface(const occ::handle<Geom_Surface>& S, const TopLoc_Location& L);

  Standard_EXPORT virtual void Perform();

  Standard_EXPORT const TopoDS_Wire& Wire() const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT void SetSplitCurve3dTool(
    const occ::handle<ShapeUpgrade_SplitCurve3d>& splitCurve3dTool);

  Standard_EXPORT void SetSplitCurve2dTool(
    const occ::handle<ShapeUpgrade_SplitCurve2d>& splitCurve2dTool);

  Standard_EXPORT void SetTransferParamTool(
    const occ::handle<ShapeAnalysis_TransferParameters>& TransferParam);

  Standard_EXPORT void SetEdgeDivideTool(
    const occ::handle<ShapeUpgrade_EdgeDivide>& edgeDivideTool);

  Standard_EXPORT virtual occ::handle<ShapeUpgrade_EdgeDivide> GetEdgeDivideTool() const;

  Standard_EXPORT virtual occ::handle<ShapeAnalysis_TransferParameters> GetTransferParamTool();

  Standard_EXPORT void SetEdgeMode(const int EdgeMode);

  Standard_EXPORT void SetFixSmallCurveTool(
    const occ::handle<ShapeUpgrade_FixSmallCurves>& FixSmallCurvesTool);

  Standard_EXPORT occ::handle<ShapeUpgrade_FixSmallCurves> GetFixSmallCurveTool() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_WireDivide, ShapeUpgrade_Tool)

protected:
  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitCurve3d> GetSplitCurve3dTool() const;

  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitCurve2d> GetSplitCurve2dTool() const;

  TopoDS_Face myFace;
  TopoDS_Wire myWire;
  int         myStatus;
  int         myEdgeMode;

private:
  occ::handle<ShapeUpgrade_SplitCurve3d>        mySplitCurve3dTool;
  occ::handle<ShapeUpgrade_SplitCurve2d>        mySplitCurve2dTool;
  occ::handle<ShapeUpgrade_EdgeDivide>          myEdgeDivide;
  occ::handle<ShapeAnalysis_TransferParameters> myTransferParamTool;
  occ::handle<ShapeUpgrade_FixSmallCurves>      myFixSmallCurveTool;
};
