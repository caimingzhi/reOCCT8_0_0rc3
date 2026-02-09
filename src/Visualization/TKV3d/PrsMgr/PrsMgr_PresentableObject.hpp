#pragma once

#include <Aspect_TypeOfFacingModel.hpp>
#include <gp_GTrsf.hpp>
#include <Graphic3d_ClipPlane.hpp>
#include <Prs3d_Drawer.hpp>

#include <NCollection_List.hpp>

class PrsMgr_PresentableObject;

#include <PrsMgr_Presentation.hpp>
#include <NCollection_Sequence.hpp>
#include <PrsMgr_DisplayStatus.hpp>

#include <Standard_Macro.hpp>

enum PrsMgr_TypeOfPresentation3d
{

  PrsMgr_TOP_AllView,

  PrsMgr_TOP_ProjectorDependent
};

Standard_DEPRECATED("PrsMgr_TOP_ProjectorDependent should be used instead")
const PrsMgr_TypeOfPresentation3d PrsMgr_TOP_ProjectorDependant = PrsMgr_TOP_ProjectorDependent;

#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
class PrsMgr_Presentation;

class PrsMgr_PresentationManager;

class PrsMgr_PresentableObject : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(PrsMgr_PresentableObject, Standard_Transient)
  friend class PrsMgr_Presentation;
  friend class PrsMgr_PresentationManager;

public:
  NCollection_Sequence<occ::handle<PrsMgr_Presentation>>& Presentations()
  {
    return myPresentations;
  }

  Graphic3d_ZLayerId ZLayer() const { return myDrawer->ZLayer(); }

  Standard_EXPORT virtual void SetZLayer(const Graphic3d_ZLayerId theLayerId);

  bool IsMutable() const { return myIsMutable; }

  Standard_EXPORT virtual void SetMutable(const bool theIsMutable);

  const occ::handle<Graphic3d_ViewAffinity>& ViewAffinity() const { return myViewAffinity; }

  bool HasDisplayMode() const { return myDrawer->DisplayMode() != -1; }

  int DisplayMode() const { return myDrawer->DisplayMode(); }

  void SetDisplayMode(const int theMode)
  {
    if (AcceptDisplayMode(theMode))
    {
      myDrawer->SetDisplayMode(theMode);
    }
  }

  void UnsetDisplayMode() { myDrawer->SetDisplayMode(-1); }

  bool HasHilightMode() const
  {
    return !myHilightDrawer.IsNull() && myHilightDrawer->DisplayMode() != -1;
  }

  int HilightMode() const
  {
    return !myHilightDrawer.IsNull() ? myHilightDrawer->DisplayMode() : -1;
  }

  Standard_EXPORT void SetHilightMode(const int theMode);

  void UnsetHilightMode()
  {
    if (!myHilightDrawer.IsNull())
    {
      myHilightDrawer->SetDisplayMode(-1);
    }
    if (!myDynHilightDrawer.IsNull())
    {
      myDynHilightDrawer->SetDisplayMode(-1);
    }
  }

  virtual bool AcceptDisplayMode(const int theMode) const
  {
    (void)theMode;
    return true;
  }

  virtual int DefaultDisplayMode() const { return 0; }

  Standard_EXPORT bool ToBeUpdated(bool theToIncludeHidden = false) const;

  Standard_EXPORT void SetToUpdate(int theMode);

  void SetToUpdate() { SetToUpdate(-1); }

  bool IsInfinite() const { return myInfiniteState; }

  Standard_EXPORT void SetInfiniteState(const bool theFlag = true);

  PrsMgr_TypeOfPresentation3d TypeOfPresentation3d() const { return myTypeOfPresentation3d; }

  Standard_EXPORT void SetTypeOfPresentation(const PrsMgr_TypeOfPresentation3d theType);

  PrsMgr_DisplayStatus DisplayStatus() const { return myDisplayStatus; }

public:
  const occ::handle<Prs3d_Drawer>& Attributes() const { return myDrawer; }

  virtual void SetAttributes(const occ::handle<Prs3d_Drawer>& theDrawer) { myDrawer = theDrawer; }

  const occ::handle<Prs3d_Drawer>& HilightAttributes() const { return myHilightDrawer; }

  virtual void SetHilightAttributes(const occ::handle<Prs3d_Drawer>& theDrawer)
  {
    myHilightDrawer = theDrawer;
  }

  const occ::handle<Prs3d_Drawer>& DynamicHilightAttributes() const { return myDynHilightDrawer; }

  virtual void SetDynamicHilightAttributes(const occ::handle<Prs3d_Drawer>& theDrawer)
  {
    myDynHilightDrawer = theDrawer;
  }

  virtual void UnsetHilightAttributes() { myHilightDrawer.Nullify(); }

  Standard_EXPORT void SynchronizeAspects();

