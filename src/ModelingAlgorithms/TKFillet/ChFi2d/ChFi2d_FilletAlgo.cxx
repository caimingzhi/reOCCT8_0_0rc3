

#include <ChFi2d_FilletAlgo.hpp>

#include <GeomProjLib.hpp>
#include <BRep_Tool.hpp>
#include <Precision.hpp>
#include <ElSLib.hpp>
#include <ElCLib.hpp>

#include <Geom2dAPI_ProjectPointOnCurve.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <Geom2dAPI_InterCurveCurve.hpp>

#include <TopoDS.hpp>
#include <TopoDS_Iterator.hpp>
#include <NCollection_List.hpp>

#include <Geom_Circle.hpp>
#include <Geom2d_Line.hpp>

#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepAdaptor_Curve.hpp>

ChFi2d_FilletAlgo::ChFi2d_FilletAlgo()
    : myStart1(0.0),
      myEnd1(0.0),
      myStart2(0.0),
      myEnd2(0.0),
      myRadius(0.0),
      myStartSide(false),
      myEdgesExchnged(false),
      myDegreeOfRecursion(0)
{
}

ChFi2d_FilletAlgo::ChFi2d_FilletAlgo(const TopoDS_Wire& theWire, const gp_Pln& thePlane)
    : myStart1(0.0),
      myEnd1(0.0),
      myStart2(0.0),
      myEnd2(0.0),
      myRadius(0.0),
      myStartSide(false),
      myEdgesExchnged(false),
      myDegreeOfRecursion(0)
{
  Init(theWire, thePlane);
}

ChFi2d_FilletAlgo::ChFi2d_FilletAlgo(const TopoDS_Edge& theEdge1,
                                     const TopoDS_Edge& theEdge2,
                                     const gp_Pln&      thePlane)
    : myEdge1(theEdge1),
      myEdge2(theEdge2),
      myStart1(0.0),
      myEnd1(0.0),
      myStart2(0.0),
      myEnd2(0.0),
      myRadius(0.0),
      myStartSide(false),
      myEdgesExchnged(false),
      myDegreeOfRecursion(0)
{
  Init(theEdge1, theEdge2, thePlane);
}

void ChFi2d_FilletAlgo::Init(const TopoDS_Wire& theWire, const gp_Pln& thePlane)
{
  TopoDS_Edge     theEdge1, theEdge2;
  TopoDS_Iterator itr(theWire);
  for (; itr.More(); itr.Next())
  {
    if (theEdge1.IsNull())
      theEdge1 = TopoDS::Edge(itr.Value());
    else if (theEdge2.IsNull())
      theEdge2 = TopoDS::Edge(itr.Value());
    else
      break;
  }
  if (theEdge1.IsNull() || theEdge2.IsNull())
    throw Standard_ConstructionError(
      "The fillet algorithms expects a wire consisting of two edges.");
  Init(theEdge1, theEdge2, thePlane);
}

void ChFi2d_FilletAlgo::Init(const TopoDS_Edge& theEdge1,
                             const TopoDS_Edge& theEdge2,
                             const gp_Pln&      thePlane)
{
  myPlane = new Geom_Plane(thePlane);

  myEdgesExchnged = false;

  BRepAdaptor_Curve aBAC1(theEdge1);
  BRepAdaptor_Curve aBAC2(theEdge2);
  if (aBAC1.GetType() < aBAC2.GetType())
  {
    myEdge1         = theEdge2;
    myEdge2         = theEdge1;
    myEdgesExchnged = true;
  }
  else
  {
    myEdge1 = theEdge1;
    myEdge2 = theEdge2;
  }

  occ::handle<Geom_Curve> aCurve1 = BRep_Tool::Curve(myEdge1, myStart1, myEnd1);
  occ::handle<Geom_Curve> aCurve2 = BRep_Tool::Curve(myEdge2, myStart2, myEnd2);

  myCurve1 = GeomProjLib::Curve2d(aCurve1, myStart1, myEnd1, myPlane);
  myCurve2 = GeomProjLib::Curve2d(aCurve2, myStart2, myEnd2, myPlane);

  while (myCurve1->IsPeriodic() && myStart1 >= myEnd1)
    myEnd1 += myCurve1->Period();
  while (myCurve2->IsPeriodic() && myStart2 >= myEnd2)
    myEnd2 += myCurve2->Period();

  if (aBAC1.GetType() == aBAC2.GetType())
  {
    if (myEnd2 - myStart2 < myEnd1 - myStart1)
    {
      TopoDS_Edge anEdge               = myEdge1;
      myEdge1                          = myEdge2;
      myEdge2                          = anEdge;
      occ::handle<Geom2d_Curve> aCurve = myCurve1;
      myCurve1                         = myCurve2;
      myCurve2                         = aCurve;
      double a                         = myStart1;
      myStart1                         = myStart2;
      myStart2                         = a;
      a                                = myEnd1;
      myEnd1                           = myEnd2;
      myEnd2                           = a;
      myEdgesExchnged                  = true;
    }
  }
}

