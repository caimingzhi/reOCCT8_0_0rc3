#include <Geom_OffsetSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_SweptSurface.hpp>
#include <Precision.hpp>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade.hpp>
#include <ShapeUpgrade_SplitCurve3dContinuity.hpp>
#include <ShapeUpgrade_SplitSurfaceContinuity.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_SplitSurfaceContinuity, ShapeUpgrade_SplitSurface)

ShapeUpgrade_SplitSurfaceContinuity::ShapeUpgrade_SplitSurfaceContinuity()
    : myCont(0)
{
  myCriterion = GeomAbs_C1;
  myTolerance = Precision::Confusion();
}

void ShapeUpgrade_SplitSurfaceContinuity::SetCriterion(const GeomAbs_Shape Criterion)
{
  myCriterion = Criterion;
  switch (myCriterion)
  {
    default:
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
  }
}

void ShapeUpgrade_SplitSurfaceContinuity::SetTolerance(const double Tol)
{
  myTolerance = Tol;
}

void ShapeUpgrade_SplitSurfaceContinuity::Compute(const bool Segment)
{
  if (!Segment)
  {
    double UF, UL, VF, VL;
    mySurface->Bounds(UF, UL, VF, VL);
    if (!Precision::IsInfinite(UF))
      myUSplitValues->SetValue(1, UF);
    if (!Precision::IsInfinite(UL))
      myUSplitValues->SetValue(myUSplitValues->Length(), UL);
    if (!Precision::IsInfinite(VF))
      myVSplitValues->SetValue(1, VF);
    if (!Precision::IsInfinite(VL))
      myVSplitValues->SetValue(myVSplitValues->Length(), VL);
  }

  double           UFirst    = myUSplitValues->Value(1);
  double           ULast     = myUSplitValues->Value(myUSplitValues->Length());
  double           VFirst    = myVSplitValues->Value(1);
  double           VLast     = myVSplitValues->Value(myVSplitValues->Length());
  constexpr double precision = Precision::Confusion();

  if (mySurface->Continuity() < myCriterion)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
  if (myUSplitValues->Length() > 2 || myVSplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);

  if (mySurface->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
  {
    occ::handle<Geom_SurfaceOfRevolution> Surface =
      occ::down_cast<Geom_SurfaceOfRevolution>(mySurface);
    if (Surface->Continuity() >= myCriterion && myUSplitValues->Length() == 2
        && myVSplitValues->Length() == 2)
    {
      return;
    }
    occ::handle<Geom_Curve>             BasCurve = Surface->BasisCurve();
    ShapeUpgrade_SplitCurve3dContinuity spc;
    spc.Init(BasCurve, VFirst, VLast);
    spc.SetCriterion(myCriterion);
    spc.SetTolerance(myTolerance);
    spc.SetSplitValues(myVSplitValues);
    spc.Compute();
    myVSplitValues->Clear();
    myVSplitValues->ChangeSequence() = spc.SplitValues()->Sequence();
    if (spc.Status(ShapeExtend_DONE1))
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
    if (spc.Status(ShapeExtend_DONE2))
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
    if (spc.Status(ShapeExtend_DONE3))
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
    return;
  }
  if (mySurface->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)))
  {
    occ::handle<Geom_SurfaceOfLinearExtrusion> Surface =
      occ::down_cast<Geom_SurfaceOfLinearExtrusion>(mySurface);
    if (Surface->Continuity() >= myCriterion && myUSplitValues->Length() == 2
        && myVSplitValues->Length() == 2)
    {
      return;
    }
    occ::handle<Geom_Curve>             BasCurve = Surface->BasisCurve();
    ShapeUpgrade_SplitCurve3dContinuity spc;
    spc.Init(BasCurve, UFirst, ULast);
    spc.SetCriterion(myCriterion);
    spc.SetTolerance(myTolerance);
    spc.SetSplitValues(myUSplitValues);
    spc.Compute();
    myUSplitValues->Clear();
    myUSplitValues->ChangeSequence() = spc.SplitValues()->Sequence();
    if (spc.Status(ShapeExtend_DONE1))
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
    if (spc.Status(ShapeExtend_DONE2))
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
    if (spc.Status(ShapeExtend_DONE3))
    {
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
      const occ::handle<Geom_Curve>& aNewBascurve = spc.GetCurve();
      Surface->SetBasisCurve(aNewBascurve);
    }
    return;
  }

  if (mySurface->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    occ::handle<Geom_RectangularTrimmedSurface> tmp =
      occ::down_cast<Geom_RectangularTrimmedSurface>(mySurface);
    if (tmp->Continuity() >= myCriterion && myUSplitValues->Length() == 2
        && myVSplitValues->Length() == 2)
    {
      return;
    }
    double U1, U2, V1, V2;
    tmp->Bounds(U1, U2, V1, V2);
    occ::handle<Geom_Surface>           theSurf = tmp->BasisSurface();
    ShapeUpgrade_SplitSurfaceContinuity sps;
    sps.Init(theSurf,
             std::max(U1, UFirst),
             std::min(U2, ULast),
             std::max(V1, VFirst),
             std::min(V2, VLast));
    sps.SetUSplitValues(myUSplitValues);
    sps.SetVSplitValues(myVSplitValues);
    sps.SetTolerance(myTolerance);
    sps.SetCriterion(myCriterion);
    sps.Compute(true);
    myUSplitValues->Clear();
    myUSplitValues->ChangeSequence() = sps.USplitValues()->Sequence();
    myVSplitValues->Clear();
    myVSplitValues->ChangeSequence() = sps.VSplitValues()->Sequence();
    myStatus |= sps.myStatus;
    return;
  }
  else if (mySurface->IsKind(STANDARD_TYPE(Geom_OffsetSurface)))
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
        std::cout << "Warning: ShapeUpgrade_SplitSurfaceContinuity: criterion C3 for Offset surface"
                  << std::endl;
