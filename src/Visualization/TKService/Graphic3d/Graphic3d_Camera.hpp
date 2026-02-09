#pragma once

#include <Aspect_Eye.hpp>
#include <Aspect_FrustumLRBT.hpp>
#include <Graphic3d_CameraTile.hpp>
#include <NCollection_Mat4.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <Graphic3d_WorldViewProjState.hpp>
#include <NCollection_Lerp.hpp>
#include <NCollection_Array1.hpp>

#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>

#include <Standard_Macro.hpp>

#include <Bnd_Box.hpp>

class Graphic3d_Camera : public Standard_Transient
{
private:
  template <typename Elem_t>
  struct TransformMatrices
  {

    TransformMatrices()
        : myIsOrientationValid(false),
          myIsProjectionValid(false)
    {
    }

    void InitOrientation()
    {
      myIsOrientationValid = true;
      Orientation.InitIdentity();
    }

    void InitProjection()
    {
      myIsProjectionValid = true;
      MProjection.InitIdentity();
      LProjection.InitIdentity();
      RProjection.InitIdentity();
    }

    void ResetOrientation() { myIsOrientationValid = false; }

    void ResetProjection() { myIsProjectionValid = false; }

    bool IsOrientationValid() const { return myIsOrientationValid; }

    bool IsProjectionValid() const { return myIsProjectionValid; }

    void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
    {
      if (IsOrientationValid())
      {
        OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &Orientation)
      }
      if (IsProjectionValid())
      {
        OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &MProjection)
        OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &LProjection)
        OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &RProjection)
      }
      OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsOrientationValid)
      OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsProjectionValid)
    }

  public:
    NCollection_Mat4<Elem_t> Orientation;
    NCollection_Mat4<Elem_t> MProjection;
    NCollection_Mat4<Elem_t> LProjection;
    NCollection_Mat4<Elem_t> RProjection;

  private:
    bool myIsOrientationValid;
    bool myIsProjectionValid;
  };

public:
  enum Projection
  {
    Projection_Orthographic,
    Projection_Perspective,
    Projection_Stereo,
    Projection_MonoLeftEye,
    Projection_MonoRightEye
  };

  enum FocusType
  {
    FocusType_Absolute,
    FocusType_Relative
  };

  enum IODType
  {
    IODType_Absolute,
    IODType_Relative
  };

public:
  Standard_EXPORT static void Interpolate(const occ::handle<Graphic3d_Camera>& theStart,
                                          const occ::handle<Graphic3d_Camera>& theEnd,
                                          const double                         theT,
                                          occ::handle<Graphic3d_Camera>&       theCamera);

public:
  Standard_EXPORT Graphic3d_Camera();

  Standard_EXPORT Graphic3d_Camera(const occ::handle<Graphic3d_Camera>& theOther);

  Standard_EXPORT void CopyMappingData(const occ::handle<Graphic3d_Camera>& theOtherCamera);

  Standard_EXPORT void CopyOrientationData(const occ::handle<Graphic3d_Camera>& theOtherCamera);

  Standard_EXPORT void Copy(const occ::handle<Graphic3d_Camera>& theOther);

