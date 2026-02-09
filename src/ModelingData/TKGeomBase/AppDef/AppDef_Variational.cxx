

#include <AppDef_MultiLine.hpp>
#include <AppDef_Variational.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DomainError.hpp>

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError
#define No_Standard_ConstructionError

#include <Standard_Macro.hpp>

#include <iostream>

#include <iomanip>

#include <fstream>

#include <AppParCurves.hpp>
#include <AppParCurves_Constraint.hpp>
#include <AppParCurves_ConstraintCouple.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <AppParCurves_MultiPoint.hpp>
#include <AppDef_LinearCriteria.hpp>
#include <Convert_CompPolynomialToPoles.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StdFail_NotDone.hpp>
#include <Precision.hpp>
#include <AppDef_MyLineTool.hpp>

#include <FEmTool_Assembly.hpp>
#include <FEmTool_Curve.hpp>
#include <math_Vector.hpp>
#include <PLib_HermitJacobi.hpp>

#include <algorithm>

#if defined(_MSC_VER)
  #include <stdio.h>
#endif

AppDef_Variational::AppDef_Variational(
  const AppDef_MultiLine&                                                SSP,
  const int                                                              FirstPoint,
  const int                                                              LastPoint,
  const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& TheConstraints,
  const int                                                              MaxDegree,
  const int                                                              MaxSegment,
  const GeomAbs_Shape                                                    Continuity,
  const bool                                                             WithMinMax,
  const bool                                                             WithCutting,
  const double                                                           Tolerance,
  const int                                                              NbIterations)
    : mySSP(SSP),
      myFirstPoint(FirstPoint),
      myLastPoint(LastPoint),
      myConstraints(TheConstraints),
      myMaxDegree(MaxDegree),
      myMaxSegment(MaxSegment),
      myNbIterations(NbIterations),
      myTolerance(Tolerance),
      myContinuity(Continuity),
      myWithMinMax(WithMinMax),
      myWithCutting(WithCutting)
{

  if (myMaxDegree < 1)
    throw Standard_DomainError();
  myMaxDegree = std::min(30, myMaxDegree);

  if (myMaxSegment < 1)
    throw Standard_DomainError();

  if (myWithMinMax != 0 && myWithMinMax != 1)
    throw Standard_DomainError();
  if (myWithCutting != 0 && myWithCutting != 1)
    throw Standard_DomainError();

  myIsOverConstr = false;
  myIsCreated    = false;
  myIsDone       = false;
  switch (myContinuity)
  {
    case GeomAbs_C0:
      myNivCont = 0;
      break;
    case GeomAbs_C1:
      myNivCont = 1;
      break;
    case GeomAbs_C2:
      myNivCont = 2;
      break;
    default:
      throw Standard_ConstructionError();
  }

  myNbP2d     = AppDef_MyLineTool::NbP2d(SSP);
  myNbP3d     = AppDef_MyLineTool::NbP3d(SSP);
  myDimension = 2 * myNbP2d + 3 * myNbP3d;

  myPercent[0] = 0.4;
  myPercent[1] = 0.2;
  myPercent[2] = 0.4;
  myKnots      = new NCollection_HArray1<double>(1, 2);
  myKnots->SetValue(1, 0.);
  myKnots->SetValue(2, 1.);

  mySmoothCriterion = new AppDef_LinearCriteria(mySSP, myFirstPoint, myLastPoint);
  myParameters      = new NCollection_HArray1<double>(myFirstPoint, myLastPoint);
  myNbPoints        = myLastPoint - myFirstPoint + 1;
  if (myNbPoints <= 0)
    throw Standard_ConstructionError();

  myTabPoints = new NCollection_HArray1<double>(1, myDimension * myNbPoints);

  int                          ipoint, jp2d, jp3d, index;
  NCollection_Array1<gp_Pnt>   TabP3d(1, std::max(1, myNbP3d));
  NCollection_Array1<gp_Pnt2d> TabP2d(1, std::max(1, myNbP2d));
  gp_Pnt2d                     P2d;
  gp_Pnt                       P3d;
  index = 1;

  for (ipoint = myFirstPoint; ipoint <= myLastPoint; ipoint++)
  {

    if (myNbP2d != 0 && myNbP3d == 0)
    {
      AppDef_MyLineTool::Value(mySSP, ipoint, TabP2d);

      for (jp2d = 1; jp2d <= myNbP2d; jp2d++)
      {
        P2d = TabP2d.Value(jp2d);

        myTabPoints->SetValue(index++, P2d.X());
        myTabPoints->SetValue(index++, P2d.Y());
      }
    }
    if (myNbP3d != 0 && myNbP2d == 0)
    {
      AppDef_MyLineTool::Value(mySSP, ipoint, TabP3d);

      for (jp3d = 1; jp3d <= myNbP3d; jp3d++)

      {
        P3d = TabP3d.Value(jp3d);

        myTabPoints->SetValue(index++, P3d.X());
        myTabPoints->SetValue(index++, P3d.Y());
        myTabPoints->SetValue(index++, P3d.Z());
      }
    }
    if (myNbP3d != 0 && myNbP2d != 0)
    {
      AppDef_MyLineTool::Value(mySSP, ipoint, TabP3d, TabP2d);

      for (jp3d = 1; jp3d <= myNbP3d; jp3d++)

      {
        P3d = TabP3d.Value(jp3d);

        myTabPoints->SetValue(index++, P3d.X());
        myTabPoints->SetValue(index++, P3d.Y());
        myTabPoints->SetValue(index++, P3d.Z());
      }
      for (jp2d = 1; jp2d <= myNbP2d; jp2d++)

      {
        P2d = TabP2d.Value(jp2d);

        myTabPoints->SetValue(index++, P2d.X());
        myTabPoints->SetValue(index++, P2d.Y());
      }
    }
  }
  Init();
}

void AppDef_Variational::Init()
{

  int                          ipoint, jp2d, jp3d, index, jndex;
  int                          CurMultyPoint;
  NCollection_Array1<gp_Vec>   TabV3d(1, std::max(1, myNbP3d));
  NCollection_Array1<gp_Vec2d> TabV2d(1, std::max(1, myNbP2d));
  NCollection_Array1<gp_Vec>   TabV3dcurv(1, std::max(1, myNbP3d));
  NCollection_Array1<gp_Vec2d> TabV2dcurv(1, std::max(1, myNbP2d));

  gp_Vec   Vt3d, Vc3d;
  gp_Vec2d Vt2d, Vc2d;

  myNbConstraints = myConstraints->Length();
  if (myNbConstraints < 0)
    throw Standard_ConstructionError();

  myTypConstraints = new NCollection_HArray1<int>(1, std::max(1, 2 * myNbConstraints));
  myTabConstraints =
    new NCollection_HArray1<double>(1, std::max(1, 2 * myDimension * myNbConstraints));
  myTtheta =
    new NCollection_HArray1<double>(1, std::max(1, (2 * myNbP2d + 6 * myNbP3d) * myNbConstraints));
  myTfthet =
    new NCollection_HArray1<double>(1, std::max(1, (2 * myNbP2d + 6 * myNbP3d) * myNbConstraints));

  int iconstr;
  index          = 1;
  jndex          = 1;
  CurMultyPoint  = 1;
  myNbPassPoints = 0;
  myNbTangPoints = 0;
  myNbCurvPoints = 0;
  AppParCurves_Constraint valcontr;

  for (iconstr = myConstraints->Lower(); iconstr <= myConstraints->Upper(); iconstr++)
  {
    ipoint = (myConstraints->Value(iconstr)).Index();

    valcontr = (myConstraints->Value(iconstr)).Constraint();
    switch (valcontr)
    {
      case AppParCurves_NoConstraint:
        CurMultyPoint -= myNbP3d * 6 + myNbP2d * 2;
        break;
      case AppParCurves_PassPoint:
        myTypConstraints->SetValue(index++, ipoint);
        myTypConstraints->SetValue(index++, 0);
        myNbPassPoints++;
        if (myNbP2d != 0)
          jndex = jndex + 4 * myNbP2d;
        if (myNbP3d != 0)
          jndex = jndex + 6 * myNbP3d;
        break;
      case AppParCurves_TangencyPoint:
        myTypConstraints->SetValue(index++, ipoint);
        myTypConstraints->SetValue(index++, 1);
        myNbTangPoints++;
        if (myNbP2d != 0 && myNbP3d == 0)
        {
          if (!AppDef_MyLineTool::Tangency(mySSP, ipoint, TabV2d))
            throw Standard_ConstructionError();
          for (jp2d = 1; jp2d <= myNbP2d; jp2d++)
          {
            Vt2d = TabV2d.Value(jp2d);
            Vt2d.Normalize();
            myTabConstraints->SetValue(jndex++, Vt2d.X());
            myTabConstraints->SetValue(jndex++, Vt2d.Y());
            jndex = jndex + 2;
            InitTthetaF(2, valcontr, CurMultyPoint + (jp2d - 1) * 2, jndex - 4);
          }
        }
        if (myNbP3d != 0 && myNbP2d == 0)
        {
          if (!AppDef_MyLineTool::Tangency(mySSP, ipoint, TabV3d))
            throw Standard_ConstructionError();
          for (jp3d = 1; jp3d <= myNbP3d; jp3d++)
          {
            Vt3d = TabV3d.Value(jp3d);
            Vt3d.Normalize();
            myTabConstraints->SetValue(jndex++, Vt3d.X());

            myTabConstraints->SetValue(jndex++, Vt3d.Y());

            myTabConstraints->SetValue(jndex++, Vt3d.Z());
            jndex = jndex + 3;
            InitTthetaF(3, valcontr, CurMultyPoint + (jp3d - 1) * 6, jndex - 6);
          }
        }
        if (myNbP3d != 0 && myNbP2d != 0)
        {
          if (!AppDef_MyLineTool::Tangency(mySSP, ipoint, TabV3d, TabV2d))
            throw Standard_ConstructionError();
          for (jp3d = 1; jp3d <= myNbP3d; jp3d++)
          {
            Vt3d = TabV3d.Value(jp3d);
            Vt3d.Normalize();
            myTabConstraints->SetValue(jndex++, Vt3d.X());
            myTabConstraints->SetValue(jndex++, Vt3d.Y());
            myTabConstraints->SetValue(jndex++, Vt3d.Z());
            jndex = jndex + 3;
            InitTthetaF(3, valcontr, CurMultyPoint + (jp3d - 1) * 6, jndex - 6);
          }

          for (jp2d = 1; jp2d <= myNbP2d; jp2d++)
          {
            Vt2d = TabV2d.Value(jp2d);
            Vt2d.Normalize();
            myTabConstraints->SetValue(jndex++, Vt2d.X());
            myTabConstraints->SetValue(jndex++, Vt2d.Y());
            jndex = jndex + 2;
            InitTthetaF(2, valcontr, CurMultyPoint + (jp2d - 1) * 2 + myNbP3d * 6, jndex - 4);
          }
        }

        break;

      case AppParCurves_CurvaturePoint:
        myTypConstraints->SetValue(index++, ipoint);
        myTypConstraints->SetValue(index++, 2);
        myNbCurvPoints++;
        if (myNbP2d != 0 && myNbP3d == 0)
        {
          if (!AppDef_MyLineTool::Tangency(mySSP, ipoint, TabV2d))
            throw Standard_ConstructionError();
          if (!AppDef_MyLineTool::Curvature(mySSP, ipoint, TabV2dcurv))
            throw Standard_ConstructionError();
          for (jp2d = 1; jp2d <= myNbP2d; jp2d++)
          {
            Vt2d = TabV2d.Value(jp2d);
            Vt2d.Normalize();
            Vc2d = TabV2dcurv.Value(jp2d);
            if (std::abs(std::abs(Vc2d.Angle(Vt2d)) - M_PI / 2.) > Precision::Angular())
              throw Standard_ConstructionError();
            myTabConstraints->SetValue(jndex++, Vt2d.X());
            myTabConstraints->SetValue(jndex++, Vt2d.Y());
            myTabConstraints->SetValue(jndex++, Vc2d.X());
            myTabConstraints->SetValue(jndex++, Vc2d.Y());
            InitTthetaF(2, valcontr, CurMultyPoint + (jp2d - 1) * 2, jndex - 4);
          }
        }

        if (myNbP3d != 0 && myNbP2d == 0)
        {
          if (!AppDef_MyLineTool::Tangency(mySSP, ipoint, TabV3d))
            throw Standard_ConstructionError();
          if (!AppDef_MyLineTool::Curvature(mySSP, ipoint, TabV3dcurv))
            throw Standard_ConstructionError();
          for (jp3d = 1; jp3d <= myNbP3d; jp3d++)
          {
            Vt3d = TabV3d.Value(jp3d);
            Vt3d.Normalize();
            Vc3d = TabV3dcurv.Value(jp3d);
            if (!(Vc3d.Normalized()).IsNormal(Vt3d, Precision::Angular()))
              throw Standard_ConstructionError();
            myTabConstraints->SetValue(jndex++, Vt3d.X());
            myTabConstraints->SetValue(jndex++, Vt3d.Y());
            myTabConstraints->SetValue(jndex++, Vt3d.Z());
            myTabConstraints->SetValue(jndex++, Vc3d.X());
            myTabConstraints->SetValue(jndex++, Vc3d.Y());
            myTabConstraints->SetValue(jndex++, Vc3d.Z());
            InitTthetaF(3, valcontr, CurMultyPoint + (jp3d - 1) * 6, jndex - 6);
          }
        }
        if (myNbP3d != 0 && myNbP2d != 0)
        {
          if (!AppDef_MyLineTool::Tangency(mySSP, ipoint, TabV3d, TabV2d))
            throw Standard_ConstructionError();
          if (!AppDef_MyLineTool::Curvature(mySSP, ipoint, TabV3dcurv, TabV2dcurv))
            throw Standard_ConstructionError();
          for (jp3d = 1; jp3d <= myNbP3d; jp3d++)
          {
            Vt3d = TabV3d.Value(jp3d);
            Vt3d.Normalize();
            Vc3d = TabV3dcurv.Value(jp3d);
            if (!(Vc3d.Normalized()).IsNormal(Vt3d, Precision::Angular()))
              throw Standard_ConstructionError();
            myTabConstraints->SetValue(jndex++, Vt3d.X());
            myTabConstraints->SetValue(jndex++, Vt3d.Y());
            myTabConstraints->SetValue(jndex++, Vt3d.Z());
            myTabConstraints->SetValue(jndex++, Vc3d.X());
            myTabConstraints->SetValue(jndex++, Vc3d.Y());
            myTabConstraints->SetValue(jndex++, Vc3d.Z());
            InitTthetaF(3, valcontr, CurMultyPoint + (jp3d - 1) * 6, jndex - 6);
          }
          for (jp2d = 1; jp2d <= myNbP2d; jp2d++)
          {
            Vt2d = TabV2d.Value(jp2d);
            Vt2d.Normalize();
            Vc2d = TabV2dcurv.Value(jp2d);
            if (std::abs(std::abs(Vc2d.Angle(Vt2d)) - M_PI / 2.) > Precision::Angular())
              throw Standard_ConstructionError();
            myTabConstraints->SetValue(jndex++, Vt2d.X());
            myTabConstraints->SetValue(jndex++, Vt2d.Y());
            myTabConstraints->SetValue(jndex++, Vc2d.X());
            myTabConstraints->SetValue(jndex++, Vc2d.Y());
            InitTthetaF(2, valcontr, CurMultyPoint + (jp2d - 1) * 2 + myNbP3d * 6, jndex - 4);
          }
        }
        break;
      default:
        throw Standard_ConstructionError();
    }
    CurMultyPoint += myNbP3d * 6 + myNbP2d * 2;
  }

  int MaxSeg;
  if (myWithCutting)
    MaxSeg = myMaxSegment;
  else
    MaxSeg = 1;
  if (((myMaxDegree - myNivCont) * MaxSeg - myNbPassPoints - 2 * myNbTangPoints
       - 3 * myNbCurvPoints)
      < 0)
  {
    myIsOverConstr = true;
    myIsCreated    = false;
  }
  else
  {
    InitSmoothCriterion();
    myIsCreated = true;
  }
}

