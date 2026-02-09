#include <PrsDim_AngleDimension.hpp>

#include <PrsDim.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRep_Tool.hpp>
#include <ElCLib.hpp>
#include <GCPnts_UniformAbscissa.hpp>
#include <GC_MakeArcOfCircle.hpp>
#include <gce_MakeLin2d.hpp>
#include <gce_MakeLin.hpp>
#include <gce_MakeCirc.hpp>
#include <gce_MakeCone.hpp>
#include <gce_MakePln.hpp>
#include <gce_MakeDir.hpp>
#include <Geom_Circle.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_OffsetSurface.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_Group.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <ProjLib.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <Select3D_SensitiveGroup.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_Selection.hpp>
#include <Standard_ProgramError.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_AngleDimension, PrsDim_Dimension)

namespace
{
  constexpr double   THE_EMPTY_LABEL_WIDTH = 0.0;
  constexpr char16_t THE_DEGREE_SYMBOL     = 0x00B0;
  constexpr double   THE_3D_TEXT_MARGIN    = 0.1;

  static bool isSameLine(const gp_Pnt& theFirstPoint,
                         const gp_Pnt& theCenterPoint,
                         const gp_Pnt& theSecondPoint)
  {
    gp_Vec aVec1(theFirstPoint, theCenterPoint);
    gp_Vec aVec2(theCenterPoint, theSecondPoint);

    return aVec1.IsParallel(aVec2, Precision::Angular());
  }
} // namespace

PrsDim_AngleDimension::PrsDim_AngleDimension(const TopoDS_Edge& theFirstEdge,
                                             const TopoDS_Edge& theSecondEdge)
    : PrsDim_Dimension(PrsDim_KOD_PLANEANGLE)
{
  Init();
  SetMeasuredGeometry(theFirstEdge, theSecondEdge);
}

PrsDim_AngleDimension::PrsDim_AngleDimension(const gp_Pnt& theFirstPoint,
                                             const gp_Pnt& theSecondPoint,
                                             const gp_Pnt& theThirdPoint)
    : PrsDim_Dimension(PrsDim_KOD_PLANEANGLE)
{
  Init();
  SetMeasuredGeometry(theFirstPoint, theSecondPoint, theThirdPoint);
}

PrsDim_AngleDimension::PrsDim_AngleDimension(const TopoDS_Vertex& theFirstVertex,
                                             const TopoDS_Vertex& theSecondVertex,
                                             const TopoDS_Vertex& theThirdVertex)
    : PrsDim_Dimension(PrsDim_KOD_PLANEANGLE)
{
  Init();
  SetMeasuredGeometry(theFirstVertex, theSecondVertex, theThirdVertex);
}

PrsDim_AngleDimension::PrsDim_AngleDimension(const TopoDS_Face& theCone)
    : PrsDim_Dimension(PrsDim_KOD_PLANEANGLE)
{
  Init();
  SetMeasuredGeometry(theCone);
}

PrsDim_AngleDimension::PrsDim_AngleDimension(const TopoDS_Face& theFirstFace,
                                             const TopoDS_Face& theSecondFace)
    : PrsDim_Dimension(PrsDim_KOD_PLANEANGLE)
{
  Init();
  SetMeasuredGeometry(theFirstFace, theSecondFace);
}

PrsDim_AngleDimension::PrsDim_AngleDimension(const TopoDS_Face& theFirstFace,
                                             const TopoDS_Face& theSecondFace,
                                             const gp_Pnt&      thePoint)
    : PrsDim_Dimension(PrsDim_KOD_PLANEANGLE)
{
  Init();
  SetMeasuredGeometry(theFirstFace, theSecondFace, thePoint);
}

void PrsDim_AngleDimension::SetMeasuredGeometry(const TopoDS_Edge& theFirstEdge,
                                                const TopoDS_Edge& theSecondEdge)
{
  gp_Pln aComputedPlane;

  myFirstShape      = theFirstEdge;
  mySecondShape     = theSecondEdge;
  myThirdShape      = TopoDS_Shape();
  myGeometryType    = GeometryType_Edges;
  myIsGeometryValid = InitTwoEdgesAngle(aComputedPlane);

  if (myIsGeometryValid && !myIsPlaneCustom)
  {
    myPlane = aComputedPlane;
  }

  SetToUpdate();
}

void PrsDim_AngleDimension::SetMeasuredGeometry(const gp_Pnt& theFirstPoint,
                                                const gp_Pnt& theSecondPoint,
                                                const gp_Pnt& theThirdPoint)
{
  myFirstPoint      = theFirstPoint;
  myCenterPoint     = theSecondPoint;
  mySecondPoint     = theThirdPoint;
  myFirstShape      = BRepLib_MakeVertex(myFirstPoint);
  mySecondShape     = BRepLib_MakeVertex(myCenterPoint);
  myThirdShape      = BRepLib_MakeVertex(mySecondPoint);
  myGeometryType    = GeometryType_Points;
  myIsGeometryValid = IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);

  bool anIsSameLine = isSameLine(myFirstPoint, myCenterPoint, mySecondPoint);
  if (myIsGeometryValid && !myIsPlaneCustom && !anIsSameLine)
  {
    ComputePlane();
  }

  SetToUpdate();
}

void PrsDim_AngleDimension::SetMeasuredGeometry(const TopoDS_Vertex& theFirstVertex,
                                                const TopoDS_Vertex& theSecondVertex,
                                                const TopoDS_Vertex& theThirdVertex)
{
  myFirstShape      = theFirstVertex;
  mySecondShape     = theSecondVertex;
  myThirdShape      = theThirdVertex;
  myFirstPoint      = BRep_Tool::Pnt(theFirstVertex);
  myCenterPoint     = BRep_Tool::Pnt(theSecondVertex);
  mySecondPoint     = BRep_Tool::Pnt(theThirdVertex);
  myGeometryType    = GeometryType_Points;
  myIsGeometryValid = IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);

  bool anIsSameLine = isSameLine(myFirstPoint, myCenterPoint, mySecondPoint);
  if (myIsGeometryValid && !myIsPlaneCustom && !anIsSameLine)
  {
    ComputePlane();
  }

  SetToUpdate();
}

void PrsDim_AngleDimension::SetMeasuredGeometry(const TopoDS_Face& theCone)
{
  myFirstShape      = theCone;
  mySecondShape     = TopoDS_Shape();
  myThirdShape      = TopoDS_Shape();
  myGeometryType    = GeometryType_Face;
  myIsGeometryValid = InitConeAngle();

  if (myIsGeometryValid && !myIsPlaneCustom)
  {
    ComputePlane();
  }

  SetToUpdate();
}

