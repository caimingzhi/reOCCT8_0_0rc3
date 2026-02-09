#include <PrsDim.hpp>
#include <PrsDim_MaxRadiusDimension.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <DsgPrs_EllipseRadiusPresentation.hpp>
#include <ElCLib.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveBox.hpp>
#include <Select3D_SensitiveCurve.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_MaxRadiusDimension, PrsDim_EllipseRadiusDimension)

PrsDim_MaxRadiusDimension::PrsDim_MaxRadiusDimension(const TopoDS_Shape&               aShape,
                                                     const double                      aVal,
                                                     const TCollection_ExtendedString& aText)
    : PrsDim_EllipseRadiusDimension(aShape, aText)
{
  myVal               = aVal;
  mySymbolPrs         = DsgPrs_AS_LASTAR;
  myAutomaticPosition = true;
  myArrowSize         = myVal / 100.;
}

PrsDim_MaxRadiusDimension::PrsDim_MaxRadiusDimension(const TopoDS_Shape&               aShape,
                                                     const double                      aVal,
                                                     const TCollection_ExtendedString& aText,
                                                     const gp_Pnt&                     aPosition,
                                                     const DsgPrs_ArrowSide            aSymbolPrs,
                                                     const double                      anArrowSize)
    : PrsDim_EllipseRadiusDimension(aShape, aText)
{
  myVal               = aVal;
  mySymbolPrs         = aSymbolPrs;
  myPosition          = aPosition;
  myAutomaticPosition = false;
  SetArrowSize(anArrowSize);
}

void PrsDim_MaxRadiusDimension::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                        const occ::handle<Prs3d_Presentation>& aPresentation,
                                        const int)
{

  {
    ComputeGeometry();
    myEllipse.SetMajorRadius(myVal);
    gp_Vec v1(myEllipse.XAxis().Direction());
    v1 *= myVal;
    myApexP = myEllipse.Location().Translated(v1);
    myApexN = myEllipse.Location().Translated(-v1);
  }
  if (myIsAnArc)
    ComputeArcOfEllipse(aPresentation);
  else
    ComputeEllipse(aPresentation);
}

void PrsDim_MaxRadiusDimension::ComputeEllipse(const occ::handle<Prs3d_Presentation>& aPresentation)
{

  occ::handle<Prs3d_DimensionAspect> la  = myDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();

  if (!myArrowSizeIsDefined)
  {
    myArrowSize = std::min(myArrowSize, myVal / 5.);
  }
  arr->SetLength(myArrowSize);

  double U;
  gp_Pnt curPos, Center;
  Center = myEllipse.Location();
  if (myAutomaticPosition)
  {
    myPosition          = Center;
    myEndOfArrow        = myApexP;
    myAutomaticPosition = true;

    if (myIsSetBndBox)
      myPosition =
        PrsDim::TranslatePointToBound(myPosition, gp_Dir(gp_Vec(Center, myPosition)), myBndBox);
    curPos = myPosition;
  }
  else
  {
    curPos = myPosition;
    gp_Lin L1(myEllipse.XAxis());
    U      = ElCLib::Parameter(L1, curPos);
    curPos = ElCLib::Value(U, L1);
    if (curPos.Distance(myApexP) < curPos.Distance(myApexN))
      myEndOfArrow = myApexP;
    else
      myEndOfArrow = myApexN;
  }

  DsgPrs_EllipseRadiusPresentation::Add(aPresentation,
                                        myDrawer,
                                        myVal,
                                        myText,
                                        curPos,
                                        myEndOfArrow,
                                        Center,
                                        true,
                                        mySymbolPrs);
}

