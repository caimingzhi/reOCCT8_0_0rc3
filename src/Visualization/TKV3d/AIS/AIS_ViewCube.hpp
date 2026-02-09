#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Graphic3d_Camera.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Prs3d_DatumParts.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <Prs3d_TextAspect.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <V3d_TypeOfOrientation.hpp>
#include <Select3D_SensitivePrimitiveArray.hpp>

class AIS_AnimationCamera;
class AIS_ViewCubeOwner;
class Graphic3d_ArrayOfTriangles;
class V3d_View;

class AIS_ViewCube : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_ViewCube, AIS_InteractiveObject)
public:
  Standard_EXPORT static bool IsBoxSide(V3d_TypeOfOrientation theOrient);

  Standard_EXPORT static bool IsBoxEdge(V3d_TypeOfOrientation theOrient);

  Standard_EXPORT static bool IsBoxCorner(V3d_TypeOfOrientation theOrient);

public:
  Standard_EXPORT AIS_ViewCube();

  const occ::handle<AIS_AnimationCamera>& ViewAnimation() const { return myViewAnimation; }

  void SetViewAnimation(const occ::handle<AIS_AnimationCamera>& theAnimation)
  {
    myViewAnimation = theAnimation;
  }

  bool ToAutoStartAnimation() const { return myToAutoStartAnim; }

  void SetAutoStartAnimation(bool theToEnable) { myToAutoStartAnim = theToEnable; }

  bool IsFixedAnimationLoop() const { return myIsFixedAnimation; }

  void SetFixedAnimationLoop(bool theToEnable) { myIsFixedAnimation = theToEnable; }

  Standard_EXPORT void ResetStyles();

protected:
  Standard_EXPORT void setDefaultAttributes();

  Standard_EXPORT void setDefaultHighlightAttributes();

public:
  double Size() const { return mySize; }

  Standard_EXPORT void SetSize(double theValue, bool theToAdaptAnother = true);

  double BoxFacetExtension() const { return myBoxFacetExtension; }

  void SetBoxFacetExtension(double theValue)
  {
    if (std::abs(myBoxFacetExtension - theValue) > Precision::Confusion())
    {
      myBoxFacetExtension = theValue;
      SetToUpdate();
    }
  }

  double AxesPadding() const { return myAxesPadding; }

  void SetAxesPadding(double theValue)
  {
    if (std::abs(myAxesPadding - theValue) > Precision::Confusion())
    {
      myAxesPadding = theValue;
      SetToUpdate();
    }
  }

  double BoxEdgeGap() const { return myBoxEdgeGap; }

  void SetBoxEdgeGap(double theValue)
  {
    if (std::abs(myBoxEdgeGap - theValue) > Precision::Confusion())
    {
      myBoxEdgeGap = theValue;
      SetToUpdate();
    }
  }

  double BoxEdgeMinSize() const { return myBoxEdgeMinSize; }

  void SetBoxEdgeMinSize(double theValue)
  {
    if (std::abs(myBoxEdgeMinSize - theValue) > Precision::Confusion())
    {
      myBoxEdgeMinSize = theValue;
      SetToUpdate();
    }
  }

  double BoxCornerMinSize() const { return myCornerMinSize; }

  void SetBoxCornerMinSize(double theValue)
  {
    if (std::abs(myCornerMinSize - theValue) > Precision::Confusion())
    {
      myCornerMinSize = theValue;
      SetToUpdate();
    }
  }

  double RoundRadius() const { return myRoundRadius; }

  Standard_EXPORT void SetRoundRadius(const double theValue);

  double AxesRadius() const { return myAxesRadius; }

  void SetAxesRadius(const double theRadius)
  {
    if (std::abs(myAxesRadius - theRadius) > Precision::Confusion())
    {
      myAxesRadius = theRadius;
      SetToUpdate();
    }
  }

  double AxesConeRadius() const { return myAxesConeRadius; }

  void SetAxesConeRadius(double theRadius)
  {
    if (std::abs(myAxesConeRadius - theRadius) > Precision::Confusion())
    {
      myAxesConeRadius = theRadius;
      SetToUpdate();
    }
  }

  double AxesSphereRadius() const { return myAxesSphereRadius; }

  void SetAxesSphereRadius(double theRadius)
  {
    if (std::abs(myAxesSphereRadius - theRadius) > Precision::Confusion())
    {
      myAxesSphereRadius = theRadius;
      SetToUpdate();
    }
  }

  bool ToDrawAxes() const { return myToDisplayAxes; }

  void SetDrawAxes(bool theValue)
  {
    if (myToDisplayAxes != theValue)
    {
      myToDisplayAxes = theValue;
      SetToUpdate();
    }
  }

  bool ToDrawEdges() const { return myToDisplayEdges; }

  void SetDrawEdges(bool theValue)
  {
    if (myToDisplayEdges != theValue)
    {
      myToDisplayEdges = theValue;
      SetToUpdate();
    }
  }

  bool ToDrawVertices() const { return myToDisplayVertices; }

  void SetDrawVertices(bool theValue)
  {
    if (myToDisplayVertices != theValue)
    {
      myToDisplayVertices = theValue;
      SetToUpdate();
    }
  }

  bool IsYup() const { return myIsYup; }

  Standard_EXPORT void SetYup(bool theIsYup, bool theToUpdateLabels = true);