static bool IsRadiusIntersected(const occ::handle<Geom2d_Curve>& theCurve,
                                const double                     theCurveMin,
                                const double                     theCurveMax,
                                const gp_Pnt2d                   theStart,
                                const gp_Pnt2d                   theEnd,
                                const bool                       theStartConnected)
{

  if (theStart.SquareDistance(theEnd) < Precision::SquareConfusion())
  {
    return false;
  }
  occ::handle<Geom2d_Line>  line = new Geom2d_Line(theStart, gp_Dir2d(gp_Vec2d(theStart, theEnd)));
  Geom2dAPI_InterCurveCurve anInter(theCurve, line, Precision::Confusion());
  int                       a;
  gp_Pnt2d                  aPoint;
  for (a = anInter.NbPoints(); a > 0; a--)
  {
    aPoint = anInter.Point(a);
    Geom2dAPI_ProjectPointOnCurve aProjInt(aPoint, theCurve, theCurveMin, theCurveMax);
    if (aProjInt.NbPoints() < 1 || aProjInt.LowerDistanceParameter() > Precision::Confusion())
      continue;

    if (aPoint.Distance(theStart) < Precision::Confusion())
    {
      if (!theStartConnected)
        return true;
    }
    if (aPoint.Distance(theEnd) < Precision::Confusion())
      return true;
    if (gp_Vec2d(aPoint, theStart).IsOpposite(gp_Vec2d(aPoint, theEnd), Precision::Angular()))
      return true;
  }
  const occ::handle<Geom2d_Curve>& aCurve = theCurve;
  for (a = anInter.NbSegments(); a > 0; a--)
  {

    aPoint = aCurve->Value(aCurve->FirstParameter());

    Geom2dAPI_ProjectPointOnCurve aProjInt(aPoint, theCurve, theCurveMin, theCurveMax);
    if (aProjInt.NbPoints() && aProjInt.LowerDistanceParameter() < Precision::Confusion())
    {
      if (aPoint.Distance(theStart) < Precision::Confusion())
        if (!theStartConnected)
          return true;
      if (aPoint.Distance(theEnd) < Precision::Confusion())
        return true;
      if (gp_Vec2d(aPoint, theStart).IsOpposite(gp_Vec2d(aPoint, theEnd), Precision::Angular()))
        return true;
    }
    aPoint = aCurve->Value(aCurve->LastParameter());

    aProjInt.Init(aPoint, theCurve, theCurveMin, theCurveMax);
    if (aProjInt.NbPoints() && aProjInt.LowerDistanceParameter() < Precision::Confusion())
    {
      if (aPoint.Distance(theStart) < Precision::Confusion())
        if (!theStartConnected)
          return true;
      if (aPoint.Distance(theEnd) < Precision::Confusion())
        return true;
      if (gp_Vec2d(aPoint, theStart).IsOpposite(gp_Vec2d(aPoint, theEnd), Precision::Angular()))
        return true;
    }
  }
  return false;
}