public:
  const gp_Dir& Direction() const { return myDirection; }

  Standard_EXPORT void SetDirectionFromEye(const gp_Dir& theDir);

  Standard_EXPORT void SetDirection(const gp_Dir& theDir);

  const gp_Dir& Up() const { return myUp; }

  Standard_EXPORT void SetUp(const gp_Dir& theUp);

  Standard_EXPORT void OrthogonalizeUp();

  Standard_EXPORT gp_Dir OrthogonalizedUp() const;

  gp_Dir SideRight() const { return -(gp_Vec(Direction()) ^ gp_Vec(OrthogonalizedUp())); }

  const gp_Pnt& Eye() const { return myEye; }

  Standard_EXPORT void MoveEyeTo(const gp_Pnt& theEye);

  Standard_EXPORT void SetEyeAndCenter(const gp_Pnt& theEye, const gp_Pnt& theCenter);

  Standard_EXPORT void SetEye(const gp_Pnt& theEye);

  gp_Pnt Center() const { return myEye.XYZ() + myDirection.XYZ() * myDistance; }

  Standard_EXPORT void SetCenter(const gp_Pnt& theCenter);

  double Distance() const { return myDistance; }

  Standard_EXPORT void SetDistance(const double theDistance);

  Standard_EXPORT double Scale() const;

  Standard_EXPORT void SetScale(const double theScale);

  const gp_XYZ& AxialScale() const { return myAxialScale; }

  Standard_EXPORT void SetAxialScale(const gp_XYZ& theAxialScale);

  Standard_EXPORT void SetProjectionType(const Projection theProjection);

  Projection ProjectionType() const { return myProjType; }

  bool IsOrthographic() const { return (myProjType == Projection_Orthographic); }

  bool IsStereo() const { return (myProjType == Projection_Stereo); }

  Standard_EXPORT void SetFOVy(const double theFOVy);

  double FOVy() const { return myFOVy; }

  double FOVx() const { return myFOVx; }

  double FOV2d() const { return myFOV2d; }

  Standard_EXPORT void SetFOV2d(double theFOV);

  Standard_EXPORT bool FitMinMax(const Bnd_Box& theBox,
                                 const double   theResolution,
                                 const bool     theToEnlargeIfLine);

  Standard_EXPORT bool ZFitAll(const double   theScaleFactor,
                               const Bnd_Box& theMinMax,
                               const Bnd_Box& theGraphicBB,
                               double&        theZNear,
                               double&        theZFar) const;

  void ZFitAll(const double theScaleFactor, const Bnd_Box& theMinMax, const Bnd_Box& theGraphicBB)
  {
    double aZNear = 0.0, aZFar = 1.0;
    ZFitAll(theScaleFactor, theMinMax, theGraphicBB, aZNear, aZFar);
    SetZRange(aZNear, aZFar);
  }

  Standard_EXPORT void SetZRange(const double theZNear, const double theZFar);

  double ZNear() const { return myZNear; }

  double ZFar() const { return myZFar; }

  bool IsZeroToOneDepth() const { return myIsZeroToOneDepth; }

  void SetZeroToOneDepth(bool theIsZeroToOne)
  {
    if (myIsZeroToOneDepth != theIsZeroToOne)
    {
      myIsZeroToOneDepth = theIsZeroToOne;
      InvalidateProjection();
    }
  }

  Standard_EXPORT void SetAspect(const double theAspect);

  double Aspect() const { return myAspect; }

  Standard_EXPORT void SetZFocus(const FocusType theType, const double theZFocus);

  double ZFocus() const { return myZFocus; }

  FocusType ZFocusType() const { return myZFocusType; }

  Standard_EXPORT void SetIOD(const IODType theType, const double theIOD);

  double IOD() const { return myIOD; }

  IODType GetIODType() const { return myIODType; }

  const Graphic3d_CameraTile& Tile() const { return myTile; }

  Standard_EXPORT void SetTile(const Graphic3d_CameraTile& theTile);

  Standard_EXPORT void SetIdentityOrientation();

public:
  Standard_EXPORT void Transform(const gp_Trsf& theTrsf);

  gp_XYZ ViewDimensions() const { return ViewDimensions(Distance()); }

  Standard_EXPORT gp_XYZ ViewDimensions(const double theZValue) const;

  double NDC2dOffsetX() const { return myFOV2d >= myFOVx ? 0.5 : 0.5 * myFOV2d / myFOVx; }

  double NDC2dOffsetY() const { return myFOV2d >= myFOVy ? 0.5 : 0.5 * myFOV2d / myFOVy; }

  Standard_EXPORT void Frustum(gp_Pln& theLeft,
                               gp_Pln& theRight,
                               gp_Pln& theBottom,
                               gp_Pln& theTop,
                               gp_Pln& theNear,
                               gp_Pln& theFar) const;

