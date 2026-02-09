#pragma once

#include <Graphic3d_Camera.hpp>
#include <NCollection_Vec4.hpp>
#include <Standard_TypeDef.hpp>
#include <Graphic3d_WorldViewProjState.hpp>

class Graphic3d_CullingTool
{
public:
  struct CullingContext
  {
    double DistCull;
    double SizeCull2;

    CullingContext()
        : DistCull(-1.0),
          SizeCull2(-1.0)
    {
    }
  };

  struct Plane
  {

    Plane()
        : Origin(0.0, 0.0, 0.0),
          Normal(0.0, 0.0, 1.0)
    {
    }

    Plane(const NCollection_Vec3<double>& theOrigin, const NCollection_Vec3<double>& theNormal)
        : Origin(theOrigin),
          Normal(theNormal)
    {
    }

    NCollection_Vec3<double> Origin;
    NCollection_Vec3<double> Normal;
  };

public:
  Standard_EXPORT Graphic3d_CullingTool();

  Standard_EXPORT void SetViewVolume(
    const occ::handle<Graphic3d_Camera>& theCamera,
    const NCollection_Mat4<double>&      theModelWorld = NCollection_Mat4<double>());

  Standard_EXPORT void SetViewportSize(int    theViewportWidth,
                                       int    theViewportHeight,
                                       double theResolutionRatio);

  Standard_EXPORT void SetCullingDistance(CullingContext& theCtx, double theDistance) const;

  Standard_EXPORT void SetCullingSize(CullingContext& theCtx, double theSize) const;

  Standard_EXPORT void CacheClipPtsProjections();

  bool IsCulled(const CullingContext&           theCtx,
                const NCollection_Vec3<double>& theMinPnt,
                const NCollection_Vec3<double>& theMaxPnt,
                bool*                           theIsInside = nullptr) const
  {
    return IsOutFrustum(theMinPnt, theMaxPnt, theIsInside)
           || IsTooDistant(theCtx, theMinPnt, theMaxPnt, theIsInside)
           || IsTooSmall(theCtx, theMinPnt, theMaxPnt);
  }

  const occ::handle<Graphic3d_Camera>& Camera() const { return myCamera; }

  const NCollection_Mat4<double>& ProjectionMatrix() const { return myProjectionMat; }

  const NCollection_Mat4<double>& WorldViewMatrix() const { return myWorldViewMat; }

  int ViewportWidth() const { return myViewportWidth; }

  int ViewportHeight() const { return myViewportHeight; }

  const Graphic3d_WorldViewProjState& WorldViewProjState() const { return myWorldViewProjState; }

  const NCollection_Vec3<double>& CameraEye() const { return myCamEye; }

  const NCollection_Vec3<double>& CameraDirection() const { return myCamDir; }

public:
  Standard_EXPORT double SignedPlanePointDistance(const NCollection_Vec4<double>& theNormal,
                                                  const NCollection_Vec4<double>& thePnt);