void ChFi2d_FilletAlgo::FillPoint(FilletPoint* thePoint, const double theLimit)
{

  bool     aValid = false;
  double   aStep  = Precision::Confusion();
  gp_Pnt2d aCenter, aPoint;
  double   aParam = thePoint->getParam();
  if (theLimit < aParam)
    aStep = -aStep;
  for (aValid = false; !aValid; aParam += aStep)
  {
    if ((aParam - aStep - theLimit) * (aParam - theLimit) <= 0)
      break;
    aStep *= 2;
    gp_Vec2d aVec;
    myCurve1->D1(aParam, aPoint, aVec);
    if (aVec.SquareMagnitude() < Precision::Confusion())
      continue;

    gp_Vec2d aPerp(((myStartSide) ? -1 : 1) * aVec.Y(), ((myStartSide) ? 1 : -1) * aVec.X());
    aPerp.Normalize();
    aPerp.Multiply(myRadius);
    aCenter = aPoint.Translated(aPerp);

    Geom2dAPI_ProjectPointOnCurve aProjInt(aPoint, myCurve2, myStart2, myEnd2);
    if (aProjInt.NbPoints() == 0
        || aPoint.Distance(aProjInt.NearestPoint()) > Precision::Confusion())
    {
      aValid = true;
      break;
    }
  }
  if (aValid)
  {
    thePoint->setParam(aParam);
    thePoint->setCenter(aCenter);
    aValid = !IsRadiusIntersected(myCurve2, myStart2, myEnd2, aPoint, aCenter, true);
  }

  Geom2dAPI_ProjectPointOnCurve aProj(aCenter, myCurve2);
  int                           a, aNB = aProj.NbPoints();
  for (a = aNB; a > 0; a--)
  {
    if (aPoint.SquareDistance(aProj.Point(a)) < Precision::Confusion())
      continue;

    bool aValid2 = aValid;
    if (aValid2)
      aValid2 = !IsRadiusIntersected(myCurve1, myStart1, myEnd1, aCenter, aProj.Point(a), false);

    double aParamProj = aProj.Parameter(a);
    while (myCurve2->IsPeriodic() && aParamProj < myStart2)
      aParamProj += myCurve2->Period();

    const double d = aProj.Distance(a);
    thePoint->appendValue(d * d - myRadius * myRadius,
                          (aParamProj >= myStart2 && aParamProj <= myEnd2 && aValid2));
    if (std::abs(d - myRadius) < Precision::Confusion())
      thePoint->setParam2(aParamProj);
  }
}

void ChFi2d_FilletAlgo::FillDiff(FilletPoint* thePoint, double theDiffStep, bool theFront)
{
  double       aDelta = theFront ? (theDiffStep) : (-theDiffStep);
  FilletPoint* aDiff  = new FilletPoint(thePoint->getParam() + aDelta);
  FillPoint(aDiff, aDelta * 999.);
  if (!thePoint->calculateDiff(aDiff))
  {
    aDiff->setParam(thePoint->getParam() - aDelta);
    FillPoint(aDiff, -aDelta * 999);
    thePoint->calculateDiff(aDiff);
  }
  delete aDiff;
}

bool ChFi2d_FilletAlgo::Perform(const double theRadius)
{
  myDegreeOfRecursion = 0;
  myResultParams.Clear();
  myResultOrientation.Clear();

  double              aNBSteps;
  Geom2dAdaptor_Curve aGAC(myCurve1);
  switch (aGAC.GetType())
  {
    case GeomAbs_Line:
      aNBSteps = 2;
      break;
    case GeomAbs_Circle:
      aNBSteps = 4;
      break;
    case GeomAbs_Ellipse:
      aNBSteps = 5;
      break;
    case GeomAbs_BSplineCurve:
      aNBSteps = 2 + aGAC.Degree() * aGAC.NbPoles();
      break;
    default:
      aNBSteps = 100;
  }

  myRadius = theRadius;
  double aParam, aStep, aDStep;
  aStep  = (myEnd1 - myStart1) / aNBSteps;
  aDStep = 1.e-4 * aStep;

  int aCycle;
  for (aCycle = 2, myStartSide = false; aCycle; myStartSide = !myStartSide, aCycle--)
  {
    FilletPoint *aLeft = nullptr, *aRight;

    for (aParam = myStart1 + aStep;
         aParam < myEnd1 || std::abs(myEnd1 - aParam) < Precision::Confusion();
         aParam += aStep)
    {
      if (!aLeft)
      {
        aLeft = new FilletPoint(aParam - aStep);
        FillPoint(aLeft, aParam);
        FillDiff(aLeft, aDStep, true);
      }

      aRight = new FilletPoint(aParam);
      FillPoint(aRight, aParam - aStep);
      FillDiff(aRight, aDStep, false);

      aLeft->FilterPoints(aRight);
      PerformNewton(aLeft, aRight);

      delete aLeft;
      aLeft = aRight;
    }
    delete aLeft;
  }

  return !myResultParams.IsEmpty();
}