public:
  Standard_EXPORT gp_Pnt Project(const gp_Pnt& thePnt) const;

  Standard_EXPORT gp_Pnt UnProject(const gp_Pnt& thePnt) const;

  Standard_EXPORT gp_Pnt ConvertView2Proj(const gp_Pnt& thePnt) const;

  Standard_EXPORT gp_Pnt ConvertProj2View(const gp_Pnt& thePnt) const;

  Standard_EXPORT gp_Pnt ConvertWorld2View(const gp_Pnt& thePnt) const;

  Standard_EXPORT gp_Pnt ConvertView2World(const gp_Pnt& thePnt) const;

public:
  const Graphic3d_WorldViewProjState& WorldViewProjState() const { return myWorldViewProjState; }

  size_t ProjectionState() const { return myWorldViewProjState.ProjectionState(); }

  size_t WorldViewState() const { return myWorldViewProjState.WorldViewState(); }

public:
  Standard_EXPORT const NCollection_Mat4<double>& OrientationMatrix() const;

  Standard_EXPORT const NCollection_Mat4<float>& OrientationMatrixF() const;

  Standard_EXPORT const NCollection_Mat4<double>& ProjectionMatrix() const;

  Standard_EXPORT const NCollection_Mat4<float>& ProjectionMatrixF() const;

  Standard_EXPORT const NCollection_Mat4<double>& ProjectionStereoLeft() const;

  Standard_EXPORT const NCollection_Mat4<float>& ProjectionStereoLeftF() const;

  Standard_EXPORT const NCollection_Mat4<double>& ProjectionStereoRight() const;

  Standard_EXPORT const NCollection_Mat4<float>& ProjectionStereoRightF() const;

  Standard_EXPORT void InvalidateProjection();

  Standard_EXPORT void InvalidateOrientation();

public:
  Standard_EXPORT void StereoProjection(NCollection_Mat4<double>& theProjL,
                                        NCollection_Mat4<double>& theHeadToEyeL,
                                        NCollection_Mat4<double>& theProjR,
                                        NCollection_Mat4<double>& theHeadToEyeR) const;

  Standard_EXPORT void StereoProjectionF(NCollection_Mat4<float>& theProjL,
                                         NCollection_Mat4<float>& theHeadToEyeL,
                                         NCollection_Mat4<float>& theProjR,
                                         NCollection_Mat4<float>& theHeadToEyeR) const;

  Standard_EXPORT void ResetCustomProjection();

  bool IsCustomStereoFrustum() const { return myIsCustomFrustomLR; }

  Standard_EXPORT void SetCustomStereoFrustums(const Aspect_FrustumLRBT<double>& theFrustumL,
                                               const Aspect_FrustumLRBT<double>& theFrustumR);

  bool IsCustomStereoProjection() const { return myIsCustomProjMatLR; }

  Standard_EXPORT void SetCustomStereoProjection(const NCollection_Mat4<double>& theProjL,
                                                 const NCollection_Mat4<double>& theHeadToEyeL,
                                                 const NCollection_Mat4<double>& theProjR,
                                                 const NCollection_Mat4<double>& theHeadToEyeR);

  bool IsCustomMonoProjection() const { return myIsCustomProjMatM; }

  Standard_EXPORT void SetCustomMonoProjection(const NCollection_Mat4<double>& theProj);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  template <typename Elem_t>
  Standard_EXPORT void stereoProjection(NCollection_Mat4<Elem_t>& theProjL,
                                        NCollection_Mat4<Elem_t>& theHeadToEyeL,
                                        NCollection_Mat4<Elem_t>& theProjR,
                                        NCollection_Mat4<Elem_t>& theHeadToEyeR) const;

  template <typename Elem_t>
  Standard_EXPORT void computeProjection(NCollection_Mat4<Elem_t>& theProjM,
                                         NCollection_Mat4<Elem_t>& theProjL,
                                         NCollection_Mat4<Elem_t>& theProjR,
                                         bool                      theToAddHeadToEye) const;

  template <typename Elem_t>
  TransformMatrices<Elem_t>& UpdateProjection(TransformMatrices<Elem_t>& theMatrices) const
  {
    if (!theMatrices.IsProjectionValid())
    {
      theMatrices.InitProjection();
      computeProjection(theMatrices.MProjection,
                        theMatrices.LProjection,
                        theMatrices.RProjection,
                        true);
    }
    return theMatrices;
  }

  template <typename Elem_t>
  Standard_EXPORT TransformMatrices<Elem_t>& UpdateOrientation(
    TransformMatrices<Elem_t>& theMatrices) const;