  bool IsOutFrustum(const NCollection_Vec3<double>& theMinPnt,
                    const NCollection_Vec3<double>& theMaxPnt,
                    bool*                           theIsInside = nullptr) const
  {

    if (theMinPnt[0] > myMaxOrthoProjectionPts[0] || theMaxPnt[0] < myMinOrthoProjectionPts[0]
        || theMinPnt[1] > myMaxOrthoProjectionPts[1] || theMaxPnt[1] < myMinOrthoProjectionPts[1]
        || theMinPnt[2] > myMaxOrthoProjectionPts[2] || theMaxPnt[2] < myMinOrthoProjectionPts[2])
    {
      return true;
    }
    if (theIsInside != nullptr && *theIsInside)
    {
      *theIsInside =
        theMinPnt[0] >= myMinOrthoProjectionPts[0] && theMaxPnt[0] <= myMaxOrthoProjectionPts[0]
        && theMinPnt[1] >= myMinOrthoProjectionPts[1] && theMaxPnt[1] <= myMaxOrthoProjectionPts[1]
        && theMinPnt[1] >= myMinOrthoProjectionPts[2] && theMaxPnt[1] <= myMaxOrthoProjectionPts[2];
    }

    const int anIncFactor = myIsProjectionParallel ? 2 : 1;
    for (int aPlaneIter = 0; aPlaneIter < PlanesNB - 1; aPlaneIter += anIncFactor)
    {

      const NCollection_Vec3<double>& anAxis = myClipPlanes[aPlaneIter].Normal;
      const NCollection_Vec3<double>  aPVertex(anAxis.x() > 0.0 ? theMaxPnt.x() : theMinPnt.x(),
                                              anAxis.y() > 0.0 ? theMaxPnt.y() : theMinPnt.y(),
                                              anAxis.z() > 0.0 ? theMaxPnt.z() : theMinPnt.z());
      const double aPnt0 = aPVertex.Dot(anAxis);
      if (theIsInside == nullptr && aPnt0 >= myMinClipProjectionPts[aPlaneIter]
          && aPnt0 <= myMaxClipProjectionPts[aPlaneIter])
      {
        continue;
      }

      const NCollection_Vec3<double> aNVertex(anAxis.x() > 0.0 ? theMinPnt.x() : theMaxPnt.x(),
                                              anAxis.y() > 0.0 ? theMinPnt.y() : theMaxPnt.y(),
                                              anAxis.z() > 0.0 ? theMinPnt.z() : theMaxPnt.z());
      const double aPnt1 = aNVertex.Dot(anAxis);

      const double aBoxProjMin = aPnt0 < aPnt1 ? aPnt0 : aPnt1;
      const double aBoxProjMax = aPnt0 > aPnt1 ? aPnt0 : aPnt1;
      if (aBoxProjMin > myMaxClipProjectionPts[aPlaneIter]
          || aBoxProjMax < myMinClipProjectionPts[aPlaneIter])
      {
        return true;
      }

      if (theIsInside != nullptr && *theIsInside)
      {
        *theIsInside = aBoxProjMin >= myMinClipProjectionPts[aPlaneIter]
                       && aBoxProjMax <= myMaxClipProjectionPts[aPlaneIter];
      }
    }
    return false;
  }

  bool IsTooDistant(const CullingContext&           theCtx,
                    const NCollection_Vec3<double>& theMinPnt,
                    const NCollection_Vec3<double>& theMaxPnt,
                    bool*                           theIsInside = nullptr) const
  {
    if (theCtx.DistCull <= 0.0)
    {
      return false;
    }

    const NCollection_Vec3<double> aSphereCenter = (theMinPnt + theMaxPnt) * 0.5;
    const double                   aSphereRadius = (theMaxPnt - theMinPnt).maxComp() * 0.5;
    const double                   aDistToCenter = (aSphereCenter - myCamEye).Modulus();
    if ((aDistToCenter - aSphereRadius) > theCtx.DistCull)
    {

      return true;
    }
    if (theIsInside != nullptr && *theIsInside)
    {

      *theIsInside = (aDistToCenter + aSphereRadius) <= theCtx.DistCull;
    }
    return false;
  }

  bool IsTooSmall(const CullingContext&           theCtx,
                  const NCollection_Vec3<double>& theMinPnt,
                  const NCollection_Vec3<double>& theMaxPnt) const
  {
    if (theCtx.SizeCull2 <= 0.0)
    {
      return false;
    }

    const double aBoxDiag2 = (theMaxPnt - theMinPnt).SquareModulus();
    if (myIsProjectionParallel)
    {
      return aBoxDiag2 < theCtx.SizeCull2;
    }

    const NCollection_Vec3<double> aBndCenter = (theMinPnt + theMaxPnt) * 0.5;
    const double                   aBndDist   = (aBndCenter - myCamEye).Dot(myCamDir);
    return aBoxDiag2 < theCtx.SizeCull2 * aBndDist * aBndDist;
  }

protected:
  enum
  {
    Plane_Left,
    Plane_Right,
    Plane_Bottom,
    Plane_Top,
    Plane_Near,
    Plane_Far,
    PlanesNB
  };

protected:
  Plane                                        myClipPlanes[PlanesNB];
  NCollection_Array1<NCollection_Vec3<double>> myClipVerts;

  occ::handle<Graphic3d_Camera> myCamera;

  double myMaxClipProjectionPts[PlanesNB];
  double myMinClipProjectionPts[PlanesNB];

  double myMaxOrthoProjectionPts[3];
  double myMinOrthoProjectionPts[3];

  bool myIsProjectionParallel;

  NCollection_Mat4<double> myProjectionMat;
  NCollection_Mat4<double> myWorldViewMat;

  int myViewportWidth;
  int myViewportHeight;

  Graphic3d_WorldViewProjState myWorldViewProjState;

  NCollection_Vec3<double> myCamEye;
  NCollection_Vec3<double> myCamDir;
  double                   myCamScale;
  double                   myPixelSize;
};
