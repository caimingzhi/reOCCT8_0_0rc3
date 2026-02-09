#pragma once

#include <Graphic3d_ClipPlane.hpp>
#include <Graphic3d_Texture2D.hpp>
#include <Graphic3d_TypeOfShadingModel.hpp>
#include <Image_PixMap.hpp>
#include <Quantity_TypeOfColor.hpp>

#include <Graphic3d_BufferType.hpp>
#include <V3d_StereoDumpOptions.hpp>
#include <Graphic3d_ZLayerId.hpp>

struct V3d_ImageDumpOptions
{

  int                   Width;
  int                   Height;
  Graphic3d_BufferType  BufferType;
  V3d_StereoDumpOptions StereoOptions;
  int                   TileSize;
  bool                  ToAdjustAspect;
  Graphic3d_ZLayerId    TargetZLayerId;
  bool                  IsSingleLayer;
  const char*           LightName;

public:
  V3d_ImageDumpOptions()
      : Width(0),
        Height(0),
        BufferType(Graphic3d_BT_RGB),
        StereoOptions(V3d_SDO_MONO),
        TileSize(0),
        ToAdjustAspect(true),
        TargetZLayerId(Graphic3d_ZLayerId_BotOSD),
        IsSingleLayer(false),
        LightName("")
  {
  }
};

#include <V3d_Viewer.hpp>
#include <V3d_Trihedron.hpp>
#include <V3d_TypeOfAxe.hpp>
#include <V3d_TypeOfOrientation.hpp>
#include <V3d_TypeOfView.hpp>
#include <V3d_TypeOfVisualization.hpp>

class Aspect_Grid;
class Aspect_Window;
class Graphic3d_Group;
class Graphic3d_Structure;
class Graphic3d_TextureEnv;

class V3d_View : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(V3d_View, Standard_Transient)
public:
  Standard_EXPORT V3d_View(const occ::handle<V3d_Viewer>& theViewer,
                           const V3d_TypeOfView           theType = V3d_ORTHOGRAPHIC);

  Standard_EXPORT V3d_View(const occ::handle<V3d_Viewer>& theViewer,
                           const occ::handle<V3d_View>&   theView);

  Standard_EXPORT ~V3d_View() override;

  Standard_EXPORT void SetWindow(const occ::handle<Aspect_Window>& theWindow,
                                 const Aspect_RenderingContext     theContext = nullptr);

  Standard_EXPORT void SetWindow(
    const occ::handle<V3d_View>&    theParentView,
    const NCollection_Vec2<double>& theSize,
    Aspect_TypeOfTriedronPosition   theCorner  = Aspect_TOTP_LEFT_UPPER,
    const NCollection_Vec2<double>& theOffset  = NCollection_Vec2<double>(),
    const NCollection_Vec2<int>&    theMargins = NCollection_Vec2<int>());

  Standard_EXPORT void SetMagnify(const occ::handle<Aspect_Window>& theWindow,
                                  const occ::handle<V3d_View>&      thePreviousView,
                                  const int                         theX1,
                                  const int                         theY1,
                                  const int                         theX2,
                                  const int                         theY2);

  Standard_EXPORT void Remove();

  Standard_EXPORT void Update() const;

  Standard_EXPORT virtual void Redraw() const;

  Standard_EXPORT virtual void RedrawImmediate() const;

  Standard_EXPORT void Invalidate() const;

  Standard_EXPORT bool IsInvalidated() const;

  bool IsInvalidatedImmediate() const { return myIsInvalidatedImmediate; }

  void InvalidateImmediate() { myIsInvalidatedImmediate = true; }

  Standard_EXPORT void MustBeResized();

  Standard_EXPORT void DoMapping();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT void UpdateLights() const;

  Standard_EXPORT void SetAutoZFitMode(const bool theIsOn, const double theScaleFactor = 1.0);

  bool AutoZFitMode() const { return myAutoZFitIsOn; }

  double AutoZFitScaleFactor() const { return myAutoZFitScaleFactor; }

  Standard_EXPORT void AutoZFit() const;

  Standard_EXPORT void ZFitAll(const double theScaleFactor = 1.0) const;