private:
  template <typename Elem_t>
  void orthoProj(NCollection_Mat4<Elem_t>&         theOutMx,
                 const Aspect_FrustumLRBT<Elem_t>& theLRBT,
                 const Elem_t                      theNear,
                 const Elem_t                      theFar) const;

  template <typename Elem_t>
  void perspectiveProj(NCollection_Mat4<Elem_t>&         theOutMx,
                       const Aspect_FrustumLRBT<Elem_t>& theLRBT,
                       const Elem_t                      theNear,
                       const Elem_t                      theFar) const;

  template <typename Elem_t>
  void stereoEyeProj(NCollection_Mat4<Elem_t>&         theOutMx,
                     const Aspect_FrustumLRBT<Elem_t>& theLRBT,
                     const Elem_t                      theNear,
                     const Elem_t                      theFar,
                     const Elem_t                      theIOD,
                     const Elem_t                      theZFocus,
                     const Aspect_Eye                  theEyeIndex) const;

  template <typename Elem_t>
  static void LookOrientation(const NCollection_Vec3<Elem_t>& theEye,
                              const NCollection_Vec3<Elem_t>& theFwdDir,
                              const NCollection_Vec3<Elem_t>& theUpDir,
                              const NCollection_Vec3<Elem_t>& theAxialScale,
                              NCollection_Mat4<Elem_t>&       theOutMx);

public:
  enum
  {
    FrustumVert_LeftBottomNear,
    FrustumVert_LeftBottomFar,
    FrustumVert_LeftTopNear,
    FrustumVert_LeftTopFar,
    FrustumVert_RightBottomNear,
    FrustumVert_RightBottomFar,
    FrustumVert_RightTopNear,
    FrustumVert_RightTopFar,
    FrustumVerticesNB
  };

  Standard_EXPORT void FrustumPoints(
    NCollection_Array1<NCollection_Vec3<double>>& thePoints,
    const NCollection_Mat4<double>&               theModelWorld = NCollection_Mat4<double>()) const;

private:
  gp_Dir myUp;
  gp_Dir myDirection;
  gp_Pnt myEye;
  double myDistance;

  gp_XYZ myAxialScale;

  Projection myProjType;
  double     myFOVy;
  double     myFOVx;
  double     myFOV2d;
  double     myFOVyTan;
  double     myZNear;
  double     myZFar;
  double     myAspect;
  bool       myIsZeroToOneDepth;

  double    myScale;
  double    myZFocus;
  FocusType myZFocusType;

  double  myIOD;
  IODType myIODType;

  Graphic3d_CameraTile myTile;

  NCollection_Mat4<double>   myCustomProjMatM;
  NCollection_Mat4<double>   myCustomProjMatL;
  NCollection_Mat4<double>   myCustomProjMatR;
  NCollection_Mat4<double>   myCustomHeadToEyeMatL;
  NCollection_Mat4<double>   myCustomHeadToEyeMatR;
  Aspect_FrustumLRBT<double> myCustomFrustumL;
  Aspect_FrustumLRBT<double> myCustomFrustumR;
  bool                       myIsCustomProjMatM;

  bool myIsCustomProjMatLR;

  bool myIsCustomFrustomLR;

  mutable TransformMatrices<double> myMatricesD;
  mutable TransformMatrices<float>  myMatricesF;

  mutable Graphic3d_WorldViewProjState myWorldViewProjState;

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Camera, Standard_Transient)
};

template <>
inline void NCollection_Lerp<occ::handle<Graphic3d_Camera>>::Interpolate(
  const double                   theT,
  occ::handle<Graphic3d_Camera>& theResult) const
{
  Graphic3d_Camera::Interpolate(myStart, myEnd, theT, theResult);
}