void PrsDim_AngleDimension::SetMeasuredGeometry(const TopoDS_Face& theFirstFace,
                                                const TopoDS_Face& theSecondFace)
{
  myFirstShape      = theFirstFace;
  mySecondShape     = theSecondFace;
  myThirdShape      = TopoDS_Shape();
  myGeometryType    = GeometryType_Faces;
  myIsGeometryValid = InitTwoFacesAngle();

  if (myIsGeometryValid && !myIsPlaneCustom)
  {
    ComputePlane();
  }

  SetToUpdate();
}

void PrsDim_AngleDimension::SetMeasuredGeometry(const TopoDS_Face& theFirstFace,
                                                const TopoDS_Face& theSecondFace,
                                                const gp_Pnt&      thePoint)
{
  myFirstShape      = theFirstFace;
  mySecondShape     = theSecondFace;
  myThirdShape      = TopoDS_Shape();
  myGeometryType    = GeometryType_Faces;
  myIsGeometryValid = InitTwoFacesAngle(thePoint);

  if (myIsGeometryValid && !myIsPlaneCustom)
  {
    ComputePlane();
  }

  SetToUpdate();
}

void PrsDim_AngleDimension::Init()
{
  SetType(PrsDim_TypeOfAngle_Interior);
  SetArrowsVisibility(PrsDim_TypeOfAngleArrowVisibility_Both);
  SetSpecialSymbol(THE_DEGREE_SYMBOL);
  SetDisplaySpecialSymbol(PrsDim_DisplaySpecialSymbol_After);
  SetFlyout(15.0);
}

gp_Pnt PrsDim_AngleDimension::GetCenterOnArc(const gp_Pnt& theFirstAttach,
                                             const gp_Pnt& theSecondAttach,
                                             const gp_Pnt& theCenter) const
{

  gce_MakePln aConstructPlane(theFirstAttach, theSecondAttach, theCenter);
  if (!aConstructPlane.IsDone())
  {
    return gp::Origin();
  }

  gp_Pln aPlane = aConstructPlane.Value();

  if (myType == PrsDim_TypeOfAngle_Exterior)
  {
    gp_Ax1 anAxis = aPlane.Axis();
    gp_Dir aDir   = anAxis.Direction();
    aDir.Reverse();
    aPlane.SetAxis(gp_Ax1(anAxis.Location(), aDir));
  }

  double aRadius = theFirstAttach.Distance(theCenter);

  gce_MakeCirc aConstructCircle(theCenter, aPlane, aRadius);
  if (!aConstructCircle.IsDone())
  {
    return gp::Origin();
  }

  gp_Circ aCircle = aConstructCircle.Value();

  double aParamBeg = ElCLib::Parameter(aCircle, theFirstAttach);
  double aParamEnd = ElCLib::Parameter(aCircle, theSecondAttach);
  ElCLib::AdjustPeriodic(0.0, M_PI * 2, Precision::PConfusion(), aParamBeg, aParamEnd);

  return ElCLib::Value((aParamBeg + aParamEnd) * 0.5, aCircle);
}

gp_Dir PrsDim_AngleDimension::GetNormalForMinAngle() const
{
  const gp_Dir& aNormal = myPlane.Axis().Direction();
  gp_Dir        aFirst(gp_Vec(myCenterPoint, myFirstPoint));
  gp_Dir        aSecond(gp_Vec(myCenterPoint, mySecondPoint));

  return aFirst.AngleWithRef(aSecond, aNormal) < 0.0 ? aNormal.Reversed() : aNormal;
}

void PrsDim_AngleDimension::DrawArc(const occ::handle<Prs3d_Presentation>& thePresentation,
                                    const gp_Pnt&                          theFirstAttach,
                                    const gp_Pnt&                          theSecondAttach,
                                    const gp_Pnt&                          theCenter,
                                    const double                           theRadius,
                                    const int                              theMode)
{
  gp_Pln aPlane(myCenterPoint, GetNormalForMinAngle());

  if (myType == PrsDim_TypeOfAngle_Exterior)
  {
    gp_Ax1 anAxis = aPlane.Axis();
    gp_Dir aDir   = anAxis.Direction();
    aDir.Reverse();
    aPlane.SetAxis(gp_Ax1(anAxis.Location(), aDir));
  }

  gce_MakeCirc aConstructCircle(theCenter, aPlane, theRadius);
  if (!aConstructCircle.IsDone())
  {
    return;
  }

  gp_Circ aCircle = aConstructCircle.Value();

  GC_MakeArcOfCircle aConstructArc(aCircle, theFirstAttach, theSecondAttach, true);
  if (!aConstructArc.IsDone())
  {
    return;
  }

  const occ::handle<Geom_TrimmedCurve>& anArcCurve = aConstructArc.Value();

  GeomAdaptor_Curve anArcAdaptor(anArcCurve,
                                 anArcCurve->FirstParameter(),
                                 anArcCurve->LastParameter());

  gp_Vec aCenterToFirstVec(theCenter, theFirstAttach);
  gp_Vec aCenterToSecondVec(theCenter, theSecondAttach);
  double anAngle = aCenterToFirstVec.Angle(aCenterToSecondVec);
  if (myType == PrsDim_TypeOfAngle_Exterior)
    anAngle = 2.0 * M_PI - anAngle;

  const int aNbPoints = std::max(4, int(50.0 * anAngle / M_PI));

  GCPnts_UniformAbscissa aMakePnts(anArcAdaptor, aNbPoints);
  if (!aMakePnts.IsDone())
  {
    return;
  }

  occ::handle<Graphic3d_ArrayOfPolylines> aPrimSegments = new Graphic3d_ArrayOfPolylines(aNbPoints);

  SelectionGeometry::Curve& aSensitiveCurve = mySelectionGeom.NewCurve();

  for (int aPntIt = 1; aPntIt <= aMakePnts.NbPoints(); ++aPntIt)
  {
    gp_Pnt aPnt = anArcAdaptor.Value(aMakePnts.Parameter(aPntIt));

    aPrimSegments->AddVertex(aPnt);

    aSensitiveCurve.Append(aPnt);
  }

  if (!myDrawer->DimensionAspect()->IsText3d() && theMode == ComputeMode_All)
  {
    thePresentation->CurrentGroup()->SetStencilTestOptions(true);
  }
  occ::handle<Graphic3d_AspectLine3d> aDimensionLineStyle =
    myDrawer->DimensionAspect()->LineAspect()->Aspect();
  thePresentation->CurrentGroup()->SetPrimitivesAspect(aDimensionLineStyle);
  thePresentation->CurrentGroup()->AddPrimitiveArray(aPrimSegments);
  if (!myDrawer->DimensionAspect()->IsText3d() && theMode == ComputeMode_All)
  {
    thePresentation->CurrentGroup()->SetStencilTestOptions(false);
  }
}

