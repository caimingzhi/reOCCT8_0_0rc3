#include <AIS_Line.hpp>

#include <AIS_GraphicTool.hpp>
#include <Aspect_TypeOfLine.hpp>
#include <Geom_Line.hpp>
#include <Geom_Point.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_Structure.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Quantity_Color.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <Standard_Type.hpp>
#include <StdPrs_Curve.hpp>
#include <UnitsAPI.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_Line, AIS_InteractiveObject)

//=================================================================================================

AIS_Line::AIS_Line(const occ::handle<Geom_Line>& aComponent)
    : myComponent(aComponent),
      myLineIsSegment(false)
{
  SetInfiniteState();
}

//=================================================================================================

AIS_Line::AIS_Line(const occ::handle<Geom_Point>& aStartPoint,
                   const occ::handle<Geom_Point>& aEndPoint)
    : myStartPoint(aStartPoint),
      myEndPoint(aEndPoint),
      myLineIsSegment(true)
{
}

//=================================================================================================

void AIS_Line::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                       const occ::handle<Prs3d_Presentation>& thePrs,
                       const int)
{
  if (!myLineIsSegment)
  {
    ComputeInfiniteLine(thePrs);
  }
  else
  {
    ComputeSegmentLine(thePrs);
  }
}

//=================================================================================================

void AIS_Line::ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                                const int                               theMode)
{
  // Do not support selection modes different from 0 currently
  if (theMode)
    return;

  if (!myLineIsSegment)
  {
    ComputeInfiniteLineSelection(theSelection);
  }
  else
  {
    ComputeSegmentLineSelection(theSelection);
  }
}

//=================================================================================================

void AIS_Line::replaceWithNewLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect)
{
  if (!myDrawer->HasLink())
  {
    myDrawer->SetLineAspect(theAspect);
    return;
  }

  const occ::handle<Graphic3d_Aspects>& anAspectOld = myDrawer->LineAspect()->Aspect();
  const occ::handle<Graphic3d_Aspects>& anAspectNew =
    !theAspect.IsNull() ? theAspect->Aspect() : myDrawer->Link()->LineAspect()->Aspect();
  if (anAspectNew != anAspectOld)
  {
    myDrawer->SetLineAspect(theAspect);
    NCollection_DataMap<occ::handle<Graphic3d_Aspects>, occ::handle<Graphic3d_Aspects>> aReplaceMap;
    aReplaceMap.Bind(anAspectOld, anAspectNew);
    replaceAspects(aReplaceMap);
  }
}

//=================================================================================================

void AIS_Line::SetColor(const Quantity_Color& aCol)
{
  hasOwnColor = true;
  myDrawer->SetColor(aCol);

  double WW = HasWidth()            ? myOwnWidth
              : myDrawer->HasLink() ? AIS_GraphicTool::GetLineWidth(myDrawer->Link(), AIS_TOA_Line)
                                    : 1.;

  if (!myDrawer->HasOwnLineAspect())
  {
    replaceWithNewLineAspect(new Prs3d_LineAspect(aCol, Aspect_TOL_SOLID, WW));
  }
  else
  {
    myDrawer->LineAspect()->SetColor(aCol);
    SynchronizeAspects();
  }
}

//=================================================================================================

void AIS_Line::UnsetColor()
{
  hasOwnColor = false;

  if (!HasWidth())
  {
    replaceWithNewLineAspect(occ::handle<Prs3d_LineAspect>());
  }
  else
  {
    Quantity_Color CC = Quantity_NOC_YELLOW;
    if (HasColor())
      CC = myDrawer->Color();
    else if (myDrawer->HasLink())
      AIS_GraphicTool::GetLineColor(myDrawer->Link(), AIS_TOA_Line, CC);
    myDrawer->LineAspect()->SetColor(CC);
    myDrawer->SetColor(CC);
    SynchronizeAspects();
  }
}

//=================================================================================================

