#pragma once

#include <AIS_InteractiveObject.hpp>

enum AIS_ManipulatorMode
{
  AIS_MM_None        = 0,
  AIS_MM_Translation = 1,
  AIS_MM_Rotation,
  AIS_MM_Scaling,
  AIS_MM_TranslationPlane
};

#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <Graphic3d_Group.hpp>
#include <NCollection_HSequence.hpp>
#include <Poly_Triangulation.hpp>
#include <V3d_View.hpp>
#include <Standard_DefineHandle.hpp>

class AIS_Manipulator : public AIS_InteractiveObject
{
public:
  Standard_EXPORT AIS_Manipulator();

  Standard_EXPORT AIS_Manipulator(const gp_Ax2& thePosition);

  Standard_EXPORT void SetPart(const int                 theAxisIndex,
                               const AIS_ManipulatorMode theMode,
                               const bool                theIsEnabled);

  Standard_EXPORT void SetPart(const AIS_ManipulatorMode theMode, const bool theIsEnabled);

  struct OptionsForAttach
  {

    OptionsForAttach()
        : AdjustPosition(true),
          AdjustSize(false),
          EnableModes(true)
    {
    }

    OptionsForAttach& SetAdjustPosition(const bool theApply)
    {
      AdjustPosition = theApply;
      return *this;
    }

    OptionsForAttach& SetAdjustSize(const bool theApply)
    {
      AdjustSize = theApply;
      return *this;
    }

    OptionsForAttach& SetEnableModes(const bool theApply)
    {
      EnableModes = theApply;
      return *this;
    }

    bool AdjustPosition;
    bool AdjustSize;
    bool EnableModes;
  };

  Standard_EXPORT void Attach(const occ::handle<AIS_InteractiveObject>& theObject,
                              const OptionsForAttach& theOptions = OptionsForAttach());

  Standard_EXPORT void Attach(
    const occ::handle<NCollection_HSequence<occ::handle<AIS_InteractiveObject>>>& theObject,
    const OptionsForAttach& theOptions = OptionsForAttach());

  Standard_EXPORT void EnableMode(const AIS_ManipulatorMode theMode);

  void SetModeActivationOnDetection(const bool theToEnable)
  {
    myIsActivationOnDetection = theToEnable;
  }

  bool IsModeActivationOnDetection() const { return myIsActivationOnDetection; }

public:
  Standard_EXPORT bool ProcessDragging(const occ::handle<AIS_InteractiveContext>& theCtx,
                                       const occ::handle<V3d_View>&               theView,
                                       const occ::handle<SelectMgr_EntityOwner>&  theOwner,
                                       const NCollection_Vec2<int>&               theDragFrom,
                                       const NCollection_Vec2<int>&               theDragTo,
                                       const AIS_DragAction theAction) override;

  Standard_EXPORT void StartTransform(const int                    theX,
                                      const int                    theY,
                                      const occ::handle<V3d_View>& theView);

  Standard_EXPORT void Transform(const gp_Trsf& aTrsf);

  Standard_EXPORT void RecomputeTransformation(
    const occ::handle<Graphic3d_Camera>& theCamera) override;

  Standard_EXPORT void RecomputeSelection(const AIS_ManipulatorMode theMode);

  Standard_EXPORT void StopTransform(const bool theToApply = true);

  Standard_EXPORT gp_Trsf Transform(const int                    theX,
                                    const int                    theY,
                                    const occ::handle<V3d_View>& theView);

  Standard_EXPORT bool ObjectTransformation(const int                    theX,
                                            const int                    theY,
                                            const occ::handle<V3d_View>& theView,
                                            gp_Trsf&                     theTrsf);

  Standard_EXPORT void DeactivateCurrentMode();

  Standard_EXPORT void Detach();

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<AIS_InteractiveObject>>> Objects()
    const;

  Standard_EXPORT occ::handle<AIS_InteractiveObject> Object() const;

  Standard_EXPORT occ::handle<AIS_InteractiveObject> Object(const int theIndex) const;

  bool IsAttached() const { return HasOwner(); }

  bool HasActiveMode() const { return IsAttached() && myCurrentMode != AIS_MM_None; }

  bool HasActiveTransformation() { return myHasStartedTransformation; }

  gp_Trsf StartTransformation() const
  {
    return !myStartTrsfs.IsEmpty() ? myStartTrsfs.First() : gp_Trsf();
  }

  gp_Trsf StartTransformation(int theIndex) const
  {
    Standard_ProgramError_Raise_if(
      theIndex < 1 || theIndex > Objects()->Upper(),
      "AIS_Manipulator::StartTransformation(): theIndex is out of bounds");
    return !myStartTrsfs.IsEmpty() ? myStartTrsfs(theIndex) : gp_Trsf();
  }

public:
  Standard_EXPORT void SetZoomPersistence(const bool theToEnable);