void PrsDim_AngleDimension::DrawArcWithText(const occ::handle<Prs3d_Presentation>& thePresentation,
                                            const gp_Pnt&                          theFirstAttach,
                                            const gp_Pnt&                          theSecondAttach,
                                            const gp_Pnt&                          theCenter,
                                            const TCollection_ExtendedString&      theText,
                                            const double                           theTextWidth,
                                            const int                              theMode,
                                            const int                              theLabelPosition)
{
  gp_Pln aPlane(myCenterPoint, GetNormalForMinAngle());

  double aRadius = theFirstAttach.Distance(myCenterPoint);

  gce_MakeCirc aConstructCircle(theCenter, aPlane, aRadius);
  if (!aConstructCircle.IsDone())
  {
    return;
  }

  gp_Circ aCircle = aConstructCircle.Value();

  double aParamBeg = ElCLib::Parameter(aCircle, theFirstAttach);
  double aParamEnd = ElCLib::Parameter(aCircle, theSecondAttach);
  ElCLib::AdjustPeriodic(0.0, M_PI * 2, Precision::PConfusion(), aParamBeg, aParamEnd);

  double aParamMid = (aParamBeg + aParamEnd) * 0.5;

  if (theMode == ComputeMode_All || theMode == ComputeMode_Text)
  {
    gp_Pnt aTextPos = ElCLib::Value(aParamMid, aCircle);
    gp_Dir aTextDir = gce_MakeDir(theFirstAttach, theSecondAttach);

    drawText(thePresentation, aTextPos, aTextDir, theText, theLabelPosition);
  }

  if (theMode != ComputeMode_All && theMode != ComputeMode_Line)
  {
    return;
  }

  occ::handle<Prs3d_DimensionAspect> aDimensionAspect = myDrawer->DimensionAspect();

  bool isLineBreak =
    aDimensionAspect->TextVerticalPosition() == Prs3d_DTVP_Center && aDimensionAspect->IsText3d();

  if (isLineBreak)
  {

    double aSectorOfText = theTextWidth / aRadius;
    double aTextBegin    = aParamMid - aSectorOfText * 0.5;
    double aTextEnd      = aParamMid + aSectorOfText * 0.5;
    gp_Pnt aTextPntBeg   = ElCLib::Value(aTextBegin, aCircle);
    gp_Pnt aTextPntEnd   = ElCLib::Value(aTextEnd, aCircle);

    if (aTextBegin > aParamBeg)
    {
      DrawArc(thePresentation, theFirstAttach, aTextPntBeg, theCenter, aRadius, theMode);
    }
    if (aTextEnd < aParamEnd)
    {
      DrawArc(thePresentation, aTextPntEnd, theSecondAttach, theCenter, aRadius, theMode);
    }
  }
  else
  {
    DrawArc(thePresentation, theFirstAttach, theSecondAttach, theCenter, aRadius, theMode);
  }
}

bool PrsDim_AngleDimension::CheckPlane(const gp_Pln& thePlane) const
{
  return thePlane.Contains(myFirstPoint, Precision::Confusion())
         || thePlane.Contains(mySecondPoint, Precision::Confusion())
         || thePlane.Contains(myCenterPoint, Precision::Confusion());
}

void PrsDim_AngleDimension::ComputePlane()
{
  if (!myIsGeometryValid)
  {
    return;
  }

  gp_Vec aFirstVec   = gp_Vec(myCenterPoint, myFirstPoint);
  gp_Vec aSecondVec  = gp_Vec(myCenterPoint, mySecondPoint);
  gp_Vec aDirectionN = aSecondVec ^ aFirstVec;
  gp_Vec aDirectionY = aFirstVec + aSecondVec;
  gp_Vec aDirectionX = aDirectionY ^ aDirectionN;

  myPlane = gp_Pln(gp_Ax3(myCenterPoint, gp_Dir(aDirectionN), gp_Dir(aDirectionX)));
}

const TCollection_AsciiString& PrsDim_AngleDimension::GetModelUnits() const
{
  return myDrawer->DimAngleModelUnits();
}

const TCollection_AsciiString& PrsDim_AngleDimension::GetDisplayUnits() const
{
  return myDrawer->DimAngleDisplayUnits();
}

void PrsDim_AngleDimension::SetModelUnits(const TCollection_AsciiString& theUnits)
{
  myDrawer->SetDimAngleModelUnits(theUnits);
}

void PrsDim_AngleDimension::SetDisplayUnits(const TCollection_AsciiString& theUnits)
{
  myDrawer->SetDimAngleDisplayUnits(theUnits);
}

double PrsDim_AngleDimension::ComputeValue() const
{
  if (!IsValid())
  {
    return 0.0;
  }

  gp_Vec aVec1(myCenterPoint, myFirstPoint);
  gp_Vec aVec2(myCenterPoint, mySecondPoint);

  double anAngle = aVec1.AngleWithRef(aVec2, GetNormalForMinAngle());

  return anAngle > 0.0 ? anAngle : (2.0 * M_PI + anAngle);
}

