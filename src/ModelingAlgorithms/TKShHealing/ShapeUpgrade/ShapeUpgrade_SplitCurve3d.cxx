#include <Geom_BezierCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_OffsetCurve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <Precision.hpp>
#include <ShapeAnalysis_Curve.hpp>
#include <ShapeExtend.hpp>
#include <ShapeUpgrade_SplitCurve3d.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

IMPLEMENT_STANDARD_RTTIEXT(ShapeUpgrade_SplitCurve3d, ShapeUpgrade_SplitCurve)

//=================================================================================================

ShapeUpgrade_SplitCurve3d::ShapeUpgrade_SplitCurve3d() = default;

//=================================================================================================

void ShapeUpgrade_SplitCurve3d::Init(const occ::handle<Geom_Curve>& C)
{
  Init(C, C->FirstParameter(), C->LastParameter());
}

//=================================================================================================

void ShapeUpgrade_SplitCurve3d::Init(const occ::handle<Geom_Curve>& C,
                                     const double                   First,
                                     const double                   Last)
{
  //  if (ShapeUpgrade::Debug()) std::cout << "SplitCurve3d::Init"<<std::endl;
  occ::handle<Geom_Curve> CopyOfC   = occ::down_cast<Geom_Curve>(C->Copy());
  myCurve                           = CopyOfC;
  constexpr double        precision = Precision::PConfusion();
  double                  firstPar  = First;
  double                  lastPar   = Last;
  occ::handle<Geom_Curve> aCurve    = myCurve;
  if (aCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
    aCurve = occ::down_cast<Geom_TrimmedCurve>(aCurve)->BasisCurve();
  // 15.11.2002 PTV OCC966
  if (!ShapeAnalysis_Curve::IsPeriodic(C))
  {
    double fP = aCurve->FirstParameter();
    double lP = aCurve->LastParameter();
    if (std::abs(firstPar - fP) < precision)
      firstPar = fP;
    if (std::abs(lastPar - lP) < precision)
      lastPar = lP;
    if (firstPar < fP)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: The range of the edge exceeds the curve domain" << std::endl;
#endif
      firstPar = fP;
    }
    if (lastPar > lP)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: The range of the edge exceeds the curve domain" << std::endl;
#endif
      lastPar = lP;
    }
    if ((lastPar - firstPar) < precision)
      lastPar = firstPar + 2 * precision;
  }

  ShapeUpgrade_SplitCurve::Init(firstPar, lastPar);

  // first, we make a copy of C to prevent modification:
  //  if (ShapeUpgrade::Debug()) std::cout << ". copy of the curve"<<std::endl;

  myNbCurves = 1;
}

//=================================================================================================

