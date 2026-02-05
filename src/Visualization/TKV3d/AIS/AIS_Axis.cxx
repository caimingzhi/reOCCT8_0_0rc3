#include <AIS_Axis.hpp>

#include <Aspect_TypeOfLine.hpp>
#include <DsgPrs_XYZAxisPresentation.hpp>
#include <Geom_Axis1Placement.hpp>
#include <Geom_Axis2Placement.hpp>
#include <Geom_Line.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_Structure.hpp>
#include <Prs3d_DatumAspect.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Quantity_Color.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <Standard_NumericError.hpp>
#include <StdPrs_Curve.hpp>
#include <UnitsAPI.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_Axis, AIS_InteractiveObject)

//=================================================================================================

AIS_Axis::AIS_Axis(const occ::handle<Geom_Line>& aComponent)
    : myComponent(aComponent),
      myTypeOfAxis(AIS_TOAX_Unknown),
      myIsXYZAxis(false)
{
  myDrawer->SetLineAspect(new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_DOTDASH, 1.));
  SetInfiniteState();

  gp_Dir thedir  = myComponent->Position().Direction();
  gp_Pnt loc     = myComponent->Position().Location();
  double aLength = UnitsAPI::AnyToLS(250000., "mm");
  myPfirst       = loc.XYZ() + aLength * thedir.XYZ();
  myPlast        = loc.XYZ() - aLength * thedir.XYZ();
}

//=======================================================================
// function : AIS_Axis
// purpose  :  Xaxis, YAxis, ZAxis
//=======================================================================
AIS_Axis::AIS_Axis(const occ::handle<Geom_Axis2Placement>& aComponent,
                   const AIS_TypeOfAxis                    anAxisType)
    : myAx2(aComponent),
      myTypeOfAxis(anAxisType),
      myIsXYZAxis(true)
{
  occ::handle<Prs3d_DatumAspect> DA = new Prs3d_DatumAspect();
  double                         aLength;
  try
  {
    aLength = UnitsAPI::AnyToLS(100., "mm");
  }
  catch (Standard_Failure const&)
  {
    aLength = 0.1;
  }
  DA->SetAxisLength(aLength, aLength, aLength);
  Quantity_Color col(Quantity_NOC_TURQUOISE);
  DA->LineAspect(Prs3d_DatumParts_XAxis)->SetColor(col);
  DA->LineAspect(Prs3d_DatumParts_YAxis)->SetColor(col);
  DA->LineAspect(Prs3d_DatumParts_ZAxis)->SetColor(col);
  myDrawer->SetDatumAspect(DA);

  ComputeFields();
}

//=================================================================================================

AIS_Axis::AIS_Axis(const occ::handle<Geom_Axis1Placement>& anAxis)
    : myComponent(new Geom_Line(anAxis->Ax1())),
      myTypeOfAxis(AIS_TOAX_Unknown),
      myIsXYZAxis(false)
{
  myDrawer->SetLineAspect(new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_DOTDASH, 1.));
  SetInfiniteState();

  gp_Dir thedir  = myComponent->Position().Direction();
  gp_Pnt loc     = myComponent->Position().Location();
  double aLength = UnitsAPI::AnyToLS(250000., "mm");
  myPfirst       = loc.XYZ() + aLength * thedir.XYZ();
  myPlast        = loc.XYZ() - aLength * thedir.XYZ();
}

//=================================================================================================

AIS_Axis::AIS_Axis(const gp_Ax1& theAxis, const double theLength)
    : myComponent(new Geom_Line(theAxis)),
      myTypeOfAxis(AIS_TOAX_ZAxis),
      myIsXYZAxis(true)
{
  myDir    = theAxis.Direction();
  myPfirst = theAxis.Location();
  if (theLength <= 0 && theLength != -1)
  {
    throw Standard_NumericError("AIS_Axis::AIS_Axis : invalid value for theLength parameter");
  }
  myVal   = (theLength == -1) ? UnitsAPI::AnyToLS(250000., "mm") : theLength;
  myPlast = myPfirst.XYZ() + myVal * myDir.XYZ();
  SetInfiniteState();
  occ::handle<Prs3d_DatumAspect> aDatumAspect = new Prs3d_DatumAspect();
  aDatumAspect->SetDrawLabels(false);
  myDrawer->SetDatumAspect(aDatumAspect);
  occ::handle<Prs3d_LineAspect> aDefaultLineAspect =
    new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_SOLID, 1.0);
  myDrawer->SetLineAspect(aDefaultLineAspect);
  myLineAspect = myDrawer->LineAspect();
}