void PrsDim_MaxRadiusDimension::ComputeArcOfEllipse(
  const occ::handle<Prs3d_Presentation>& aPresentation)
{

  occ::handle<Prs3d_DimensionAspect> la  = myDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();

  if (!myArrowSizeIsDefined)
  {
    myArrowSize = std::min(myArrowSize, myVal / 5.);
  }
  arr->SetLength(myArrowSize);

  double par;
  gp_Pnt curPos, Center;
  Center          = myEllipse.Location();
  bool IsInDomain = true;
  if (myAutomaticPosition)
  {
    myEndOfArrow =
      PrsDim::NearestApex(myEllipse, myApexP, myApexN, myFirstPar, myLastPar, IsInDomain);
    myPosition          = Center;
    myAutomaticPosition = true;
    if (myIsSetBndBox)
      myPosition =
        PrsDim::TranslatePointToBound(myPosition, gp_Dir(gp_Vec(Center, myPosition)), myBndBox);
    curPos = myPosition;
  }
  else
  {
    curPos = myPosition;

    gp_Lin L1(myEllipse.XAxis());
    par    = ElCLib::Parameter(L1, curPos);
    curPos = ElCLib::Value(par, L1);
    if (curPos.Distance(myApexP) < curPos.Distance(myApexN))
      myEndOfArrow = myApexP;
    else
      myEndOfArrow = myApexN;
    par        = ElCLib::Parameter(myEllipse, myEndOfArrow);
    IsInDomain = PrsDim::InDomain(myFirstPar, myLastPar, par);
    myPosition = curPos;
  }

  double parStart = 0.;
  if (!IsInDomain)
  {
    if (PrsDim::DistanceFromApex(myEllipse, myEndOfArrow, myFirstPar)
        < PrsDim::DistanceFromApex(myEllipse, myEndOfArrow, myLastPar))
      parStart = myFirstPar;
    else
      parStart = myLastPar;
  }
  if (!myIsOffset)
    DsgPrs_EllipseRadiusPresentation::Add(aPresentation,
                                          myDrawer,
                                          myVal,
                                          myText,
                                          myEllipse,
                                          curPos,
                                          myEndOfArrow,
                                          Center,
                                          parStart,
                                          IsInDomain,
                                          true,
                                          mySymbolPrs);
  else
    DsgPrs_EllipseRadiusPresentation::Add(aPresentation,
                                          myDrawer,
                                          myVal,
                                          myText,
                                          myOffsetCurve,
                                          curPos,
                                          myEndOfArrow,
                                          Center,
                                          parStart,
                                          IsInDomain,
                                          true,
                                          mySymbolPrs);
}

void PrsDim_MaxRadiusDimension::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                                 const int)
{

  gp_Pnt center          = myEllipse.Location();
  gp_Pnt AttachmentPoint = myPosition;
  double dist            = center.Distance(AttachmentPoint);
  double aRadius         = myVal;

  gp_Pnt pt1;
  if (dist > aRadius)
    pt1 = AttachmentPoint;
  else
    pt1 = myEndOfArrow;
  occ::handle<SelectMgr_EntityOwner>     own = new SelectMgr_EntityOwner(this, 7);
  occ::handle<Select3D_SensitiveSegment> seg = new Select3D_SensitiveSegment(own, center, pt1);
  aSelection->Add(seg);

  double                             size(std::min(myVal / 100. + 1.e-6, myArrowSize + 1.e-6));
  occ::handle<Select3D_SensitiveBox> box = new Select3D_SensitiveBox(own,
                                                                     AttachmentPoint.X(),
                                                                     AttachmentPoint.Y(),
                                                                     AttachmentPoint.Z(),
                                                                     AttachmentPoint.X() + size,
                                                                     AttachmentPoint.Y() + size,
                                                                     AttachmentPoint.Z() + size);
  aSelection->Add(box);

  if (myIsAnArc)
  {

    double parEnd = ElCLib::Parameter(myEllipse, myEndOfArrow);
    if (!PrsDim::InDomain(myFirstPar, myLastPar, parEnd))
    {
      double parStart, par;
      if (PrsDim::DistanceFromApex(myEllipse, myEndOfArrow, myFirstPar)
          < PrsDim::DistanceFromApex(myEllipse, myEndOfArrow, myLastPar))
        par = myFirstPar;
      else
        par = myLastPar;
      gp_Vec Vapex(center, ElCLib::Value(parEnd, myEllipse));
      gp_Vec Vpnt(center, ElCLib::Value(par, myEllipse));
      gp_Dir dir(Vpnt ^ Vapex);
      if (myEllipse.Position().Direction().IsOpposite(dir, Precision::Angular()))
      {
        parStart = parEnd;
        parEnd   = par;
      }
      else
        parStart = par;

      occ::handle<Geom_Curve> TrimCurve;
      if (myIsOffset)
      {
        occ::handle<Geom_Curve> aCurve = myOffsetCurve;
        TrimCurve                      = new Geom_TrimmedCurve(aCurve, parStart, parEnd);
      }
      else
      {
        occ::handle<Geom_Ellipse> Ellipse = new Geom_Ellipse(myEllipse);
        TrimCurve                         = new Geom_TrimmedCurve(Ellipse, parStart, parEnd);
      }
      occ::handle<Select3D_SensitiveCurve> SensArc;
      SensArc = new Select3D_SensitiveCurve(own, TrimCurve);
      aSelection->Add(SensArc);
    }
  }
}