void PrsDim_AngleDimension::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                    const occ::handle<Prs3d_Presentation>& thePresentation,
                                    const int                              theMode)
{
  mySelectionGeom.Clear(theMode);

  if (!IsValid())
  {
    return;
  }

  occ::handle<Prs3d_DimensionAspect> aDimensionAspect = myDrawer->DimensionAspect();

  thePresentation->CurrentGroup()->SetPrimitivesAspect(aDimensionAspect->LineAspect()->Aspect());

  double anArrowLength = aDimensionAspect->ArrowAspect()->Length();

  double                     aLabelWidth;
  TCollection_ExtendedString aLabelString = GetValueString(aLabelWidth);

  if (aDimensionAspect->IsText3d())
  {
    aLabelWidth += aDimensionAspect->TextAspect()->Height() * THE_3D_TEXT_MARGIN * 2.0;
  }

  double                                anExtensionSize = aDimensionAspect->ExtensionSize();
  Prs3d_DimensionTextHorizontalPosition aHorisontalTextPos =
    aDimensionAspect->TextHorizontalPosition();

  if (IsTextPositionCustom())
  {
    AdjustParameters(myFixedTextPosition, anExtensionSize, aHorisontalTextPos, myFlyout);
  }

  bool isArrowsExternal = false;
  int  aLabelPosition   = LabelPosition_None;

  FitTextAlignment(aHorisontalTextPos, aLabelPosition, isArrowsExternal);

  gp_Pnt aFirstAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, myFirstPoint).Normalized() * GetFlyout());
  gp_Pnt aSecondAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, mySecondPoint).Normalized() * GetFlyout());

  gp_Vec aWorkingPlaneDir(GetNormalForMinAngle());

  gp_Dir aFirstExtensionDir  = aWorkingPlaneDir.Reversed() ^ gp_Vec(myCenterPoint, aFirstAttach);
  gp_Dir aSecondExtensionDir = aWorkingPlaneDir ^ gp_Vec(myCenterPoint, aSecondAttach);

  gp_Vec aFirstArrowVec  = gp_Vec(aFirstExtensionDir) * anArrowLength;
  gp_Vec aSecondArrowVec = gp_Vec(aSecondExtensionDir) * anArrowLength;

  if (isArrowsExternal)
  {
    aFirstArrowVec.Reverse();
    aSecondArrowVec.Reverse();
  }

  gp_Pnt aFirstArrowBegin(0.0, 0.0, 0.0);
  gp_Pnt aFirstArrowEnd(0.0, 0.0, 0.0);
  gp_Pnt aSecondArrowBegin(0.0, 0.0, 0.0);
  gp_Pnt aSecondArrowEnd(0.0, 0.0, 0.0);

  aFirstArrowBegin  = aFirstAttach;
  aSecondArrowBegin = aSecondAttach;
  aFirstArrowEnd    = aFirstAttach;
  aSecondArrowEnd   = aSecondAttach;

  if (aDimensionAspect->ArrowAspect()->IsZoomable())
  {
    aFirstArrowEnd.Translate(-aFirstArrowVec);
    aSecondArrowEnd.Translate(-aSecondArrowVec);
  }

  thePresentation->NewGroup();

  int aHPosition = aLabelPosition & LabelPosition_HMask;

  switch (aHPosition)
  {
    case LabelPosition_HCenter:
    {
      bool isLineBreak = aDimensionAspect->TextVerticalPosition() == Prs3d_DTVP_Center
                         && aDimensionAspect->IsText3d();

      if (isLineBreak)
      {
        DrawArcWithText(thePresentation,
                        aFirstAttach,
                        aSecondAttach,
                        myCenterPoint,
                        aLabelString,
                        aLabelWidth,
                        theMode,
                        aLabelPosition);
        break;
      }

      if (theMode == ComputeMode_All || theMode == ComputeMode_Text)
      {
        gp_Vec aDimensionDir(aFirstAttach, aSecondAttach);
        gp_Pnt aTextPos = IsTextPositionCustom()
                            ? myFixedTextPosition
                            : GetCenterOnArc(aFirstAttach, aSecondAttach, myCenterPoint);
        gp_Dir aTextDir = aDimensionDir;

        drawText(thePresentation, aTextPos, aTextDir, aLabelString, aLabelPosition);
      }

      if (theMode == ComputeMode_All || theMode == ComputeMode_Line)
      {
        DrawArc(thePresentation,
                (isArrowsExternal || !isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_First))
                  ? aFirstAttach
                  : aFirstArrowEnd,
                (isArrowsExternal || !isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_Second))
                  ? aSecondAttach
                  : aSecondArrowEnd,
                myCenterPoint,
                std::abs(GetFlyout()),
                theMode);
      }
    }
    break;

    case LabelPosition_Left:
    {
      DrawExtension(thePresentation,
                    anExtensionSize,
                    (isArrowsExternal && isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_First))
                      ? aFirstArrowEnd
                      : aFirstAttach,
                    aFirstExtensionDir,
                    aLabelString,
                    aLabelWidth,
                    theMode,
                    aLabelPosition);
    }
    break;

    case LabelPosition_Right:
    {
      DrawExtension(thePresentation,
                    anExtensionSize,
                    (isArrowsExternal && isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_Second))
                      ? aSecondArrowEnd
                      : aSecondAttach,
                    aSecondExtensionDir,
                    aLabelString,
                    aLabelWidth,
                    theMode,
                    aLabelPosition);
    }
    break;
  }

  if ((theMode == ComputeMode_All || theMode == ComputeMode_Line)
      && aHPosition != LabelPosition_HCenter)
  {
    thePresentation->NewGroup();

    DrawArc(thePresentation,
            (isArrowsExternal || !isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_First))
              ? aFirstAttach
              : aFirstArrowEnd,
            (isArrowsExternal || !isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_Second))
              ? aSecondAttach
              : aSecondArrowEnd,
            myCenterPoint,
            std::abs(GetFlyout()),
            theMode);
  }

  if (theMode == ComputeMode_All || theMode == ComputeMode_Line)
  {
    thePresentation->NewGroup();

    if (isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_First))
      DrawArrow(thePresentation, aFirstArrowBegin, gp_Dir(aFirstArrowVec));
    if (isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_Second))
      DrawArrow(thePresentation, aSecondArrowBegin, gp_Dir(aSecondArrowVec));
  }

  if ((theMode == ComputeMode_All || theMode == ComputeMode_Line) && isArrowsExternal)
  {
    thePresentation->NewGroup();

    if (aHPosition != LabelPosition_Left && isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_First))
    {
      DrawExtension(thePresentation,
                    aDimensionAspect->ArrowTailSize(),
                    aFirstArrowEnd,
                    aFirstExtensionDir,
                    TCollection_ExtendedString::EmptyString(),
                    THE_EMPTY_LABEL_WIDTH,
                    theMode,
                    LabelPosition_None);
    }

    if (aHPosition != LabelPosition_Right
        && isArrowVisible(PrsDim_TypeOfAngleArrowVisibility_Second))
    {
      DrawExtension(thePresentation,
                    aDimensionAspect->ArrowTailSize(),
                    aSecondArrowEnd,
                    aSecondExtensionDir,
                    TCollection_ExtendedString::EmptyString(),
                    THE_EMPTY_LABEL_WIDTH,
                    theMode,
                    LabelPosition_None);
    }
  }

  if (theMode == ComputeMode_All)
  {
    thePresentation->NewGroup();

    occ::handle<Graphic3d_ArrayOfSegments> aPrimSegments = new Graphic3d_ArrayOfSegments(4);
    aPrimSegments->AddVertex(myCenterPoint);
    aPrimSegments->AddVertex(aFirstAttach);
    aPrimSegments->AddVertex(myCenterPoint);
    aPrimSegments->AddVertex(aSecondAttach);

    occ::handle<Graphic3d_AspectLine3d> aFlyoutStyle =
      myDrawer->DimensionAspect()->LineAspect()->Aspect();
    thePresentation->CurrentGroup()->SetPrimitivesAspect(aFlyoutStyle);
    thePresentation->CurrentGroup()->AddPrimitiveArray(aPrimSegments);
  }

  mySelectionGeom.IsComputed = true;
}

