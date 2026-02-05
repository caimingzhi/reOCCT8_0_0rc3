#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepAdaptor_Curve2d, Geom2dAdaptor_Curve)

//=================================================================================================

BRepAdaptor_Curve2d::BRepAdaptor_Curve2d() = default;

//=================================================================================================

BRepAdaptor_Curve2d::BRepAdaptor_Curve2d(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  Initialize(E, F);
}

//=================================================================================================

occ::handle<Adaptor2d_Curve2d> BRepAdaptor_Curve2d::ShallowCopy() const
{
  occ::handle<BRepAdaptor_Curve2d> aCopy = new BRepAdaptor_Curve2d();

  aCopy->myCurve     = myCurve;
  aCopy->myTypeCurve = myTypeCurve;
  aCopy->myFirst     = myFirst;
  aCopy->myLast      = myLast;
  aCopy->myCurveData = myCurveData; // Copy variant (cache will be rebuilt on demand)
  aCopy->myEdge      = myEdge;
  aCopy->myFace      = myFace;

  return aCopy;
}

//=================================================================================================

void BRepAdaptor_Curve2d::Initialize(const TopoDS_Edge& E, const TopoDS_Face& F)
{
  myEdge = E;
  myFace = F;
  double                          aFirs, aLast;
  const occ::handle<Geom2d_Curve> aPCurve = BRep_Tool::CurveOnSurface(E, F, aFirs, aLast);
  if (!aPCurve.IsNull())
  {
    Geom2dAdaptor_Curve::Load(aPCurve, aFirs, aLast);
  }
}

//=================================================================================================

const TopoDS_Edge& BRepAdaptor_Curve2d::Edge() const
{
  return myEdge;
}

//=================================================================================================

const TopoDS_Face& BRepAdaptor_Curve2d::Face() const
{
  return myFace;
}
