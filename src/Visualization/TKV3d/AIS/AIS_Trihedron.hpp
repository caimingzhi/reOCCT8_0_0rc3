#pragma once

#include <AIS_InteractiveObject.hpp>
#include <AIS_KindOfInteractive.hpp>
#include <Graphic3d_ArrayOfTriangles.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <Prs3d_DatumAspect.hpp>

enum Prs3d_DatumMode
{
  Prs3d_DM_WireFrame = 0,
  Prs3d_DM_Shaded
};

#include <Prs3d_DatumParts.hpp>
#include <Prs3d_LineAspect.hpp>
#include <SelectMgr_Selection.hpp>
#include <Quantity_Color.hpp>

class Geom_Axis2Placement;

class AIS_Trihedron : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_Trihedron, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_Trihedron(const occ::handle<Geom_Axis2Placement>& theComponent);

  Prs3d_DatumMode DatumDisplayMode() const { return myTrihDispMode; }

  void SetDatumDisplayMode(Prs3d_DatumMode theMode) { myTrihDispMode = theMode; }

  const occ::handle<Geom_Axis2Placement>& Component() const { return myComponent; }

  Standard_EXPORT void SetComponent(const occ::handle<Geom_Axis2Placement>& theComponent);

  bool HasOwnSize() const { return myHasOwnSize; }

  Standard_EXPORT double Size() const;

  Standard_EXPORT void SetSize(const double theValue);

  Standard_EXPORT void UnsetSize();

  bool HasTextColor() const { return myHasOwnTextColor; }

  Standard_EXPORT Quantity_Color TextColor() const;

  Standard_EXPORT void SetTextColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetTextColor(const Prs3d_DatumParts thePart, const Quantity_Color& theColor);

  bool HasArrowColor() const { return myHasOwnArrowColor; }

  Standard_EXPORT Quantity_Color ArrowColor() const;

  Standard_EXPORT void SetArrowColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetArrowColor(const Prs3d_DatumParts thePart,
                                     const Quantity_Color&  theColor);

  Standard_EXPORT Quantity_Color DatumPartColor(Prs3d_DatumParts thePart);

  Standard_EXPORT void SetDatumPartColor(const Prs3d_DatumParts thePart,
                                         const Quantity_Color&  theColor);

  Standard_EXPORT void SetOriginColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetXAxisColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetYAxisColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetAxisColor(const Quantity_Color& theColor);

  Standard_EXPORT bool ToDrawArrows() const;

  Standard_EXPORT void SetDrawArrows(const bool theToDraw);

  int SelectionPriority(Prs3d_DatumParts thePart) { return mySelectionPriority[thePart]; }

  void SetSelectionPriority(Prs3d_DatumParts thePart, int thePriority)
  {
    mySelectionPriority[thePart] = thePriority;
  }

  const TCollection_ExtendedString& Label(Prs3d_DatumParts thePart) { return myLabels[thePart]; }

  void SetLabel(const Prs3d_DatumParts thePart, const TCollection_ExtendedString& theName)
  {
    myLabels[thePart] = theName;
  }

public:
  Standard_EXPORT void SetColor(const Quantity_Color& theColor) override;

  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0; }

  int Signature() const override { return 3; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Datum; }

  Standard_EXPORT void UnsetColor() override;

public:
  Standard_EXPORT void ClearSelected() override;

  Standard_EXPORT void HilightSelected(
    const occ::handle<PrsMgr_PresentationManager>&                  thePM,
    const NCollection_Sequence<occ::handle<SelectMgr_EntityOwner>>& theOwners) override;

  Standard_EXPORT void HilightOwnerWithColor(
    const occ::handle<PrsMgr_PresentationManager>& thePM,
    const occ::handle<Prs3d_Drawer>&               theStyle,
    const occ::handle<SelectMgr_EntityOwner>&      theOwner) override;

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> createSensitiveEntity(
    const Prs3d_DatumParts                    thePart,
    const occ::handle<SelectMgr_EntityOwner>& theOwner) const;

  Standard_EXPORT void computePresentation(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                           const occ::handle<Prs3d_Presentation>&         thePrs);

  Standard_EXPORT void setOwnDatumAspect();

  const occ::handle<Graphic3d_ArrayOfPrimitives>& arrayOfPrimitives(Prs3d_DatumParts thePart) const
  {
    return myPrimitives[thePart];
  }

  Standard_EXPORT void updatePrimitives(const occ::handle<Prs3d_DatumAspect>& theAspect,
                                        Prs3d_DatumMode                       theMode,
                                        const gp_Pnt&                         theOrigin,
                                        const gp_Dir&                         theXDir,
                                        const gp_Dir&                         theYDir,
                                        const gp_Dir&                         theZDir);

protected:
  occ::handle<Geom_Axis2Placement> myComponent;
  Prs3d_DatumMode                  myTrihDispMode;
  bool                             myHasOwnSize;
  bool                             myHasOwnTextColor;
  bool                             myHasOwnArrowColor;

  TCollection_ExtendedString myLabels[Prs3d_DatumParts_NB];
  int                        mySelectionPriority[Prs3d_DatumParts_NB];

  occ::handle<Graphic3d_Group>        myPartToGroup[Prs3d_DatumParts_NB];
  NCollection_List<Prs3d_DatumParts>  mySelectedParts;
  occ::handle<Graphic3d_AspectLine3d> myHiddenLineAspect;

  occ::handle<Graphic3d_ArrayOfPrimitives> myPrimitives[Prs3d_DatumParts_NB];
};
