#pragma once

#include <Aspect_GridDrawMode.hpp>

enum Aspect_GridType
{
  Aspect_GT_Rectangular,
  Aspect_GT_Circular
};

#include <Graphic3d_StructureManager.hpp>
#include <Graphic3d_Vertex.hpp>
#include <Graphic3d_ZLayerSettings.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <V3d_Light.hpp>
#include <NCollection_List.hpp>
#include <V3d_TypeOfOrientation.hpp>
#include <V3d_TypeOfView.hpp>
#include <V3d_TypeOfVisualization.hpp>
#include <Quantity_Color.hpp>

class Aspect_Grid;
class Graphic3d_AspectMarker3d;
class Graphic3d_GraphicDriver;
class Graphic3d_Group;
class Graphic3d_Structure;
class V3d_CircularGrid;
class V3d_RectangularGrid;
class V3d_View;

class V3d_Viewer : public Standard_Transient
{
  friend class V3d_View;
  DEFINE_STANDARD_RTTIEXT(V3d_Viewer, Standard_Transient)
public:
  Standard_EXPORT V3d_Viewer(const occ::handle<Graphic3d_GraphicDriver>& theDriver);

  Standard_EXPORT bool IfMoreViews() const;

  Standard_EXPORT occ::handle<V3d_View> CreateView();

  Standard_EXPORT void SetViewOn();

  Standard_EXPORT void SetViewOn(const occ::handle<V3d_View>& theView);

  Standard_EXPORT void SetViewOff();

  Standard_EXPORT void SetViewOff(const occ::handle<V3d_View>& theView);

  void Update() { Redraw(); }

  Standard_EXPORT void Redraw() const;

  Standard_EXPORT void RedrawImmediate() const;

  Standard_EXPORT void Invalidate() const;

  Standard_EXPORT void Remove();

  const occ::handle<Graphic3d_GraphicDriver>& Driver() const { return myDriver; }

  occ::handle<Graphic3d_StructureManager> StructureManager() const { return myStructureManager; }

  const Graphic3d_RenderingParams& DefaultRenderingParams() const
  {
    return myDefaultRenderingParams;
  }

  void SetDefaultRenderingParams(const Graphic3d_RenderingParams& theParams)
  {
    myDefaultRenderingParams = theParams;
  }

  void SetDefaultBackgroundColor(const Quantity_Color& theColor)
  {
    myBackground.SetColor(theColor);
  }

  const Aspect_GradientBackground& GetGradientBackground() const { return myGradientBackground; }

  void SetDefaultBgGradientColors(
    const Quantity_Color&           theColor1,
    const Quantity_Color&           theColor2,
    const Aspect_GradientFillMethod theFillStyle = Aspect_GradientFillMethod_Horizontal)
  {
    myGradientBackground.SetColors(theColor1, theColor2, theFillStyle);
  }

  double DefaultViewSize() const { return myViewSize; }

  Standard_EXPORT void SetDefaultViewSize(const double theSize);

  V3d_TypeOfOrientation DefaultViewProj() const { return myViewProj; }

  void SetDefaultViewProj(const V3d_TypeOfOrientation theOrientation)
  {
    myViewProj = theOrientation;
  }

  V3d_TypeOfVisualization DefaultVisualization() const { return myVisualization; }

  void SetDefaultVisualization(const V3d_TypeOfVisualization theType) { myVisualization = theType; }

  Graphic3d_TypeOfShadingModel DefaultShadingModel() const
  {
    return myDefaultRenderingParams.ShadingModel;
  }

  void SetDefaultShadingModel(const Graphic3d_TypeOfShadingModel theType)
  {
    myDefaultRenderingParams.ShadingModel = theType;
  }

  V3d_TypeOfView DefaultTypeOfView() const { return myDefaultTypeOfView; }

  void SetDefaultTypeOfView(const V3d_TypeOfView theType) { myDefaultTypeOfView = theType; }