bool ChFi2d_FilletAlgo::ProcessPoint(FilletPoint* theLeft,
                                     FilletPoint* theRight,
                                     double       theParameter)
{
  if (theParameter >= theLeft->getParam() && theParameter < theRight->getParam())
  {
    double aDX = (theRight->getParam() - theLeft->getParam());
    if (theParameter - theLeft->getParam() < aDX / 100.0)
    {
      theParameter = theLeft->getParam() + aDX / 100.0;
    }
    if (theRight->getParam() - theParameter < aDX / 100.0)
    {
      theParameter = theRight->getParam() - aDX / 100.0;
    }

    myDegreeOfRecursion++;
    double diffx = 0.001 * aDX;
    if (myDegreeOfRecursion > 100)
    {
      diffx *= 10.0;
      if (myDegreeOfRecursion > 1000)
      {
        diffx *= 10.0;
        if (myDegreeOfRecursion > 3000)
        {
          return true;
        }
      }
    }

    FilletPoint* aPoint1 = theLeft->Copy();
    FilletPoint* aPoint2 = new FilletPoint(theParameter);
    FillPoint(aPoint2, aPoint1->getParam());
    FillDiff(aPoint2, diffx, true);

    aPoint1->FilterPoints(aPoint2);
    PerformNewton(aPoint1, aPoint2);
    aPoint2->FilterPoints(theRight);
    PerformNewton(aPoint2, theRight);

    delete aPoint1;
    delete aPoint2;
    return true;
  }

  return false;
}

void ChFi2d_FilletAlgo::PerformNewton(FilletPoint* theLeft, FilletPoint* theRight)
{
  int a;

  a = theLeft->hasSolution(myRadius);
  if (a)
  {
    if (theLeft->isValid(a))
    {
      myResultParams.Append(theLeft->getParam());
      myResultOrientation.Append(myStartSide);
    }
    return;
  }

  double aDX = theRight->getParam() - theLeft->getParam();
  if (aDX < 1.e-6 * Precision::Confusion())
  {
    a = theRight->hasSolution(myRadius);
    if (a && theRight->isValid(a))
    {
      myResultParams.Append(theRight->getParam());
      myResultOrientation.Append(myStartSide);
    }
    return;
  }
  for (a = 1; a <= theLeft->getNBValues(); a++)
  {
    int aNear = theLeft->getNear(a);

    double aA = (theRight->getDiff(aNear) - theLeft->getDiff(a)) / aDX;
    double aB = theLeft->getDiff(a) - aA * theLeft->getParam();
    double aC = theLeft->getValue(a) - theLeft->getDiff(a) * theLeft->getParam()
                + aA * theLeft->getParam() * theLeft->getParam() / 2.0;
    double aDet = aB * aB - 2.0 * aA * aC;

    if (std::abs(aA) < Precision::Confusion())
    {

      if (std::abs(aB) > 10e-20)
      {
        double aX0 = -aC / aB;
        if (aX0 > theLeft->getParam() && aX0 < theRight->getParam())
          ProcessPoint(theLeft, theRight, aX0);
      }
      else
      {
        ProcessPoint(theLeft, theRight, theLeft->getParam() + aDX / 2.0);
      }
    }
    else
    {
      if (std::abs(aB) > std::abs(aDet * 1000000.))
      {

        ProcessPoint(theLeft, theRight, theLeft->getParam() + aDX / 2.0);
      }
      else
      {
        if (aDet > 0)
        {
          aDet      = sqrt(aDet);
          bool aRes = ProcessPoint(theLeft, theRight, (-aB + aDet) / aA);
          if (!aRes)
            aRes = ProcessPoint(theLeft, theRight, (-aB - aDet) / aA);
          if (!aRes)
            ProcessPoint(theLeft, theRight, theLeft->getParam() + aDX / 2.0);
        }
        else
        {

          double aX0 = -aB / aA;
          if (aX0 > theLeft->getParam() && aX0 < theRight->getParam())
            ProcessPoint(theLeft, theRight, aX0);
          else
            ProcessPoint(theLeft, theRight, theLeft->getParam() + aDX / 2.0);
        }
      }
    }
  }
}