#endif
      case GeomAbs_CN:
        BasCriterion = GeomAbs_CN;
        break;
    }
    occ::handle<Geom_OffsetSurface> tmp     = occ::down_cast<Geom_OffsetSurface>(mySurface);
    occ::handle<Geom_Surface>       theSurf = tmp->BasisSurface();
    if (theSurf->Continuity() >= BasCriterion && myUSplitValues->Length() == 2
        && myVSplitValues->Length() == 2)
    {
      return;
    }
    ShapeUpgrade_SplitSurfaceContinuity sps;
    sps.Init(theSurf, UFirst, ULast, VFirst, VLast);
    sps.SetUSplitValues(myUSplitValues);
    sps.SetVSplitValues(myVSplitValues);
    sps.SetTolerance(myTolerance);
    sps.SetCriterion(BasCriterion);
    sps.Compute(true);
    myUSplitValues->Clear();
    myUSplitValues->ChangeSequence() = sps.USplitValues()->Sequence();
    myVSplitValues->Clear();
    myVSplitValues->ChangeSequence() = sps.VSplitValues()->Sequence();
    myStatus |= sps.myStatus;
    return;
  }

  occ::handle<Geom_BSplineSurface> MyBSpline;
  if (mySurface->IsKind(STANDARD_TYPE(Geom_BSplineSurface)))
    MyBSpline = occ::down_cast<Geom_BSplineSurface>(mySurface->Copy());
  if (MyBSpline.IsNull())
  {

    return;
  }
  if (mySurface->Continuity() >= myCriterion)
  {
    return;
  }

  int UDeg      = MyBSpline->UDegree();
  int VDeg      = MyBSpline->VDegree();
  int NbUKnots  = MyBSpline->NbUKnots();
  int UFirstInd = MyBSpline->FirstUKnotIndex() + 1, ULastInd = MyBSpline->LastUKnotIndex() - 1,
      VFirstInd = MyBSpline->FirstVKnotIndex() + 1, VLastInd = MyBSpline->LastVKnotIndex() - 1;
  int NbVKnots = MyBSpline->NbVKnots();

  if (NbUKnots > 2)
  {

    int iknot = UFirstInd;
    for (int j = 2; j <= myUSplitValues->Length(); j++)
    {
      ULast = myUSplitValues->Value(j);

      for (; iknot <= ULastInd; iknot++)
      {
        double valknot = MyBSpline->UKnot(iknot);
        if (valknot <= UFirst + precision)
          continue;
        if (valknot >= ULast - precision)
          break;
        int Continuity = UDeg - MyBSpline->UMultiplicity(iknot);
        if (Continuity < myCont)
        {

          int  newMultiplicity = UDeg - myCont;
          bool corrected       = false;
          if (newMultiplicity >= 0)
            corrected = MyBSpline->RemoveUKnot(iknot, newMultiplicity, myTolerance);
          if (corrected && newMultiplicity > 0)
          {
            Continuity = UDeg - MyBSpline->UMultiplicity(iknot);
            corrected  = (Continuity >= myCont);
          }
          if (corrected)
          {

            if (newMultiplicity == 0)
            {
              iknot--;
              ULastInd--;
            }
            myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
          }
          else
          {

            double u = MyBSpline->UKnot(iknot);
            myUSplitValues->InsertBefore(j++, u);
            myNbResultingRow++;
          }
        }
      }
      UFirst = ULast;
    }
  }

  if (NbVKnots > 2)
  {

    int iknot = VFirstInd;
    for (int j1 = 2; j1 <= myVSplitValues->Length(); j1++)
    {
      VLast = myVSplitValues->Value(j1);
      for (; iknot <= VLastInd; iknot++)
      {
        double valknot = MyBSpline->VKnot(iknot);
        if (valknot <= VFirst + precision)
          continue;
        if (valknot >= VLast - precision)
          break;
        int Continuity = VDeg - MyBSpline->VMultiplicity(iknot);
        if (Continuity < myCont)
        {

          int  newMultiplicity = VDeg - myCont;
          bool corrected       = false;
          if (newMultiplicity >= 0)
            corrected = MyBSpline->RemoveVKnot(iknot, newMultiplicity, myTolerance);
          if (corrected && newMultiplicity > 0)
          {
            Continuity = VDeg - MyBSpline->VMultiplicity(iknot);
            corrected  = (Continuity >= myCont);
          }
          if (corrected)
          {

            if (newMultiplicity == 0)
            {
              iknot--;
              VLastInd--;
            }
            myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
          }
          else
          {

            double v = MyBSpline->VKnot(iknot);
            myVSplitValues->InsertBefore(j1++, v);
            myNbResultingCol++;
          }
        }
      }
      VFirst = VLast;
    }
  }
  if (Status(ShapeExtend_DONE3))
  {
    mySurface = MyBSpline;
  }

  if (myUSplitValues->Length() > 2 || myVSplitValues->Length() > 2)
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
}