void AppDef_Variational::Approximate()

{
  if (!myIsCreated)
    throw StdFail_NotDone();

  double WQuadratic, WQuality;

  NCollection_Array1<double> Ecarts(myFirstPoint, myLastPoint);

  mySmoothCriterion->GetWeight(WQuadratic, WQuality);

  occ::handle<FEmTool_Curve> TheCurve;

  mySmoothCriterion->GetCurve(TheCurve);

  TheMotor(mySmoothCriterion, WQuadratic, WQuality, TheCurve, Ecarts);

  if (myWithMinMax && myTolerance < myMaxError)
    Adjusting(mySmoothCriterion, WQuadratic, WQuality, TheCurve, Ecarts);

  int jp2d, jp3d, ipole, NbElem = TheCurve->NbElements();

  NCollection_Array1<gp_Pnt>   TabP3d(1, std::max(1, myNbP3d));
  NCollection_Array1<gp_Pnt2d> TabP2d(1, std::max(1, myNbP2d));
  double                       debfin[2] = {-1., 1};

  gp_Pnt2d P2d;
  gp_Pnt   P3d;
  {
    occ::handle<NCollection_HArray2<double>> PolynomialIntervalsPtr =
      new NCollection_HArray2<double>(1, NbElem, 1, 2);

    occ::handle<NCollection_HArray1<int>> NbCoeffPtr =
      new NCollection_HArray1<int>(1, myMaxSegment);

    int                                      size = myMaxSegment * (myMaxDegree + 1) * myDimension;
    occ::handle<NCollection_HArray1<double>> CoeffPtr = new NCollection_HArray1<double>(1, size);

    CoeffPtr->Init(0.);

    occ::handle<NCollection_HArray1<double>> IntervallesPtr =
      new NCollection_HArray1<double>(1, NbElem + 1);

    IntervallesPtr->ChangeArray1() = TheCurve->Knots();

    TheCurve->GetPolynom(CoeffPtr->ChangeArray1());

    int ii;

    for (ii = 1; ii <= NbElem; ii++)
      NbCoeffPtr->SetValue(ii, TheCurve->Degree(ii) + 1);

    for (ii = PolynomialIntervalsPtr->LowerRow(); ii <= PolynomialIntervalsPtr->UpperRow(); ii++)
    {
      PolynomialIntervalsPtr->SetValue(ii, 1, debfin[0]);
      PolynomialIntervalsPtr->SetValue(ii, 2, debfin[1]);
    }

    Convert_CompPolynomialToPoles AConverter(NbElem,
                                             myNivCont,
                                             myDimension,
                                             myMaxDegree,
                                             NbCoeffPtr,
                                             CoeffPtr,
                                             PolynomialIntervalsPtr,
                                             IntervallesPtr);
    if (AConverter.IsDone())
    {
      occ::handle<NCollection_HArray2<double>> PolesPtr;
      occ::handle<NCollection_HArray1<int>>    Mults;
      int                                      NbPoles = AConverter.NbPoles();

      NCollection_Array1<AppParCurves_MultiPoint> TabMU(1, NbPoles);
      AConverter.Poles(PolesPtr);
      AConverter.Knots(myKnots);
      AConverter.Multiplicities(Mults);

      for (ipole = PolesPtr->LowerRow(); ipole <= PolesPtr->UpperRow(); ipole++)
      {
        int index = PolesPtr->LowerCol();

        if (myNbP3d != 0)
        {
          for (jp3d = 1; jp3d <= myNbP3d; jp3d++)
          {

            P3d.SetX(PolesPtr->Value(ipole, index++));

            P3d.SetY(PolesPtr->Value(ipole, index++));

            P3d.SetZ(PolesPtr->Value(ipole, index++));
            TabP3d.SetValue(jp3d, P3d);
          }
        }
        if (myNbP2d != 0)
        {
          for (jp2d = 1; jp2d <= myNbP2d; jp2d++)
          {
            P2d.SetX(PolesPtr->Value(ipole, index++));
            P2d.SetY(PolesPtr->Value(ipole, index++));
            TabP2d.SetValue(jp2d, P2d);
          }
        }
        if (myNbP2d != 0 && myNbP3d != 0)
        {
          AppParCurves_MultiPoint aMultiPoint(TabP3d, TabP2d);
          TabMU.SetValue(ipole, aMultiPoint);
        }
        else if (myNbP2d != 0)
        {
          AppParCurves_MultiPoint aMultiPoint(TabP2d);
          TabMU.SetValue(ipole, aMultiPoint);
        }
        else
        {

          AppParCurves_MultiPoint aMultiPoint(TabP3d);
          TabMU.SetValue(ipole, aMultiPoint);
        }
      }
      AppParCurves_MultiBSpCurve aCurve(TabMU, myKnots->Array1(), Mults->Array1());
      myMBSpCurve = aCurve;
      myIsDone    = true;
    }
  }
}

bool AppDef_Variational::IsCreated() const
{
  return myIsCreated;
}

bool AppDef_Variational::IsDone() const
{
  return myIsDone;
}

bool AppDef_Variational::IsOverConstrained() const
{
  return myIsOverConstr;
}

AppParCurves_MultiBSpCurve AppDef_Variational::Value() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myMBSpCurve;
}

double AppDef_Variational::MaxError() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myMaxError;
}

int AppDef_Variational::MaxErrorIndex() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myMaxErrorIndex;
}

double AppDef_Variational::QuadraticError() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myCriterium[0];
}

void AppDef_Variational::Distance(math_Matrix& mat)

{
  if (!myIsDone)
    throw StdFail_NotDone();
  int                          ipoint, jp2d, jp3d, index;
  NCollection_Array1<gp_Pnt>   TabP3d(1, std::max(1, myNbP3d));
  NCollection_Array1<gp_Pnt2d> TabP2d(1, std::max(1, myNbP2d));
  int                          j0 = mat.LowerCol() - myFirstPoint;

  gp_Pnt2d P2d;
  gp_Pnt   P3d;

  gp_Pnt   Pt3d;
  gp_Pnt2d Pt2d;

  for (ipoint = myFirstPoint; ipoint <= myLastPoint; ipoint++)
  {
    index = 1;
    if (myNbP3d != 0)
    {
      AppDef_MyLineTool::Value(mySSP, ipoint, TabP3d);

      for (jp3d = 1; jp3d <= myNbP3d; jp3d++)

      {
        P3d = TabP3d.Value(jp3d);
        myMBSpCurve.Value(index, myParameters->Value(ipoint), Pt3d);
        mat(index++, j0 + ipoint) = P3d.Distance(Pt3d);
      }
    }
    if (myNbP2d != 0)
    {
      if (myNbP3d == 0)
        AppDef_MyLineTool::Value(mySSP, ipoint, TabP2d);
      else
        AppDef_MyLineTool::Value(mySSP, ipoint, TabP3d, TabP2d);
      for (jp2d = 1; jp2d <= myNbP2d; jp2d++)

      {
        P2d = TabP2d.Value(jp2d);
        myMBSpCurve.Value(index, myParameters->Value(ipoint), Pt2d);
        mat(index++, j0 + ipoint) = P2d.Distance(Pt2d);
      }
    }
  }
}