//=================================================================================================

void AIS_Axis::SetComponent(const occ::handle<Geom_Line>& aComponent)
{
  myComponent  = aComponent;
  myTypeOfAxis = AIS_TOAX_Unknown;
  myIsXYZAxis  = false;
  SetInfiniteState();

  gp_Dir thedir  = myComponent->Position().Direction();
  gp_Pnt loc     = myComponent->Position().Location();
  double aLength = UnitsAPI::AnyToLS(250000., "mm");
  myPfirst       = loc.XYZ() + aLength * thedir.XYZ();
  myPlast        = loc.XYZ() - aLength * thedir.XYZ();
}

//=================================================================================================

void AIS_Axis::SetAxis2Placement(const occ::handle<Geom_Axis2Placement>& aComponent,
                                 const AIS_TypeOfAxis                    anAxisType)
{
  myAx2        = aComponent;
  myTypeOfAxis = anAxisType;
  myIsXYZAxis  = true;
  ComputeFields();
}

//=================================================================================================

void AIS_Axis::SetAxis1Placement(const occ::handle<Geom_Axis1Placement>& anAxis)
{
  SetComponent(new Geom_Line(anAxis->Ax1()));
}

//=================================================================================================

void AIS_Axis::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                       const occ::handle<Prs3d_Presentation>& thePrs,
                       const int)
{
  thePrs->SetInfiniteState(myInfiniteState);
  if (!myIsXYZAxis)
  {
    GeomAdaptor_Curve curv(myComponent);
    StdPrs_Curve::Add(thePrs, curv, myDrawer);
  }
  else
  {
    DsgPrs_XYZAxisPresentation::Add(thePrs,
                                    myLineAspect,
                                    myDir,
                                    myVal,
                                    myDrawer->DatumAspect()->ToDrawLabels() ? myText : "",
                                    myPfirst,
                                    myPlast);
  }
}

//=================================================================================================

void AIS_Axis::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection, const int)
{
  occ::handle<SelectMgr_EntityOwner>     eown = new SelectMgr_EntityOwner(this, 3);
  occ::handle<Select3D_SensitiveSegment> seg =
    new Select3D_SensitiveSegment(eown, myPfirst, myPlast);
  aSelection->Add(seg);
}

//=================================================================================================

void AIS_Axis::SetColor(const Quantity_Color& aCol)
{
  hasOwnColor = true;
  myDrawer->SetColor(aCol);
  myDrawer->LineAspect()->SetColor(aCol);

  const occ::handle<Prs3d_DatumAspect>& DA = myDrawer->DatumAspect();
  DA->LineAspect(Prs3d_DatumParts_XAxis)->SetColor(aCol);
  DA->LineAspect(Prs3d_DatumParts_YAxis)->SetColor(aCol);
  DA->LineAspect(Prs3d_DatumParts_ZAxis)->SetColor(aCol);
  SynchronizeAspects();
}

//=================================================================================================

void AIS_Axis::SetWidth(const double aValue)
{
  if (aValue < 0.0)
    return;
  if (aValue == 0)
    UnsetWidth();

  myDrawer->LineAspect()->SetWidth(aValue);

  const occ::handle<Prs3d_DatumAspect>& DA = myDrawer->DatumAspect();
  DA->LineAspect(Prs3d_DatumParts_XAxis)->SetWidth(aValue);
  DA->LineAspect(Prs3d_DatumParts_YAxis)->SetWidth(aValue);
  DA->LineAspect(Prs3d_DatumParts_ZAxis)->SetWidth(aValue);
  SynchronizeAspects();
}