void PrsDim_AngleDimension::ComputeFlyoutSelection(
  const occ::handle<SelectMgr_Selection>&   theSelection,
  const occ::handle<SelectMgr_EntityOwner>& theOwner)
{
  gp_Pnt aFirstAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, myFirstPoint).Normalized() * GetFlyout());
  gp_Pnt aSecondAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, mySecondPoint).Normalized() * GetFlyout());

  occ::handle<Select3D_SensitiveGroup> aSensitiveEntity = new Select3D_SensitiveGroup(theOwner);
  aSensitiveEntity->Add(new Select3D_SensitiveSegment(theOwner, myCenterPoint, aFirstAttach));
  aSensitiveEntity->Add(new Select3D_SensitiveSegment(theOwner, myCenterPoint, aSecondAttach));

  theSelection->Add(aSensitiveEntity);
}

bool PrsDim_AngleDimension::InitTwoEdgesAngle(gp_Pln& theComputedPlane)
{
  TopoDS_Edge aFirstEdge  = TopoDS::Edge(myFirstShape);
  TopoDS_Edge aSecondEdge = TopoDS::Edge(mySecondShape);

  BRepAdaptor_Curve aMakeFirstLine(aFirstEdge);
  BRepAdaptor_Curve aMakeSecondLine(aSecondEdge);

  if (aMakeFirstLine.GetType() != GeomAbs_Line || aMakeSecondLine.GetType() != GeomAbs_Line)
  {
    return false;
  }

  occ::handle<Geom_Line> aFirstLine  = new Geom_Line(aMakeFirstLine.Line());
  occ::handle<Geom_Line> aSecondLine = new Geom_Line(aMakeSecondLine.Line());

  gp_Lin aFirstLin  = aFirstLine->Lin();
  gp_Lin aSecondLin = aSecondLine->Lin();

  bool isParallelLines =
    aFirstLin.Direction().IsParallel(aSecondLin.Direction(), Precision::Angular());

  theComputedPlane = isParallelLines
                       ? gp_Pln(gp::XOY())
                       : gp_Pln(aSecondLin.Location(),
                                gp_Vec(aFirstLin.Direction()) ^ gp_Vec(aSecondLin.Direction()));

  bool                    isInfinite1, isInfinite2;
  gp_Pnt                  aFirstPoint1, aLastPoint1, aFirstPoint2, aLastPoint2;
  occ::handle<Geom_Curve> aFirstCurve = aFirstLine, aSecondCurve = aSecondLine;
  if (!PrsDim::ComputeGeometry(aFirstEdge,
                               aSecondEdge,
                               aFirstCurve,
                               aSecondCurve,
                               aFirstPoint1,
                               aLastPoint1,
                               aFirstPoint2,
                               aLastPoint2,
                               isInfinite1,
                               isInfinite2))
  {
    return false;
  }

  bool isSameLines = aFirstLin.Direction().IsEqual(aSecondLin.Direction(), Precision::Angular())
                     && aFirstLin.Location().IsEqual(aSecondLin.Location(), Precision::Confusion());

  bool isSameEdges = (aFirstPoint1.IsEqual(aFirstPoint2, Precision::Confusion())
                      && aLastPoint1.IsEqual(aLastPoint2, Precision::Confusion()))
                     || (aFirstPoint1.IsEqual(aLastPoint2, Precision::Confusion())
                         && aLastPoint1.IsEqual(aFirstPoint2, Precision::Confusion()));

  if (isParallelLines)
  {

    if (isSameLines && isSameEdges)
    {
      return false;
    }

    const double aParam11 = ElCLib::Parameter(aFirstLin, aFirstPoint1);
    const double aParam12 = ElCLib::Parameter(aFirstLin, aLastPoint1);
    const double aParam21 = ElCLib::Parameter(aFirstLin, aFirstPoint2);
    const double aParam22 = ElCLib::Parameter(aFirstLin, aLastPoint2);
    myCenterPoint =
      ElCLib::Value((std::min(aParam11, aParam12) + std::max(aParam21, aParam22)) * 0.5, aFirstLin);
    myFirstPoint  = myCenterPoint.Translated(gp_Vec(aFirstLin.Direction()) * std::abs(GetFlyout()));
    mySecondPoint = myCenterPoint.XYZ()
                    + (aFirstLin.Direction().IsEqual(aSecondLin.Direction(), Precision::Angular())
                         ? aFirstLin.Direction().Reversed().XYZ() * std::abs(GetFlyout())
                         : aSecondLin.Direction().XYZ() * std::abs(GetFlyout()));
  }
  else
  {

    gp_Lin2d aFirstLin2d  = ProjLib::Project(theComputedPlane, aFirstLin);
    gp_Lin2d aSecondLin2d = ProjLib::Project(theComputedPlane, aSecondLin);

    IntAna2d_AnaIntersection anInt2d(aFirstLin2d, aSecondLin2d);
    gp_Pnt2d                 anIntersectPoint;
    if (!anInt2d.IsDone() || anInt2d.IsEmpty())
    {
      return false;
    }

    anIntersectPoint = gp_Pnt2d(anInt2d.Point(1).Value());
    myCenterPoint    = ElCLib::To3d(theComputedPlane.Position().Ax2(), anIntersectPoint);

    if (isInfinite1 || isInfinite2)
    {
      myFirstPoint =
        myCenterPoint.Translated(gp_Vec(aFirstLin.Direction()) * std::abs(GetFlyout()));
      mySecondPoint =
        myCenterPoint.Translated(gp_Vec(aSecondLin.Direction()) * std::abs(GetFlyout()));

      return IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);
    }

    myFirstPoint = myCenterPoint.Distance(aFirstPoint1) > myCenterPoint.Distance(aLastPoint1)
                     ? aFirstPoint1
                     : aLastPoint1;

    mySecondPoint = myCenterPoint.Distance(aFirstPoint2) > myCenterPoint.Distance(aLastPoint2)
                      ? aFirstPoint2
                      : aLastPoint2;
  }

  return IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);
}