public:
  Standard_EXPORT void SetBackgroundColor(const Quantity_TypeOfColor theType,
                                          const double               theV1,
                                          const double               theV2,
                                          const double               theV3);

  Standard_EXPORT void SetBackgroundColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetBgGradientColors(
    const Quantity_Color&           theColor1,
    const Quantity_Color&           theColor2,
    const Aspect_GradientFillMethod theFillStyle = Aspect_GradientFillMethod_Horizontal,
    const bool                      theToUpdate  = false);

  Standard_EXPORT void SetBgGradientStyle(
    const Aspect_GradientFillMethod theMethod   = Aspect_GradientFillMethod_Horizontal,
    const bool                      theToUpdate = false);

  Standard_EXPORT void SetBackgroundImage(const char*             theFileName,
                                          const Aspect_FillMethod theFillStyle = Aspect_FM_CENTERED,
                                          const bool              theToUpdate  = false);

  Standard_EXPORT void SetBackgroundImage(const occ::handle<Graphic3d_Texture2D>& theTexture,
                                          const Aspect_FillMethod theFillStyle = Aspect_FM_CENTERED,
                                          const bool              theToUpdate  = false);

  Standard_EXPORT void SetBgImageStyle(const Aspect_FillMethod theFillStyle,
                                       const bool              theToUpdate = false);

  Standard_EXPORT void SetBackgroundCubeMap(const occ::handle<Graphic3d_CubeMap>& theCubeMap,
                                            bool theToUpdatePBREnv = true,
                                            bool theToUpdate       = false);

  const Aspect_SkydomeBackground& BackgroundSkydome() const { return myView->BackgroundSkydome(); }

  Standard_EXPORT void SetBackgroundSkydome(const Aspect_SkydomeBackground& theAspect,
                                            bool theToUpdatePBREnv = true);

  Standard_EXPORT bool IsImageBasedLighting() const;

  Standard_EXPORT void SetImageBasedLighting(bool theToEnableIBL, bool theToUpdate = false);

  void GeneratePBREnvironment(bool theToUpdate = false)
  {
    SetImageBasedLighting(true, theToUpdate);
  }

  void ClearPBREnvironment(bool theToUpdate = false) { SetImageBasedLighting(true, theToUpdate); }

  Standard_EXPORT void SetTextureEnv(const occ::handle<Graphic3d_TextureEnv>& theTexture);

  Standard_EXPORT void SetAxis(const double X,
                               const double Y,
                               const double Z,
                               const double Vx,
                               const double Vy,
                               const double Vz);

