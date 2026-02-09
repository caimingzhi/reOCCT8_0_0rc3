#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Precision.hpp>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade.hpp>
#include <ShapeUpgrade_SplitCurve3dContinuity.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve3dContinuity, ShapeUpgrade_SplitCurve3d)

ShapeUpgrade_SplitCurve3dContinuity::ShapeUpgrade_SplitCurve3dContinuity()
{
  myCriterion = GeomAbs_C1;
  myTolerance = Precision::Confusion();
  myCont      = 1;
}

void ShapeUpgrade_SplitCurve3dContinuity::SetCriterion(const GeomAbs_Shape Criterion)
{
  myCriterion = Criterion;
  switch (myCriterion)
  {
    case GeomAbs_C0:
      myCont = 0;
      break;
    case GeomAbs_C1:
      myCont = 1;
      break;
    case GeomAbs_C2:
      myCont = 2;
      break;
    case GeomAbs_C3:
      myCont = 3;
      break;
    case GeomAbs_CN:
      myCont = 4;
      break;
    default:
      myCont = 1;
  }
}

void ShapeUpgrade_SplitCurve3dContinuity::SetTolerance(const double Tol)
{
  myTolerance = Tol;
}

void ShapeUpgrade_SplitCurve3dContinuity::Compute()
{
  double           First     = mySplitValues->Value(1);
  double           Last      = mySplitValues->Value(mySplitValues->Length());
  constexpr double precision = Precision::PConfusion();
  if (myCurve->Continuity() < myCriterion)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
  if (mySplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (myCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve>      tmp      = occ::down_cast<Geom_TrimmedCurve>(myCurve);
    occ::handle<Geom_Curve>             BasCurve = tmp->BasisCurve();
    ShapeUpgrade_SplitCurve3dContinuity spc;

    spc.Init(BasCurve, First, Last);
    spc.SetSplitValues(mySplitValues);
    spc.SetTolerance(myTolerance);
    spc.SetCriterion(myCriterion);
    spc.Compute();
    mySplitValues->Clear();
    mySplitValues->ChangeSequence() = spc.SplitValues()->Sequence();
    myStatus |= spc.myStatus;
    return;
  }
  else if (myCurve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {
    GeomAbs_Shape BasCriterion;
    switch (myCriterion)
    {
      default:
      case GeomAbs_C1:
        BasCriterion = GeomAbs_C2;
        break;
      case GeomAbs_C2:
        BasCriterion = GeomAbs_C3;
        break;
      case GeomAbs_C3:

#ifdef OCCT_DEBUG
        std::cout << "Warning: ShapeUpgrade_SplitCurve3dContinuity: criterion C3 for Offset curve"
                  << std::endl;
#endif
      case GeomAbs_CN:
        BasCriterion = GeomAbs_CN;
        break;
    }
    occ::handle<Geom_OffsetCurve> tmp      = occ::down_cast<Geom_OffsetCurve>(myCurve);
    occ::handle<Geom_Curve>       BasCurve = tmp->BasisCurve();

    ShapeUpgrade_SplitCurve3dContinuity spc;

    spc.Init(BasCurve, First, Last);
    spc.SetSplitValues(mySplitValues);
    spc.SetTolerance(myTolerance);
    spc.SetCriterion(BasCriterion);
    spc.Compute();
    mySplitValues->Clear();
    mySplitValues->ChangeSequence() = spc.SplitValues()->Sequence();
    myStatus |= spc.myStatus;
    return;
  }

  occ::handle<Geom_BSplineCurve> MyBSpline = occ::down_cast<Geom_BSplineCurve>(myCurve);
  if (MyBSpline.IsNull())
  {

    return;
  }

  myNbCurves  = 1;
  int Deg     = MyBSpline->Degree();
  int NbKnots = MyBSpline->NbKnots();

  if (NbKnots <= 2)
  {
    return;
  }

  int FirstInd = MyBSpline->FirstUKnotIndex() + 1, LastInd = MyBSpline->LastUKnotIndex() - 1;
  for (int j = 2; j <= mySplitValues->Length(); j++)
  {
    Last = mySplitValues->Value(j);
    for (int iknot = FirstInd; iknot <= LastInd; iknot++)
    {
      double valknot = MyBSpline->Knot(iknot);
      if (valknot <= First + precision)
        continue;
      if (valknot > Last - precision)
        break;
      int Continuity = Deg - MyBSpline->Multiplicity(iknot);
      if (Continuity < myCont)
      {

        bool corrected       = false;
        int  newMultiplicity = Deg - myCont;
        if (newMultiplicity < 0)
          newMultiplicity = 0;
        {
          try
          {
            OCC_CATCH_SIGNALS
            corrected = MyBSpline->RemoveKnot(iknot, newMultiplicity, myTolerance);
          }
          catch (Standard_Failure const&)
          {
            corrected = false;
          }
        }

        if (corrected && newMultiplicity > 0)
        {
          Continuity = Deg - MyBSpline->Multiplicity(iknot);
          corrected  = (Continuity >= myCont);
        }
        if (corrected)
        {

          myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
          if (newMultiplicity == 0)
          {

            LastInd = MyBSpline->LastUKnotIndex() - 1;
            iknot--;
          }
        }
        else
        {

          mySplitValues->InsertBefore(j++, MyBSpline->Knot(iknot));
          myNbCurves++;
        }
      }
    }
    First = Last;
  }

  if (mySplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
}

const occ::handle<Geom_Curve>& ShapeUpgrade_SplitCurve3dContinuity::GetCurve() const
{
  return myCurve;
}