double AppDef_Variational::AverageError() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myAverageError;
}

const occ::handle<NCollection_HArray1<double>>& AppDef_Variational::Parameters() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myParameters;
}

const occ::handle<NCollection_HArray1<double>>& AppDef_Variational::Knots() const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  return myKnots;
}

void AppDef_Variational::Criterium(double& VFirstOrder,
                                   double& VSecondOrder,
                                   double& VThirdOrder) const
{
  if (!myIsDone)
    throw StdFail_NotDone();
  VFirstOrder  = myCriterium[1];
  VSecondOrder = myCriterium[2];
  VThirdOrder  = myCriterium[3];
}

void AppDef_Variational::CriteriumWeight(double& Percent1, double& Percent2, double& Percent3) const
{
  Percent1 = myPercent[0];
  Percent2 = myPercent[1];
  Percent3 = myPercent[2];
}

int AppDef_Variational::MaxDegree() const
{
  return myMaxDegree;
}

int AppDef_Variational::MaxSegment() const
{
  return myMaxSegment;
}

GeomAbs_Shape AppDef_Variational::Continuity() const
{
  return myContinuity;
}

bool AppDef_Variational::WithMinMax() const
{
  return myWithMinMax;
}

bool AppDef_Variational::WithCutting() const
{
  return myWithCutting;
}

double AppDef_Variational::Tolerance() const
{
  return myTolerance;
}

int AppDef_Variational::NbIterations() const
{
  return myNbIterations;
}

void AppDef_Variational::Dump(Standard_OStream& o) const
{
  o << " \nVariational Smoothing " << std::endl;
  o << " Number of multipoints                   " << myNbPoints << std::endl;
  o << " Number of 2d par multipoint " << myNbP2d << std::endl;
  o << " Nombre of 3d par multipoint " << myNbP3d << std::endl;
  o << " Number of PassagePoint      " << myNbPassPoints << std::endl;
  o << " Number of TangencyPoints    " << myNbTangPoints << std::endl;
  o << " Number of CurvaturePoints   " << myNbCurvPoints << std::endl;
  o << " \nTolerance " << o.setf(std::ios::scientific) << std::setprecision(3) << std::setw(9)
    << myTolerance;
  if (WithMinMax())
  {
    o << "  as Max Error." << std::endl;
  }
  else
  {
    o << "  as size Error." << std::endl;
  }
  o << "CriteriumWeights : " << myPercent[0] << " , " << myPercent[1] << " , " << myPercent[2]
    << std::endl;

  if (myIsDone)
  {
    o << " MaxError             " << std::setprecision(3) << std::setw(9) << myMaxError
      << std::endl;
    o << " Index of  MaxError   " << myMaxErrorIndex << std::endl;
    o << " Average Error        " << std::setprecision(3) << std::setw(9) << myAverageError
      << std::endl;
    o << " Quadratic Error      " << std::setprecision(3) << std::setw(9) << myCriterium[0]
      << std::endl;
    o << " Tension Criterium    " << std::setprecision(3) << std::setw(9) << myCriterium[1]
      << std::endl;
    o << " Flexion  Criterium   " << std::setprecision(3) << std::setw(9) << myCriterium[2]
      << std::endl;
    o << " Jerk  Criterium      " << std::setprecision(3) << std::setw(9) << myCriterium[3]
      << std::endl;
    o << " NbSegments           " << myKnots->Length() - 1 << std::endl;
  }
  else
  {
    o << (myIsOverConstr ? " The problem is overconstraint" : " Error in approximation")
      << std::endl;
  }
}

bool AppDef_Variational::SetConstraints(
  const occ::handle<NCollection_HArray1<AppParCurves_ConstraintCouple>>& aConstraint)

{
  myConstraints = aConstraint;
  Init();
  return !myIsOverConstr;
}

void AppDef_Variational::SetParameters(const occ::handle<NCollection_HArray1<double>>& param)
{
  myParameters->ChangeArray1() = param->Array1();
}

bool AppDef_Variational::SetKnots(const occ::handle<NCollection_HArray1<double>>& knots)
{
  myKnots->ChangeArray1() = knots->Array1();
  return true;
}

bool AppDef_Variational::SetMaxDegree(const int Degree)
{
  if (((Degree - myNivCont) * myMaxSegment - myNbPassPoints - 2 * myNbTangPoints
       - 3 * myNbCurvPoints)
      < 0)
    return false;
  else
  {
    myMaxDegree = Degree;

    InitSmoothCriterion();

    return true;
  }
}

bool AppDef_Variational::SetMaxSegment(const int NbSegment)
{
  if (myWithCutting
      && ((myMaxDegree - myNivCont) * NbSegment - myNbPassPoints - 2 * myNbTangPoints
          - 3 * myNbCurvPoints)
           < 0)
    return false;
  else
  {
    myMaxSegment = NbSegment;
    return true;
  }
}

bool AppDef_Variational::SetContinuity(const GeomAbs_Shape C)
{
  int NivCont = 0;
  switch (C)
  {
    case GeomAbs_C0:
      NivCont = 0;
      break;
    case GeomAbs_C1:
      NivCont = 1;
      break;
    case GeomAbs_C2:
      NivCont = 2;
      break;
    default:
      throw Standard_ConstructionError();
  }
  if (((myMaxDegree - NivCont) * myMaxSegment - myNbPassPoints - 2 * myNbTangPoints
       - 3 * myNbCurvPoints)
      < 0)
    return false;
  else
  {
    myContinuity = C;
    myNivCont    = NivCont;

    InitSmoothCriterion();
    return true;
  }
}

void AppDef_Variational::SetWithMinMax(const bool MinMax)
{
  myWithMinMax = MinMax;

  InitSmoothCriterion();
}

bool AppDef_Variational::SetWithCutting(const bool Cutting)
{
  if (!Cutting)
  {
    if (((myMaxDegree - myNivCont) * myKnots->Length() - myNbPassPoints - 2 * myNbTangPoints
         - 3 * myNbCurvPoints)
        < 0)
      return false;

    else
    {
      myWithCutting = Cutting;
      InitSmoothCriterion();
      return true;
    }
  }
  else
  {
    if (((myMaxDegree - myNivCont) * myMaxSegment - myNbPassPoints - 2 * myNbTangPoints
         - 3 * myNbCurvPoints)
        < 0)
      return false;

    else
    {
      myWithCutting = Cutting;
      InitSmoothCriterion();
      return true;
    }
  }
}

void AppDef_Variational::SetCriteriumWeight(const double Percent1,
                                            const double Percent2,
                                            const double Percent3)
{
  if (Percent1 < 0 || Percent2 < 0 || Percent3 < 0)
    throw Standard_DomainError();
  double Total = Percent1 + Percent2 + Percent3;
  myPercent[0] = Percent1 / Total;
  myPercent[1] = Percent2 / Total;
  myPercent[2] = Percent3 / Total;

  InitSmoothCriterion();
}

void AppDef_Variational::SetCriteriumWeight(const int Order, const double Percent)
{
  if (Percent < 0)
    throw Standard_DomainError();
  if (Order < 1 || Order > 3)
    throw Standard_ConstructionError();
  myPercent[Order - 1] = Percent;
  double Total         = myPercent[0] + myPercent[1] + myPercent[2];
  myPercent[0]         = myPercent[0] / Total;
  myPercent[1]         = myPercent[1] / Total;
  myPercent[2]         = myPercent[2] / Total;

  InitSmoothCriterion();
}

void AppDef_Variational::SetTolerance(const double Tol)
{
  myTolerance = Tol;
  InitSmoothCriterion();
}

void AppDef_Variational::SetNbIterations(const int Iter)
{
  myNbIterations = Iter;
}