  bool ZoomPersistence() const { return myIsZoomPersistentMode; }

  Standard_EXPORT void SetTransformPersistence(
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers) override;

public:
  enum ManipulatorSkin
  {
    ManipulatorSkin_Shaded,
    ManipulatorSkin_Flat
  };

  ManipulatorSkin SkinMode() const { return mySkinMode; }

  Standard_EXPORT void SetSkinMode(const ManipulatorSkin theSkinMode);

  AIS_ManipulatorMode ActiveMode() const { return myCurrentMode; }

  int ActiveAxisIndex() const { return myCurrentIndex; }

  const gp_Ax2& Position() const { return myPosition; }

  Standard_EXPORT void SetPosition(const gp_Ax2& thePosition);

  float Size() const { return myAxes[0].Size(); }

  Standard_EXPORT void SetSize(const float theSideLength);

  Standard_EXPORT void SetGap(const float theValue);

public:
  struct BehaviorOnTransform
  {

    BehaviorOnTransform()
        : FollowTranslation(true),
          FollowRotation(true),
          FollowDragging(true)
    {
    }

    BehaviorOnTransform& SetFollowTranslation(const bool theApply)
    {
      FollowTranslation = theApply;
      return *this;
    }

    BehaviorOnTransform& SetFollowRotation(const bool theApply)
    {
      FollowRotation = theApply;
      return *this;
    }

    BehaviorOnTransform& SetFollowDragging(const bool theApply)
    {
      FollowDragging = theApply;
      return *this;
    }

    bool FollowTranslation;
    bool FollowRotation;
    bool FollowDragging;
  };

  void SetTransformBehavior(const BehaviorOnTransform& theSettings)
  {
    myBehaviorOnTransform = theSettings;
  }

  BehaviorOnTransform& ChangeTransformBehavior() { return myBehaviorOnTransform; }

  const BehaviorOnTransform& TransformBehavior() const { return myBehaviorOnTransform; }

public:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode = 0) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  bool IsAutoHilight() const override { return false; }

  Standard_EXPORT void ClearSelected() override;

  Standard_EXPORT void HilightSelected(
    const occ::handle<PrsMgr_PresentationManager>&                  thePM,
    const NCollection_Sequence<occ::handle<SelectMgr_EntityOwner>>& theSeq) override;

  Standard_EXPORT void HilightOwnerWithColor(
    const occ::handle<PrsMgr_PresentationManager>& thePM,
    const occ::handle<Prs3d_Drawer>&               theStyle,
    const occ::handle<SelectMgr_EntityOwner>&      theOwner) override;

protected:
  Standard_EXPORT void init();

  Standard_EXPORT void updateTransformation();

  Standard_EXPORT occ::handle<Prs3d_Presentation> getHighlightPresentation(
    const occ::handle<SelectMgr_EntityOwner>& theOwner) const;

  Standard_EXPORT occ::handle<Graphic3d_Group> getGroup(const int                 theIndex,
                                                        const AIS_ManipulatorMode theMode) const;

  Standard_EXPORT void attachToPoint(const gp_Pnt& thePoint);

  Standard_EXPORT void attachToBox(const Bnd_Box& theBox);

  Standard_EXPORT void adjustSize(const Bnd_Box& theBox);

  Standard_EXPORT void setTransformPersistence(
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);

  Standard_EXPORT void setLocalTransformation(const occ::handle<TopLoc_Datum3D>& theTrsf) override;
  using AIS_InteractiveObject::SetLocalTransformation;