public:
  Standard_EXPORT void SetVisualization(const V3d_TypeOfVisualization theType);

  Standard_EXPORT void SetLightOn(const occ::handle<V3d_Light>& theLight);

  Standard_EXPORT void SetLightOn();

  Standard_EXPORT void SetLightOff(const occ::handle<V3d_Light>& theLight);

  Standard_EXPORT void SetLightOff();

  Standard_EXPORT bool IsActiveLight(const occ::handle<V3d_Light>& theLight) const;

  Standard_EXPORT bool SetImmediateUpdate(const bool theImmediateUpdate);

  const occ::handle<V3d_Trihedron>& Trihedron(bool theToCreate = true)
  {
    if (myTrihedron.IsNull() && theToCreate)
    {
      myTrihedron = new V3d_Trihedron();
    }
    return myTrihedron;
  }

  Standard_EXPORT void ZBufferTriedronSetup(const Quantity_Color& theXColor    = Quantity_NOC_RED,
                                            const Quantity_Color& theYColor    = Quantity_NOC_GREEN,
                                            const Quantity_Color& theZColor    = Quantity_NOC_BLUE1,
                                            const double          theSizeRatio = 0.8,
                                            const double          theAxisDiametr = 0.05,
                                            const int             theNbFacettes  = 12);

  Standard_EXPORT void TriedronDisplay(
    const Aspect_TypeOfTriedronPosition thePosition = Aspect_TOTP_CENTER,
    const Quantity_Color&               theColor    = Quantity_NOC_WHITE,
    const double                        theScale    = 0.02,
    const V3d_TypeOfVisualization       theMode     = V3d_WIREFRAME);

  Standard_EXPORT void TriedronErase();

  Standard_EXPORT const Graphic3d_GraduatedTrihedron& GetGraduatedTrihedron() const;

  Standard_EXPORT void GraduatedTrihedronDisplay(
    const Graphic3d_GraduatedTrihedron& theTrihedronData);

  Standard_EXPORT void GraduatedTrihedronErase();

  Standard_EXPORT void SetFront();

  Standard_EXPORT void Rotate(const double Ax,
                              const double Ay,
                              const double Az,
                              const bool   Start = true);

  Standard_EXPORT void Rotate(const double Ax,
                              const double Ay,
                              const double Az,
                              const double X,
                              const double Y,
                              const double Z,
                              const bool   Start = true);

  Standard_EXPORT void Rotate(const V3d_TypeOfAxe Axe,
                              const double        Angle,
                              const double        X,
                              const double        Y,
                              const double        Z,
                              const bool          Start = true);

  Standard_EXPORT void Rotate(const V3d_TypeOfAxe Axe, const double Angle, const bool Start = true);

  Standard_EXPORT void Rotate(const double Angle, const bool Start = true);

  Standard_EXPORT void Move(const double Dx,
                            const double Dy,
                            const double Dz,
                            const bool   Start = true);

  Standard_EXPORT void Move(const V3d_TypeOfAxe Axe, const double Length, const bool Start = true);

  Standard_EXPORT void Move(const double Length, const bool Start = true);

  Standard_EXPORT void Translate(const double Dx,
                                 const double Dy,
                                 const double Dz,
                                 const bool   Start = true);

  Standard_EXPORT void Translate(const V3d_TypeOfAxe Axe,
                                 const double        Length,
                                 const bool          Start = true);

  Standard_EXPORT void Translate(const double Length, const bool Start = true);

  Standard_EXPORT void Place(const int theXp, const int theYp, const double theZoomFactor = 1);

  Standard_EXPORT void Turn(const double Ax,
                            const double Ay,
                            const double Az,
                            const bool   Start = true);

  Standard_EXPORT void Turn(const V3d_TypeOfAxe Axe, const double Angle, const bool Start = true);

  Standard_EXPORT void Turn(const double Angle, const bool Start = true);

  Standard_EXPORT void SetTwist(const double Angle);

  Standard_EXPORT void SetEye(const double X, const double Y, const double Z);

  Standard_EXPORT void SetDepth(const double Depth);

  Standard_EXPORT void SetProj(const double Vx, const double Vy, const double Vz);

  Standard_EXPORT void SetProj(const V3d_TypeOfOrientation theOrientation,
                               const bool                  theIsYup = false);

  Standard_EXPORT void SetAt(const double X, const double Y, const double Z);

  Standard_EXPORT void SetUp(const double Vx, const double Vy, const double Vz);

  Standard_EXPORT void SetUp(const V3d_TypeOfOrientation Orientation);

  Standard_EXPORT void SetViewOrientationDefault();

  Standard_EXPORT void ResetViewOrientation();

  Standard_EXPORT void Panning(const double theDXv,
                               const double theDYv,
                               const double theZoomFactor = 1,
                               const bool   theToStart    = true);

  Standard_EXPORT void SetCenter(const int theXp, const int theYp);

  Standard_EXPORT void SetSize(const double theSize);

  Standard_EXPORT void SetZSize(const double SetZSize);

  Standard_EXPORT void SetZoom(const double Coef, const bool Start = true);

  Standard_EXPORT void SetScale(const double Coef);

  Standard_EXPORT void SetAxialScale(const double Sx, const double Sy, const double Sz);

  Standard_EXPORT void FitAll(const double theMargin = 0.01, const bool theToUpdate = true);

  Standard_EXPORT void FitAll(const Bnd_Box& theBox,
                              const double   theMargin   = 0.01,
                              const bool     theToUpdate = true);

  Standard_EXPORT void DepthFitAll(const double Aspect = 0.01, const double Margin = 0.01);

  Standard_EXPORT void FitAll(const double theMinXv,
                              const double theMinYv,
                              const double theMaxXv,
                              const double theMaxYv);

  Standard_EXPORT void WindowFit(const int theMinXp,
                                 const int theMinYp,
                                 const int theMaxXp,
                                 const int theMaxYp);

  Standard_EXPORT void SetViewMappingDefault();

  Standard_EXPORT void ResetViewMapping();

  Standard_EXPORT void Reset(const bool theToUpdate = true);

  Standard_EXPORT double Convert(const int Vp) const;

  Standard_EXPORT void Convert(const int Xp, const int Yp, double& Xv, double& Yv) const;

  Standard_EXPORT int Convert(const double Vv) const;

  Standard_EXPORT void Convert(const double Xv, const double Yv, int& Xp, int& Yp) const;

  Standard_EXPORT void Convert(const int Xp, const int Yp, double& X, double& Y, double& Z) const;

  Standard_EXPORT void ConvertWithProj(const int Xp,
                                       const int Yp,
                                       double&   X,
                                       double&   Y,
                                       double&   Z,
                                       double&   Vx,
                                       double&   Vy,
                                       double&   Vz) const;

  Standard_EXPORT void ConvertToGrid(const int Xp,
                                     const int Yp,
                                     double&   Xg,
                                     double&   Yg,
                                     double&   Zg) const;

  Standard_EXPORT void ConvertToGrid(const double X,
                                     const double Y,
                                     const double Z,
                                     double&      Xg,
                                     double&      Yg,
                                     double&      Zg) const;

  Standard_EXPORT void Convert(const double X,
                               const double Y,
                               const double Z,
                               int&         Xp,
                               int&         Yp) const;

  Standard_EXPORT void Project(const double theX,
                               const double theY,
                               const double theZ,
                               double&      theXp,
                               double&      theYp) const;

  Standard_EXPORT void Project(const double theX,
                               const double theY,
                               const double theZ,
                               double&      theXp,
                               double&      theYp,
                               double&      theZp) const;

  Standard_EXPORT void BackgroundColor(const Quantity_TypeOfColor Type,
                                       double&                    V1,
                                       double&                    V2,
                                       double&                    V3) const;

  Standard_EXPORT Quantity_Color BackgroundColor() const;

  Standard_EXPORT void GradientBackgroundColors(Quantity_Color& theColor1,
                                                Quantity_Color& theColor2) const;

  Standard_EXPORT Aspect_GradientBackground GradientBackground() const;

  Standard_EXPORT double Scale() const;

  Standard_EXPORT void AxialScale(double& Sx, double& Sy, double& Sz) const;

  Standard_EXPORT void Size(double& Width, double& Height) const;

  Standard_EXPORT double ZSize() const;

  Standard_EXPORT void Eye(double& X, double& Y, double& Z) const;

  void FocalReferencePoint(double& X, double& Y, double& Z) const { Eye(X, Y, Z); }

  Standard_EXPORT void ProjReferenceAxe(const int Xpix,
                                        const int Ypix,
                                        double&   XP,
                                        double&   YP,
                                        double&   ZP,
                                        double&   VX,
                                        double&   VY,
                                        double&   VZ) const;

  Standard_EXPORT double Depth() const;

  Standard_EXPORT void Proj(double& Vx, double& Vy, double& Vz) const;

  Standard_EXPORT void At(double& X, double& Y, double& Z) const;

  Standard_EXPORT void Up(double& Vx, double& Vy, double& Vz) const;

  Standard_EXPORT double Twist() const;

  Standard_EXPORT Graphic3d_TypeOfShadingModel ShadingModel() const;

  Standard_EXPORT void SetShadingModel(const Graphic3d_TypeOfShadingModel theShadingModel);

  Standard_EXPORT occ::handle<Graphic3d_TextureEnv> TextureEnv() const;

  Standard_EXPORT V3d_TypeOfVisualization Visualization() const;

  const NCollection_List<occ::handle<Graphic3d_CLight>>& ActiveLights() const
  {
    return myActiveLights;
  }

  NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator ActiveLightIterator() const
  {
    return NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator(myActiveLights);
  }

  Standard_EXPORT int LightLimit() const;

  occ::handle<V3d_Viewer> Viewer() const { return MyViewer; }

  Standard_EXPORT bool IfWindow() const;

  const occ::handle<Aspect_Window>& Window() const { return MyWindow; }

  Standard_EXPORT V3d_TypeOfView Type() const;

  Standard_EXPORT void Pan(const int    theDXp,
                           const int    theDYp,
                           const double theZoomFactor = 1,
                           const bool   theToStart    = true);

  Standard_EXPORT void Zoom(const int theXp1, const int theYp1, const int theXp2, const int theYp2);

  Standard_EXPORT void StartZoomAtPoint(const int theXp, const int theYp);

  Standard_EXPORT void ZoomAtPoint(const int theMouseStartX,
                                   const int theMouseStartY,
                                   const int theMouseEndX,
                                   const int theMouseEndY);

  Standard_EXPORT void AxialScale(const int Dx, const int Dy, const V3d_TypeOfAxe Axis);

  Standard_EXPORT void StartRotation(const int    X,
                                     const int    Y,
                                     const double zRotationThreshold = 0.0);

  Standard_EXPORT void Rotation(const int X, const int Y);

  Standard_EXPORT void SetFocale(const double Focale);

  Standard_EXPORT double Focale() const;

  const occ::handle<Graphic3d_CView>& View() const { return myView; }

  Standard_EXPORT void SetComputedMode(const bool theMode);

  Standard_EXPORT bool ComputedMode() const;

  void WindowFitAll(const int Xmin, const int Ymin, const int Xmax, const int Ymax)
  {
    WindowFit(Xmin, Ymin, Xmax, Ymax);
  }

  Standard_EXPORT bool FitMinMax(const occ::handle<Graphic3d_Camera>& theCamera,
                                 const Bnd_Box&                       theBox,
                                 const double                         theMargin,
                                 const double                         theResolution = 0.0,
                                 const bool theToEnlargeIfLine                      = true) const;

  Standard_EXPORT void SetGrid(const gp_Ax3& aPlane, const occ::handle<Aspect_Grid>& aGrid);

  Standard_EXPORT void SetGridActivity(const bool aFlag);

  Standard_EXPORT bool Dump(const char*                 theFile,
                            const Graphic3d_BufferType& theBufferType = Graphic3d_BT_RGB);

  Standard_EXPORT bool ToPixMap(Image_PixMap& theImage, const V3d_ImageDumpOptions& theParams);

  bool ToPixMap(Image_PixMap&               theImage,
                const int                   theWidth,
                const int                   theHeight,
                const Graphic3d_BufferType& theBufferType     = Graphic3d_BT_RGB,
                const bool                  theToAdjustAspect = true,
                const Graphic3d_ZLayerId    theTargetZLayerId = Graphic3d_ZLayerId_BotOSD,
                const int                   theIsSingleLayer  = false,
                const V3d_StereoDumpOptions theStereoOptions  = V3d_SDO_MONO,
                const char*                 theLightName      = "")
  {
    V3d_ImageDumpOptions aParams;
    aParams.Width          = theWidth;
    aParams.Height         = theHeight;
    aParams.BufferType     = theBufferType;
    aParams.StereoOptions  = theStereoOptions;
    aParams.ToAdjustAspect = theToAdjustAspect;
    aParams.TargetZLayerId = theTargetZLayerId;
    aParams.IsSingleLayer  = theIsSingleLayer;
    aParams.LightName      = theLightName;
    return ToPixMap(theImage, aParams);
  }

  Standard_EXPORT void SetBackFacingModel(
    const Graphic3d_TypeOfBackfacingModel theModel = Graphic3d_TypeOfBackfacingModel_Auto);

  Standard_EXPORT Graphic3d_TypeOfBackfacingModel BackFacingModel() const;

  Standard_EXPORT virtual void AddClipPlane(const occ::handle<Graphic3d_ClipPlane>& thePlane);

  Standard_EXPORT virtual void RemoveClipPlane(const occ::handle<Graphic3d_ClipPlane>& thePlane);

  Standard_EXPORT const occ::handle<Graphic3d_SequenceOfHClipPlane>& ClipPlanes() const;

  Standard_EXPORT void SetClipPlanes(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes);

  Standard_EXPORT int PlaneLimit() const;

  Standard_EXPORT void SetCamera(const occ::handle<Graphic3d_Camera>& theCamera);

  Standard_EXPORT const occ::handle<Graphic3d_Camera>& Camera() const;

  const occ::handle<Graphic3d_Camera>& DefaultCamera() const { return myDefaultCamera; }

  Standard_EXPORT const Graphic3d_RenderingParams& RenderingParams() const;

  Standard_EXPORT Graphic3d_RenderingParams& ChangeRenderingParams();

  bool IsCullingEnabled() const
  {
    return RenderingParams().FrustumCullingState == Graphic3d_RenderingParams::FrustumCulling_On;
  }

  void SetFrustumCulling(bool theMode)
  {
    ChangeRenderingParams().FrustumCullingState = theMode
                                                    ? Graphic3d_RenderingParams::FrustumCulling_On
                                                    : Graphic3d_RenderingParams::FrustumCulling_Off;
  }

  Standard_EXPORT void DiagnosticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict,
    Graphic3d_DiagnosticInfo                                                      theFlags) const;

  Standard_EXPORT TCollection_AsciiString StatisticInformation() const;

  Standard_EXPORT void StatisticInformation(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theDict) const;

  Standard_EXPORT gp_Pnt GravityPoint() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  bool IsSubview() const { return myParentView != nullptr; }

  V3d_View* ParentView() { return myParentView; }

  const NCollection_Sequence<occ::handle<V3d_View>>& Subviews() const { return mySubviews; }

  Standard_EXPORT occ::handle<V3d_View> PickSubview(const NCollection_Vec2<int>& thePnt) const;

  Standard_EXPORT void AddSubview(const occ::handle<V3d_View>& theView);

  Standard_EXPORT bool RemoveSubview(const V3d_View* theView);