void AppDef_Variational::TheMotor(occ::handle<AppDef_SmoothCriterion>& J,

                                  const double,
                                  const double                WQuality,
                                  occ::handle<FEmTool_Curve>& TheCurve,
                                  NCollection_Array1<double>& Ecarts)
{

  const double BigValue = 1.e37, SmallValue = 1.e-6, SmallestValue = 1.e-9;

  occ::handle<NCollection_HArray1<double>> CurrentTi, NewTi, OldTi;
  occ::handle<NCollection_HArray2<int>>    Dependence;
  bool                                     lestim, ToOptim, iscut;
  bool                                     isnear = false, again = true;
  int                                      NbEst, ICDANA, NumPnt, Iter;
  int                                      MaxNbEst = 5;
  double VOCRI[3] = {BigValue, BigValue, BigValue}, EROLD = BigValue, VALCRI[3], ERRMAX = BigValue,
         ERRMOY, ERRQUA;
  double                     CBLONG, LNOLD;
  int                        NbrPnt        = myLastPoint - myFirstPoint + 1;
  int                        NbrConstraint = myNbPassPoints + myNbTangPoints + myNbCurvPoints;
  occ::handle<FEmTool_Curve> CCurrent, COld, CNew;
  double                     EpsLength = SmallValue;
  double                     EpsDeg;

  double e1, e2, e3;
  double J1min, J2min, J3min;
  int    iprog;

  J->GetEstimation(e1, e2, e3);
  J1min = 1.e-8;
  J2min = J3min = (e1 + 1.e-8) * 1.e-6;

  if (e1 < J1min)
    e1 = J1min;
  if (e2 < J2min)
    e2 = J2min;
  if (e3 < J3min)
    e3 = J3min;

  J->SetEstimation(e1, e2, e3);

  CCurrent                  = TheCurve;
  CurrentTi                 = new NCollection_HArray1<double>(1, myParameters->Length());
  CurrentTi->ChangeArray1() = myParameters->Array1();
  OldTi                     = new (NCollection_HArray1<double>)(1, CurrentTi->Length());
  OldTi->ChangeArray1()     = CurrentTi->Array1();
  COld                      = CCurrent;
  LNOLD = CBLONG = J->EstLength();
  Dependence     = J->DependenceTable();

  J->SetCurve(CCurrent);
  FEmTool_Assembly* TheAssembly = new FEmTool_Assembly(Dependence->Array2(), J->AssemblyTable());

  while (again)
  {

    lestim      = true;
    bool lconst = true;
    NbEst       = 0;

    J->SetCurve(CCurrent);

    while (lestim)
    {

      EpsLength = SmallValue * CBLONG / NbrPnt;
      CNew      = new (
        FEmTool_Curve)(CCurrent->Dimension(), CCurrent->NbElements(), CCurrent->Base(), EpsLength);
      CNew->Knots() = CCurrent->Knots();

      J->SetParameters(CurrentTi);
      EpsDeg = std::min(WQuality * .1, CBLONG * .001);

      Optimization(J, *TheAssembly, lconst, EpsDeg, CNew, CurrentTi->Array1());

      lconst = false;

      ICDANA = J->QualityValues(J1min, J2min, J3min, VALCRI[0], VALCRI[1], VALCRI[2]);

      if (ICDANA > 0)
        lconst = true;

      J->ErrorValues(ERRMAX, ERRQUA, ERRMOY);

      isnear = ((std::sqrt(ERRQUA / NbrPnt) < 2 * WQuality) && (myNbIterations > 1));

      if (isnear)
      {
        NewTi = new (NCollection_HArray1<double>)(1, CurrentTi->Length());
        Project(CNew,
                CurrentTi->Array1(),
                NewTi->ChangeArray1(),
                Ecarts,
                NumPnt,
                ERRMAX,
                ERRQUA,
                ERRMOY,
                2);
      }
      else
        NewTi = CurrentTi;

      iprog = 0;
      if ((EROLD > WQuality) && (ERRMAX < 0.95 * EROLD))
        iprog++;
      if ((EROLD > WQuality) && (ERRMAX < 0.8 * EROLD))
        iprog++;
      if ((EROLD > WQuality) && (ERRMAX < WQuality))
        iprog++;
      if ((EROLD > WQuality) && (ERRMAX < 0.99 * EROLD) && (ERRMAX < 1.1 * WQuality))
        iprog++;
      if (VALCRI[0] < 0.975 * VOCRI[0])
        iprog++;
      if (VALCRI[0] < 0.9 * VOCRI[0])
        iprog++;
      if (VALCRI[1] < 0.95 * VOCRI[1])
        iprog++;
      if (VALCRI[1] < 0.8 * VOCRI[1])
        iprog++;
      if (VALCRI[2] < 0.95 * VOCRI[2])
        iprog++;
      if (VALCRI[2] < 0.8 * VOCRI[2])
        iprog++;
      if ((VOCRI[1] > SmallestValue) && (VOCRI[2] > SmallestValue))
      {
        if ((VALCRI[1] / VOCRI[1] + 2 * VALCRI[2] / VOCRI[2]) < 2.8)
          iprog++;
      }

      if (iprog < 2 && NbEst == 0)
      {

        VALCRI[0] = VOCRI[0];
        VALCRI[1] = VOCRI[1];
        VALCRI[2] = VOCRI[2];
        ERRMAX    = EROLD;
        CBLONG    = LNOLD;
        CCurrent  = COld;
        CurrentTi = OldTi;

        goto L8000;
      }

      VOCRI[0] = VALCRI[0];
      VOCRI[1] = VALCRI[1];
      VOCRI[2] = VALCRI[2];
      LNOLD    = CBLONG;
      EROLD    = ERRMAX;

      CCurrent  = CNew;
      CurrentTi = NewTi;

      NbEst++;
      lestim = ((NbEst < MaxNbEst) && (ICDANA == 2) && (iprog > 0));

      if (lestim && isnear)
      {

        std::stable_sort(CurrentTi->begin(), CurrentTi->end());

        int Decima = 4;

        CCurrent->Length(0., 1., CBLONG);
        J->EstLength() = CBLONG;

        ACR(CCurrent, CurrentTi->ChangeArray1(), Decima);
        lconst = true;
      }
    }

    Iter    = 1;
    ToOptim = ((Iter < myNbIterations) && (isnear));

    while (ToOptim)
    {
      Iter++;

      VOCRI[0]              = VALCRI[0];
      VOCRI[1]              = VALCRI[1];
      VOCRI[2]              = VALCRI[2];
      EROLD                 = ERRMAX;
      LNOLD                 = CBLONG;
      COld                  = CCurrent;
      OldTi->ChangeArray1() = CurrentTi->Array1();

      std::stable_sort(CurrentTi->begin(), CurrentTi->end());

      int Decima = 4;

      CCurrent->Length(0., 1., CBLONG);
      J->EstLength() = CBLONG;

      ACR(CCurrent, CurrentTi->ChangeArray1(), Decima);
      lconst = true;

      EpsLength = SmallValue * CBLONG / NbrPnt;

      CNew = new (
        FEmTool_Curve)(CCurrent->Dimension(), CCurrent->NbElements(), CCurrent->Base(), EpsLength);
      CNew->Knots() = CCurrent->Knots();

      J->SetParameters(CurrentTi);

      EpsDeg = std::min(WQuality * .1, CBLONG * .001);
      Optimization(J, *TheAssembly, lconst, EpsDeg, CNew, CurrentTi->Array1());

      CCurrent = CNew;

      ICDANA = J->QualityValues(J1min, J2min, J3min, VALCRI[0], VALCRI[1], VALCRI[2]);
      if (ICDANA > 0)
        lconst = true;

      J->GetEstimation(e1, e2, e3);

      NewTi = new (NCollection_HArray1<double>)(1, CurrentTi->Length());
      Project(CCurrent,
              CurrentTi->Array1(),
              NewTi->ChangeArray1(),
              Ecarts,
              NumPnt,
              ERRMAX,
              ERRQUA,
              ERRMOY,
              2);

      int iregre = 0;
      if (NbrConstraint < NbrPnt)
      {
        if ((ERRMAX > WQuality) && (ERRMAX > 1.05 * EROLD))
          iregre++;
        if ((ERRMAX > WQuality) && (ERRMAX > 2 * EROLD))
          iregre++;
        if ((EROLD > WQuality) && (ERRMAX <= 0.5 * EROLD))
          iregre--;
      }
      double E1, E2, E3;
      J->GetEstimation(E1, E2, E3);
      if ((VALCRI[0] > E1) && (VALCRI[0] > 1.1 * VOCRI[0]))
        iregre++;
      if ((VALCRI[1] > E2) && (VALCRI[1] > 1.1 * VOCRI[1]))
        iregre++;
      if ((VALCRI[2] > E3) && (VALCRI[2] > 1.1 * VOCRI[2]))
        iregre++;

      if (iregre >= 2)
      {

        VALCRI[0]                 = VOCRI[0];
        VALCRI[1]                 = VOCRI[1];
        VALCRI[2]                 = VOCRI[2];
        ERRMAX                    = EROLD;
        CBLONG                    = LNOLD;
        CCurrent                  = COld;
        CurrentTi->ChangeArray1() = OldTi->Array1();
        ToOptim                   = false;
      }
      else
      {
        CCurrent  = CNew;
        CurrentTi = NewTi;
      }
      if (Iter >= myNbIterations)
        ToOptim = false;
    }

    if ((CCurrent->NbElements() < myMaxSegment) && myWithCutting)
    {

      VOCRI[0]              = VALCRI[0];
      VOCRI[1]              = VALCRI[1];
      VOCRI[2]              = VALCRI[2];
      EROLD                 = ERRMAX;
      COld                  = CCurrent;
      OldTi->ChangeArray1() = CurrentTi->Array1();

      std::stable_sort(CurrentTi->begin(), CurrentTi->end());

      if ((CurrentTi->Value(1) != 0.) || (CurrentTi->Value(NbrPnt) != 1.))
      {
        double t, DelatT = 1.0 / (CurrentTi->Value(NbrPnt) - CurrentTi->Value(1));
        for (int ii = 2; ii < NbrPnt; ii++)
        {
          t = (CurrentTi->Value(ii) - CurrentTi->Value(1)) * DelatT;
          CurrentTi->SetValue(ii, t);
        }
        CurrentTi->SetValue(1, 0.);
        CurrentTi->SetValue(NbrPnt, 1.);
      }

      SplitCurve(CCurrent, CurrentTi->Array1(), EpsLength, CNew, iscut);
      if (!iscut)
        again = false;
      else
      {
        CCurrent = CNew;

        J->SetCurve(CNew);
        delete TheAssembly;
        TheAssembly = new FEmTool_Assembly(Dependence->Array2(), J->AssemblyTable());
      }
    }
    else
    {
      again = false;
    }
  }

L8000:

  NewTi = new (NCollection_HArray1<double>)(1, CurrentTi->Length());
  Project(CCurrent,
          CurrentTi->Array1(),
          NewTi->ChangeArray1(),
          Ecarts,
          NumPnt,
          ERRMAX,
          ERRQUA,
          ERRMOY,
          10);

  TheCurve                     = CCurrent;
  J->EstLength()               = CBLONG;
  myParameters->ChangeArray1() = NewTi->Array1();
  myCriterium[0]               = ERRQUA;
  myCriterium[1]               = std::sqrt(VALCRI[0]);
  myCriterium[2]               = std::sqrt(VALCRI[1]);
  myCriterium[3]               = std::sqrt(VALCRI[2]);
  myMaxError                   = ERRMAX;
  myMaxErrorIndex              = NumPnt;
  if (NbrPnt > NbrConstraint)
    myAverageError = ERRMOY / (NbrPnt - NbrConstraint);
  else
    myAverageError = ERRMOY / NbrConstraint;

  delete TheAssembly;
}

void AppDef_Variational::Optimization(occ::handle<AppDef_SmoothCriterion>& J,
                                      FEmTool_Assembly&                    A,
                                      const bool                           ToAssemble,
                                      const double                         EpsDeg,
                                      occ::handle<FEmTool_Curve>&          Curve,
                                      const NCollection_Array1<double>&    Parameters) const
{
  int MxDeg = Curve->Base().WorkDegree(), NbElm = Curve->NbElements(), NbDim = Curve->Dimension();

  occ::handle<NCollection_HArray2<occ::handle<NCollection_HArray1<int>>>> AssTable;

  math_Matrix H(0, MxDeg, 0, MxDeg);
  math_Vector G(0, MxDeg), Sol(1, A.NbGlobVar());

  int el, dim;

  A.GetAssemblyTable(AssTable);
  int NbConstr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;

  double CBLONG = J->EstLength();

  if (ToAssemble)
    A.NullifyMatrix();
  A.NullifyVector();

  for (el = 1; el <= NbElm; el++)
  {
    if (ToAssemble)
    {
      J->Hessian(el, 1, 1, H);
      for (dim = 1; dim <= NbDim; dim++)
        A.AddMatrix(el, dim, dim, H);
    }

    for (dim = 1; dim <= NbDim; dim++)
    {
      J->Gradient(el, dim, G);
      A.AddVector(el, dim, G);
    }
  }

  if (ToAssemble)
  {
    if (NbConstr != 0)
    {
      AssemblingConstraints(Curve, Parameters, CBLONG, A);
    }
    A.Solve();
  }
  A.Solution(Sol);

  J->SetCurve(Curve);
  J->InputVector(Sol, AssTable);

  int    Newdeg;
  double MaxError;

  if (NbConstr == 0)
  {
    for (el = 1; el <= NbElm; el++)
    {
      Curve->ReduceDegree(el, EpsDeg, Newdeg, MaxError);
    }
  }
  else
  {

    NCollection_Array1<double>& TabInt = Curve->Knots();
    int                         Icnt = 1, p0 = Parameters.Lower() - myFirstPoint, point;
    for (el = 1; el <= NbElm; el++)
    {
      while ((Icnt < NbConstr)
             && (Parameters(p0 + myTypConstraints->Value(2 * Icnt - 1)) <= TabInt(el)))
        Icnt++;
      point = p0 + myTypConstraints->Value(2 * Icnt - 1);
      if (Parameters(point) <= TabInt(el) || Parameters(point) >= TabInt(el + 1))
        Curve->ReduceDegree(el, EpsDeg, Newdeg, MaxError);
      else if (Curve->Degree(el) < MxDeg)
        Curve->SetDegree(el, MxDeg);
    }
  }
}

void AppDef_Variational::Project(const occ::handle<FEmTool_Curve>& C,
                                 const NCollection_Array1<double>& Ti,
                                 NCollection_Array1<double>&       ProjTi,
                                 NCollection_Array1<double>&       Distance,
                                 int&                              NumPoints,
                                 double&                           MaxErr,
                                 double&                           QuaErr,
                                 double&                           AveErr,
                                 const int                         NbIterations) const