public:
  const occ::handle<Prs3d_ShadingAspect>& BoxSideStyle() const { return myDrawer->ShadingAspect(); }

  const occ::handle<Prs3d_ShadingAspect>& BoxEdgeStyle() const { return myBoxEdgeAspect; }

  const occ::handle<Prs3d_ShadingAspect>& BoxCornerStyle() const { return myBoxCornerAspect; }

  const Quantity_Color& BoxColor() const { return myDrawer->ShadingAspect()->Color(); }

  void SetBoxColor(const Quantity_Color& theColor)
  {
    if (!myDrawer->ShadingAspect()->Color().IsEqual(theColor)
        || !myBoxEdgeAspect->Color().IsEqual(theColor)
        || !myBoxCornerAspect->Color().IsEqual(theColor))
    {
      myDrawer->ShadingAspect()->SetColor(theColor);
      myBoxEdgeAspect->SetColor(theColor);
      myBoxCornerAspect->SetColor(theColor);
      SynchronizeAspects();
    }
  }

  double BoxTransparency() const { return myDrawer->ShadingAspect()->Transparency(); }

  void SetBoxTransparency(double theValue)
  {
    if (std::abs(myDrawer->ShadingAspect()->Transparency() - theValue) > Precision::Confusion()
        || std::abs(myBoxEdgeAspect->Transparency() - theValue) > Precision::Confusion()
        || std::abs(myBoxCornerAspect->Transparency() - theValue) > Precision::Confusion())
    {
      myDrawer->ShadingAspect()->SetTransparency(theValue);
      myBoxEdgeAspect->SetTransparency(theValue);
      myBoxCornerAspect->SetTransparency(theValue);
      SynchronizeAspects();
    }
  }

  const Quantity_Color& InnerColor() const
  {
    return myDrawer->ShadingAspect()->Color(Aspect_TOFM_BACK_SIDE);
  }

  void SetInnerColor(const Quantity_Color& theColor)
  {
    myDrawer->ShadingAspect()->SetColor(theColor, Aspect_TOFM_BACK_SIDE);
    SynchronizeAspects();
  }

  TCollection_AsciiString BoxSideLabel(V3d_TypeOfOrientation theSide) const
  {
    const TCollection_AsciiString* aLabel = myBoxSideLabels.Seek(theSide);
    return aLabel != nullptr ? *aLabel : TCollection_AsciiString();
  }

  void SetBoxSideLabel(const V3d_TypeOfOrientation theSide, const TCollection_AsciiString& theLabel)
  {
    if (!IsBoxSide(theSide))
    {
      throw Standard_ProgramError("AIS_ViewCube::SetBoxSideLabel(), invalid enumeration value");
    }
    myBoxSideLabels.Bind(theSide, theLabel);
    SetToUpdate();
  }

  const Quantity_Color& TextColor() const { return myDrawer->TextAspect()->Aspect()->Color(); }

  void SetTextColor(const Quantity_Color& theColor)
  {
    myDrawer->TextAspect()->SetColor(theColor);
    SynchronizeAspects();
  }

  const TCollection_AsciiString& Font() const { return myDrawer->TextAspect()->Aspect()->Font(); }

  void SetFont(const TCollection_AsciiString& theFont)
  {
    myDrawer->TextAspect()->Aspect()->SetFont(theFont);
    SynchronizeAspects();
  }

  double FontHeight() const { return myDrawer->TextAspect()->Height(); }

  void SetFontHeight(double theValue)
  {
    if (std::abs(myDrawer->TextAspect()->Height() - theValue) > Precision::Confusion())
    {
      myDrawer->TextAspect()->SetHeight(theValue);
      SetToUpdate();
    }
  }

  TCollection_AsciiString AxisLabel(Prs3d_DatumParts theAxis) const
  {
    const TCollection_AsciiString* aLabel = myAxesLabels.Seek(theAxis);
    return aLabel != nullptr ? *aLabel : TCollection_AsciiString();
  }

  void SetAxesLabels(const TCollection_AsciiString& theX,
                     const TCollection_AsciiString& theY,
                     const TCollection_AsciiString& theZ)
  {
    myAxesLabels.Bind(Prs3d_DatumParts_XAxis, theX);
    myAxesLabels.Bind(Prs3d_DatumParts_YAxis, theY);
    myAxesLabels.Bind(Prs3d_DatumParts_ZAxis, theZ);
    SetToUpdate();
  }