//=================================================================================================

void AIS_Axis::SetDisplayAspect(const occ::handle<Prs3d_LineAspect>& theNewLineAspect)
{
  myDrawer->SetLineAspect(theNewLineAspect);
  myLineAspect = myDrawer->LineAspect();
  SetColor(theNewLineAspect->Aspect()->Color());
}

//=================================================================================================

void AIS_Axis::ComputeFields()
{
  if (myIsXYZAxis)
  {
    // compute myPFirst,myPlast
    occ::handle<Prs3d_DatumAspect> DA     = myDrawer->DatumAspect();
    gp_Ax2                         anAxis = myAx2->Ax2();
    const gp_Pnt&                  Orig   = anAxis.Location();
    const gp_Dir&                  oX     = anAxis.XDirection();
    const gp_Dir&                  oY     = anAxis.YDirection();
    const gp_Dir&                  oZ     = anAxis.Direction();
    double                         xo, yo, zo, x = 0., y = 0., z = 0.;
    Orig.Coord(xo, yo, zo);
    myPfirst.SetCoord(xo, yo, zo);

    switch (myTypeOfAxis)
    {
      case AIS_TOAX_XAxis:
      {
        oX.Coord(x, y, z);
        myVal        = DA->AxisLength(Prs3d_DatumParts_XAxis);
        myDir        = oX;
        myLineAspect = DA->LineAspect(Prs3d_DatumParts_XAxis);
        myText       = static_cast<const char*>("X");
        break;
      }
      case AIS_TOAX_YAxis:
      {
        oY.Coord(x, y, z);
        myVal        = DA->AxisLength(Prs3d_DatumParts_YAxis);
        myDir        = oY;
        myLineAspect = DA->LineAspect(Prs3d_DatumParts_YAxis);
        myText       = static_cast<const char*>("Y");
        break;
      }
      case AIS_TOAX_ZAxis:
      {
        oZ.Coord(x, y, z);
        myVal        = DA->AxisLength(Prs3d_DatumParts_ZAxis);
        myDir        = oZ;
        myLineAspect = DA->LineAspect(Prs3d_DatumParts_ZAxis);
        myText       = static_cast<const char*>("Z");
        break;
      }
      default:
        break;
    }

    myComponent = new Geom_Line(Orig, myDir);
    x           = xo + x * myVal;
    y           = yo + y * myVal;
    z           = zo + z * myVal;
    myPlast.SetCoord(x, y, z);
    SetInfiniteState();
  }
}

//=================================================================================================

bool AIS_Axis::AcceptDisplayMode(const int aMode) const
{
  return aMode == 0;
}

//=================================================================================================

void AIS_Axis::UnsetColor()
{
  myDrawer->LineAspect()->SetColor(Quantity_NOC_RED);
  hasOwnColor = false;

  myDrawer->DatumAspect()->LineAspect(Prs3d_DatumParts_XAxis)->SetColor(Quantity_NOC_TURQUOISE);
  myDrawer->DatumAspect()->LineAspect(Prs3d_DatumParts_YAxis)->SetColor(Quantity_NOC_TURQUOISE);
  myDrawer->DatumAspect()->LineAspect(Prs3d_DatumParts_ZAxis)->SetColor(Quantity_NOC_TURQUOISE);
  SynchronizeAspects();
}

//=================================================================================================

void AIS_Axis::UnsetWidth()
{
  myOwnWidth = 0.0f;
  myDrawer->LineAspect()->SetWidth(1.);
  myDrawer->DatumAspect()->LineAspect(Prs3d_DatumParts_XAxis)->SetWidth(1.);
  myDrawer->DatumAspect()->LineAspect(Prs3d_DatumParts_YAxis)->SetWidth(1.);
  myDrawer->DatumAspect()->LineAspect(Prs3d_DatumParts_ZAxis)->SetWidth(1.);
  SynchronizeAspects();
}