  Quantity_Color DefaultBackgroundColor() const { return myBackground.Color(); }

  void DefaultBgGradientColors(Quantity_Color& theColor1, Quantity_Color& theColor2) const
  {
    myGradientBackground.Colors(theColor1, theColor2);
  }

  Standard_EXPORT void GetAllZLayers(NCollection_Sequence<int>& theLayerSeq) const;

  bool AddZLayer(Graphic3d_ZLayerId&             theLayerId,
                 const Graphic3d_ZLayerSettings& theSettings = Graphic3d_ZLayerSettings())
  {
    return InsertLayerBefore(theLayerId, theSettings, Graphic3d_ZLayerId_Top);
  }

  Standard_EXPORT bool InsertLayerBefore(Graphic3d_ZLayerId&             theNewLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings,
                                         const Graphic3d_ZLayerId        theLayerAfter);

  Standard_EXPORT bool InsertLayerAfter(Graphic3d_ZLayerId&             theNewLayerId,
                                        const Graphic3d_ZLayerSettings& theSettings,
                                        const Graphic3d_ZLayerId        theLayerBefore);

  Standard_EXPORT bool RemoveZLayer(const Graphic3d_ZLayerId theLayerId);

  Standard_EXPORT const Graphic3d_ZLayerSettings& ZLayerSettings(
    const Graphic3d_ZLayerId theLayerId) const;

  Standard_EXPORT void SetZLayerSettings(const Graphic3d_ZLayerId        theLayerId,
                                         const Graphic3d_ZLayerSettings& theSettings);

public:
  const NCollection_List<occ::handle<V3d_View>>& ActiveViews() const { return myActiveViews; }

  NCollection_List<occ::handle<V3d_View>>::Iterator ActiveViewIterator() const
  {
    return NCollection_List<occ::handle<V3d_View>>::Iterator(myActiveViews);
  }

  bool LastActiveView() const { return myActiveViews.Extent() == 1; }

public:
  const NCollection_List<occ::handle<V3d_View>>& DefinedViews() const { return myDefinedViews; }

  NCollection_List<occ::handle<V3d_View>>::Iterator DefinedViewIterator() const
  {
    return NCollection_List<occ::handle<V3d_View>>::Iterator(myDefinedViews);
  }

public:
  Standard_EXPORT void SetDefaultLights();

  Standard_EXPORT void SetLightOn(const occ::handle<V3d_Light>& theLight);

  Standard_EXPORT void SetLightOn();

  Standard_EXPORT void SetLightOff(const occ::handle<V3d_Light>& theLight);

  Standard_EXPORT void SetLightOff();

  Standard_EXPORT void AddLight(const occ::handle<V3d_Light>& theLight);

  Standard_EXPORT void DelLight(const occ::handle<V3d_Light>& theLight);

  Standard_EXPORT void UpdateLights();

  Standard_EXPORT bool IsGlobalLight(const occ::handle<V3d_Light>& TheLight) const;

  const NCollection_List<occ::handle<Graphic3d_CLight>>& ActiveLights() const
  {
    return myActiveLights;
  }

  NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator ActiveLightIterator() const
  {
    return NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator(myActiveLights);
  }

public:
  const NCollection_List<occ::handle<Graphic3d_CLight>>& DefinedLights() const
  {
    return myDefinedLights;
  }

  NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator DefinedLightIterator() const
  {
    return NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator(myDefinedLights);
  }

public:
  Standard_EXPORT void Erase() const;

  Standard_EXPORT void UnHighlight() const;

public:
  bool ComputedMode() const { return myComputedMode; }

  void SetComputedMode(const bool theMode) { myComputedMode = theMode; }

  bool DefaultComputedMode() const { return myDefaultComputedMode; }

  void SetDefaultComputedMode(const bool theMode) { myDefaultComputedMode = theMode; }

public:
  const gp_Ax3& PrivilegedPlane() const { return myPrivilegedPlane; }