protected:
  class Quadric
  {
  public:
    virtual ~Quadric()
    {
      myTriangulation.Nullify();
      myArray.Nullify();
    }

    const occ::handle<Poly_Triangulation>& Triangulation() const { return myTriangulation; }

    const occ::handle<Graphic3d_ArrayOfTriangles>& Array() const { return myArray; }

  protected:
    occ::handle<Poly_Triangulation>         myTriangulation;
    occ::handle<Graphic3d_ArrayOfTriangles> myArray;
  };

  class Disk : public Quadric
  {
  public:
    Disk()
        : Quadric(),
          myInnerRad(0.0f),
          myOuterRad(1.0f)
    {
    }

    ~Disk() override = default;

    void Init(const float   theInnerRadius,
              const float   theOuterRadius,
              const gp_Ax1& thePosition,
              const double  theAngle,
              const int     theSlicesNb = 20,
              const int     theStacksNb = 20);

  protected:
    gp_Ax1 myPosition;
    float  myInnerRad;
    float  myOuterRad;
  };

  class Sphere : public Quadric
  {
  public:
    Sphere()
        : Quadric(),
          myRadius(1.0f)
    {
    }

    void Init(const float           theRadius,
              const gp_Pnt&         thePosition,
              const ManipulatorSkin theSkinMode,
              const int             theSlicesNb = 20,
              const int             theStacksNb = 20);

  protected:
    gp_Pnt myPosition;
    float  myRadius;
  };

  class Cube
  {
  public:
    Cube() = default;

    ~Cube() = default;

    void Init(const gp_Ax1& thePosition, const float myBoxSize, const ManipulatorSkin theSkinMode);

    const occ::handle<Poly_Triangulation>& Triangulation() const { return myTriangulation; }

    const occ::handle<Graphic3d_ArrayOfTriangles>& Array() const { return myArray; }

  private:
    void addTriangle(const int     theIndex,
                     const gp_Pnt& theP1,
                     const gp_Pnt& theP2,
                     const gp_Pnt& theP3,
                     const gp_Dir& theNormal);

  protected:
    occ::handle<Poly_Triangulation>         myTriangulation;
    occ::handle<Graphic3d_ArrayOfTriangles> myArray;
  };

  class Sector : public Quadric
  {
  public:
    Sector()
        : Quadric(),
          myRadius(0.0f)
    {
    }

    ~Sector() override = default;

    void Init(const float           theRadius,
              const gp_Ax1&         thePosition,
              const gp_Dir&         theXDirection,
              const ManipulatorSkin theSkinMode,
              const int             theSlicesNb = 5,
              const int             theStacksNb = 5);

  protected:
    gp_Ax1 myPosition;
    float  myRadius;
  };

  class Axis
  {
  public:
    Axis(const gp_Ax1&         theAxis   = gp_Ax1(),
         const Quantity_Color& theColor  = Quantity_Color(),
         const float           theLength = 10.0f);

    void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                 const occ::handle<Prs3d_Presentation>&         thePrs,
                 const occ::handle<Prs3d_ShadingAspect>&        theAspect,
                 const ManipulatorSkin                          theSkinMode);

    const gp_Ax1& ReferenceAxis() const { return myReferenceAxis; }

    void SetPosition(const gp_Ax1& thePosition) { myPosition = thePosition; }

    const gp_Ax1& Position() const { return myPosition; }

    void SetTransformPersistence(const occ::handle<Graphic3d_TransformPers>& theTrsfPers)
    {
      if (!myHighlightTranslator.IsNull())
      {
        myHighlightTranslator->SetTransformPersistence(theTrsfPers);
      }

      if (!myHighlightScaler.IsNull())
      {
        myHighlightScaler->SetTransformPersistence(theTrsfPers);
      }

      if (!myHighlightRotator.IsNull())
      {
        myHighlightRotator->SetTransformPersistence(theTrsfPers);
      }

      if (!myHighlightDragger.IsNull())
      {
        myHighlightDragger->SetTransformPersistence(theTrsfPers);
      }
    }

    void Transform(const occ::handle<TopLoc_Datum3D>& theTransformation)
    {
      if (!myHighlightTranslator.IsNull())
      {
        myHighlightTranslator->SetTransformation(theTransformation);
      }

      if (!myHighlightScaler.IsNull())
      {
        myHighlightScaler->SetTransformation(theTransformation);
      }

      if (!myHighlightRotator.IsNull())
      {
        myHighlightRotator->SetTransformation(theTransformation);
      }

      if (!myHighlightDragger.IsNull())
      {
        myHighlightDragger->SetTransformation(theTransformation);
      }
    }

    bool HasTranslation() const { return myHasTranslation; }

    bool HasRotation() const { return myHasRotation; }

    bool HasScaling() const { return myHasScaling; }

    bool HasDragging() const { return myHasDragging; }

    void SetTranslation(const bool theIsEnabled) { myHasTranslation = theIsEnabled; }

    void SetRotation(const bool theIsEnabled) { myHasRotation = theIsEnabled; }

    void SetScaling(const bool theIsEnabled) { myHasScaling = theIsEnabled; }

    void SetDragging(const bool theIsEnabled) { myHasDragging = theIsEnabled; }

    Quantity_Color Color() const { return myColor; }

    float AxisLength() const { return myLength; }

    float BoxSize() const { return myBoxSize; }

    float AxisRadius() const { return myAxisRadius; }

    float Indent() const { return myIndent; }

    void SetAxisRadius(const float theValue) { myAxisRadius = theValue; }

    const occ::handle<Prs3d_Presentation>& TranslatorHighlightPrs() const
    {
      return myHighlightTranslator;
    }

    const occ::handle<Prs3d_Presentation>& RotatorHighlightPrs() const
    {
      return myHighlightRotator;
    }

    const occ::handle<Prs3d_Presentation>& ScalerHighlightPrs() const { return myHighlightScaler; }

    const occ::handle<Prs3d_Presentation>& DraggerHighlightPrs() const
    {
      return myHighlightDragger;
    }

    const occ::handle<Graphic3d_Group>& TranslatorGroup() const { return myTranslatorGroup; }

    const occ::handle<Graphic3d_Group>& RotatorGroup() const { return myRotatorGroup; }

    const occ::handle<Graphic3d_Group>& ScalerGroup() const { return myScalerGroup; }

    const occ::handle<Graphic3d_Group>& DraggerGroup() const { return myDraggerGroup; }

    const occ::handle<Graphic3d_ArrayOfTriangles>& TriangleArray() const { return myTriangleArray; }

    void SetIndent(const float theValue) { myIndent = theValue; }

    float Size() const { return myInnerRadius + myDiskThickness + myIndent * 2; }

    float InnerRadius() const { return myInnerRadius + myIndent * 2.0f; }

    gp_Pnt ScalerCenter(const gp_Pnt& theLocation) const
    {
      return theLocation.XYZ()
             + myPosition.Direction().XYZ() * (myLength + myIndent + myBoxSize * 0.5f);
    }

    void SetSize(const float theValue)
    {
      if (myIndent > theValue * 0.1f)
      {
        myLength        = theValue * 0.7f;
        myBoxSize       = theValue * 0.15f;
        myDiskThickness = theValue * 0.05f;
        myIndent        = theValue * 0.05f;
      }
      else
      {
        float aLength   = theValue - 2 * myIndent;
        myLength        = aLength * 0.8f;
        myBoxSize       = aLength * 0.15f;
        myDiskThickness = aLength * 0.05f;
      }
      myInnerRadius = myIndent * 2 + myBoxSize + myLength;
      myAxisRadius  = myBoxSize / 4.0f;
    }

    int FacettesNumber() const { return myFacettesNumber; }

  public:
    const gp_Pnt& TranslatorTipPosition() const { return myArrowTipPos; }

    const Sector& DraggerSector() const { return mySector; }

    const Disk& RotatorDisk() const { return myCircle; }

    float RotatorDiskRadius() const { return myCircleRadius; }

    const Cube& ScalerCube() const { return myCube; }

    const gp_Pnt& ScalerCubePosition() const { return myCubePos; }

  protected:
    gp_Ax1         myReferenceAxis;
    gp_Ax1         myPosition;
    Quantity_Color myColor;

    bool  myHasTranslation;
    float myLength;
    float myAxisRadius;

    bool  myHasScaling;
    float myBoxSize;

    bool  myHasRotation;
    float myInnerRadius;
    float myDiskThickness;
    float myIndent;

    bool myHasDragging;

  protected:
    int myFacettesNumber;

    gp_Pnt myArrowTipPos;
    Sector mySector;
    Disk   myCircle;
    float  myCircleRadius;
    Cube   myCube;
    gp_Pnt myCubePos;

    occ::handle<Graphic3d_Group> myTranslatorGroup;
    occ::handle<Graphic3d_Group> myScalerGroup;
    occ::handle<Graphic3d_Group> myRotatorGroup;
    occ::handle<Graphic3d_Group> myDraggerGroup;

    occ::handle<Prs3d_Presentation> myHighlightTranslator;
    occ::handle<Prs3d_Presentation> myHighlightScaler;
    occ::handle<Prs3d_Presentation> myHighlightRotator;
    occ::handle<Prs3d_Presentation> myHighlightDragger;

    occ::handle<Graphic3d_ArrayOfTriangles> myTriangleArray;
  };

protected:
  Axis   myAxes[3];
  Sphere myCenter;

  gp_Ax2 myPosition;

  Disk                         myCircle;
  occ::handle<Graphic3d_Group> myCircleGroup;

  Disk                         mySector;
  occ::handle<Graphic3d_Group> mySectorGroup;

  int                 myCurrentIndex;
  AIS_ManipulatorMode myCurrentMode;
  ManipulatorSkin     mySkinMode;

  bool                myIsActivationOnDetection;
  bool                myIsZoomPersistentMode;
  BehaviorOnTransform myBehaviorOnTransform;

protected:
  NCollection_Sequence<gp_Trsf> myStartTrsfs;
  bool                          myHasStartedTransformation;

  gp_Ax2 myStartPosition;
  gp_Pnt myStartPick;
  double myPrevState;

  occ::handle<Prs3d_ShadingAspect> myHighlightAspect;

  occ::handle<Prs3d_ShadingAspect> myDraggerHighlight;

public:
  DEFINE_STANDARD_RTTIEXT(AIS_Manipulator, AIS_InteractiveObject)
};
