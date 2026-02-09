#pragma once

#include <PrsDim_DimensionOwner.hpp>

enum PrsDim_DisplaySpecialSymbol
{
  PrsDim_DisplaySpecialSymbol_No,
  PrsDim_DisplaySpecialSymbol_Before,
  PrsDim_DisplaySpecialSymbol_After
};

#include <AIS_InteractiveObject.hpp>
#include <AIS_KindOfInteractive.hpp>
#include <PrsDim_KindOfDimension.hpp>
#include <Geom_Curve.hpp>
#include <gp_Circ.hpp>
#include <gp_Pln.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <Standard.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Handle.hpp>

class PrsDim_Dimension : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(PrsDim_Dimension, AIS_InteractiveObject)
protected:
  enum GeometryType
  {
    GeometryType_UndefShapes,
    GeometryType_Edge,
    GeometryType_Face,
    GeometryType_Points,
    GeometryType_Edges,
    GeometryType_Faces,
    GeometryType_EdgeFace,
    GeometryType_EdgeVertex
  };

  enum LabelPosition
  {
    LabelPosition_None = 0x00,

    LabelPosition_Left    = 0x01,
    LabelPosition_Right   = 0x02,
    LabelPosition_HCenter = 0x04,
    LabelPosition_HMask   = LabelPosition_Left | LabelPosition_Right | LabelPosition_HCenter,

    LabelPosition_Above   = 0x10,
    LabelPosition_Below   = 0x20,
    LabelPosition_VCenter = 0x40,
    LabelPosition_VMask   = LabelPosition_Above | LabelPosition_Below | LabelPosition_VCenter
  };

  enum ValueType
  {
    ValueType_Computed,
    ValueType_CustomReal,
    ValueType_CustomText
  };

public:
  enum ComputeMode
  {
    ComputeMode_All  = 0,
    ComputeMode_Line = 1,
    ComputeMode_Text = 2
  };

public:
  Standard_EXPORT PrsDim_Dimension(const PrsDim_KindOfDimension theType);

  double GetValue() const
  {
    return myValueType == ValueType_CustomReal ? myCustomValue : ComputeValue();
  }

  void SetComputedValue() { myValueType = ValueType_Computed; }

  Standard_EXPORT void SetCustomValue(const double theValue);

  Standard_EXPORT void SetCustomValue(const TCollection_ExtendedString& theValue);

  const TCollection_ExtendedString& GetCustomValue() const { return myCustomStringValue; }

  const gp_Pln& GetPlane() const { return myPlane; }

  int GetGeometryType() const { return myGeometryType; }

  Standard_EXPORT virtual void SetCustomPlane(const gp_Pln& thePlane);

  void UnsetCustomPlane() { myIsPlaneCustom = false; }

  bool IsTextPositionCustom() const { return myIsTextPositionFixed; }

  virtual void SetTextPosition(const gp_Pnt&) {}

  virtual gp_Pnt GetTextPosition() const { return gp_Pnt(); }

public:
  occ::handle<Prs3d_DimensionAspect> DimensionAspect() const { return myDrawer->DimensionAspect(); }

  Standard_EXPORT void SetDimensionAspect(
    const occ::handle<Prs3d_DimensionAspect>& theDimensionAspect);

  PrsDim_KindOfDimension KindOfDimension() const { return myKindOfDimension; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_Dimension; }

  bool AcceptDisplayMode(const int theMode) const override { return theMode == ComputeMode_All; }

public:
  PrsDim_DisplaySpecialSymbol DisplaySpecialSymbol() const { return myDisplaySpecialSymbol; }

  Standard_EXPORT void SetDisplaySpecialSymbol(
    const PrsDim_DisplaySpecialSymbol theDisplaySpecSymbol);

  char16_t SpecialSymbol() const { return mySpecialSymbol; }

  Standard_EXPORT void SetSpecialSymbol(const char16_t theSpecialSymbol);

  Standard_EXPORT virtual const TCollection_AsciiString& GetDisplayUnits() const;

  Standard_EXPORT virtual const TCollection_AsciiString& GetModelUnits() const;

  virtual void SetDisplayUnits(const TCollection_AsciiString&) {}

  virtual void SetModelUnits(const TCollection_AsciiString&) {}

  Standard_EXPORT void UnsetFixedTextPosition();

public:
  double SelToleranceForText2d() const { return mySelToleranceForText2d; }

  Standard_EXPORT void SetSelToleranceForText2d(const double theTol);

  double GetFlyout() const { return myFlyout; }

  Standard_EXPORT void SetFlyout(const double theFlyout);

  virtual bool IsValid() const { return myIsGeometryValid && CheckPlane(GetPlane()); }