  Standard_EXPORT void SetPrivilegedPlane(const gp_Ax3& thePlane);

  Standard_EXPORT void DisplayPrivilegedPlane(const bool theOnOff, const double theSize = 1);

public:
  Standard_EXPORT void ActivateGrid(const Aspect_GridType     aGridType,
                                    const Aspect_GridDrawMode aGridDrawMode);

  Standard_EXPORT void DeactivateGrid();

  Standard_EXPORT void SetGridEcho(const bool showGrid = true);

  Standard_EXPORT void SetGridEcho(const occ::handle<Graphic3d_AspectMarker3d>& aMarker);

  bool GridEcho() const { return myGridEcho; }

  Standard_EXPORT bool IsGridActive();

  occ::handle<Aspect_Grid> Grid(bool theToCreate = true) { return Grid(myGridType, theToCreate); }

  Standard_EXPORT occ::handle<Aspect_Grid> Grid(Aspect_GridType theGridType,
                                                bool            theToCreate = true);

  Aspect_GridType GridType() const { return myGridType; }

  Standard_EXPORT Aspect_GridDrawMode GridDrawMode();

  Standard_EXPORT void RectangularGridValues(double& theXOrigin,
                                             double& theYOrigin,
                                             double& theXStep,
                                             double& theYStep,
                                             double& theRotationAngle);

  Standard_EXPORT void SetRectangularGridValues(const double XOrigin,
                                                const double YOrigin,
                                                const double XStep,
                                                const double YStep,
                                                const double RotationAngle);

  Standard_EXPORT void CircularGridValues(double& theXOrigin,
                                          double& theYOrigin,
                                          double& theRadiusStep,
                                          int&    theDivisionNumber,
                                          double& theRotationAngle);

  Standard_EXPORT void SetCircularGridValues(const double XOrigin,
                                             const double YOrigin,
                                             const double RadiusStep,
                                             const int    DivisionNumber,
                                             const double RotationAngle);

  Standard_EXPORT void CircularGridGraphicValues(double& theRadius, double& theOffSet);

  Standard_EXPORT void SetCircularGridGraphicValues(const double Radius, const double OffSet);

  Standard_EXPORT void RectangularGridGraphicValues(double& theXSize,
                                                    double& theYSize,
                                                    double& theOffSet);

  Standard_EXPORT void SetRectangularGridGraphicValues(const double XSize,
                                                       const double YSize,
                                                       const double OffSet);

  Standard_EXPORT void ShowGridEcho(const occ::handle<V3d_View>& theView,
                                    const Graphic3d_Vertex&      thePoint);

  Standard_EXPORT void HideGridEcho(const occ::handle<V3d_View>& theView);

public:
  Standard_DEPRECATED("Deprecated method - IsGridActive() should be used instead")

  bool IsActive() { return IsGridActive(); }

  Standard_DEPRECATED("Deprecated method - ActiveViews() should be used instead")

  void InitActiveViews() { myActiveViewsIterator.Initialize(myActiveViews); }

  Standard_DEPRECATED("Deprecated method - ActiveViews() should be used instead")

  bool MoreActiveViews() const { return myActiveViewsIterator.More(); }

  Standard_DEPRECATED("Deprecated method - ActiveViews() should be used instead")

  void NextActiveViews()
  {
    if (!myActiveViews.IsEmpty())
      myActiveViewsIterator.Next();
  }

  Standard_DEPRECATED("Deprecated method - ActiveViews() should be used instead")

  const occ::handle<V3d_View>& ActiveView() const { return myActiveViewsIterator.Value(); }

  Standard_DEPRECATED("Deprecated method - DefinedViews() should be used instead")

  void InitDefinedViews() { myDefinedViewsIterator.Initialize(myDefinedViews); }

  Standard_DEPRECATED("Deprecated method - DefinedViews() should be used instead")

  bool MoreDefinedViews() const { return myDefinedViewsIterator.More(); }