{

  const double Seuil = 1.e-9, Eps = 1.e-12;

  MaxErr = QuaErr = AveErr = 0.;

  int Ipnt, NItCv, Iter, i, i0 = -myDimension, d0 = Distance.Lower() - 1;

  double TNew, Dist, T0, Dist0, F1, F2, Aux, DF, Ecart;

  bool EnCour;

  NCollection_Array1<double> ValOfC(1, myDimension), FirstDerOfC(1, myDimension),
    SecndDerOfC(1, myDimension);

  for (Ipnt = 1; Ipnt <= ProjTi.Length(); Ipnt++)
  {

    i0 += myDimension;

    TNew = Ti(Ipnt);

    EnCour = true;
    NItCv  = 0;
    Iter   = 0;
    C->D0(TNew, ValOfC);

    Dist = 0;
    for (i = 1; i <= myDimension; i++)
    {
      Aux = ValOfC(i) - myTabPoints->Value(i0 + i);
      Dist += Aux * Aux;
    }
    Dist = std::sqrt(Dist);

    while (EnCour)
    {

      Iter++;
      T0    = TNew;
      Dist0 = Dist;

      C->D2(TNew, SecndDerOfC);
      C->D1(TNew, FirstDerOfC);

      F1 = F2 = 0.;
      for (i = 1; i <= myDimension; i++)
      {
        Aux = ValOfC(i) - myTabPoints->Value(i0 + i);
        DF  = FirstDerOfC(i);
        F1 += Aux * DF;
        F2 += DF * DF + Aux * SecndDerOfC(i);
      }

      if (std::abs(F2) < Eps)
        EnCour = false;
      else
      {

        TNew -= F1 / F2;
        if (TNew < 0.)
          TNew = 0.;
        if (TNew > 1.)
          TNew = 1.;

        C->D0(TNew, ValOfC);

        Dist = 0;
        for (i = 1; i <= myDimension; i++)
        {
          Aux = ValOfC(i) - myTabPoints->Value(i0 + i);
          Dist += Aux * Aux;
        }
        Dist = std::sqrt(Dist);

        Ecart = Dist0 - Dist;

        if (Ecart <= -Seuil)
        {

          EnCour = false;
          TNew   = T0;
          Dist   = Dist0;
        }
        else if (Ecart <= Seuil)

          NItCv++;
        else
          NItCv = 0;

        if ((NItCv >= 2) || (Iter >= NbIterations))
          EnCour = false;
      }
    }

    ProjTi(Ipnt)        = TNew;
    Distance(d0 + Ipnt) = Dist;
    if (Dist > MaxErr)
    {
      MaxErr    = Dist;
      NumPoints = Ipnt;
    }
    QuaErr += Dist * Dist;
    AveErr += Dist;
  }

  NumPoints = NumPoints + myFirstPoint - 1;
}

void AppDef_Variational::ACR(occ::handle<FEmTool_Curve>& Curve,
                             NCollection_Array1<double>& Ti,
                             const int                   Decima) const
{

  const double Eps = 1.e-8;

  NCollection_Array1<double>& Knots = Curve->Knots();
  int NbrPnt = Ti.Length(), TiFirst = Ti.Lower(), TiLast = Ti.Upper(), KFirst = Knots.Lower(),
      KLast = Knots.Upper();

  double CbLong, DeltaT, VTest, UNew, UOld, DU, TPara, TOld, DTInv, Ratio;
  int    ipnt, ii, IElm, IOld, POld, PCnt, ICnt = 0;
  int    NbCntr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;

  Curve->Length(Ti(TiFirst), Ti(TiLast), CbLong);

  if (NbrPnt >= 2)
  {

    DeltaT = (Ti(TiLast) - Ti(TiFirst)) / Decima;
    VTest  = Ti(TiFirst) + DeltaT;

    if (NbCntr > 0)
    {
      PCnt = myTypConstraints->Value(1) - myFirstPoint + TiFirst;
      ICnt = 1;
    }
    else
      PCnt = TiLast + 1;

    UOld = 0.;

    TOld = Ti(TiFirst);
    POld = TiFirst;

    IElm = KFirst;
    IOld = IElm;

    Ti(TiFirst) = 0.;

    for (ipnt = TiFirst + 1; ipnt <= TiLast; ipnt++)
    {

      while ((ICnt <= NbCntr) && (PCnt < ipnt))
      {
        ICnt++;
        PCnt = myTypConstraints->Value(2 * ICnt - 1) - myFirstPoint + TiFirst;
      }

      TPara = Ti(ipnt);

      if (TPara >= VTest || PCnt == ipnt)
      {

        if (Ti(TiLast) - TPara <= 1.e-2 * DeltaT)
        {
          ipnt  = TiLast;
          TPara = Ti(ipnt);
        }

        Curve->Length(Ti(TiFirst), TPara, UNew);

        UNew /= CbLong;

        while (Knots(IElm + 1) < TPara && IElm < KLast - 1)
          IElm++;

        DTInv = 1. / (TPara - TOld);
        DU    = UNew - UOld;

        for (ii = IOld + 1; ii <= IElm; ii++)
        {
          Ratio     = (Knots(ii) - TOld) * DTInv;
          Knots(ii) = UOld + Ratio * DU;
        }

        for (ii = POld + 1; ii <= ipnt - 1; ii++)
        {
          Ratio  = (Ti(ii) - TOld) * DTInv;
          Ti(ii) = UOld + Ratio * DU;
        }

        Ti(ipnt) = UNew;

        UOld = UNew;
        IOld = IElm;
        TOld = TPara;
        POld = ipnt;
      }

      if (TPara >= VTest)
      {

        VTest += std::ceil((TPara - VTest + Eps) / DeltaT) * DeltaT;
        if (VTest > 1. - Eps)
          VTest = 1.;
      }
    }
  }

  Ti(TiFirst) = 0.;
  Ti(TiLast)  = 1.;
  ii          = TiLast - 1;
  while (Ti(ii) > Knots(KLast))
  {
    Ti(ii) = 1.;
    --ii;
  }
  Knots(KFirst) = 0.;
  Knots(KLast)  = 1.;
}

static int NearIndex(const double                      T,
                     const NCollection_Array1<double>& TabPar,
                     const double                      Eps,
                     int&                              Flag)
{
  int Loi = TabPar.Lower(), Upi = TabPar.Upper();

  Flag = 0;

  if (T < TabPar(Loi))
  {
    Flag = -1;
    return Loi;
  }
  if (T > TabPar(Upi))
  {
    Flag = 1;
    return Upi;
  }

  int Ibeg = Loi, Ifin = Upi, Imidl;

  while (Ibeg + 1 != Ifin)
  {
    Imidl = (Ibeg + Ifin) / 2;
    if ((T >= TabPar(Ibeg)) && (T <= TabPar(Imidl)))
      Ifin = Imidl;
    else
      Ibeg = Imidl;
  }

  if (std::abs(T - TabPar(Ifin)) < Eps)
    return Ifin;

  return Ibeg;
}

static void GettingKnots(const NCollection_Array1<double>& TabPar,
                         const occ::handle<FEmTool_Curve>& InCurve,
                         const int                         Deg,
                         int&                              NbElm,
                         NCollection_Array1<double>&       NewKnots)

{

  const double Eps = 1.e-12;

  NCollection_Array1<double>& OldKnots = InCurve->Knots();
  int                         NbMaxOld = InCurve->NbElements();
  int                         NbMax    = NewKnots.Upper(), Ipt, Ipt1, Ipt2;
  int                         el = 0, i1 = OldKnots.Lower(), i0 = i1 - 1, Flag;
  double                      TPar;

  while ((NbElm < NbMax) && (el < NbMaxOld))
  {

    el++;
    i0++;
    i1++;

    if (InCurve->Degree(el) == Deg)
    {

      NbElm++;

      Ipt1 = NearIndex(OldKnots(i0), TabPar, Eps, Flag);
      if (Flag != 0)
        Ipt1 = TabPar.Lower();
      Ipt2 = NearIndex(OldKnots(i1), TabPar, Eps, Flag);
      if (Flag != 0)
        Ipt2 = TabPar.Upper();

      if (Ipt2 - Ipt1 >= 1)
      {

        Ipt = (Ipt1 + Ipt2) / 2;
        if (2 * Ipt == Ipt1 + Ipt2)
          TPar = 2. * TabPar(Ipt);
        else
          TPar = TabPar(Ipt) + TabPar(Ipt + 1);

        NewKnots(NbElm) = (OldKnots(i0) + OldKnots(i1) + TPar) / 4.;
      }
      else
        NewKnots(NbElm) = (OldKnots(i0) + OldKnots(i1)) / 2.;
    }
  }
}

void AppDef_Variational::SplitCurve(const occ::handle<FEmTool_Curve>& InCurve,
                                    const NCollection_Array1<double>& Ti,
                                    const double                      CurveTol,
                                    occ::handle<FEmTool_Curve>&       OutCurve,
                                    bool&                             iscut) const
{
  int NbElmOld = InCurve->NbElements();

  if (NbElmOld >= myMaxSegment)
  {
    iscut = false;
    return;
  }
#ifdef OCCT_DEBUG
  int MaxDegree =
#endif
    InCurve->Base().WorkDegree();
  int                        NbElm = NbElmOld;
  NCollection_Array1<double> NewKnots(NbElm + 1, myMaxSegment);
#ifndef OCCT_DEBUG
  GettingKnots(Ti, InCurve, InCurve->Base().WorkDegree(), NbElm, NewKnots);
  GettingKnots(Ti, InCurve, InCurve->Base().WorkDegree() - 1, NbElm, NewKnots);
#else
  GettingKnots(Ti, InCurve, MaxDegree, NbElm, NewKnots);
  GettingKnots(Ti, InCurve, MaxDegree - 1, NbElm, NewKnots);

#endif
  if (NbElm > NbElmOld)
  {

    iscut = true;

    OutCurve = new FEmTool_Curve(InCurve->Dimension(), NbElm, InCurve->Base(), CurveTol);
    NCollection_Array1<double>& OutKnots = OutCurve->Knots();
    NCollection_Array1<double>& InKnots  = InCurve->Knots();

    int i, i0 = OutKnots.Lower();
    for (i = InKnots.Lower(); i <= InKnots.Upper(); i++)
      OutKnots(i) = InKnots(i);
    for (i = NbElmOld + 1; i <= NbElm; i++)
      OutKnots(i + i0) = NewKnots(i);

    std::sort(OutKnots.begin(), OutKnots.end());
  }
  else
    iscut = false;
}

