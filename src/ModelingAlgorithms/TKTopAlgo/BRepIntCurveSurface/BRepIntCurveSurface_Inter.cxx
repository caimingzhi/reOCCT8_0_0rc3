#include <BRepIntCurveSurface_Inter.hpp>

#include <Bnd_Box.hpp>
#include <BndLib_Add3dCurve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepBndLib.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <Geom_Line.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <gp_Lin.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <StdFail_NotDone.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

BRepIntCurveSurface_Inter::BRepIntCurveSurface_Inter()
{
  myFastClass = new BRepTopAdaptor_TopolTool();
  Clear();
}

void BRepIntCurveSurface_Inter::Init(const TopoDS_Shape&      theShape,
                                     const GeomAdaptor_Curve& theCurve,
                                     const double             theTol)
{
  Load(theShape, theTol);
  Init(theCurve);
}

void BRepIntCurveSurface_Inter::Init(const TopoDS_Shape& theShape,
                                     const gp_Lin&       theLine,
                                     const double        theTol)
{

  occ::handle<Geom_Line> geomline = new Geom_Line(theLine);
  GeomAdaptor_Curve      aCurve(geomline);
  Load(theShape, theTol);
  Init(aCurve);
}

void BRepIntCurveSurface_Inter::Clear()
{
  myCurrentindex    = 0;
  myCurrentnbpoints = 0;
  myIndFace         = 0;
  myCurrentstate    = TopAbs_UNKNOWN;
  myCurrentU        = 0;
  myCurrentV        = 0;
}

void BRepIntCurveSurface_Inter::Load(const TopoDS_Shape& theShape, const double theTol)
{
  Clear();
  myFaces.Clear();
  myFaceBoxes.Nullify();
  myTolerance = theTol;
  TopExp_Explorer explorer(theShape, TopAbs_FACE);
  for (; explorer.More(); explorer.Next())
    myFaces.Append(explorer.Current());
}

void BRepIntCurveSurface_Inter::Init(const GeomAdaptor_Curve& theCurve)
{
  Clear();
  myCurveBox.SetVoid();
  double aFirst = theCurve.FirstParameter();
  double aLast  = theCurve.LastParameter();
  myCurve       = new GeomAdaptor_Curve(theCurve);
  if (!Precision::IsInfinite(aFirst) && !Precision::IsInfinite(aLast))
  {
    BndLib_Add3dCurve::Add(*myCurve, 0., myCurveBox);
  }
  Find();
}

bool BRepIntCurveSurface_Inter::More() const
{
  return (myIndFace <= myFaces.Length());
}

void BRepIntCurveSurface_Inter::Next()
{
  if (myCurrentnbpoints)
    myCurrentindex++;
  Find();
}

void BRepIntCurveSurface_Inter::Find()
{
  if (myCurrentnbpoints && myCurrentindex <= myCurrentnbpoints && FindPoint())
    return;

  myCurrentnbpoints = 0;
  myCurrentindex    = 0;

  int i = myIndFace + 1;
  for (; i <= myFaces.Length(); i++)
  {
    TopoDS_Shape aCurface = myFaces(i);
    if (myFaceBoxes.IsNull())
      myFaceBoxes = new NCollection_HArray1<Bnd_Box>(1, myFaces.Length());
    Bnd_Box& aFaceBox = myFaceBoxes->ChangeValue(i);
    if (aFaceBox.IsVoid())
    {
      BRepBndLib::Add(aCurface, aFaceBox);
      aFaceBox.SetGap(myTolerance);
    }
    bool isOut = (myCurve->GetType() == GeomAbs_Line
                    ? aFaceBox.IsOut(myCurve->Line())
                    : (!myCurveBox.IsVoid() ? aFaceBox.IsOut(myCurveBox) : false));
    if (isOut)
      continue;
    occ::handle<BRepAdaptor_Surface> aSurfForFastClass =
      new BRepAdaptor_Surface(TopoDS::Face(aCurface));
    myIntcs.Perform(myCurve, aSurfForFastClass);
    myCurrentnbpoints = myIntcs.NbPoints();
    if (!myCurrentnbpoints)
      continue;

    const occ::handle<Adaptor3d_Surface>& aSurf = aSurfForFastClass;
    myFastClass->Initialize(aSurf);
    myIndFace = i;
    if (FindPoint())
      return;
    myCurrentnbpoints = 0;
  }

  if (!myCurrentnbpoints && i > myFaces.Length())
  {
    myIndFace = i;
    return;
  }
}

bool BRepIntCurveSurface_Inter::FindPoint()
{
  int j = (!myCurrentindex ? 1 : myCurrentindex);

  for (; j <= myCurrentnbpoints; j++)
  {
    double anU = myIntcs.Point(j).U();
    double aV  = myIntcs.Point(j).V();

    gp_Pnt2d Puv(anU, aV);

    myCurrentstate = myFastClass->Classify(Puv, myTolerance);
    if (myCurrentstate == TopAbs_ON || myCurrentstate == TopAbs_IN)
    {
      myCurrentindex = j;
      myCurrentU     = anU;
      myCurrentV     = aV;
      return true;
    }
  }
  return false;
}

IntCurveSurface_IntersectionPoint BRepIntCurveSurface_Inter::Point() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();
  const IntCurveSurface_IntersectionPoint& ICPS = myIntcs.Point(myCurrentindex);
  return (IntCurveSurface_IntersectionPoint(ICPS.Pnt(),
                                            myCurrentU,
                                            myCurrentV,
                                            ICPS.W(),
                                            ICPS.Transition()));
}

double BRepIntCurveSurface_Inter::U() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();

  return (myCurrentU);
}

double BRepIntCurveSurface_Inter::V() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();

  return (myCurrentV);
}

double BRepIntCurveSurface_Inter::W() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();
  return (myIntcs.Point(myCurrentindex).W());
}

TopAbs_State BRepIntCurveSurface_Inter::State() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();

  return (myCurrentstate);
}

IntCurveSurface_TransitionOnCurve BRepIntCurveSurface_Inter::Transition() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();
  return (myIntcs.Point(myCurrentindex).Transition());
}

const TopoDS_Face& BRepIntCurveSurface_Inter::Face() const
{
  return (TopoDS::Face(myFaces.Value(myIndFace)));
}

const gp_Pnt& BRepIntCurveSurface_Inter::Pnt() const
{
  if (myCurrentindex == 0)
    throw StdFail_NotDone();
  return (myIntcs.Point(myCurrentindex).Pnt());
}