  Standard_DEPRECATED("Deprecated method - DefinedViews() should be used instead")

  void NextDefinedViews()
  {
    if (!myDefinedViews.IsEmpty())
      myDefinedViewsIterator.Next();
  }

  Standard_DEPRECATED("Deprecated method - DefinedViews() should be used instead")

  const occ::handle<V3d_View>& DefinedView() const { return myDefinedViewsIterator.Value(); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  void InitActiveLights() { myActiveLightsIterator.Initialize(myActiveLights); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  bool MoreActiveLights() const { return myActiveLightsIterator.More(); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  void NextActiveLights() { myActiveLightsIterator.Next(); }

  Standard_DEPRECATED("Deprecated method - ActiveLights() should be used instead")

  const occ::handle<V3d_Light>& ActiveLight() const { return myActiveLightsIterator.Value(); }

  Standard_DEPRECATED("Deprecated method - DefinedLights() should be used instead")

  void InitDefinedLights() { myDefinedLightsIterator.Initialize(myDefinedLights); }

  Standard_DEPRECATED("Deprecated method - DefinedLights() should be used instead")

  bool MoreDefinedLights() const { return myDefinedLightsIterator.More(); }

  Standard_DEPRECATED("Deprecated method - DefinedLights() should be used instead")

  void NextDefinedLights()
  {
    if (!myDefinedLights.IsEmpty())
      myDefinedLightsIterator.Next();
  }

  Standard_DEPRECATED("Deprecated method - DefinedLights() should be used instead")

  const occ::handle<V3d_Light>& DefinedLight() const { return myDefinedLightsIterator.Value(); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  const Aspect_Background& GetBackgroundColor() const { return myBackground; }

  Standard_EXPORT void AddView(const occ::handle<V3d_View>& theView);

  Standard_EXPORT void DelView(const V3d_View* theView);

private:
  occ::handle<Graphic3d_GraphicDriver>    myDriver;
  occ::handle<Graphic3d_StructureManager> myStructureManager;
  NCollection_Map<int>                    myLayerIds;
  Aspect_GenId                            myZLayerGenId;

  NCollection_List<occ::handle<V3d_View>>         myDefinedViews;
  NCollection_List<occ::handle<V3d_View>>         myActiveViews;
  NCollection_List<occ::handle<Graphic3d_CLight>> myDefinedLights;
  NCollection_List<occ::handle<Graphic3d_CLight>> myActiveLights;

  Aspect_Background         myBackground;
  Aspect_GradientBackground myGradientBackground;
  double                    myViewSize;
  V3d_TypeOfOrientation     myViewProj;
  V3d_TypeOfVisualization   myVisualization;
  V3d_TypeOfView            myDefaultTypeOfView;
  Graphic3d_RenderingParams myDefaultRenderingParams;

  NCollection_List<occ::handle<V3d_View>>::Iterator         myActiveViewsIterator;
  NCollection_List<occ::handle<V3d_View>>::Iterator         myDefinedViewsIterator;
  NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator myActiveLightsIterator;
  NCollection_List<occ::handle<Graphic3d_CLight>>::Iterator myDefinedLightsIterator;

  bool myComputedMode;
  bool myDefaultComputedMode;

  gp_Ax3                           myPrivilegedPlane;
  occ::handle<Graphic3d_Structure> myPlaneStructure;
  bool                             myDisplayPlane;
  double                           myDisplayPlaneLength;

  occ::handle<V3d_RectangularGrid>      myRGrid;
  occ::handle<V3d_CircularGrid>         myCGrid;
  Aspect_GridType                       myGridType;
  bool                                  myGridEcho;
  occ::handle<Graphic3d_Structure>      myGridEchoStructure;
  occ::handle<Graphic3d_Group>          myGridEchoGroup;
  occ::handle<Graphic3d_AspectMarker3d> myGridEchoAspect;
  Graphic3d_Vertex                      myGridEchoLastVert;
};