void AppDef_Variational::InitSmoothCriterion()
{

  const double Eps2 = 1.e-6, Eps3 = 1.e-9;

  double Length;

  InitParameters(Length);

  mySmoothCriterion->SetParameters(myParameters);

  double E1, E2, E3;

  InitCriterionEstimations(Length, E1, E2, E3);

  mySmoothCriterion->EstLength() = Length;
  mySmoothCriterion->SetEstimation(E1, E2, E3);

  double WQuadratic, WQuality;

  if (!myWithMinMax && myTolerance != 0.)
    WQuality = myTolerance;
  else if (myTolerance == 0.)
    WQuality = 1.;
  else
    WQuality = std::max(myTolerance, Eps2 * Length);

  int NbConstr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;
  WQuadratic   = std::sqrt((double)(myNbPoints - NbConstr)) * WQuality;
  if (WQuadratic > Eps3)
    WQuadratic = 1. / WQuadratic;

  if (WQuadratic == 0.)
    WQuadratic = std::max(std::sqrt(E1), 1.);

  mySmoothCriterion->SetWeight(WQuadratic, WQuality, myPercent[0], myPercent[1], myPercent[2]);

  PLib_HermitJacobi          TheBase(myMaxDegree, myContinuity);
  occ::handle<FEmTool_Curve> TheCurve;
  int                        NbElem;
  double                     CurvTol = Eps2 * Length / myNbPoints;

  if (myWithCutting && NbConstr != 0)
  {

    InitCutting(TheBase, CurvTol, TheCurve);
  }
  else
  {

    NbElem   = 1;
    TheCurve = new FEmTool_Curve(myDimension, NbElem, TheBase, CurvTol);
    TheCurve->Knots().SetValue(TheCurve->Knots().Lower(), myParameters->Value(myFirstPoint));
    TheCurve->Knots().SetValue(TheCurve->Knots().Upper(), myParameters->Value(myLastPoint));
  }

  mySmoothCriterion->SetCurve(TheCurve);

  return;
}

void AppDef_Variational::InitParameters(double& Length)
{

  constexpr double Eps1 = Precision::Confusion() * .01;

  double aux, dist;
  int    i, i0, i1 = 0, ipoint;

  Length = 0.;
  myParameters->SetValue(myFirstPoint, Length);

  for (ipoint = myFirstPoint + 1; ipoint <= myLastPoint; ipoint++)
  {
    i0 = i1;
    i1 += myDimension;
    dist = 0;
    for (i = 1; i <= myDimension; i++)
    {
      aux = myTabPoints->Value(i1 + i) - myTabPoints->Value(i0 + i);
      dist += aux * aux;
    }
    Length += std::sqrt(dist);
    myParameters->SetValue(ipoint, Length);
  }

  if (Length <= Eps1)
    throw Standard_ConstructionError("AppDef_Variational::InitParameters");

  for (ipoint = myFirstPoint + 1; ipoint <= myLastPoint - 1; ipoint++)
    myParameters->SetValue(ipoint, myParameters->Value(ipoint) / Length);

  myParameters->SetValue(myLastPoint, 1.);

  if (myNbPoints < 10)
    Length *= (1. + 0.1 / (myNbPoints - 1));
}

void AppDef_Variational::InitCriterionEstimations(const double Length,
                                                  double&      E1,
                                                  double&      E2,
                                                  double&      E3) const
{
  E1 = Length * Length;

  constexpr double Eps1 = Precision::Confusion() * .01;

  math_Vector VTang1(1, myDimension), VTang2(1, myDimension), VTang3(1, myDimension),
    VScnd1(1, myDimension), VScnd2(1, myDimension), VScnd3(1, myDimension);

  int ipnt = myFirstPoint;

  EstTangent(ipnt, VTang1);
  ipnt++;
  EstTangent(ipnt, VTang2);
  ipnt++;
  EstTangent(ipnt, VTang3);

  ipnt = myFirstPoint;
  EstSecnd(ipnt, VTang1, VTang2, Length, VScnd1);
  ipnt++;
  EstSecnd(ipnt, VTang1, VTang3, Length, VScnd2);

  int    anInd = ipnt;
  double Delta = .5 * (myParameters->Value(anInd) - myParameters->Value(--ipnt));

  if (Delta <= Eps1)
    Delta = 1.;

  E2 = VScnd1.Norm2() * Delta;

  E3 = (Delta > Eps1) ? VScnd2.Subtracted(VScnd1).Norm2() / (4. * Delta) : 0.;

  int CurrPoint = 2;

  for (ipnt = myFirstPoint + 1; ipnt < myLastPoint; ipnt++)
  {

    Delta = .5 * (myParameters->Value(ipnt + 1) - myParameters->Value(ipnt - 1));

    if (CurrPoint == 1)
    {
      if (ipnt + 1 != myLastPoint)
      {
        EstTangent(ipnt + 2, VTang3);
        EstSecnd(ipnt + 1, VTang1, VTang3, Length, VScnd2);
      }
      else
        EstSecnd(ipnt + 1, VTang1, VTang2, Length, VScnd2);

      E2 += VScnd1.Norm2() * Delta;
      E3 += (Delta > Eps1) ? VScnd2.Subtracted(VScnd3).Norm2() / (4. * Delta) : 0.;
    }
    else if (CurrPoint == 2)
    {
      if (ipnt + 1 != myLastPoint)
      {
        EstTangent(ipnt + 2, VTang1);
        EstSecnd(ipnt + 1, VTang2, VTang1, Length, VScnd3);
      }
      else
        EstSecnd(ipnt + 1, VTang2, VTang3, Length, VScnd3);

      E2 += VScnd2.Norm2() * Delta;
      E3 += (Delta > Eps1) ? VScnd3.Subtracted(VScnd1).Norm2() / (4. * Delta) : 0.;
    }
    else
    {
      if (ipnt + 1 != myLastPoint)
      {
        EstTangent(ipnt + 2, VTang2);
        EstSecnd(ipnt + 1, VTang3, VTang2, Length, VScnd1);
      }
      else
        EstSecnd(ipnt + 1, VTang3, VTang1, Length, VScnd1);

      E2 += VScnd3.Norm2() * Delta;
      E3 += (Delta > Eps1) ? VScnd1.Subtracted(VScnd2).Norm2() / (4. * Delta) : 0.;
    }

    CurrPoint++;
    if (CurrPoint == 4)
      CurrPoint = 1;
  }

  Delta = .5 * (myParameters->Value(myLastPoint) - myParameters->Value(myLastPoint - 1));
  if (Delta <= Eps1)
    Delta = 1.;

  double aux;

  if (CurrPoint == 1)
  {

    E2 += VScnd1.Norm2() * Delta;
    aux = VScnd1.Subtracted(VScnd3).Norm2();
    E3 += (Delta > Eps1) ? aux / (4. * Delta) : aux;
  }
  else if (CurrPoint == 2)
  {

    E2 += VScnd2.Norm2() * Delta;
    aux = VScnd2.Subtracted(VScnd1).Norm2();
    E3 += (Delta > Eps1) ? aux / (4. * Delta) : aux;
  }
  else
  {

    E2 += VScnd3.Norm2() * Delta;
    aux = VScnd3.Subtracted(VScnd2).Norm2();
    E3 += (Delta > Eps1) ? aux / (4. * Delta) : aux;
  }

  aux = Length * Length;

  E2 *= aux;
  E3 *= aux;
}

void AppDef_Variational::EstTangent(const int ipnt, math_Vector& VTang) const

{
  int              i;
  constexpr double Eps1    = Precision::Confusion() * .01;
  const double     EpsNorm = 1.e-9;

  double Wpnt = 1.;

  if (ipnt == myFirstPoint)
  {

    if (myNbPoints < 3)
      Wpnt = 0.;
    else
    {

      int adr1 = 1, adr2 = adr1 + myDimension, adr3 = adr2 + myDimension;

      math_Vector Pnt1((double*)&myTabPoints->Value(adr1), 1, myDimension);
      math_Vector Pnt2((double*)&myTabPoints->Value(adr2), 1, myDimension);
      math_Vector Pnt3((double*)&myTabPoints->Value(adr3), 1, myDimension);

      double V1 = Pnt2.Subtracted(Pnt1).Norm();
      double V2 = 0.;
      if (V1 > Eps1)
        V2 = Pnt3.Subtracted(Pnt2).Norm();
      if (V2 > Eps1)
      {
        double d = V1 / (V1 + V2), d1;
        d1       = 1. / (d * (1 - d));
        d *= d;
        VTang = ((d - 1.) * Pnt1 + Pnt2 - d * Pnt3) * d1;
      }
      else
      {

        VTang = Pnt2 - Pnt1;
      }
    }
  }
  else if (ipnt == myLastPoint)
  {

    if (myNbPoints < 3)
      Wpnt = 0.;
    else
    {

      int adr1 = (myLastPoint - 3) * myDimension + 1, adr2 = adr1 + myDimension,
          adr3 = adr2 + myDimension;

      math_Vector Pnt1((double*)&myTabPoints->Value(adr1), 1, myDimension);
      math_Vector Pnt2((double*)&myTabPoints->Value(adr2), 1, myDimension);
      math_Vector Pnt3((double*)&myTabPoints->Value(adr3), 1, myDimension);

      double V1 = Pnt2.Subtracted(Pnt1).Norm();
      double V2 = 0.;
      if (V1 > Eps1)
        V2 = Pnt3.Subtracted(Pnt2).Norm();
      if (V2 > Eps1)
      {
        double d = V1 / (V1 + V2), d1;
        d1       = 1. / (d * (1 - d));
        d *= d - 2;
        VTang = ((d + 1.) * Pnt1 - Pnt2 - d * Pnt3) * d1;
      }
      else
      {

        VTang = Pnt3 - Pnt2;
      }
    }
  }
  else
  {

    int adr1 = (ipnt - myFirstPoint - 1) * myDimension + 1, adr2 = adr1 + 2 * myDimension;

    math_Vector Pnt1((double*)&myTabPoints->Value(adr1), 1, myDimension);
    math_Vector Pnt2((double*)&myTabPoints->Value(adr2), 1, myDimension);

    VTang = Pnt2 - Pnt1;
  }

  double Vnorm = VTang.Norm();

  if (Vnorm <= EpsNorm)
    VTang.Init(0.);
  else
    VTang /= Vnorm;

  double Wcnt  = 0.;
  int    IdCnt = 1;

  int         NbConstr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;
  math_Vector VCnt(1, myDimension, 0.);

  if (NbConstr > 0)
  {

    while (myTypConstraints->Value(2 * IdCnt - 1) < ipnt && IdCnt <= NbConstr)
      IdCnt++;
    if ((myTypConstraints->Value(2 * IdCnt - 1) == ipnt)
        && (myTypConstraints->Value(2 * IdCnt) >= 1))
    {
      Wcnt   = 1.;
      int i0 = 2 * myDimension * (IdCnt - 1), k = 0;
      for (i = 1; i <= myNbP3d; i++)
      {
        for (int j = 1; j <= 3; j++)
          VCnt(++k) = myTabConstraints->Value(++i0);
        i0 += 3;
      }
      for (i = 1; i <= myNbP2d; i++)
      {
        for (int j = 1; j <= 2; j++)
          VCnt(++k) = myTabConstraints->Value(++i0);
        i0 += 2;
      }
    }
  }

  double Denom = Wpnt + Wcnt;
  if (Denom == 0.)
    Denom = 1.;
  else
    Denom = 1. / Denom;

  VTang = (Wpnt * VTang + Wcnt * VCnt) * Denom;

  Vnorm = VTang.Norm();

  if (Vnorm <= EpsNorm)
    VTang.Init(0.);
  else
    VTang /= Vnorm;
}