int ChFi2d_FilletAlgo::NbResults(const gp_Pnt& thePoint)
{
  double   aX, aY;
  gp_Pnt2d aTargetPoint2d;
  ElSLib::PlaneParameters(myPlane->Pln().Position(), thePoint, aX, aY);
  aTargetPoint2d.SetCoord(aX, aY);

  int                                i = 1, nb = 0;
  NCollection_List<double>::Iterator anIter(myResultParams);
  for (; anIter.More(); anIter.Next(), i++)
  {
    myStartSide         = (myResultOrientation.Value(i)) != 0;
    FilletPoint* aPoint = new FilletPoint(anIter.Value());
    FillPoint(aPoint, anIter.Value() + 1.);
    if (aPoint->hasSolution(myRadius))
      nb++;
    delete aPoint;
  }

  return nb;
}

TopoDS_Edge ChFi2d_FilletAlgo::Result(const gp_Pnt& thePoint,
                                      TopoDS_Edge&  theEdge1,
                                      TopoDS_Edge&  theEdge2,
                                      const int     iSolution)
{
  TopoDS_Edge aResult;
  gp_Pnt2d    aTargetPoint2d;
  double      aX, aY;
  ElSLib::PlaneParameters(myPlane->Pln().Position(), thePoint, aX, aY);
  aTargetPoint2d.SetCoord(aX, aY);

  double                             aDistance = 0.0, aP;
  FilletPoint*                       aNearest;
  int                                a, iSol = 1;
  NCollection_List<double>::Iterator anIter(myResultParams);
  for (aNearest = nullptr, a = 1; anIter.More(); anIter.Next(), a++)
  {
    myStartSide         = (myResultOrientation.Value(a)) != 0;
    FilletPoint* aPoint = new FilletPoint(anIter.Value());
    FillPoint(aPoint, anIter.Value() + 1.);
    if (!aPoint->hasSolution(myRadius))
    {
      delete aPoint;
      continue;
    }
    aP = DBL_MAX;
    if (iSolution == -1)
    {
      aP = std::abs(aPoint->getCenter().Distance(aTargetPoint2d) - myRadius);
    }
    else if (iSolution == iSol)
    {
      aP = 0.0;
    }
    if (!aNearest || aP < aDistance)
    {
      aNearest  = aPoint;
      aDistance = aP;
    }
    else
    {
      delete aPoint;
    }
    if (iSolution == iSol)
      break;
    iSol++;
  }

  if (!aNearest)
    return aResult;

  gp_Pnt                   aCenter = ElSLib::PlaneValue(aNearest->getCenter().X(),
                                      aNearest->getCenter().Y(),
                                      myPlane->Pln().Position());
  occ::handle<Geom_Circle> aCircle =
    new Geom_Circle(gp_Ax2(aCenter, myPlane->Pln().Axis().Direction()), myRadius);
  gp_Pnt2d aPoint2d1, aPoint2d2;
  myCurve1->D0(aNearest->getParam(), aPoint2d1);
  myCurve2->D0(aNearest->getParam2(), aPoint2d2);
  gp_Pnt aPoint1 = ElSLib::PlaneValue(aPoint2d1.X(), aPoint2d1.Y(), myPlane->Pln().Position());
  gp_Pnt aPoint2 = ElSLib::PlaneValue(aPoint2d2.X(), aPoint2d2.Y(), myPlane->Pln().Position());

  GeomAPI_ProjectPointOnCurve aProj(thePoint, aCircle);
  double                      aTargetParam   = aProj.LowerDistanceParameter();
  gp_Pnt                      aPointOnCircle = aProj.NearestPoint();

  gp_Pnt p0 = ElCLib::Value(0.0, aCircle->Circ());
  if (p0.Distance(thePoint) < aPointOnCircle.Distance(thePoint))
  {
    aTargetParam   = 0.0;
    aPointOnCircle = p0;
  }

  aProj.Perform(aPoint1);
  double aParam1 = aProj.LowerDistanceParameter();
  aProj.Perform(aPoint2);
  double aParam2 = aProj.LowerDistanceParameter();
  bool   aIsOut  = ((aParam1 < aTargetParam && aParam2 < aTargetParam)
                 || (aParam1 > aTargetParam && aParam2 > aTargetParam));
  if (aParam1 > aParam2)
    aIsOut = !aIsOut;
  BRepBuilderAPI_MakeEdge aBuilder(aCircle->Circ(),
                                   aIsOut ? aParam2 : aParam1,
                                   aIsOut ? aParam1 : aParam2);
  aResult = aBuilder.Edge();

  double                  aStart, anEnd;
  occ::handle<Geom_Curve> aCurve = BRep_Tool::Curve(myEdge1, aStart, anEnd);
  gp_Vec                  aDir;
  aCurve->D1(aNearest->getParam(), aPoint1, aDir);

  gp_Vec aCircleDir;
  aCircle->D1(aParam1, aPoint1, aCircleDir);

  if ((aCircleDir.Angle(aDir) > M_PI / 2.0) ? !aIsOut : aIsOut)
    aStart = aNearest->getParam();
  else
    anEnd = aNearest->getParam();

  if (fabs(aStart - anEnd) < Precision::Confusion())
    anEnd = aStart + Precision::Confusion();

  BRepBuilderAPI_MakeEdge aDivider1(aCurve, aStart, anEnd);
  if (myEdgesExchnged)
    theEdge2 = aDivider1.Edge();
  else
    theEdge1 = aDivider1.Edge();

  aCurve = BRep_Tool::Curve(myEdge2, aStart, anEnd);
  aCurve->D1(aNearest->getParam2(), aPoint2, aDir);

  aCircle->D1(aParam2, aPoint2, aCircleDir);

  if ((aCircleDir.Angle(aDir) > M_PI / 2.0) ? aIsOut : !aIsOut)
    aStart = aNearest->getParam2();
  else
    anEnd = aNearest->getParam2();

  if (fabs(aStart - anEnd) < Precision::Confusion())
    anEnd = aStart + Precision::Confusion();
  BRepBuilderAPI_MakeEdge aDivider2(aCurve, aStart, anEnd);
  if (myEdgesExchnged)
    theEdge1 = aDivider2.Edge();
  else
    theEdge2 = aDivider2.Edge();

  delete aNearest;
  return aResult;
}