bool PrsDim_AngleDimension::InitTwoFacesAngle()
{
  TopoDS_Face aFirstFace  = TopoDS::Face(myFirstShape);
  TopoDS_Face aSecondFace = TopoDS::Face(mySecondShape);

  gp_Pln                    aFirstPln, aSecondPln;
  occ::handle<Geom_Surface> aFirstBasisSurf, aSecondBasisSurf;
  PrsDim_KindOfSurface      aFirstSurfType, aSecondSurfType;
  double                    aFirstOffset, aSecondOffset;

  PrsDim::GetPlaneFromFace(aFirstFace, aFirstPln, aFirstBasisSurf, aFirstSurfType, aFirstOffset);

  PrsDim::GetPlaneFromFace(aSecondFace,
                           aSecondPln,
                           aSecondBasisSurf,
                           aSecondSurfType,
                           aSecondOffset);

  if (aFirstSurfType == PrsDim_KOS_Plane && aSecondSurfType == PrsDim_KOS_Plane)
  {

    occ::handle<Geom_Plane> aFirstPlane  = occ::down_cast<Geom_Plane>(aFirstBasisSurf);
    occ::handle<Geom_Plane> aSecondPlane = occ::down_cast<Geom_Plane>(aSecondBasisSurf);
    return PrsDim::InitAngleBetweenPlanarFaces(aFirstFace,
                                               aSecondFace,
                                               myCenterPoint,
                                               myFirstPoint,
                                               mySecondPoint)
           && IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);
  }
  else
  {

    return PrsDim::InitAngleBetweenCurvilinearFaces(aFirstFace,
                                                    aSecondFace,
                                                    aFirstSurfType,
                                                    aSecondSurfType,
                                                    myCenterPoint,
                                                    myFirstPoint,
                                                    mySecondPoint)
           && IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);
  }
}

bool PrsDim_AngleDimension::InitTwoFacesAngle(const gp_Pnt& thePointOnFirstFace)
{
  TopoDS_Face aFirstFace  = TopoDS::Face(myFirstShape);
  TopoDS_Face aSecondFace = TopoDS::Face(mySecondShape);

  gp_Pln                    aFirstPln, aSecondPln;
  occ::handle<Geom_Surface> aFirstBasisSurf, aSecondBasisSurf;
  PrsDim_KindOfSurface      aFirstSurfType, aSecondSurfType;
  double                    aFirstOffset, aSecondOffset;

  PrsDim::GetPlaneFromFace(aFirstFace, aFirstPln, aFirstBasisSurf, aFirstSurfType, aFirstOffset);

  PrsDim::GetPlaneFromFace(aSecondFace,
                           aSecondPln,
                           aSecondBasisSurf,
                           aSecondSurfType,
                           aSecondOffset);

  myFirstPoint = thePointOnFirstFace;
  if (aFirstSurfType == PrsDim_KOS_Plane && aSecondSurfType == PrsDim_KOS_Plane)
  {

    occ::handle<Geom_Plane> aFirstPlane  = occ::down_cast<Geom_Plane>(aFirstBasisSurf);
    occ::handle<Geom_Plane> aSecondPlane = occ::down_cast<Geom_Plane>(aSecondBasisSurf);
    return PrsDim::InitAngleBetweenPlanarFaces(aFirstFace,
                                               aSecondFace,
                                               myCenterPoint,
                                               myFirstPoint,
                                               mySecondPoint,
                                               true)
           && IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);
  }
  else
  {

    return PrsDim::InitAngleBetweenCurvilinearFaces(aFirstFace,
                                                    aSecondFace,
                                                    aFirstSurfType,
                                                    aSecondSurfType,
                                                    myCenterPoint,
                                                    myFirstPoint,
                                                    mySecondPoint,
                                                    true)
           && IsValidPoints(myFirstPoint, myCenterPoint, mySecondPoint);
  }
}

bool PrsDim_AngleDimension::InitConeAngle()
{
  if (myFirstShape.IsNull())
  {
    return false;
  }

  TopoDS_Face aConeShape = TopoDS::Face(myFirstShape);
  gp_Pln      aPln;
  gp_Cone     aCone;
  gp_Circ     aCircle;

  occ::handle<Geom_Surface>             aSurf;
  occ::handle<Geom_OffsetSurface>       aOffsetSurf;
  occ::handle<Geom_ConicalSurface>      aConicalSurf;
  occ::handle<Geom_SurfaceOfRevolution> aRevSurf;
  occ::handle<Geom_Line>                aLine;
  BRepAdaptor_Surface                   aConeAdaptor(aConeShape);
  TopoDS_Face                           aFace;
  PrsDim_KindOfSurface                  aSurfType;
  double                                anOffset = 0.;
  occ::handle<Standard_Type>            aType;

  const double aMaxV = aConeAdaptor.FirstVParameter();
  const double aMinV = aConeAdaptor.LastVParameter();
  PrsDim::GetPlaneFromFace(aConeShape, aPln, aSurf, aSurfType, anOffset);
  if (aSurfType == PrsDim_KOS_Revolution)
  {

    aRevSurf = occ::down_cast<Geom_SurfaceOfRevolution>(aSurf);
    gp_Lin                  aLin(aRevSurf->Axis());
    occ::handle<Geom_Curve> aBasisCurve = aRevSurf->BasisCurve();

    if (aBasisCurve->DynamicType() != STANDARD_TYPE(Geom_Line))
      return false;

    gp_Pnt aFirst1 = aConeAdaptor.Value(0., aMinV);
    gp_Pnt aLast1  = aConeAdaptor.Value(0., aMaxV);
    gp_Vec aVec1(aFirst1, aLast1);

    gp_Pnt aFirst2 = ElCLib::Value(ElCLib::Parameter(aLin, aFirst1), aLin);

    gp_Pnt aLast2 = ElCLib::Value(ElCLib::Parameter(aLin, aLast1), aLin);

    gp_Vec aVec2(aFirst2, aLast2);

    if (aVec1.IsParallel(aVec2, Precision::Angular())
        || aVec1.IsNormal(aVec2, Precision::Angular()))
      return false;

    gce_MakeCone aMkCone(aRevSurf->Axis(), aFirst1, aLast1);
    aCone         = aMkCone.Value();
    myCenterPoint = aCone.Apex();
  }
  else
  {
    aType = aSurf->DynamicType();
    if (aType == STANDARD_TYPE(Geom_OffsetSurface) || anOffset > 0.01)
    {

      aOffsetSurf = new Geom_OffsetSurface(aSurf, anOffset);
      aSurf       = aOffsetSurf->Surface();
      BRepBuilderAPI_MakeFace aMkFace(aSurf, Precision::Confusion());
      aMkFace.Build();
      if (!aMkFace.IsDone())
        return false;
      aConeAdaptor.Initialize(aMkFace.Face());
    }
    aCone         = aConeAdaptor.Cone();
    aConicalSurf  = occ::down_cast<Geom_ConicalSurface>(aSurf);
    myCenterPoint = aConicalSurf->Apex();
  }

  occ::handle<Geom_Curve> aCurve;
  double                  aMidV = (aMinV + aMaxV) / 2.5;
  aCurve                        = aSurf->VIso(aMidV);
  aCircle                       = occ::down_cast<Geom_Circle>(aCurve)->Circ();

  aCurve            = aSurf->VIso(aMaxV);
  gp_Circ aCircVmax = occ::down_cast<Geom_Circle>(aCurve)->Circ();
  aCurve            = aSurf->VIso(aMinV);
  gp_Circ aCircVmin = occ::down_cast<Geom_Circle>(aCurve)->Circ();

  if (aCircVmax.Radius() < aCircVmin.Radius())
  {
    gp_Circ aTmpCirc = aCircVmax;
    aCircVmax        = aCircVmin;
    aCircVmin        = aTmpCirc;
  }

  myFirstPoint  = ElCLib::Value(0, aCircle);
  mySecondPoint = ElCLib::Value(M_PI, aCircle);
  return true;
}