public:
  const occ::handle<Graphic3d_TransformPers>& TransformPersistence() const
  {
    return myTransformPersistence;
  }

  Standard_EXPORT virtual void SetTransformPersistence(
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);

  const occ::handle<TopLoc_Datum3D>& LocalTransformationGeom() const
  {
    return myLocalTransformation;
  }

  void SetLocalTransformation(const gp_Trsf& theTrsf)
  {
    setLocalTransformation(new TopLoc_Datum3D(theTrsf));
  }

  void SetLocalTransformation(const occ::handle<TopLoc_Datum3D>& theTrsf)
  {
    setLocalTransformation(theTrsf);
  }

  bool HasTransformation() const
  {
    return !myTransformation.IsNull() && myTransformation->Form() != gp_Identity;
  }

  const occ::handle<TopLoc_Datum3D>& TransformationGeom() const { return myTransformation; }

  const gp_Trsf& LocalTransformation() const
  {
    return !myLocalTransformation.IsNull() ? myLocalTransformation->Trsf() : getIdentityTrsf();
  }

  const gp_Trsf& Transformation() const
  {
    return !myTransformation.IsNull() ? myTransformation->Trsf() : getIdentityTrsf();
  }

  const gp_GTrsf& InversedTransformation() const { return myInvTransformation; }

  const occ::handle<TopLoc_Datum3D>& CombinedParentTransformation() const
  {
    return myCombinedParentTransform;
  }

  Standard_EXPORT virtual void ResetTransformation();

  Standard_EXPORT virtual void UpdateTransformation();

  virtual void RecomputeTransformation(const occ::handle<Graphic3d_Camera>& theProjector)
  {
    (void)theProjector;
  }

public:
  const occ::handle<Graphic3d_SequenceOfHClipPlane>& ClipPlanes() const { return myClipPlanes; }

  Standard_EXPORT virtual void SetClipPlanes(
    const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes);

  Standard_EXPORT virtual void AddClipPlane(const occ::handle<Graphic3d_ClipPlane>& thePlane);

  Standard_EXPORT virtual void RemoveClipPlane(const occ::handle<Graphic3d_ClipPlane>& thePlane);

public:
  PrsMgr_PresentableObject* Parent() const { return myParent; }

  const NCollection_List<occ::handle<PrsMgr_PresentableObject>>& Children() const
  {
    return myChildren;
  }

  Standard_EXPORT virtual void AddChild(const occ::handle<PrsMgr_PresentableObject>& theObject);

  Standard_EXPORT void AddChildWithCurrentTransformation(
    const occ::handle<PrsMgr_PresentableObject>& theObject);

  Standard_EXPORT virtual void RemoveChild(const occ::handle<PrsMgr_PresentableObject>& theObject);

  Standard_EXPORT void RemoveChildWithRestoreTransformation(
    const occ::handle<PrsMgr_PresentableObject>& theObject);

  bool HasOwnPresentations() const { return myHasOwnPresentations; }

  Standard_EXPORT virtual void BoundingBox(Bnd_Box& theBndBox);

protected:
  Standard_EXPORT PrsMgr_PresentableObject(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

  Standard_EXPORT ~PrsMgr_PresentableObject() override;

  Standard_EXPORT virtual void Fill(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                    const occ::handle<PrsMgr_Presentation>&        thePrs,
                                    const int                                      theMode);

  Standard_EXPORT virtual void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                       const occ::handle<Prs3d_Presentation>&         thePrs,
                                       const int                                      theMode) = 0;

  Standard_EXPORT virtual void computeHLR(const occ::handle<Graphic3d_Camera>&   theProjector,
                                          const occ::handle<TopLoc_Datum3D>&     theTrsf,
                                          const occ::handle<Prs3d_Presentation>& thePrs);

  Standard_EXPORT bool UpdatePresentations(bool theToIncludeHidden = false);

  Standard_EXPORT virtual void UpdateClipping();

  Standard_EXPORT virtual void SetCombinedParentTransform(
    const occ::handle<TopLoc_Datum3D>& theTrsf);

  Standard_EXPORT virtual void setLocalTransformation(
    const occ::handle<TopLoc_Datum3D>& theTransformation);

  Standard_EXPORT static const gp_Trsf& getIdentityTrsf();

  Standard_EXPORT void recomputeComputed() const;

  Standard_EXPORT void replaceAspects(
    const NCollection_DataMap<occ::handle<Graphic3d_Aspects>, occ::handle<Graphic3d_Aspects>>&
      theMap);