void AppDef_Variational::EstSecnd(const int          ipnt,
                                  const math_Vector& VTang1,
                                  const math_Vector& VTang2,
                                  const double       Length,
                                  math_Vector&       VScnd) const
{
  int i;

  const double Eps = 1.e-9;

  double Wpnt = 1.;

  double aux;

  if (ipnt == myFirstPoint)
    aux = myParameters->Value(ipnt + 1) - myParameters->Value(ipnt);
  else if (ipnt == myLastPoint)
    aux = myParameters->Value(ipnt) - myParameters->Value(ipnt - 1);
  else
    aux = myParameters->Value(ipnt + 1) - myParameters->Value(ipnt - 1);

  if (aux <= Eps)
    aux = 1.;
  else
    aux = 1. / aux;

  VScnd = (VTang2 - VTang1) * aux;

  double Wcnt  = 0.;
  int    IdCnt = 1;

  int         NbConstr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;
  math_Vector VCnt(1, myDimension, 0.);

  if (NbConstr > 0)
  {

    while (myTypConstraints->Value(2 * IdCnt - 1) < ipnt && IdCnt <= NbConstr)
      IdCnt++;

    if ((myTypConstraints->Value(2 * IdCnt - 1) == ipnt)
        && (myTypConstraints->Value(2 * IdCnt) >= 2))
    {
      Wcnt   = 1.;
      int i0 = 2 * myDimension * (IdCnt - 1) + 3, k = 0;
      for (i = 1; i <= myNbP3d; i++)
      {
        for (int j = 1; j <= 3; j++)
          VCnt(++k) = myTabConstraints->Value(++i0);
        i0 += 3;
      }
      i0--;
      for (i = 1; i <= myNbP2d; i++)
      {
        for (int j = 1; j <= 2; j++)
          VCnt(++k) = myTabConstraints->Value(++i0);
        i0 += 2;
      }
    }
  }

  double Denom = Wpnt + Wcnt;
  if (Denom == 0.)
    Denom = 1.;
  else
    Denom = 1. / Denom;

  VScnd = (Wpnt * VScnd + (Wcnt * Length) * VCnt) * Denom;
}

void AppDef_Variational::InitCutting(const PLib_HermitJacobi&    aBase,
                                     const double                CurvTol,
                                     occ::handle<FEmTool_Curve>& aCurve) const
{

  int ORCMx = -1, NCont = 0, i, kk, NbElem;
  int NbConstr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;

  for (i = 1; i <= NbConstr; i++)
  {
    kk    = std::abs(myTypConstraints->Value(2 * i)) + 1;
    ORCMx = std::max(ORCMx, kk);
    NCont += kk;
  }

  if (ORCMx > myMaxDegree - myNivCont)
    throw Standard_ConstructionError("AppDef_Variational::InitCutting");

  int NLibre = std::max(myMaxDegree - myNivCont - (myMaxDegree + 1) / 4, myNivCont + 1);

  NbElem = (NCont % NLibre == 0) ? NCont / NLibre : NCont / NLibre + 1;

  while ((NbElem > myMaxSegment) && (NLibre < myMaxDegree - myNivCont))
  {

    NLibre++;
    NbElem = (NCont % NLibre == 0) ? NCont / NLibre : NCont / NLibre + 1;
  }

  if (NbElem > myMaxSegment)
    throw Standard_ConstructionError("AppDef_Variational::InitCutting");

  aCurve = new FEmTool_Curve(myDimension, NbElem, aBase, CurvTol);

  int NCnt  = (NCont - 1) / NbElem + 1;
  int NPlus = NbElem - (NCnt * NbElem - NCont);

  NCollection_Array1<double>& Knot = aCurve->Knots();

  int IDeb = 0, IFin = NbConstr + 1, NDeb = 0, NFin = 0, IndEl = Knot.Lower(),
      IUpper = Knot.Upper(), NbEl = 0;

  Knot(IndEl)  = myParameters->Value(myFirstPoint);
  Knot(IUpper) = myParameters->Value(myLastPoint);

  while (NbElem - NbEl > 1)
  {

    IndEl++;
    NbEl++;
    if (NPlus == 0)
      NCnt--;

    while (NDeb < NCnt && IDeb < IFin)
    {
      IDeb++;
      NDeb += std::abs(myTypConstraints->Value(2 * IDeb)) + 1;
    }

    if (NDeb == NCnt)
    {
      NDeb = 0;
      if (NPlus == 1
          && myParameters->Value(myTypConstraints->Value(2 * IDeb - 1)) > Knot(IndEl - 1))

        Knot(IndEl) = myParameters->Value(myTypConstraints->Value(2 * IDeb - 1));
      else
        Knot(IndEl) = (myParameters->Value(myTypConstraints->Value(2 * IDeb - 1))
                       + myParameters->Value(myTypConstraints->Value(2 * IDeb + 1)))
                      / 2;
    }
    else
    {
      NDeb -= NCnt;
      Knot(IndEl) = myParameters->Value(myTypConstraints->Value(2 * IDeb - 1));
    }

    NPlus--;
    if (NPlus == 0)
      NCnt--;

    if (NbElem - NbEl == 1)
      break;

    NbEl++;

    while (NFin < NCnt && IDeb < IFin)
    {
      IFin--;
      NFin += std::abs(myTypConstraints->Value(2 * IFin)) + 1;
    }

    if (NFin == NCnt)
    {
      NFin                     = 0;
      Knot(IUpper + 1 - IndEl) = (myParameters->Value(myTypConstraints->Value(2 * IFin - 1))
                                  + myParameters->Value(myTypConstraints->Value(2 * IFin - 3)))
                                 / 2;
    }
    else
    {
      NFin -= NCnt;
      if (myParameters->Value(myTypConstraints->Value(2 * IFin - 1)) < Knot(IUpper - IndEl + 1))
        Knot(IUpper + 1 - IndEl) = myParameters->Value(myTypConstraints->Value(2 * IFin - 1));
      else
        Knot(IUpper + 1 - IndEl) = (myParameters->Value(myTypConstraints->Value(2 * IFin - 1))
                                    + myParameters->Value(myTypConstraints->Value(2 * IFin - 3)))
                                   / 2;
    }
  }
}

void AppDef_Variational::Adjusting(occ::handle<AppDef_SmoothCriterion>& J,
                                   double&                              WQuadratic,
                                   double&                              WQuality,
                                   occ::handle<FEmTool_Curve>&          TheCurve,
                                   NCollection_Array1<double>&          Ecarts)
{

  const int    mxiter        = 2;
  const double eps1          = 1e-6;
  int          NbrPnt        = myLastPoint - myFirstPoint + 1;
  int          NbrConstraint = myNbPassPoints + myNbTangPoints + myNbCurvPoints;
  double       CurvTol       = eps1 * J->EstLength() / NbrPnt;

  int                                 iter, ipnt;
  double                              ecart, emold, erold, tpara;
  double                              vocri[4], j1cibl, vtest, vseuil;
  int                                 i, numint, flag;
  NCollection_Array1<double>          tbpoid(myFirstPoint, myLastPoint);
  bool                                loptim, lrejet;
  occ::handle<AppDef_SmoothCriterion> JNew;
  occ::handle<FEmTool_Curve>          CNew;
  double                              E1, E2, E3;

  loptim = true;
  iter   = 0;
  tbpoid.Init(1.);

  vtest  = WQuality * .9;
  j1cibl = std::sqrt(myCriterium[0] / (NbrPnt - NbrConstraint));

  while (loptim)
  {

    ++iter;

    vocri[0] = myCriterium[0];
    vocri[1] = myCriterium[1];
    vocri[2] = myCriterium[2];
    vocri[3] = myCriterium[3];
    erold    = myMaxError;
    emold    = myAverageError;

    if (j1cibl > vtest)
    {
      WQuadratic = j1cibl / vtest * WQuadratic;
    }

    vseuil = WQuality * .88;

    for (ipnt = myFirstPoint; ipnt <= myLastPoint; ++ipnt)
    {
      if (Ecarts(ipnt) > vtest)
      {
        ecart        = (Ecarts(ipnt) - vseuil) / WQuality;
        tbpoid(ipnt) = (ecart * 3 + 1.) * tbpoid(ipnt);
      }
    }

    if (TheCurve->NbElements() < myMaxSegment && myWithCutting)
    {

      numint = NearIndex(myParameters->Value(myMaxErrorIndex), TheCurve->Knots(), 0, flag);

      tpara = (TheCurve->Knots()(numint) + TheCurve->Knots()(numint + 1)
               + myParameters->Value(myMaxErrorIndex) * 2)
              / 4;

      CNew = new FEmTool_Curve(myDimension, TheCurve->NbElements() + 1, TheCurve->Base(), CurvTol);

      for (i = 1; i <= numint; i++)
        CNew->Knots()(i) = TheCurve->Knots()(i);
      for (i = numint + 1; i <= TheCurve->Knots().Length(); i++)
        CNew->Knots()(i + 1) = TheCurve->Knots()(i);

      CNew->Knots()(numint + 1) = tpara;
    }
    else
    {

      CNew = new FEmTool_Curve(myDimension, TheCurve->NbElements(), TheCurve->Base(), CurvTol);

      CNew->Knots() = TheCurve->Knots();
    }

    JNew = new AppDef_LinearCriteria(mySSP, myFirstPoint, myLastPoint);

    JNew->EstLength() = J->EstLength();

    J->GetEstimation(E1, E2, E3);

    JNew->SetEstimation(E1, E2, E3);

    JNew->SetParameters(myParameters);

    JNew->SetWeight(WQuadratic, WQuality, myPercent[0], myPercent[1], myPercent[2]);

    JNew->SetWeight(tbpoid);

    JNew->SetCurve(CNew);

    TheMotor(JNew, WQuadratic, WQuality, CNew, Ecarts);

    j1cibl = std::sqrt(myCriterium[0] / (NbrPnt - NbrConstraint));
    vseuil = std::sqrt(vocri[1]) + (erold - myMaxError) * 4;

    lrejet = ((myMaxError > WQuality) && (myMaxError > erold * 1.01))
             || (std::sqrt(myCriterium[1]) > vseuil * 1.05);

    if (lrejet)
    {
      myCriterium[0] = vocri[0];
      myCriterium[1] = vocri[1];
      myCriterium[2] = vocri[2];
      myCriterium[3] = vocri[3];
      myMaxError     = erold;
      myAverageError = emold;

      loptim = false;
    }
    else
    {
      J        = JNew;
      TheCurve = CNew;
      J->SetCurve(TheCurve);
    }

    if (((iter >= mxiter) && (myMaxSegment == CNew->NbElements())) || myMaxError < WQuality)
    {
      loptim = false;
    }
  }
}

static bool NotParallel(gp_Vec& T, gp_Vec& V)
{
  V = T;
  V.SetX(V.X() + 1.);
  if (V.CrossMagnitude(T) > 1.e-12)
    return true;
  V.SetY(V.Y() + 1.);
  if (V.CrossMagnitude(T) > 1.e-12)
    return true;
  V.SetZ(V.Z() + 1.);
  return V.CrossMagnitude(T) > 1.e-12;
}