public:
  void SetColor(const Quantity_Color& theColor) override { SetBoxColor(theColor); }

  void UnsetColor() override
  {
    myDrawer->ShadingAspect()->SetColor(Quantity_NOC_WHITE);
    myBoxEdgeAspect->SetColor(Quantity_NOC_GRAY30);
    myBoxCornerAspect->SetColor(Quantity_NOC_GRAY30);
    SynchronizeAspects();
  }

  void SetTransparency(const double theValue) override { SetBoxTransparency(theValue); }

  void UnsetTransparency() override { SetBoxTransparency(0.0f); }

  void SetMaterial(const Graphic3d_MaterialAspect& theMat) override
  {
    myDrawer->ShadingAspect()->SetMaterial(theMat);
    myBoxEdgeAspect->SetMaterial(theMat);
    myBoxCornerAspect->SetMaterial(theMat);
    SynchronizeAspects();
  }

  void UnsetMaterial() override
  {
    Graphic3d_MaterialAspect aMat(Graphic3d_NameOfMaterial_UserDefined);
    aMat.SetColor(Quantity_NOC_WHITE);
    aMat.SetAmbientColor(Quantity_NOC_GRAY60);
    myDrawer->ShadingAspect()->SetMaterial(aMat);
    myBoxEdgeAspect->SetMaterial(aMat);
    myBoxEdgeAspect->SetColor(Quantity_NOC_GRAY30);
    myBoxCornerAspect->SetMaterial(aMat);
    myBoxCornerAspect->SetColor(Quantity_NOC_GRAY30);
    SynchronizeAspects();
  }

public:
  Standard_EXPORT double Duration() const;

  Standard_EXPORT void SetDuration(double theValue);

  bool ToResetCameraUp() const { return myToResetCameraUp; }

  void SetResetCamera(bool theToReset) { myToResetCameraUp = theToReset; }

  bool ToFitSelected() const { return myToFitSelected; }

  void SetFitSelected(bool theToFitSelected) { myToFitSelected = theToFitSelected; }

  Standard_EXPORT bool HasAnimation() const;

  Standard_EXPORT virtual void StartAnimation(const occ::handle<AIS_ViewCubeOwner>& theOwner);

  Standard_EXPORT virtual bool UpdateAnimation(const bool theToUpdate);

  Standard_EXPORT virtual void HandleClick(const occ::handle<AIS_ViewCubeOwner>& theOwner);

protected:
  Standard_EXPORT bool updateAnimation();

  Standard_EXPORT virtual void viewFitAll(const occ::handle<V3d_View>&         theView,
                                          const occ::handle<Graphic3d_Camera>& theCamera);

protected:
  virtual void onAfterAnimation() {}

  virtual void onAnimationFinished() {}

public:
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  occ::handle<SelectMgr_EntityOwner> GlobalSelOwner() const override
  {
    return occ::handle<SelectMgr_EntityOwner>();
  }

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode = 0) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  bool IsAutoHilight() const override { return false; }

  void ClearSelected() override {}

  Standard_EXPORT void HilightOwnerWithColor(
    const occ::handle<PrsMgr_PresentationManager>& thePM,
    const occ::handle<Prs3d_Drawer>&               theStyle,
    const occ::handle<SelectMgr_EntityOwner>&      theOwner) override;

  Standard_EXPORT void HilightSelected(
    const occ::handle<PrsMgr_PresentationManager>&                  thePM,
    const NCollection_Sequence<occ::handle<SelectMgr_EntityOwner>>& theSeq) override;

  void UnsetAttributes() override
  {
    setDefaultAttributes();
    SetToUpdate();
  }

  void UnsetHilightAttributes() override
  {
    myHilightDrawer.Nullify();
    setDefaultHighlightAttributes();
    SetToUpdate();
  }