public:
  void SetIsoOnTriangulation(const bool theIsEnabled)
  {
    myDrawer->SetIsoOnTriangulation(theIsEnabled);
  }

  Aspect_TypeOfFacingModel CurrentFacingModel() const { return myCurrentFacingModel; }

  void SetCurrentFacingModel(const Aspect_TypeOfFacingModel theModel = Aspect_TOFM_BOTH_SIDE)
  {
    myCurrentFacingModel = theModel;
  }

  bool HasColor() const { return hasOwnColor; }

  virtual void Color(Quantity_Color& theColor) const { theColor = myDrawer->Color(); }

  virtual void SetColor(const Quantity_Color& theColor)
  {
    myDrawer->SetColor(theColor);
    hasOwnColor = true;
  }

  virtual void UnsetColor() { hasOwnColor = false; }

  bool HasWidth() const { return myOwnWidth != 0.0f; }

  double Width() const { return myOwnWidth; }

  virtual void SetWidth(const double theWidth) { myOwnWidth = (float)theWidth; }

  virtual void UnsetWidth() { myOwnWidth = 0.0f; }

  bool HasMaterial() const { return hasOwnMaterial; }

  Standard_EXPORT virtual Graphic3d_NameOfMaterial Material() const;

  Standard_EXPORT virtual void SetMaterial(const Graphic3d_MaterialAspect& aName);

  Standard_EXPORT virtual void UnsetMaterial();

  bool IsTransparent() const { return myDrawer->Transparency() > 0.005f; }

  virtual double Transparency() const
  {
    return (myDrawer->Transparency() <= 0.005f ? 0.0 : myDrawer->Transparency());
  }

  Standard_EXPORT virtual void SetTransparency(const double aValue = 0.6);

  Standard_EXPORT virtual void UnsetTransparency();

  Standard_EXPORT virtual bool HasPolygonOffsets() const;

  Standard_EXPORT virtual void PolygonOffsets(int& aMode, float& aFactor, float& aUnits) const;

  Standard_EXPORT virtual void SetPolygonOffsets(const int   aMode,
                                                 const float aFactor = 1.0,
                                                 const float aUnits  = 0.0);

  Standard_EXPORT virtual void UnsetAttributes();

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Standard_DEPRECATED("This method is deprecated - UpdatePresentations() should be called instead")
  Standard_EXPORT void ToBeUpdated(NCollection_List<int>& ListOfMode) const;

  bool ToPropagateVisualState() const { return myToPropagateVisualState; }

  void SetPropagateVisualState(const bool theFlag) { myToPropagateVisualState = theFlag; }

protected:
  Standard_DEPRECATED("This method is deprecated - SetToUpdate() + UpdatePresentations() should be "
                      "called instead")

  void Update(bool theToIncludeHidden = false)
  {
    SetToUpdate();
    UpdatePresentations(theToIncludeHidden);
  }

  Standard_DEPRECATED(
    "This method is deprecated - SetToUpdate() + UpdatePresentations() should be called instead")
  Standard_EXPORT void Update(int theMode, bool theToClearOther);

protected:
  PrsMgr_PresentableObject*                               myParent;
  NCollection_Sequence<occ::handle<PrsMgr_Presentation>>  myPresentations;
  occ::handle<Graphic3d_ViewAffinity>                     myViewAffinity;
  occ::handle<Graphic3d_SequenceOfHClipPlane>             myClipPlanes;
  occ::handle<Prs3d_Drawer>                               myDrawer;
  occ::handle<Prs3d_Drawer>                               myHilightDrawer;
  occ::handle<Prs3d_Drawer>                               myDynHilightDrawer;
  occ::handle<Graphic3d_TransformPers>                    myTransformPersistence;
  occ::handle<TopLoc_Datum3D>                             myLocalTransformation;
  occ::handle<TopLoc_Datum3D>                             myTransformation;
  occ::handle<TopLoc_Datum3D>                             myCombinedParentTransform;
  NCollection_List<occ::handle<PrsMgr_PresentableObject>> myChildren;
  gp_GTrsf                                                myInvTransformation;
  PrsMgr_TypeOfPresentation3d                             myTypeOfPresentation3d;
  PrsMgr_DisplayStatus                                    myDisplayStatus;

  Aspect_TypeOfFacingModel myCurrentFacingModel;
  float                    myOwnWidth;
  bool                     hasOwnColor;
  bool                     hasOwnMaterial;

  bool myInfiniteState;
  bool myIsMutable;
  bool myHasOwnPresentations;

  bool myToPropagateVisualState;
};