bool PrsDim_AngleDimension::IsValidPoints(const gp_Pnt& theFirstPoint,
                                          const gp_Pnt& theCenterPoint,
                                          const gp_Pnt& theSecondPoint) const
{
  return theFirstPoint.Distance(theCenterPoint) > Precision::Confusion()
         && theSecondPoint.Distance(theCenterPoint) > Precision::Confusion()
         && gp_Vec(theCenterPoint, theFirstPoint).Angle(gp_Vec(theCenterPoint, theSecondPoint))
              > Precision::Angular();
}

bool PrsDim_AngleDimension::isArrowVisible(
  const PrsDim_TypeOfAngleArrowVisibility theArrowType) const
{
  switch (theArrowType)
  {
    case PrsDim_TypeOfAngleArrowVisibility_Both:
      return myArrowsVisibility == PrsDim_TypeOfAngleArrowVisibility_Both;
    case PrsDim_TypeOfAngleArrowVisibility_First:
      return myArrowsVisibility == PrsDim_TypeOfAngleArrowVisibility_Both
             || myArrowsVisibility == PrsDim_TypeOfAngleArrowVisibility_First;
    case PrsDim_TypeOfAngleArrowVisibility_Second:
      return myArrowsVisibility == PrsDim_TypeOfAngleArrowVisibility_Both
             || myArrowsVisibility == PrsDim_TypeOfAngleArrowVisibility_Second;
    case PrsDim_TypeOfAngleArrowVisibility_None:
      return false;
  }
  return false;
}

gp_Pnt PrsDim_AngleDimension::GetTextPosition() const
{
  if (!IsValid())
  {
    return gp::Origin();
  }

  if (IsTextPositionCustom())
  {
    return myFixedTextPosition;
  }

  gp_Pnt aTextPosition(gp::Origin());

  occ::handle<Prs3d_DimensionAspect> aDimensionAspect = myDrawer->DimensionAspect();

  double                     aLabelWidth;
  TCollection_ExtendedString aLabelString = GetValueString(aLabelWidth);

  gp_Pnt aFirstAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, myFirstPoint).Normalized() * GetFlyout());
  gp_Pnt aSecondAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, mySecondPoint).Normalized() * GetFlyout());

  bool isArrowsExternal = false;
  int  aLabelPosition   = LabelPosition_None;
  FitTextAlignment(aDimensionAspect->TextHorizontalPosition(), aLabelPosition, isArrowsExternal);

  switch (aLabelPosition & LabelPosition_HMask)
  {
    case LabelPosition_HCenter:
    {
      aTextPosition = GetCenterOnArc(aFirstAttach, aSecondAttach, myCenterPoint);
    }
    break;
    case LabelPosition_Left:
    {
      gp_Dir aPlaneNormal =
        gp_Vec(aFirstAttach, aSecondAttach) ^ gp_Vec(myCenterPoint, aFirstAttach);
      gp_Dir anExtensionDir  = aPlaneNormal ^ gp_Vec(myCenterPoint, aFirstAttach);
      double anExtensionSize = aDimensionAspect->ExtensionSize();
      double anOffset        = isArrowsExternal
                                 ? anExtensionSize + aDimensionAspect->ArrowAspect()->Length()
                                 : anExtensionSize;
      gp_Vec anExtensionVec  = gp_Vec(anExtensionDir) * -anOffset;
      aTextPosition          = aFirstAttach.Translated(anExtensionVec);
    }
    break;
    case LabelPosition_Right:
    {
      gp_Dir aPlaneNormal =
        gp_Vec(aFirstAttach, aSecondAttach) ^ gp_Vec(myCenterPoint, aFirstAttach);
      gp_Dir anExtensionDir  = aPlaneNormal ^ gp_Vec(myCenterPoint, aSecondAttach);
      double anExtensionSize = aDimensionAspect->ExtensionSize();
      double anOffset        = isArrowsExternal
                                 ? anExtensionSize + aDimensionAspect->ArrowAspect()->Length()
                                 : anExtensionSize;
      gp_Vec anExtensionVec  = gp_Vec(anExtensionDir) * anOffset;
      aTextPosition          = aSecondAttach.Translated(anExtensionVec);
    }
    break;
  }

  return aTextPosition;
}

void PrsDim_AngleDimension::SetTextPosition(const gp_Pnt& theTextPos)
{
  if (!IsValid())
  {
    return;
  }

  if (!GetPlane().Contains(theTextPos, Precision::Confusion()))
  {
    throw Standard_ProgramError(
      "The text position point for angle dimension doesn't belong to the working plane.");
  }

  myIsTextPositionFixed = true;
  myFixedTextPosition   = theTextPos;
}