protected:
  Standard_EXPORT double ValueToDisplayUnits() const;

  Standard_EXPORT TCollection_ExtendedString GetValueString(double& theWidth) const;

  Standard_EXPORT void DrawArrow(const occ::handle<Prs3d_Presentation>& thePresentation,
                                 const gp_Pnt&                          theLocation,
                                 const gp_Dir&                          theDirection);

  Standard_EXPORT void drawText(const occ::handle<Prs3d_Presentation>& thePresentation,
                                const gp_Pnt&                          theTextPos,
                                const gp_Dir&                          theTextDir,
                                const TCollection_ExtendedString&      theText,
                                const int                              theLabelPosition);

  Standard_EXPORT void DrawExtension(const occ::handle<Prs3d_Presentation>& thePresentation,
                                     const double                           theExtensionSize,
                                     const gp_Pnt&                          theExtensionStart,
                                     const gp_Dir&                          theExtensionDir,
                                     const TCollection_ExtendedString&      theLabelString,
                                     const double                           theLabelWidth,
                                     const int                              theMode,
                                     const int                              theLabelPosition);

  Standard_EXPORT void DrawLinearDimension(const occ::handle<Prs3d_Presentation>& thePresentation,
                                           const int                              theMode,
                                           const gp_Pnt&                          theFirstPoint,
                                           const gp_Pnt&                          theSecondPoint,
                                           const bool theIsOneSide = false);

  Standard_EXPORT virtual void ComputeFlyoutLinePoints(const gp_Pnt& theFirstPoint,
                                                       const gp_Pnt& theSecondPoint,
                                                       gp_Pnt&       theLineBegPoint,
                                                       gp_Pnt&       theLineEndPoint);

  Standard_EXPORT void ComputeLinearFlyouts(const occ::handle<SelectMgr_Selection>&   theSelection,
                                            const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                            const gp_Pnt&                             theFirstPoint,
                                            const gp_Pnt& theSecondPoint);

  Standard_EXPORT bool InitCircularDimension(const TopoDS_Shape& theShape,
                                             gp_Circ&            theCircle,
                                             gp_Pnt&             theMiddleArcPoint,
                                             bool&               theIsClosed);

  Standard_EXPORT void PointsForArrow(const gp_Pnt& thePeakPnt,
                                      const gp_Dir& theDirection,
                                      const gp_Dir& thePlane,
                                      const double  theArrowLength,
                                      const double  theArrowAngle,
                                      gp_Pnt&       theSidePnt1,
                                      gp_Pnt&       theSidePnt2);

  Standard_EXPORT gp_Pnt GetTextPositionForLinear(const gp_Pnt& theFirstPoint,
                                                  const gp_Pnt& theSecondPoint,
                                                  const bool    theIsOneSide = false) const;

  Standard_EXPORT void FitTextAlignmentForLinear(
    const gp_Pnt&                                theFirstPoint,
    const gp_Pnt&                                theSecondPoint,
    const bool                                   theIsOneSide,
    const Prs3d_DimensionTextHorizontalPosition& theHorizontalTextPos,
    int&                                         theLabelPosition,
    bool&                                        theIsArrowsExternal) const;

  Standard_EXPORT bool AdjustParametersForLinear(
    const gp_Pnt&                          theTextPos,
    const gp_Pnt&                          theFirstPoint,
    const gp_Pnt&                          theSecondPoint,
    double&                                theExtensionSize,
    Prs3d_DimensionTextHorizontalPosition& theAlignment,
    double&                                theFlyout,
    gp_Pln&                                thePlane,
    bool&                                  theIsPlaneOld) const;

protected:
  static bool CircleFromPlanarFace(const TopoDS_Face&       theFace,
                                   occ::handle<Geom_Curve>& theCurve,
                                   gp_Pnt&                  theFirstPoint,
                                   gp_Pnt&                  theLastPoint);

  static bool CircleFromEdge(const TopoDS_Edge& theEdge,
                             gp_Circ&           theCircle,
                             gp_Pnt&            theFirstPoint,
                             gp_Pnt&            theLastPoint);

protected:
  virtual bool CheckPlane(const gp_Pln&) const { return true; }

  virtual double ComputeValue() const { return 0.0; }

  virtual void ComputeFlyoutSelection(const occ::handle<SelectMgr_Selection>&,
                                      const occ::handle<SelectMgr_EntityOwner>&)
  {
  }

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                        const int                               theMode) override;

protected:
  struct SelectionGeometry
  {

    struct Arrow
    {
      gp_Pnt Position;
      gp_Dir Direction;
    };

    typedef NCollection_Sequence<gp_Pnt> Curve;
    typedef NCollection_Handle<Curve>    HCurve;
    typedef NCollection_Handle<Arrow>    HArrow;
    typedef NCollection_Sequence<HCurve> SeqOfCurves;
    typedef NCollection_Sequence<HArrow> SeqOfArrows;

    gp_Pnt TextPos;
    gp_Dir TextDir;
    double TextWidth;
    double TextHeight;

    SeqOfCurves DimensionLine;

    SeqOfArrows Arrows;
    bool        IsComputed;

  public:
    void Clear(const int theMode)
    {
      if (theMode == ComputeMode_All || theMode == ComputeMode_Line)
      {
        DimensionLine.Clear();
        Arrows.Clear();
      }

      if (theMode == ComputeMode_All || theMode == ComputeMode_Text)
      {
        TextPos    = gp::Origin();
        TextDir    = gp::DX();
        TextWidth  = 0.0;
        TextHeight = 0.0;
      }

      IsComputed = false;
    }

    Curve& NewCurve()
    {
      DimensionLine.Append(new Curve);
      HCurve& aLastCurve = DimensionLine.ChangeLast();
      return *aLastCurve;
    }

    Arrow& NewArrow()
    {
      Arrows.Append(new Arrow);
      HArrow& aLastArrow = Arrows.ChangeLast();
      return *aLastArrow;
    }
  } mySelectionGeom;

  double mySelToleranceForText2d;

protected:
  ValueType myValueType;
  double    myCustomValue;

  TCollection_ExtendedString myCustomStringValue;

protected:
  gp_Pnt myFixedTextPosition;
  bool   myIsTextPositionFixed;

protected:
  char16_t                    mySpecialSymbol;
  PrsDim_DisplaySpecialSymbol myDisplaySpecialSymbol;

protected:
  GeometryType myGeometryType;

  gp_Pln myPlane;
  bool   myIsPlaneCustom;

  double myFlyout;
  bool   myIsGeometryValid;

private:
  PrsDim_KindOfDimension myKindOfDimension;
};