FilletPoint::FilletPoint(const double theParam)
    : myParam(theParam),
      myParam2(0.0)
{
}

void FilletPoint::appendValue(double theValue, bool theValid)
{
  int a;
  for (a = 1; a <= myV.Length(); a++)
  {
    if (theValue < myV.Value(a))
    {
      myV.InsertBefore(a, theValue);
      myValid.InsertBefore(a, theValid);
      return;
    }
  }
  myV.Append(theValue);
  myValid.Append(theValid);
}

bool FilletPoint::calculateDiff(FilletPoint* thePoint)
{
  int    a;
  bool   aDiffsSet = (myD.Length() != 0);
  double aDX = thePoint->getParam() - myParam, aDY = 0.0;
  if (thePoint->myV.Length() == myV.Length())
  {
    for (a = 1; a <= myV.Length(); a++)
    {
      aDY = thePoint->myV.Value(a) - myV.Value(a);
      if (aDiffsSet)
        myD.SetValue(a, aDY / aDX);
      else
        myD.Append(aDY / aDX);
    }
    return true;
  }

  int b;
  for (a = 1; a <= myV.Length(); a++)
  {
    for (b = 1; b <= thePoint->myV.Length(); b++)
    {
      if (b == 1 || std::abs(thePoint->myV.Value(b) - myV.Value(a)) < std::abs(aDY))
        aDY = thePoint->myV.Value(b) - myV.Value(a);
    }
    if (aDiffsSet)
    {
      if (std::abs(aDY / aDX) < std::abs(myD.Value(a)))
        myD.SetValue(a, aDY / aDX);
    }
    else
    {
      myD.Append(aDY / aDX);
    }
  }

  return false;
}