void PrsDim_AngleDimension::AdjustParameters(const gp_Pnt& theTextPos,
                                             double&       theExtensionSize,
                                             Prs3d_DimensionTextHorizontalPosition& theAlignment,
                                             double&                                theFlyout) const
{
  occ::handle<Prs3d_DimensionAspect> aDimensionAspect = myDrawer->DimensionAspect();
  double                             anArrowLength    = aDimensionAspect->ArrowAspect()->Length();

  double aRadius = gp_Vec(myCenterPoint, theTextPos).Magnitude();

  gp_Pnt aFirstAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, myFirstPoint).Normalized() * aRadius);
  gp_Pnt aSecondAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, mySecondPoint).Normalized() * aRadius);

  gce_MakeCirc aConstructCircle(myCenterPoint, GetPlane(), aRadius);
  if (!aConstructCircle.IsDone())
  {
    return;
  }
  gp_Circ aCircle = aConstructCircle.Value();

  theExtensionSize = aDimensionAspect->ArrowAspect()->Length();
  theAlignment     = Prs3d_DTHP_Center;

  double aParamBeg = ElCLib::Parameter(aCircle, aFirstAttach);
  double aParamEnd = ElCLib::Parameter(aCircle, aSecondAttach);
  if (aParamEnd < aParamBeg)
  {
    double aParam = aParamEnd;
    aParamEnd     = aParamBeg;
    aParamBeg     = aParam;
  }

  ElCLib::AdjustPeriodic(0.0, M_PI * 2, Precision::PConfusion(), aParamBeg, aParamEnd);
  double aTextPar = ElCLib::Parameter(aCircle, theTextPos);

  if (aTextPar > aParamBeg && aTextPar < aParamEnd)
  {
    theFlyout = aRadius;
    return;
  }

  aParamBeg += M_PI;
  aParamEnd += M_PI;
  ElCLib::AdjustPeriodic(0.0, M_PI * 2, Precision::PConfusion(), aParamBeg, aParamEnd);

  if (aTextPar > aParamBeg && aTextPar < aParamEnd)
  {
    theFlyout = -aRadius;
    return;
  }

  gp_Lin aFirstLine      = gce_MakeLin(myCenterPoint, myFirstPoint);
  gp_Lin aSecondLine     = gce_MakeLin(myCenterPoint, mySecondPoint);
  gp_Pnt aFirstTextProj  = PrsDim::Nearest(aFirstLine, theTextPos);
  gp_Pnt aSecondTextProj = PrsDim::Nearest(aSecondLine, theTextPos);
  double aFirstDist      = aFirstTextProj.Distance(theTextPos);
  double aSecondDist     = aSecondTextProj.Distance(theTextPos);

  if (aFirstDist <= aSecondDist)
  {
    aRadius                  = myCenterPoint.Distance(aFirstTextProj);
    double aNewExtensionSize = aFirstDist - anArrowLength;
    theExtensionSize         = aNewExtensionSize < 0.0 ? 0.0 : aNewExtensionSize;

    theAlignment = Prs3d_DTHP_Left;

    gp_Vec aPosFlyoutDir = gp_Vec(myCenterPoint, myFirstPoint).Normalized().Scaled(aRadius);

    theFlyout =
      aFirstTextProj.Distance(myCenterPoint.Translated(aPosFlyoutDir)) > Precision::Confusion()
        ? -aRadius
        : aRadius;
  }
  else
  {
    aRadius = myCenterPoint.Distance(aSecondTextProj);

    double aNewExtensionSize = aSecondDist - anArrowLength;

    theExtensionSize = aNewExtensionSize < 0.0 ? 0.0 : aNewExtensionSize;

    theAlignment = Prs3d_DTHP_Right;

    gp_Vec aPosFlyoutDir = gp_Vec(myCenterPoint, mySecondPoint).Normalized().Scaled(aRadius);

    theFlyout =
      aSecondTextProj.Distance(myCenterPoint.Translated(aPosFlyoutDir)) > Precision::Confusion()
        ? -aRadius
        : aRadius;
  }
}

void PrsDim_AngleDimension::FitTextAlignment(
  const Prs3d_DimensionTextHorizontalPosition& theHorizontalTextPos,
  int&                                         theLabelPosition,
  bool&                                        theIsArrowsExternal) const
{
  occ::handle<Prs3d_DimensionAspect> aDimensionAspect = myDrawer->DimensionAspect();

  double anArrowLength = aDimensionAspect->ArrowAspect()->Length();

  double                     aLabelWidth;
  TCollection_ExtendedString aLabelString = GetValueString(aLabelWidth);

  if (aDimensionAspect->IsText3d())
  {
    aLabelWidth += aDimensionAspect->TextAspect()->Height() * THE_3D_TEXT_MARGIN * 2.0;
  }

  gp_Pnt aFirstAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, myFirstPoint).Normalized() * GetFlyout());
  gp_Pnt aSecondAttach =
    myCenterPoint.Translated(gp_Vec(myCenterPoint, mySecondPoint).Normalized() * GetFlyout());

  switch (aDimensionAspect->ArrowOrientation())
  {
    case Prs3d_DAO_External:
      theIsArrowsExternal = true;
      break;
    case Prs3d_DAO_Internal:
      theIsArrowsExternal = false;
      break;
    case Prs3d_DAO_Fit:
    {
      gp_Vec anAttachVector(aFirstAttach, aSecondAttach);
      double aDimensionWidth = anAttachVector.Magnitude();

      double anArrowMargin = aDimensionAspect->IsText3d()
                               ? aDimensionAspect->TextAspect()->Height() * THE_3D_TEXT_MARGIN
                               : 0.0;

      double anArrowsWidth = (anArrowLength + anArrowMargin) * 2.0;

      theIsArrowsExternal = aDimensionWidth < aLabelWidth + anArrowsWidth;
      break;
    }
  }

  switch (theHorizontalTextPos)
  {
    case Prs3d_DTHP_Left:
      theLabelPosition |= LabelPosition_Left;
      break;
    case Prs3d_DTHP_Right:
      theLabelPosition |= LabelPosition_Right;
      break;
    case Prs3d_DTHP_Center:
      theLabelPosition |= LabelPosition_HCenter;
      break;
    case Prs3d_DTHP_Fit:
    {
      gp_Vec anAttachVector(aFirstAttach, aSecondAttach);
      double aDimensionWidth = anAttachVector.Magnitude();
      double anArrowsWidth   = anArrowLength * 2.0;
      double aContentWidth   = theIsArrowsExternal ? aLabelWidth : aLabelWidth + anArrowsWidth;

      theLabelPosition |=
        aDimensionWidth < aContentWidth ? LabelPosition_Left : LabelPosition_HCenter;
      break;
    }
  }

  switch (aDimensionAspect->TextVerticalPosition())
  {
    case Prs3d_DTVP_Above:
      theLabelPosition |= LabelPosition_Above;
      break;
    case Prs3d_DTVP_Below:
      theLabelPosition |= LabelPosition_Below;
      break;
    case Prs3d_DTVP_Center:
      theLabelPosition |= LabelPosition_VCenter;
      break;
  }
}