void AppDef_Variational::AssemblingConstraints(const occ::handle<FEmTool_Curve>& Curve,
                                               const NCollection_Array1<double>& Parameters,
                                               const double                      CBLONG,
                                               FEmTool_Assembly&                 A) const
{

  int MxDeg = Curve->Base().WorkDegree(), NbElm = Curve->NbElements(), NbDim = Curve->Dimension();

  NCollection_Array1<double> G0(0, MxDeg), G1(0, MxDeg), G2(0, MxDeg);
  math_Vector                V0((double*)&G0(0), 0, MxDeg), V1((double*)&G1(0), 0, MxDeg),
    V2((double*)&G2(0), 0, MxDeg);

  int IndexOfConstraint, Ng3d, Ng2d, NBeg2d, NPass, NgPC1, NTang3d, NTang2d, Point, TypOfConstr,
    p0 = Parameters.Lower() - myFirstPoint, curel = 1, el, i, ipnt, ityp, j, k, pnt, curdim, jt,
    Ntheta     = 6 * myNbP3d + 2 * myNbP2d;
  int NbConstr = myNbPassPoints + myNbTangPoints + myNbCurvPoints;

  Ng3d   = 3 * NbConstr + 3 * myNbTangPoints + 5 * myNbCurvPoints;
  Ng2d   = 2 * NbConstr + 2 * myNbTangPoints + 3 * myNbCurvPoints;
  NBeg2d = Ng3d * myNbP3d;

  NgPC1   = NbConstr + myNbTangPoints + myNbCurvPoints;
  NPass   = 0;
  NTang3d = 3 * NgPC1;
  NTang2d = 2 * NgPC1;

  NCollection_Array1<double>& Intervals = Curve->Knots();

  double t, R1, R2;

  const PLib_HermitJacobi& myHermitJacobi = Curve->Base();
  int                      Order          = myHermitJacobi.NivConstr() + 1;

  double UFirst, ULast, coeff, c0, mfact, mfact1;

  A.NullifyConstraint();

  ipnt = -1;
  ityp = 0;
  for (i = 1; i <= NbConstr; i++)
  {

    ipnt += 2;
    ityp += 2;

    Point       = myTypConstraints->Value(ipnt);
    TypOfConstr = myTypConstraints->Value(ityp);

    t = Parameters(p0 + Point);

    for (el = curel; el <= NbElm;)
    {
      if (t <= Intervals(++el))
      {
        curel = el - 1;
        break;
      }
    }

    UFirst = Intervals(curel);
    ULast  = Intervals(curel + 1);
    coeff  = (ULast - UFirst) / 2.;
    c0     = (ULast + UFirst) / 2.;

    t = (t - c0) / coeff;

    if (TypOfConstr == 0)
    {
      myHermitJacobi.D0(t, G0);
      for (k = 1; k < Order; k++)
      {
        mfact = std::pow(coeff, k);
        G0(k) *= mfact;
        G0(k + Order) *= mfact;
      }
    }
    else if (TypOfConstr == 1)
    {
      myHermitJacobi.D1(t, G0, G1);
      for (k = 1; k < Order; k++)
      {
        mfact = std::pow(coeff, k);
        G0(k) *= mfact;
        G0(k + Order) *= mfact;
        G1(k) *= mfact;
        G1(k + Order) *= mfact;
      }
      mfact = 1. / coeff;
      for (k = 0; k <= MxDeg; k++)
      {
        G1(k) *= mfact;
      }
    }
    else
    {
      myHermitJacobi.D2(t, G0, G1, G2);
      for (k = 1; k < Order; k++)
      {
        mfact = std::pow(coeff, k);
        G0(k) *= mfact;
        G0(k + Order) *= mfact;
        G1(k) *= mfact;
        G1(k + Order) *= mfact;
        G2(k) *= mfact;
        G2(k + Order) *= mfact;
      }
      mfact  = 1. / coeff;
      mfact1 = mfact / coeff;
      for (k = 0; k <= MxDeg; k++)
      {
        G1(k) *= mfact;
        G2(k) *= mfact1;
      }
    }

    NPass++;

    j      = NbDim * (Point - myFirstPoint);
    int n0 = NPass;
    curdim = 0;
    for (pnt = 1; pnt <= myNbP3d; pnt++)
    {
      IndexOfConstraint = n0;
      for (k = 1; k <= 3; k++)
      {
        curdim++;
        A.AddConstraint(IndexOfConstraint, curel, curdim, V0, myTabPoints->Value(j + k));
        IndexOfConstraint += NgPC1;
      }
      j += 3;
      n0 += Ng3d;
    }

    n0 = NPass + NBeg2d;
    for (pnt = 1; pnt <= myNbP2d; pnt++)
    {
      IndexOfConstraint = n0;
      for (k = 1; k <= 2; k++)
      {
        curdim++;
        A.AddConstraint(IndexOfConstraint, curel, curdim, V0, myTabPoints->Value(j + k));
        IndexOfConstraint += NgPC1;
      }
      j += 2;
      n0 += Ng2d;
    }

    if (TypOfConstr == 1)
    {

      NPass++;
      n0     = NPass;
      j      = 2 * NbDim * (i - 1);
      curdim = 0;
      for (pnt = 1; pnt <= myNbP3d; pnt++)
      {
        IndexOfConstraint = n0;
        for (k = 1; k <= 3; k++)
        {
          curdim++;
          A.AddConstraint(IndexOfConstraint,
                          curel,
                          curdim,
                          V1,
                          CBLONG * myTabConstraints->Value(j + k));
          IndexOfConstraint += NgPC1;
        }
        n0 += Ng3d;
        j += 6;
      }

      n0 = NPass + NBeg2d;
      for (pnt = 1; pnt <= myNbP2d; pnt++)
      {
        IndexOfConstraint = n0;
        for (k = 1; k <= 2; k++)
        {
          curdim++;
          A.AddConstraint(IndexOfConstraint,
                          curel,
                          curdim,
                          V1,
                          CBLONG * myTabConstraints->Value(j + k));
          IndexOfConstraint += NgPC1;
        }
        n0 += Ng2d;
        j += 4;
      }
    }
    if (TypOfConstr == 2)
    {

      NPass++;
      n0     = NPass;
      j      = 2 * NbDim * (i - 1);
      curdim = 0;
      for (pnt = 1; pnt <= myNbP3d; pnt++)
      {
        IndexOfConstraint = n0;
        for (k = 1; k <= 3; k++)
        {
          curdim++;
          A.AddConstraint(IndexOfConstraint,
                          curel,
                          curdim,
                          V1,
                          CBLONG * myTabConstraints->Value(j + k));
          IndexOfConstraint += NgPC1;
        }
        n0 += Ng3d;
        j += 6;
      }

      n0 = NPass + NBeg2d;
      for (pnt = 1; pnt <= myNbP2d; pnt++)
      {
        IndexOfConstraint = n0;
        for (k = 1; k <= 2; k++)
        {
          curdim++;
          A.AddConstraint(IndexOfConstraint,
                          curel,
                          curdim,
                          V1,
                          CBLONG * myTabConstraints->Value(j + k));
          IndexOfConstraint += NgPC1;
        }
        n0 += Ng2d;
        j += 4;
      }

      j                 = 2 * NbDim * (i - 1) + 3;
      jt                = Ntheta * (i - 1);
      IndexOfConstraint = NTang3d + 1;
      curdim            = 0;
      for (pnt = 1; pnt <= myNbP3d; pnt++)
      {
        R1 = 0.;
        R2 = 0.;
        for (k = 1; k <= 3; k++)
        {
          R1 += myTabConstraints->Value(j + k) * myTtheta->Value(jt + k);
          R2 += myTabConstraints->Value(j + k) * myTtheta->Value(jt + 3 + k);
        }
        R1 *= CBLONG * CBLONG;
        R2 *= CBLONG * CBLONG;
        for (k = 1; k <= 3; k++)
        {
          curdim++;
          if (k > 1)
            R1 = R2 = 0.;
          A.AddConstraint(IndexOfConstraint, curel, curdim, myTfthet->Value(jt + k) * V2, R1);
          A.AddConstraint(IndexOfConstraint + 1,
                          curel,
                          curdim,
                          myTfthet->Value(jt + 3 + k) * V2,
                          R2);
        }
        IndexOfConstraint += Ng3d;
        j += 6;
        jt += 6;
      }

      j--;
      IndexOfConstraint = NBeg2d + NTang2d + 1;
      for (pnt = 1; pnt <= myNbP2d; pnt++)
      {
        R1 = 0.;
        for (k = 1; k <= 2; k++)
        {
          R1 += myTabConstraints->Value(j + k) * myTtheta->Value(jt + k);
        }
        R1 *= CBLONG * CBLONG;
        for (k = 1; k <= 2; k++)
        {
          curdim++;
          if (k > 1)
            R1 = 0.;
          A.AddConstraint(IndexOfConstraint, curel, curdim, myTfthet->Value(jt + k) * V2, R1);
        }
        IndexOfConstraint += Ng2d;
        j += 4;
        jt += 2;
      }

      NTang3d += 2;
      NTang2d += 1;
    }
  }
}

bool AppDef_Variational::InitTthetaF(const int                     ndimen,
                                     const AppParCurves_Constraint typcon,
                                     const int                     begin,
                                     const int                     jndex)
{
  if ((ndimen < 2) || (ndimen > 3))
    return false;
  gp_Vec T, V;
  gp_Vec theta1, theta2;
  gp_Vec F;
  double XX, XY, YY, XZ, YZ, ZZ;

  if ((typcon == AppParCurves_TangencyPoint) || (typcon == AppParCurves_CurvaturePoint))
  {
    T.SetX(myTabConstraints->Value(jndex));
    T.SetY(myTabConstraints->Value(jndex + 1));
    if (ndimen == 3)
      T.SetZ(myTabConstraints->Value(jndex + 2));
    else
      T.SetZ(0.);
    if (ndimen == 2)
    {
      V.SetX(0.);
      V.SetY(0.);
      V.SetZ(1.);
    }
    if (ndimen == 3)
      if (!NotParallel(T, V))
        return false;
    theta1 = V ^ T;
    theta1.Normalize();
    myTtheta->SetValue(begin, theta1.X());
    myTtheta->SetValue(begin + 1, theta1.Y());
    if (ndimen == 3)
    {
      theta2 = T ^ theta1;
      theta2.Normalize();
      myTtheta->SetValue(begin + 2, theta1.Z());
      myTtheta->SetValue(begin + 3, theta2.X());
      myTtheta->SetValue(begin + 4, theta2.Y());
      myTtheta->SetValue(begin + 5, theta2.Z());
    }

    if (typcon == AppParCurves_CurvaturePoint)
    {
      XX = std::pow(T.X(), 2);
      XY = T.X() * T.Y();
      YY = std::pow(T.Y(), 2);
      if (ndimen == 2)
      {
        F.SetX(YY * theta1.X() - XY * theta1.Y());
        F.SetY(XX * theta1.Y() - XY * theta1.X());
        myTfthet->SetValue(begin, F.X());
        myTfthet->SetValue(begin + 1, F.Y());
      }
      if (ndimen == 3)
      {
        XZ = T.X() * T.Z();
        YZ = T.Y() * T.Z();
        ZZ = std::pow(T.Z(), 2);

        F.SetX((ZZ + YY) * theta1.X() - XY * theta1.Y() - XZ * theta1.Z());
        F.SetY((XX + ZZ) * theta1.Y() - XY * theta1.X() - YZ * theta1.Z());
        F.SetZ((XX + YY) * theta1.Z() - XZ * theta1.X() - YZ * theta1.Y());
        myTfthet->SetValue(begin, F.X());
        myTfthet->SetValue(begin + 1, F.Y());
        myTfthet->SetValue(begin + 2, F.Z());
        F.SetX((ZZ + YY) * theta2.X() - XY * theta2.Y() - XZ * theta2.Z());
        F.SetY((XX + ZZ) * theta2.Y() - XY * theta2.X() - YZ * theta2.Z());
        F.SetZ((XX + YY) * theta2.Z() - XZ * theta2.X() - YZ * theta2.Y());
        myTfthet->SetValue(begin + 3, F.X());
        myTfthet->SetValue(begin + 4, F.Y());
        myTfthet->SetValue(begin + 5, F.Z());
      }
    }
  }
  return true;
}