void FilletPoint::FilterPoints(FilletPoint* thePoint)
{
  int                          a, b;
  NCollection_Sequence<double> aDiffs;
  double                       aY, aY2, aDX = thePoint->getParam() - myParam;
  for (a = 1; a <= myV.Length(); a++)
  {

    int    aNear = 0;
    double aDiff = aDX * 10000.;
    aY           = myV.Value(a) + myD.Value(a) * aDX;
    for (b = 1; b <= thePoint->myV.Length(); b++)
    {

      aY2 = aY + aDX * (thePoint->myD.Value(b) - myD.Value(a)) / 2.0;
      if (aNear == 0 || std::abs(aY2 - thePoint->myV.Value(b)) < std::abs(aDiff))
      {
        aNear = b;
        aDiff = aY2 - thePoint->myV.Value(b);
      }
    }

    if (aNear)
    {
      if (myV.Value(a) * thePoint->myV.Value(aNear) > 0)
      {
        if (myV.Value(a) * myD.Value(a) > 0)
        {
          if (std::abs(myD.Value(a)) > Precision::Confusion())
            aNear = 0;
        }
        else
        {
          if (std::abs(myV.Value(a)) > std::abs(thePoint->myV.Value(aNear)))
            if (thePoint->myV.Value(aNear) * thePoint->myD.Value(aNear) < 0
                && std::abs(thePoint->myD.Value(aNear)) > Precision::Confusion())
            {
              aNear = 0;
            }
        }
      }
    }

    if (aNear)
    {
      if (myV.Value(a) * thePoint->myV.Value(aNear) > 0)
      {
        if ((myV.Value(a) + myD.Value(a) * aDX) * myV.Value(a) > Precision::Confusion()
            && (thePoint->myV.Value(aNear) + thePoint->myD.Value(aNear) * aDX)
                   * thePoint->myV.Value(aNear)
                 > Precision::Confusion())
        {
          aNear = 0;
        }
      }
    }

    if (aNear)
    {
      if (std::abs(aDiff / aDX) > 1.e+7)
      {
        aNear = 0;
      }
    }

    if (aNear == 0)
    {
      myV.Remove(a);
      myD.Remove(a);
      myValid.Remove(a);
      a--;
    }
    else
    {
      bool aFound = false;
      for (b = 1; b <= myNear.Length(); b++)
      {
        if (myNear.Value(b) == aNear)
        {
          if (std::abs(aDiffs.Value(b)) < std::abs(aDiff))
          {
            aFound = true;
            myV.Remove(a);
            myD.Remove(a);
            myValid.Remove(a);
            a--;
            break;
          }
          else
          {
            myV.Remove(b);
            myD.Remove(b);
            myValid.Remove(b);
            myNear.Remove(b);
            aDiffs.Remove(b);
            a--;
            break;
          }
        }
      }
      if (!aFound)
      {
        myNear.Append(aNear);
        aDiffs.Append(aDiff);
      }
    }
  }
}

FilletPoint* FilletPoint::Copy()
{
  FilletPoint* aCopy = new FilletPoint(myParam);
  int          a;
  for (a = 1; a <= myV.Length(); a++)
  {
    aCopy->myV.Append(myV.Value(a));
    aCopy->myD.Append(myD.Value(a));
    aCopy->myValid.Append(myValid.Value(a));
  }
  return aCopy;
}

int FilletPoint::hasSolution(const double theRadius)
{
  int a;
  for (a = 1; a <= myV.Length(); a++)
  {
    if (std::abs(sqrt(std::abs(std::abs(myV.Value(a)) + theRadius * theRadius)) - theRadius)
        < Precision::Confusion())
      return a;
  }
  return 0;
}

void FilletPoint::remove(int theIndex)
{
  myV.Remove(theIndex);
  myD.Remove(theIndex);
  myValid.Remove(theIndex);
  myNear.Remove(theIndex);
}
