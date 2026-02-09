#include <SelectMgr_TriangularFrustum.hpp>

#include <SelectMgr_FrustumBuilder.hpp>
#include <SelectMgr_ViewClipRange.hpp>

IMPLEMENT_STANDARD_RTTIEXT(SelectMgr_TriangularFrustum, Standard_Transient)

namespace
{
  void computeFrustumNormals(const gp_Vec* theEdges, gp_Vec* theNormals)
  {

    theNormals[0] = theEdges[0].Crossed(theEdges[3]);

    theNormals[1] = theEdges[1].Crossed(theEdges[4]);

    theNormals[2] = theEdges[0].Crossed(theEdges[5]);

    theNormals[3] = theEdges[3].Crossed(theEdges[4]);

    theNormals[4] = -theNormals[3];
  }
} // namespace

SelectMgr_TriangularFrustum::SelectMgr_TriangularFrustum() = default;

SelectMgr_TriangularFrustum::~SelectMgr_TriangularFrustum()
{
  Clear();
}

void SelectMgr_TriangularFrustum::cacheVertexProjections(
  SelectMgr_TriangularFrustum* theFrustum) const
{
  for (int aPlaneIdx = 0; aPlaneIdx < 5; ++aPlaneIdx)
  {
    double        aMax   = -DBL_MAX;
    double        aMin   = DBL_MAX;
    const gp_XYZ& aPlane = theFrustum->myPlanes[aPlaneIdx].XYZ();
    for (int aVertIdx = 0; aVertIdx < 6; ++aVertIdx)
    {
      double aProjection = aPlane.Dot(theFrustum->myVertices[aVertIdx].XYZ());
      aMax               = std::max(aMax, aProjection);
      aMin               = std::min(aMin, aProjection);
    }
    theFrustum->myMaxVertsProjections[aPlaneIdx] = aMax;
    theFrustum->myMinVertsProjections[aPlaneIdx] = aMin;
  }

  for (int aDim = 0; aDim < 3; ++aDim)
  {
    double aMax = -DBL_MAX;
    double aMin = DBL_MAX;
    for (int aVertIdx = 0; aVertIdx < 6; ++aVertIdx)
    {
      double aProjection = theFrustum->myVertices[aVertIdx].XYZ().GetData()[aDim];
      aMax               = std::max(aMax, aProjection);
      aMin               = std::min(aMin, aProjection);
    }
    theFrustum->myMaxOrthoVertsProjections[aDim] = aMax;
    theFrustum->myMinOrthoVertsProjections[aDim] = aMin;
  }
}

void SelectMgr_TriangularFrustum::Init(const gp_Pnt2d& theP1,
                                       const gp_Pnt2d& theP2,
                                       const gp_Pnt2d& theP3)
{
  mySelTriangle.Points[0] = theP1;
  mySelTriangle.Points[1] = theP2;
  mySelTriangle.Points[2] = theP3;
}

void SelectMgr_TriangularFrustum::Build()
{

  myVertices[0] =
    myBuilder->ProjectPntOnViewPlane(mySelTriangle.Points[0].X(), mySelTriangle.Points[0].Y(), 0.0);

  myVertices[1] =
    myBuilder->ProjectPntOnViewPlane(mySelTriangle.Points[1].X(), mySelTriangle.Points[1].Y(), 0.0);

  myVertices[2] =
    myBuilder->ProjectPntOnViewPlane(mySelTriangle.Points[2].X(), mySelTriangle.Points[2].Y(), 0.0);

  myVertices[3] =
    myBuilder->ProjectPntOnViewPlane(mySelTriangle.Points[0].X(), mySelTriangle.Points[0].Y(), 1.0);

  myVertices[4] =
    myBuilder->ProjectPntOnViewPlane(mySelTriangle.Points[1].X(), mySelTriangle.Points[1].Y(), 1.0);

  myVertices[5] =
    myBuilder->ProjectPntOnViewPlane(mySelTriangle.Points[2].X(), mySelTriangle.Points[2].Y(), 1.0);

  myEdgeDirs[0] = myVertices[0].XYZ() - myVertices[3].XYZ();

  myEdgeDirs[1] = myVertices[1].XYZ() - myVertices[4].XYZ();

  myEdgeDirs[2] = myVertices[2].XYZ() - myVertices[5].XYZ();

  myEdgeDirs[3] = myVertices[1].XYZ() - myVertices[0].XYZ();

  myEdgeDirs[4] = myVertices[2].XYZ() - myVertices[1].XYZ();

  myEdgeDirs[5] = myVertices[2].XYZ() - myVertices[0].XYZ();

  computeFrustumNormals(myEdgeDirs, myPlanes);

  cacheVertexProjections(this);
}