protected:
  Standard_EXPORT virtual void createBoxPartTriangles(
    const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
    int&                                           theNbNodes,
    int&                                           theNbTris,
    V3d_TypeOfOrientation                          theDir) const;

  Standard_EXPORT virtual void createBoxSideTriangles(
    const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
    int&                                           theNbNodes,
    int&                                           theNbTris,
    V3d_TypeOfOrientation                          theDir) const;

  Standard_EXPORT virtual void createBoxEdgeTriangles(
    const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
    int&                                           theNbNodes,
    int&                                           theNbTris,
    V3d_TypeOfOrientation                          theDir) const;

  Standard_EXPORT virtual void createBoxCornerTriangles(
    const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
    int&                                           theNbNodes,
    int&                                           theNbTris,
    V3d_TypeOfOrientation                          theDir) const;

protected:
  Standard_EXPORT static void createRoundRectangleTriangles(
    const occ::handle<Graphic3d_ArrayOfTriangles>& theTris,
    int&                                           theNbNodes,
    int&                                           theNbTris,
    const gp_XY&                                   theSize,
    double                                         theRadius,
    const gp_Trsf&                                 theTrsf);

protected:
  NCollection_DataMap<V3d_TypeOfOrientation, TCollection_AsciiString> myBoxSideLabels;
  NCollection_DataMap<Prs3d_DatumParts, TCollection_AsciiString>      myAxesLabels;
  occ::handle<Prs3d_ShadingAspect>                                    myBoxEdgeAspect;
  occ::handle<Prs3d_ShadingAspect>                                    myBoxCornerAspect;

  double mySize;
  double myBoxEdgeMinSize;
  double myBoxEdgeGap;
  double myBoxFacetExtension;
  double myAxesPadding;

  double myAxesRadius;
  double myAxesConeRadius;
  double myAxesSphereRadius;
  double myCornerMinSize;
  double myRoundRadius;
  bool   myToDisplayAxes;
  bool   myToDisplayEdges;
  bool   myToDisplayVertices;
  bool   myIsYup;

protected:
  occ::handle<AIS_AnimationCamera> myViewAnimation;
  occ::handle<Graphic3d_Camera>    myStartState;
  occ::handle<Graphic3d_Camera>    myEndState;
  bool                             myToAutoStartAnim;
  bool                             myIsFixedAnimation;
  bool                             myToFitSelected;

  bool myToResetCameraUp;
};

class AIS_ViewCubeOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(AIS_ViewCubeOwner, SelectMgr_EntityOwner)
public:
  AIS_ViewCubeOwner(const occ::handle<AIS_ViewCube>& theObject,
                    V3d_TypeOfOrientation            theOrient,
                    int                              thePriority = 5)
      : SelectMgr_EntityOwner((const occ::handle<SelectMgr_SelectableObject>&)theObject,
                              thePriority),
        myMainOrient(theOrient)
  {
    myFromDecomposition = true;
  }

  bool IsForcedHilight() const override { return true; }

  V3d_TypeOfOrientation MainOrientation() const { return myMainOrient; }

  bool HandleMouseClick(const NCollection_Vec2<int>& thePoint,
                        Aspect_VKeyMouse             theButton,
                        Aspect_VKeyFlags             theModifiers,
                        bool                         theIsDoubleClick) override
  {
    (void)thePoint;
    (void)theButton;
    (void)theModifiers;
    (void)theIsDoubleClick;
    AIS_ViewCube* aCubePrs = dynamic_cast<AIS_ViewCube*>(mySelectable);
    aCubePrs->HandleClick(this);
    return true;
  }

protected:
  V3d_TypeOfOrientation myMainOrient;
};

class AIS_ViewCubeSensitive : public Select3D_SensitivePrimitiveArray
{
  DEFINE_STANDARD_RTTIEXT(AIS_ViewCubeSensitive, Select3D_SensitivePrimitiveArray)
public:
  Standard_EXPORT AIS_ViewCubeSensitive(const occ::handle<SelectMgr_EntityOwner>&      theOwner,
                                        const occ::handle<Graphic3d_ArrayOfTriangles>& theTris);

  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

protected:
  Standard_EXPORT bool isValidRay(const SelectBasics_SelectingVolumeManager& theMgr) const;
};