public:
  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")
  Standard_EXPORT bool IfMoreLights() const;

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  void InitActiveLights() { myActiveLightsIterator.Initialize(myActiveLights); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  bool MoreActiveLights() const { return myActiveLightsIterator.More(); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  void NextActiveLights() { myActiveLightsIterator.Next(); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  const occ::handle<V3d_Light>& ActiveLight() const { return myActiveLightsIterator.Value(); }

protected:
  Standard_EXPORT void ImmediateUpdate() const;

  Standard_EXPORT void Scale(const occ::handle<Graphic3d_Camera>& theCamera,
                             const double                         theSizeXv,
                             const double                         theSizeYv) const;

  Standard_EXPORT void Translate(const occ::handle<Graphic3d_Camera>& theCamera,
                                 const double                         theDXv,
                                 const double                         theDYv) const;

private:
  Standard_EXPORT void SetRatio();

  Standard_EXPORT static bool screenAxis(const gp_Dir& theVpn,
                                         const gp_Dir& theVup,
                                         gp_Vec&       theXaxe,
                                         gp_Vec&       theYaxe,
                                         gp_Vec&       theZaxe);

  Standard_EXPORT static gp_XYZ TrsPoint(const Graphic3d_Vertex&           V,
                                         const NCollection_Array2<double>& Matrix);

  Standard_EXPORT int MinMax(double& Umin, double& Vmin, double& Umax, double& Vmax) const;

  Standard_EXPORT int MinMax(double& Xmin,
                             double& Ymin,
                             double& Zmin,
                             double& Xmax,
                             double& Ymax,
                             double& Zmax) const;

  Standard_EXPORT void Init();

  Standard_EXPORT Graphic3d_Vertex Compute(const Graphic3d_Vertex& AVertex) const;

protected:
  double                        myOldMouseX;
  double                        myOldMouseY;
  gp_Dir                        myCamStartOpUp;
  gp_Dir                        myCamStartOpDir;
  gp_Pnt                        myCamStartOpEye;
  gp_Pnt                        myCamStartOpCenter;
  occ::handle<Graphic3d_Camera> myDefaultCamera;
  occ::handle<Graphic3d_CView>  myView;
  bool                          myImmediateUpdate;
  mutable bool                  myIsInvalidatedImmediate;

private:
  V3d_Viewer* MyViewer;

  NCollection_Sequence<occ::handle<V3d_View>> mySubviews;
  V3d_View*                                   myParentView;

  NCollection_List<occ::handle<Graphic3d_CLight>>           myActiveLights;
  gp_Dir                                                    myDefaultViewAxis;
  gp_Pnt                                                    myDefaultViewPoint;
  occ::handle<Aspect_Window>                                MyWindow;
  NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator myActiveLightsIterator;
  int                                                       sx;
  int                                                       sy;
  double                                                    rx;
  double                                                    ry;
  gp_Pnt                                                    myRotateGravity;
  bool                                                      myComputedMode;
  bool                                                      SwitchSetFront;
  bool                                                      myZRotation;
  int                                                       MyZoomAtPointX;
  int                                                       MyZoomAtPointY;
  occ::handle<V3d_Trihedron>                                myTrihedron;
  occ::handle<Aspect_Grid>                                  MyGrid;
  gp_Ax3                                                    MyPlane;
  NCollection_Array2<double>                                MyTrsf;
  occ::handle<Graphic3d_Structure>                          MyGridEchoStructure;
  occ::handle<Graphic3d_Group>                              MyGridEchoGroup;
  gp_Vec                                                    myXscreenAxis;
  gp_Vec                                                    myYscreenAxis;
  gp_Vec                                                    myZscreenAxis;
  gp_Dir                                                    myViewAxis;
  Graphic3d_Vertex                                          myGravityReferencePoint;
  bool                                                      myAutoZFitIsOn;
  double                                                    myAutoZFitScaleFactor;
};