void ShapeUpgrade_SplitCurve3d::Build(const bool Segment)
{
  //  if (ShapeUpgrade::Debug()) std::cout<<"ShapeUpgrade_SplitCurve3d::Build"<<std::endl;
  double First = mySplitValues->Value(1);
  double Last  = mySplitValues->Value(mySplitValues->Length());

  if (mySplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
  if (myCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> tmp      = occ::down_cast<Geom_TrimmedCurve>(myCurve);
    occ::handle<Geom_Curve>        BasCurve = tmp->BasisCurve();
    ShapeUpgrade_SplitCurve3d      spc;
    spc.Init(BasCurve, First, Last);
    spc.SetSplitValues(mySplitValues);
    spc.Build(Segment);
    myNbCurves        = spc.GetCurves()->Length();
    myResultingCurves = new NCollection_HArray1<occ::handle<Geom_Curve>>(1, myNbCurves);
    if (myNbCurves == 1)
    {
      occ::handle<Geom_TrimmedCurve> NewTrimCurve =
        new Geom_TrimmedCurve(spc.GetCurves()->Value(1), First, Last);
      myResultingCurves->SetValue(1, NewTrimCurve);
    }
    else
      myResultingCurves = spc.GetCurves();
    myStatus |= spc.myStatus;
    return;
  }
  else if (myCurve->IsKind(STANDARD_TYPE(Geom_OffsetCurve)))
  {
    occ::handle<Geom_OffsetCurve> tmp      = occ::down_cast<Geom_OffsetCurve>(myCurve);
    occ::handle<Geom_Curve>       BasCurve = tmp->BasisCurve();
    double                        Offset   = tmp->Offset();
    gp_Dir                        Direct   = tmp->Direction();
    ShapeUpgrade_SplitCurve3d     spc;
    spc.Init(BasCurve, First, Last);
    spc.SetSplitValues(mySplitValues);
    spc.Build(Segment);
    myNbCurves        = spc.GetCurves()->Length();
    myResultingCurves = new NCollection_HArray1<occ::handle<Geom_Curve>>(1, myNbCurves);
    for (int i = 1; i <= myNbCurves; i++)
    {
      occ::handle<Geom_OffsetCurve> NewOffsetCurve =
        new Geom_OffsetCurve(spc.GetCurves()->Value(i), Offset, Direct);
      myResultingCurves->SetValue(i, NewOffsetCurve);
    }
    myStatus |= spc.myStatus;
    return;
  }

  // pdn fix on BuildCurve 3d
  //  15.11.2002 PTV OCC966
  if (!ShapeAnalysis_Curve::IsPeriodic(myCurve))
  {
    // pdn exceptons only on non periodic curves
    constexpr double precision = Precision::PConfusion();
    double           firstPar  = myCurve->FirstParameter();
    double           lastPar   = myCurve->LastParameter();
    if (std::abs(First - firstPar) < precision)
      First = firstPar;
    if (std::abs(Last - lastPar) < precision)
      Last = lastPar;
    if (First < firstPar)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: The range of the edge exceeds the curve domain" << std::endl;
#endif
      First = firstPar;
      mySplitValues->SetValue(1, First);
    }
    if (Last > lastPar)
    {
#ifdef OCCT_DEBUG
      std::cout << "Warning: The range of the edge exceeds the curve domain" << std::endl;
#endif
      Last = lastPar;
      mySplitValues->SetValue(mySplitValues->Length(), Last);
    }
  }

  myNbCurves        = mySplitValues->Length() - 1;
  myResultingCurves = new NCollection_HArray1<occ::handle<Geom_Curve>>(1, myNbCurves);
  if (myNbCurves == 1)
  {
    bool filled = true;
    if (std::abs(myCurve->FirstParameter() - First) < Precision::PConfusion()
        && std::abs(myCurve->LastParameter() - Last) < Precision::PConfusion())
      myResultingCurves->SetValue(1, myCurve);

    else if (!Segment
             || (!myCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve))
                 && !myCurve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
             || !Status(ShapeExtend_DONE2))
    {
      /*      if(myCurve->IsKind (STANDARD_TYPE (Geom_BSplineCurve)) ||
               myCurve->IsKind (STANDARD_TYPE (Geom_BezierCurve) )) {
          occ::handle<Geom_Curve> theNewCurve = occ::down_cast<Geom_Curve>(myCurve->Copy());
          try {
            OCC_CATCH_SIGNALS
            if (myCurve->IsKind (STANDARD_TYPE (Geom_BSplineCurve)))
              occ::down_cast<Geom_BSplineCurve>(theNewCurve)->Segment (First, Last);
            else if (myCurve->IsKind (STANDARD_TYPE (Geom_BezierCurve)))
              occ::down_cast<Geom_BezierCurve>(theNewCurve)->Segment (First, Last);
          }
            catch (Standard_Failure) {
      #ifdef OCCT_DEBUG
            std::cout << "Warning: ShapeUpgrade_Split3dCurve::Build(): Exception in Segment      :";
            Standard_Failure::Caught()->Print(std::cout); std::cout << std::endl;
      #endif
            theNewCurve = new
      Geom_TrimmedCurve(occ::down_cast<Geom_Curve>(myCurve->Copy()),First,Last);
          }
          myResultingCurves->SetValue (1, theNewCurve);
            }
            else {*/
      occ::handle<Geom_TrimmedCurve> theNewCurve =
        new Geom_TrimmedCurve(occ::down_cast<Geom_Curve>(myCurve->Copy()), First, Last);
      myResultingCurves->SetValue(1, theNewCurve);
      // }
    }
    else
      filled = false;
    if (filled)
      return;
  }
  if (myCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
  {
    occ::handle<Geom_BSplineCurve> BsCurve = occ::down_cast<Geom_BSplineCurve>(myCurve->Copy());
    int FirstInd = BsCurve->FirstUKnotIndex(), LastInd = BsCurve->LastUKnotIndex();
    int j = FirstInd;
    for (int ii = 1; ii <= mySplitValues->Length(); ii++)
    {
      double spval = mySplitValues->Value(ii);
      for (; j <= LastInd; j++)
      {
        if (spval > BsCurve->Knot(j) + Precision::PConfusion())
          continue;
        if (spval < BsCurve->Knot(j) - Precision::PConfusion())
          break;
        mySplitValues->SetValue(ii, BsCurve->Knot(j));
      }
      if (j == LastInd)
        break;
    }
  }

  for (int i = 1; i <= myNbCurves; i++)
  {
    // skl : in the next block I change "First","Last" to "Firstt","Lastt"
    double                  Firstt = mySplitValues->Value(i), Lastt = mySplitValues->Value(i + 1);
    occ::handle<Geom_Curve> theNewCurve;
    if (Segment)
    {
      if (myCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve))
          || myCurve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
      {
        theNewCurve = occ::down_cast<Geom_Curve>(myCurve->Copy());
        try
        {
          OCC_CATCH_SIGNALS
          if (myCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve)))
            occ::down_cast<Geom_BSplineCurve>(theNewCurve)->Segment(Firstt, Lastt);
          else if (myCurve->IsKind(STANDARD_TYPE(Geom_BezierCurve)))
            occ::down_cast<Geom_BezierCurve>(theNewCurve)->Segment(Firstt, Lastt);
          myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE3);
        }
        catch (Standard_Failure const& anException)
        {
#ifdef OCCT_DEBUG
          std::cout << "Warning: ShapeUpgrade_Split3dCurve::Build(): Exception in Segment      :";
          anException.Print(std::cout);
          std::cout << std::endl;
#endif
          (void)anException;
          theNewCurve =
            new Geom_TrimmedCurve(occ::down_cast<Geom_Curve>(myCurve->Copy()), Firstt, Lastt);
        }
      }
      else
        theNewCurve =
          new Geom_TrimmedCurve(occ::down_cast<Geom_Curve>(myCurve->Copy()), Firstt, Lastt);
    }
    myResultingCurves->SetValue(i, theNewCurve);
  }
}

//=================================================================================================

const occ::handle<NCollection_HArray1<occ::handle<Geom_Curve>>>& ShapeUpgrade_SplitCurve3d::
  GetCurves() const
{
  return myResultingCurves;
}