occ::handle<SelectMgr_BaseIntersector> SelectMgr_TriangularFrustum::ScaleAndTransform(
  const int,
  const gp_GTrsf& theTrsf,
  const occ::handle<SelectMgr_FrustumBuilder>&) const
{
  occ::handle<SelectMgr_TriangularFrustum> aRes = new SelectMgr_TriangularFrustum();
  aRes->SetCamera(myCamera);

  for (int anIt = 0; anIt < 6; anIt++)
  {
    gp_Pnt aPoint = myVertices[anIt];
    theTrsf.Transforms(aPoint.ChangeCoord());
    aRes->myVertices[anIt] = aPoint;
  }

  aRes->myEdgeDirs[0] = aRes->myVertices[0].XYZ() - aRes->myVertices[3].XYZ();

  aRes->myEdgeDirs[1] = aRes->myVertices[1].XYZ() - aRes->myVertices[4].XYZ();

  aRes->myEdgeDirs[2] = aRes->myVertices[2].XYZ() - aRes->myVertices[5].XYZ();

  aRes->myEdgeDirs[3] = aRes->myVertices[1].XYZ() - aRes->myVertices[0].XYZ();

  aRes->myEdgeDirs[4] = aRes->myVertices[2].XYZ() - aRes->myVertices[1].XYZ();

  aRes->myEdgeDirs[5] = aRes->myVertices[2].XYZ() - aRes->myVertices[0].XYZ();

  computeFrustumNormals(aRes->myEdgeDirs, aRes->myPlanes);

  cacheVertexProjections(aRes.get());

  aRes->mySelTriangle = mySelTriangle;

  return aRes;
}

occ::handle<SelectMgr_BaseIntersector> SelectMgr_TriangularFrustum::CopyWithBuilder(
  const occ::handle<SelectMgr_FrustumBuilder>& theBuilder) const
{
  occ::handle<SelectMgr_TriangularFrustum> aRes = new SelectMgr_TriangularFrustum();
  aRes->mySelTriangle                           = mySelTriangle;
  aRes->SetBuilder(theBuilder);

  return aRes;
}

bool SelectMgr_TriangularFrustum::OverlapsBox(const NCollection_Vec3<double>& theMinPt,
                                              const NCollection_Vec3<double>& theMaxPt,
                                              const SelectMgr_ViewClipRange&,
                                              SelectBasics_PickResult&) const
{
  return hasBoxOverlap(theMinPt, theMaxPt);
}

bool SelectMgr_TriangularFrustum::OverlapsBox(const NCollection_Vec3<double>& theMinPt,
                                              const NCollection_Vec3<double>& theMaxPt,
                                              bool*) const
{
  return hasBoxOverlap(theMinPt, theMaxPt, nullptr);
}

bool SelectMgr_TriangularFrustum::OverlapsPoint(const gp_Pnt& thePnt,
                                                const SelectMgr_ViewClipRange&,
                                                SelectBasics_PickResult&) const
{
  return hasPointOverlap(thePnt);
}

bool SelectMgr_TriangularFrustum::OverlapsPolygon(const NCollection_Array1<gp_Pnt>& theArrayOfPnts,
                                                  Select3D_TypeOfSensitivity        theSensType,
                                                  const SelectMgr_ViewClipRange&,
                                                  SelectBasics_PickResult&) const
{
  if (theSensType == Select3D_TOS_BOUNDARY)
  {
    const int aLower  = theArrayOfPnts.Lower();
    const int anUpper = theArrayOfPnts.Upper();
    for (int aPtIdx = aLower; aPtIdx <= anUpper; ++aPtIdx)
    {
      const gp_Pnt& aStartPt = theArrayOfPnts.Value(aPtIdx);
      const gp_Pnt& aEndPt   = theArrayOfPnts.Value(aPtIdx == anUpper ? aLower : (aPtIdx + 1));
      if (!hasSegmentOverlap(aStartPt, aEndPt))
      {
        return false;
      }
    }
  }
  else if (theSensType == Select3D_TOS_INTERIOR)
  {
    gp_Vec aNorm(gp_XYZ(RealLast(), RealLast(), RealLast()));
    return hasPolygonOverlap(theArrayOfPnts, aNorm);
  }

  return false;
}

bool SelectMgr_TriangularFrustum::OverlapsSegment(const gp_Pnt& thePnt1,
                                                  const gp_Pnt& thePnt2,
                                                  const SelectMgr_ViewClipRange&,
                                                  SelectBasics_PickResult&) const
{
  return hasSegmentOverlap(thePnt1, thePnt2);
}

