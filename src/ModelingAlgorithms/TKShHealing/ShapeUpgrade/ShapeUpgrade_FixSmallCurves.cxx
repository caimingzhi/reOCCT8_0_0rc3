#include <ShapeUpgrade_FixSmallCurves.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_FixSmallCurves, ShapeUpgrade_Tool)

// #include <NCollection_HArray1<occ::handle<Geom_Curve>>.hxx>
// #include <NCollection_HSequence<double>.hxx>
#//include <NCollection_HArray1<occ::handle<Geom2d_Curve>>.hxx>
// #include <NCollection_HSequence<double>.hxx>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade_SplitCurve3d.hpp>
#include <ShapeUpgrade_SplitCurve2d.hpp>

//=================================================================================================

ShapeUpgrade_FixSmallCurves::ShapeUpgrade_FixSmallCurves()
{
  myStatus = ShapeExtend::EncodeStatus(ShapeExtend_OK);
}

//=================================================================================================

void ShapeUpgrade_FixSmallCurves::Init(const TopoDS_Edge& theEdge, const TopoDS_Face& theFace)
{
  myEdge = theEdge;
  myFace = theFace;
}

//=================================================================================================

bool ShapeUpgrade_FixSmallCurves::Approx(occ::handle<Geom_Curve>& /*Curve3d*/,
                                         occ::handle<Geom2d_Curve>& /*Curve2d*/,
                                         occ::handle<Geom2d_Curve>& /*Curve2dR*/,
                                         double& /*First*/,
                                         double& /*Last*/)
{
  return false;
}

//=================================================================================================

void ShapeUpgrade_FixSmallCurves::SetSplitCurve3dTool(
  const occ::handle<ShapeUpgrade_SplitCurve3d>& splitCurve3dTool)
{
  mySplitCurve3dTool = splitCurve3dTool;
}

//=================================================================================================

void ShapeUpgrade_FixSmallCurves::SetSplitCurve2dTool(
  const occ::handle<ShapeUpgrade_SplitCurve2d>& splitCurve2dTool)
{
  mySplitCurve2dTool = splitCurve2dTool;
}

//=================================================================================================

occ::handle<ShapeUpgrade_SplitCurve3d> ShapeUpgrade_FixSmallCurves::GetSplitCurve3dTool() const
{
  return mySplitCurve3dTool;
}

//=================================================================================================

occ::handle<ShapeUpgrade_SplitCurve2d> ShapeUpgrade_FixSmallCurves::GetSplitCurve2dTool() const
{
  return mySplitCurve2dTool;
}

//=================================================================================================

bool ShapeUpgrade_FixSmallCurves::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}