void AIS_Line::SetWidth(const double aValue)
{
  myOwnWidth = (float)aValue;

  if (!myDrawer->HasOwnLineAspect())
  {
    Quantity_Color CC = Quantity_NOC_YELLOW;
    if (HasColor())
      CC = myDrawer->Color();
    else if (myDrawer->HasLink())
      AIS_GraphicTool::GetLineColor(myDrawer->Link(), AIS_TOA_Line, CC);
    replaceWithNewLineAspect(new Prs3d_LineAspect(CC, Aspect_TOL_SOLID, aValue));
  }
  else
  {
    myDrawer->LineAspect()->SetWidth(aValue);
    SynchronizeAspects();
  }
}

//=================================================================================================

void AIS_Line::UnsetWidth()
{
  if (!HasColor())
  {
    replaceWithNewLineAspect(occ::handle<Prs3d_LineAspect>());
  }
  else
  {
    float WW = myDrawer->HasLink()
                 ? (float)AIS_GraphicTool::GetLineWidth(myDrawer->Link(), AIS_TOA_Line)
                 : 1.0f;
    myDrawer->LineAspect()->SetWidth(WW);
    myOwnWidth = WW;
    SynchronizeAspects();
  }
}

//=================================================================================================

void AIS_Line::ComputeInfiniteLine(const occ::handle<Prs3d_Presentation>& aPresentation)
{
  GeomAdaptor_Curve curv(myComponent);
  StdPrs_Curve::Add(aPresentation, curv, myDrawer);

  // pas de prise en compte lors du FITALL
  aPresentation->SetInfiniteState(true);
}

//=================================================================================================

void AIS_Line::ComputeSegmentLine(const occ::handle<Prs3d_Presentation>& aPresentation)
{
  gp_Pnt P1 = myStartPoint->Pnt();
  gp_Pnt P2 = myEndPoint->Pnt();

  myComponent = new Geom_Line(P1, gp_Dir(P2.XYZ() - P1.XYZ()));

  double            dist = P1.Distance(P2);
  GeomAdaptor_Curve curv(myComponent, 0., dist);
  StdPrs_Curve::Add(aPresentation, curv, myDrawer);
}

//=================================================================================================

void AIS_Line::ComputeInfiniteLineSelection(const occ::handle<SelectMgr_Selection>& aSelection)
{

  /*  // on calcule les points min max a partir desquels on cree un segment sensible...
    GeomAdaptor_Curve curv(myComponent);
    gp_Pnt P1,P2;
    FindLimits(curv,myDrawer->MaximalParameterValue(),P1,P2);
  */
  const gp_Dir& thedir  = myComponent->Position().Direction();
  const gp_Pnt& loc     = myComponent->Position().Location();
  const gp_XYZ& dir_xyz = thedir.XYZ();
  const gp_XYZ& loc_xyz = loc.XYZ();
  // POP  double aLength = UnitsAPI::CurrentToLS (250000. ,"LENGTH");
  double                                 aLength = UnitsAPI::AnyToLS(250000., "mm");
  gp_Pnt                                 P1      = loc_xyz + aLength * dir_xyz;
  gp_Pnt                                 P2      = loc_xyz - aLength * dir_xyz;
  occ::handle<SelectMgr_EntityOwner>     eown    = new SelectMgr_EntityOwner(this, 5);
  occ::handle<Select3D_SensitiveSegment> seg     = new Select3D_SensitiveSegment(eown, P1, P2);
  aSelection->Add(seg);
}

//=================================================================================================

void AIS_Line::ComputeSegmentLineSelection(const occ::handle<SelectMgr_Selection>& aSelection)
{

  occ::handle<SelectMgr_EntityOwner>     eown = new SelectMgr_EntityOwner(this, 5);
  occ::handle<Select3D_SensitiveSegment> seg =
    new Select3D_SensitiveSegment(eown, myStartPoint->Pnt(), myEndPoint->Pnt());
  aSelection->Add(seg);
}