bool SelectMgr_TriangularFrustum::OverlapsTriangle(const gp_Pnt&                  thePnt1,
                                                   const gp_Pnt&                  thePnt2,
                                                   const gp_Pnt&                  thePnt3,
                                                   Select3D_TypeOfSensitivity     theSensType,
                                                   const SelectMgr_ViewClipRange& theClipRange,
                                                   SelectBasics_PickResult& thePickResult) const
{
  if (theSensType == Select3D_TOS_BOUNDARY)
  {
    const gp_Pnt                     aPntsArrayBuf[3] = {thePnt1, thePnt2, thePnt3};
    const NCollection_Array1<gp_Pnt> aPntsArray(aPntsArrayBuf[0], 1, 3);
    return OverlapsPolygon(aPntsArray, Select3D_TOS_BOUNDARY, theClipRange, thePickResult);
  }
  else if (theSensType == Select3D_TOS_INTERIOR)
  {
    gp_Vec aNorm(gp_XYZ(RealLast(), RealLast(), RealLast()));
    return hasTriangleOverlap(thePnt1, thePnt2, thePnt3, aNorm);
  }

  return true;
}

bool SelectMgr_TriangularFrustum::OverlapsSphere(const gp_Pnt& theCenter,
                                                 const double  theRadius,
                                                 bool*         theInside) const
{
  (void)theInside;
  return hasBoxOverlap(NCollection_Vec3<double>(theCenter.X() - theRadius,
                                                theCenter.Y() - theRadius,
                                                theCenter.Z() - theRadius),
                       NCollection_Vec3<double>(theCenter.X() + theRadius,
                                                theCenter.Y() + theRadius,
                                                theCenter.Z() + theRadius),
                       nullptr);
}

bool SelectMgr_TriangularFrustum::OverlapsSphere(const gp_Pnt&                  theCenter,
                                                 const double                   theRadius,
                                                 const SelectMgr_ViewClipRange& theClipRange,
                                                 SelectBasics_PickResult&       thePickResult) const
{
  (void)theClipRange;
  (void)thePickResult;
  return hasSphereOverlap(theCenter, theRadius);
}

bool SelectMgr_TriangularFrustum::OverlapsCylinder(const double                   theBottomRad,
                                                   const double                   theTopRad,
                                                   const double                   theHeight,
                                                   const gp_Trsf&                 theTrsf,
                                                   const bool                     theIsHollow,
                                                   const SelectMgr_ViewClipRange& theClipRange,
                                                   SelectBasics_PickResult& thePickResult) const
{
  (void)theClipRange;
  (void)thePickResult;
  return hasCylinderOverlap(theBottomRad, theTopRad, theHeight, theTrsf, theIsHollow);
}

bool SelectMgr_TriangularFrustum::OverlapsCylinder(const double   theBottomRad,
                                                   const double   theTopRad,
                                                   const double   theHeight,
                                                   const gp_Trsf& theTrsf,
                                                   const bool     theIsHollow,
                                                   bool*          theInside) const
{
  (void)theInside;
  return hasCylinderOverlap(theBottomRad, theTopRad, theHeight, theTrsf, theIsHollow);
}

bool SelectMgr_TriangularFrustum::OverlapsCircle(const double                   theRadius,
                                                 const gp_Trsf&                 theTrsf,
                                                 const bool                     theIsFilled,
                                                 const SelectMgr_ViewClipRange& theClipRange,
                                                 SelectBasics_PickResult&       thePickResult) const
{
  (void)theClipRange;
  (void)thePickResult;
  return hasCircleOverlap(theRadius, theTrsf, theIsFilled);
}

bool SelectMgr_TriangularFrustum::OverlapsCircle(const double   theRadius,
                                                 const gp_Trsf& theTrsf,
                                                 const bool     theIsFilled,
                                                 bool*          theInside) const
{
  (void)theInside;
  return hasCircleOverlap(theRadius, theTrsf, theIsFilled);
}

void SelectMgr_TriangularFrustum::Clear()
{
  myBuilder.Nullify();
}

void SelectMgr_TriangularFrustum::GetPlanes(
  NCollection_Vector<NCollection_Vec4<double>>& thePlaneEquations) const
{
  NCollection_Vec4<double> aPlaneEquation;
  for (int aPlaneIdx = 0; aPlaneIdx < 5; ++aPlaneIdx)
  {
    const gp_Vec& aNorm = myPlanes[aPlaneIdx];
    aPlaneEquation.x()  = aNorm.X();
    aPlaneEquation.y()  = aNorm.Y();
    aPlaneEquation.z()  = aNorm.Z();
    aPlaneEquation.w()  = -(aNorm.XYZ().Dot(myVertices[aPlaneIdx % 2 == 0 ? aPlaneIdx : 1].XYZ()));
    thePlaneEquations.Append(aPlaneEquation);
  }
}

void SelectMgr_TriangularFrustum::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, SelectMgr_TriangularFrustum)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, SelectMgr_Frustum)
}
