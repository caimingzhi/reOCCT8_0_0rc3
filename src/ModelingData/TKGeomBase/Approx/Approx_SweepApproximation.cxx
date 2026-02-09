#include <AdvApprox_ApproxAFunction.hpp>
#include <AdvApprox_DichoCutting.hpp>
#include <AdvApprox_PrefAndRec.hpp>
#include <Approx_SweepApproximation.hpp>
#include <Approx_SweepFunction.hpp>
#include <BSplCLib.hpp>
#include <Standard_DomainError.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XYZ.hpp>

class Approx_SweepApproximation_Eval : public AdvApprox_EvaluatorFunction
{
public:
  Approx_SweepApproximation_Eval(Approx_SweepApproximation& theTool)
      : Tool(theTool)
  {
  }

  void Evaluate(int*    Dimension,
                double  StartEnd[2],
                double* Parameter,
                int*    DerivativeRequest,
                double* Result,
                int*    ErrorCode) override;

private:
  Approx_SweepApproximation& Tool;
};

void Approx_SweepApproximation_Eval::Evaluate(int*,
                                              double  StartEnd[2],
                                              double* Parameter,
                                              int*    DerivativeRequest,
                                              double* Result,
                                              int*    ErrorCode)
{
  *ErrorCode = Tool.Eval(*Parameter, *DerivativeRequest, StartEnd[0], StartEnd[1], Result[0]);
}

Approx_SweepApproximation::Approx_SweepApproximation(const occ::handle<Approx_SweepFunction>& Func)
{
  myFunc = Func;

  myParam = 0;
  myOrder = -1;
  first   = 1.e100;
  last    = -1.e100;
  done    = false;
}

void Approx_SweepApproximation::Perform(const double        First,
                                        const double        Last,
                                        const double        Tol3d,
                                        const double        BoundTol,
                                        const double        Tol2d,
                                        const double        TolAngular,
                                        const GeomAbs_Shape Continuity,
                                        const int           Degmax,
                                        const int           Segmax)
{
  int           NbPolSect, NbKnotSect, ii;
  double        Tol, Tol3dMin = Tol3d, The3D2DTol = 0;
  GeomAbs_Shape continuity = Continuity;

  myFunc->SectionShape(NbPolSect, NbKnotSect, udeg);
  Num2DSS   = myFunc->Nb2dCurves();
  tabUKnots = new (NCollection_HArray1<double>)(1, NbKnotSect);
  tabUMults = new (NCollection_HArray1<int>)(1, NbKnotSect);
  myFunc->Knots(tabUKnots->ChangeArray1());
  myFunc->Mults(tabUMults->ChangeArray1());

  occ::handle<NCollection_HArray1<double>> OneDTol, TwoDTol, ThreeDTol;
  Num3DSS = NbPolSect;

  OneDTol   = new (NCollection_HArray1<double>)(1, Num3DSS);
  ThreeDTol = new (NCollection_HArray1<double>)(1, Num3DSS);

  myFunc->GetTolerance(BoundTol, Tol3d, TolAngular, ThreeDTol->ChangeArray1());

  for (ii = 1; ii <= Num3DSS; ii++)
    if (ThreeDTol->Value(ii) < Tol3dMin)
      Tol3dMin = ThreeDTol->Value(ii);

  if (myFunc->IsRational())
  {
    double Size;
    Num1DSS = NbPolSect;
    NCollection_Array1<double> Wmin(1, Num1DSS);
    myFunc->GetMinimalWeight(Wmin);
    Size = myFunc->MaximalSection();
    Translation.SetXYZ(myFunc->BarycentreOfSurf().XYZ());
    for (ii = 1; ii <= Num3DSS; ii++)
    {
      Tol = ThreeDTol->Value(ii) / 2;
      OneDTol->SetValue(ii, Tol * Wmin(ii) / Size);
      Tol *= Wmin(ii);
      ThreeDTol->SetValue(ii, std::max(Tol, 1.e-20));
    }
  }
  else
  {
    Num1DSS = 0;
  }

  if (Num2DSS == 0)
  {
    TwoDTol.Nullify();
  }
  else
  {

    double res, tolu, tolv;
    TwoDTol    = new (NCollection_HArray1<double>)(1, Num2DSS);
    AAffin     = new (NCollection_HArray1<gp_GTrsf2d>)(1, Num2DSS);
    The3D2DTol = 0.9 * BoundTol;
    for (ii = 1; ii <= Num2DSS; ii++)
    {
      myFunc->Resolution(ii, The3D2DTol, tolu, tolv);
      if (tolu > tolv)
      {
        res = tolv;
        AAffin->ChangeValue(ii).SetValue(1, 1, tolv / tolu);
      }
      else
      {
        res = tolu;
        AAffin->ChangeValue(ii).SetValue(2, 2, tolu / tolv);
      }
      TwoDTol->SetValue(ii, std::min(Tol2d, res));
    }
  }

  myPoles   = new (NCollection_HArray1<gp_Pnt>)(1, Num3DSS);
  myDPoles  = new (NCollection_HArray1<gp_Vec>)(1, Num3DSS);
  myD2Poles = new (NCollection_HArray1<gp_Vec>)(1, Num3DSS);

  myWeigths   = new (NCollection_HArray1<double>)(1, Num3DSS);
  myDWeigths  = new (NCollection_HArray1<double>)(1, Num3DSS);
  myD2Weigths = new (NCollection_HArray1<double>)(1, Num3DSS);

  if (Num2DSS > 0)
  {
    myPoles2d   = new (NCollection_HArray1<gp_Pnt2d>)(1, Num2DSS);
    myDPoles2d  = new (NCollection_HArray1<gp_Vec2d>)(1, Num2DSS);
    myD2Poles2d = new (NCollection_HArray1<gp_Vec2d>)(1, Num2DSS);
    COnSurfErr  = new (NCollection_HArray1<double>)(1, Num2DSS);
  }
  else
  {
    myPoles2d   = new NCollection_HArray1<gp_Pnt2d>();
    myDPoles2d  = new NCollection_HArray1<gp_Vec2d>();
    myD2Poles2d = new NCollection_HArray1<gp_Vec2d>();
    COnSurfErr  = new NCollection_HArray1<double>();
  }

  if (continuity >= GeomAbs_C2)
  {
    bool B;
    B = myFunc->D2(First,
                   First,
                   Last,
                   myPoles->ChangeArray1(),
                   myDPoles->ChangeArray1(),
                   myD2Poles->ChangeArray1(),
                   myPoles2d->ChangeArray1(),
                   myDPoles2d->ChangeArray1(),
                   myD2Poles2d->ChangeArray1(),
                   myWeigths->ChangeArray1(),
                   myDWeigths->ChangeArray1(),
                   myD2Weigths->ChangeArray1());
    if (!B)
      continuity = GeomAbs_C1;
  }

  if (continuity == GeomAbs_C1)
  {
    bool B;
    B = myFunc->D1(First,
                   First,
                   Last,
                   myPoles->ChangeArray1(),
                   myDPoles->ChangeArray1(),
                   myPoles2d->ChangeArray1(),
                   myDPoles2d->ChangeArray1(),
                   myWeigths->ChangeArray1(),
                   myDWeigths->ChangeArray1());
    if (!B)
      continuity = GeomAbs_C0;
  }

  myFunc->SetTolerance(Tol3dMin / 20, Tol2d / 20);

  int NbIntervalC2 = myFunc->NbIntervals(GeomAbs_C2);
  int NbIntervalC3 = myFunc->NbIntervals(GeomAbs_C3);

  if (NbIntervalC3 > 1)
  {

    NCollection_Array1<double> Param_de_decoupeC2(1, NbIntervalC2 + 1);
    myFunc->Intervals(Param_de_decoupeC2, GeomAbs_C2);
    NCollection_Array1<double> Param_de_decoupeC3(1, NbIntervalC3 + 1);
    myFunc->Intervals(Param_de_decoupeC3, GeomAbs_C3);

    AdvApprox_PrefAndRec Preferentiel(Param_de_decoupeC2, Param_de_decoupeC3);

    Approx_SweepApproximation_Eval ev(*this);
    Approximation(OneDTol,
                  TwoDTol,
                  ThreeDTol,
                  The3D2DTol,
                  First,
                  Last,
                  continuity,
                  Degmax,
                  Segmax,
                  ev,
                  Preferentiel);
  }
  else
  {

    AdvApprox_DichoCutting         Dichotomie;
    Approx_SweepApproximation_Eval ev(*this);
    Approximation(OneDTol,
                  TwoDTol,
                  ThreeDTol,
                  The3D2DTol,
                  First,
                  Last,
                  continuity,
                  Degmax,
                  Segmax,
                  ev,
                  Dichotomie);
  }
}

void Approx_SweepApproximation::Approximation(
  const occ::handle<NCollection_HArray1<double>>& OneDTol,
  const occ::handle<NCollection_HArray1<double>>& TwoDTol,
  const occ::handle<NCollection_HArray1<double>>& ThreeDTol,
  const double                                    BoundTol,
  const double                                    First,
  const double                                    Last,
  const GeomAbs_Shape                             Continuity,
  const int                                       Degmax,
  const int                                       Segmax,
  const AdvApprox_EvaluatorFunction&              TheApproxFunction,
  const AdvApprox_Cutting&                        TheCuttingTool)
{
  AdvApprox_ApproxAFunction Approx(Num1DSS,
                                   Num2DSS,
                                   Num3DSS,
                                   OneDTol,
                                   TwoDTol,
                                   ThreeDTol,
                                   First,
                                   Last,
                                   Continuity,
                                   Degmax,
                                   Segmax,
                                   TheApproxFunction,
                                   TheCuttingTool);
  done = Approx.HasResult();

  if (done)
  {

    int ii, jj;

    vdeg = Approx.Degree();

    tabPoles   = new (NCollection_HArray2<gp_Pnt>)(1, Num3DSS, 1, Approx.NbPoles());
    tabWeights = new (NCollection_HArray2<double>)(1, Num3DSS, 1, Approx.NbPoles());

    if (Num1DSS == Num3DSS)
    {
      double wpoid;
      gp_Pnt P;
      for (ii = 1; ii <= Num3DSS; ii++)
      {
        for (jj = 1; jj <= Approx.NbPoles(); jj++)
        {
          P     = Approx.Poles()->Value(jj, ii);
          wpoid = Approx.Poles1d()->Value(jj, ii);
          P.ChangeCoord() /= wpoid;
          P.Translate(Translation);
          tabPoles->SetValue(ii, jj, P);
          tabWeights->SetValue(ii, jj, wpoid);
        }
      }
    }
    else
    {
      tabWeights->Init(1);
      for (ii = 1; ii <= Num3DSS; ii++)
      {
        for (jj = 1; jj <= Approx.NbPoles(); jj++)
        {
          tabPoles->SetValue(ii, jj, Approx.Poles()->Value(jj, ii));
        }
      }
    }

    tabVKnots = Approx.Knots();
    tabVMults = Approx.Multiplicities();

    if (Num2DSS > 0)
    {
      gp_GTrsf2d TrsfInv;
      deg2d      = vdeg;
      tab2dKnots = Approx.Knots();
      tab2dMults = Approx.Multiplicities();

      for (ii = 1; ii <= Num2DSS; ii++)
      {
        TrsfInv = AAffin->Value(ii).Inverted();
        occ::handle<NCollection_HArray1<gp_Pnt2d>> P2d =
          new (NCollection_HArray1<gp_Pnt2d>)(1, Approx.NbPoles());
        Approx.Poles2d(ii, P2d->ChangeArray1());

        for (jj = 1; jj <= Approx.NbPoles(); jj++)
        {
          TrsfInv.Transforms(P2d->ChangeValue(jj).ChangeCoord());
        }
        seqPoles2d.Append(P2d);
      }
    }

    MError3d = new (NCollection_HArray1<double>)(1, Num3DSS);
    AError3d = new (NCollection_HArray1<double>)(1, Num3DSS);
    for (ii = 1; ii <= Num3DSS; ii++)
    {
      MError3d->SetValue(ii, Approx.MaxError(3, ii));
      AError3d->SetValue(ii, Approx.AverageError(3, ii));
    }

    if (myFunc->IsRational())
    {
      MError1d = new (NCollection_HArray1<double>)(1, Num3DSS);
      AError1d = new (NCollection_HArray1<double>)(1, Num3DSS);
      for (ii = 1; ii <= Num1DSS; ii++)
      {
        MError1d->SetValue(ii, Approx.MaxError(1, ii));
        AError1d->SetValue(ii, Approx.AverageError(1, ii));
      }
    }

    if (Num2DSS > 0)
    {
      tab2dError = new (NCollection_HArray1<double>)(1, Num2DSS);
      Ave2dError = new (NCollection_HArray1<double>)(1, Num2DSS);
      for (ii = 1; ii <= Num2DSS; ii++)
      {
        tab2dError->SetValue(ii, Approx.MaxError(2, ii));
        Ave2dError->SetValue(ii, Approx.AverageError(2, ii));
        COnSurfErr->SetValue(ii, (tab2dError->Value(ii) / TwoDTol->Value(ii)) * BoundTol);
      }
    }
  }
}

int Approx_SweepApproximation::Eval(const double Parameter,
                                    const int    DerivativeRequest,
                                    const double First,
                                    const double Last,
                                    double&      Result)
{
  int ier = 0;
  switch (DerivativeRequest)
  {
    case 0:
      ier = (!D0(Parameter, First, Last, Result));
      break;
    case 1:
      ier = (!D1(Parameter, First, Last, Result));
      break;
    case 2:
      ier = (!D2(Parameter, First, Last, Result));
      break;
    default:
      ier = 2;
  }
  return ier;
}

bool Approx_SweepApproximation::D0(const double Param,
                                   const double First,
                                   const double Last,
                                   double&      Result)
{
  int     index, ii;
  bool    Ok          = true;
  double* LocalResult = &Result;

  if ((first != First) || (Last != last))
  {
    myFunc->SetInterval(First, Last);
  }

  if ((Param != myParam) || (myOrder < 0) || (first != First) || (Last != last))
  {

    Ok = myFunc->D0(Param,
                    First,
                    Last,
                    myPoles->ChangeArray1(),
                    myPoles2d->ChangeArray1(),
                    myWeigths->ChangeArray1());

    for (ii = 1; ii <= Num1DSS; ii++)
    {
      myPoles->ChangeValue(ii).ChangeCoord() -= Translation.XYZ();
      myPoles->ChangeValue(ii).ChangeCoord() *= myWeigths->Value(ii);
    }

    for (ii = 1; ii <= Num2DSS; ii++)
    {
      AAffin->Value(ii).Transforms(myPoles2d->ChangeValue(ii).ChangeCoord());
    }

    first   = First;
    last    = Last;
    myOrder = 0;
    myParam = Param;
  }

  index = 0;
  for (ii = 1; ii <= Num1DSS; ii++)
  {
    LocalResult[index] = myWeigths->Value(ii);
    index++;
  }
  for (ii = 1; ii <= Num2DSS; ii++)
  {
    LocalResult[index]     = myPoles2d->Value(ii).X();
    LocalResult[index + 1] = myPoles2d->Value(ii).Y();
    index += 2;
  }
  for (ii = 1; ii <= Num3DSS; ii++, index += 3)
  {
    LocalResult[index]     = myPoles->Value(ii).X();
    LocalResult[index + 1] = myPoles->Value(ii).Y();
    LocalResult[index + 2] = myPoles->Value(ii).Z();
  }

  return Ok;
}

bool Approx_SweepApproximation::D1(const double Param,
                                   const double First,
                                   const double Last,
                                   double&      Result)
{
  gp_XY   Vcoord;
  gp_Vec  Vaux;
  int     index, ii;
  bool    Ok          = true;
  double* LocalResult = &Result;

  if ((first != First) || (Last != last))
  {
    myFunc->SetInterval(First, Last);
  }

  if ((Param != myParam) || (myOrder < 1) || (first != First) || (Last != last))
  {

    Ok = myFunc->D1(Param,
                    First,
                    Last,
                    myPoles->ChangeArray1(),
                    myDPoles->ChangeArray1(),
                    myPoles2d->ChangeArray1(),
                    myDPoles2d->ChangeArray1(),
                    myWeigths->ChangeArray1(),
                    myDWeigths->ChangeArray1());

    for (ii = 1; ii <= Num1DSS; ii++)
    {

      myPoles->ChangeValue(ii).ChangeCoord() -= Translation.XYZ();

      const double aWeight = myWeigths->Value(ii);
      myDPoles->ChangeValue(ii) *= aWeight;
      Vaux.SetXYZ(myPoles->Value(ii).Coord());
      myDPoles->ChangeValue(ii) += myDWeigths->Value(ii) * Vaux;
      myPoles->ChangeValue(ii).ChangeCoord() *= aWeight;
    }

    for (ii = 1; ii <= Num2DSS; ii++)
    {
      Vcoord = myDPoles2d->Value(ii).XY();
      AAffin->Value(ii).Transforms(Vcoord);
      myDPoles2d->ChangeValue(ii).SetXY(Vcoord);
      AAffin->Value(ii).Transforms(myPoles2d->ChangeValue(ii).ChangeCoord());
    }

    first   = First;
    last    = Last;
    myOrder = 1;
    myParam = Param;
  }

  index = 0;
  for (ii = 1; ii <= Num1DSS; ii++)
  {
    LocalResult[index] = myDWeigths->Value(ii);
    index++;
  }
  for (ii = 1; ii <= Num2DSS; ii++)
  {
    LocalResult[index]     = myDPoles2d->Value(ii).X();
    LocalResult[index + 1] = myDPoles2d->Value(ii).Y();
    index += 2;
  }
  for (ii = 1; ii <= Num3DSS; ii++, index += 3)
  {
    LocalResult[index]     = myDPoles->Value(ii).X();
    LocalResult[index + 1] = myDPoles->Value(ii).Y();
    LocalResult[index + 2] = myDPoles->Value(ii).Z();
  }
  return Ok;
}

bool Approx_SweepApproximation::D2(const double Param,
                                   const double First,
                                   const double Last,
                                   double&      Result)
{
  gp_XY   Vcoord;
  gp_Vec  Vaux;
  int     index, ii;
  bool    Ok          = true;
  double* LocalResult = &Result;

  if ((first != First) || (Last != last))
  {
    myFunc->SetInterval(First, Last);
  }

  if ((Param != myParam) || (myOrder < 2) || (first != First) || (Last != last))
  {

    Ok = myFunc->D2(Param,
                    First,
                    Last,
                    myPoles->ChangeArray1(),
                    myDPoles->ChangeArray1(),
                    myD2Poles->ChangeArray1(),
                    myPoles2d->ChangeArray1(),
                    myDPoles2d->ChangeArray1(),
                    myD2Poles2d->ChangeArray1(),
                    myWeigths->ChangeArray1(),
                    myDWeigths->ChangeArray1(),
                    myD2Weigths->ChangeArray1());

    for (ii = 1; ii <= Num1DSS; ii++)
    {

      myPoles->ChangeValue(ii).ChangeCoord() -= Translation.XYZ();

      myD2Poles->ChangeValue(ii) *= myWeigths->Value(ii);
      Vaux.SetXYZ(myDPoles->Value(ii).XYZ());
      myD2Poles->ChangeValue(ii) += (2 * myDWeigths->Value(ii)) * Vaux;
      Vaux.SetXYZ(myPoles->Value(ii).Coord());
      myD2Poles->ChangeValue(ii) += myD2Weigths->Value(ii) * Vaux;

      myDPoles->ChangeValue(ii) *= myWeigths->Value(ii);
      Vaux.SetXYZ(myPoles->Value(ii).Coord());
      myDPoles->ChangeValue(ii) += myDWeigths->Value(ii) * Vaux;
      myPoles->ChangeValue(ii).ChangeCoord() *= myWeigths->Value(ii);
    }

    for (ii = 1; ii <= Num2DSS; ii++)
    {
      Vcoord = myD2Poles2d->Value(ii).XY();
      AAffin->Value(ii).Transforms(Vcoord);
      myD2Poles2d->ChangeValue(ii).SetXY(Vcoord);
      Vcoord = myDPoles2d->Value(ii).XY();
      AAffin->Value(ii).Transforms(Vcoord);
      myDPoles2d->ChangeValue(ii).SetXY(Vcoord);
      AAffin->Value(ii).Transforms(myPoles2d->ChangeValue(ii).ChangeCoord());
    }

    first   = First;
    last    = Last;
    myOrder = 2;
    myParam = Param;
  }

  index = 0;
  for (ii = 1; ii <= Num1DSS; ii++)
  {
    LocalResult[index] = myD2Weigths->Value(ii);
    index++;
  }
  for (ii = 1; ii <= Num2DSS; ii++)
  {
    LocalResult[index]     = myD2Poles2d->Value(ii).X();
    LocalResult[index + 1] = myD2Poles2d->Value(ii).Y();
    index += 2;
  }
  for (ii = 1; ii <= Num3DSS; ii++, index += 3)
  {
    LocalResult[index]     = myD2Poles->Value(ii).X();
    LocalResult[index + 1] = myD2Poles->Value(ii).Y();
    LocalResult[index + 2] = myD2Poles->Value(ii).Z();
  }

  return Ok;
}

void Approx_SweepApproximation::SurfShape(int& UDegree,
                                          int& VDegree,
                                          int& NbUPoles,
                                          int& NbVPoles,
                                          int& NbUKnots,
                                          int& NbVKnots) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  UDegree  = udeg;
  VDegree  = vdeg;
  NbUPoles = tabPoles->ColLength();
  NbVPoles = tabPoles->RowLength();
  NbUKnots = tabUKnots->Length();
  NbVKnots = tabVKnots->Length();
}

void Approx_SweepApproximation::Surface(NCollection_Array2<gp_Pnt>& TPoles,
                                        NCollection_Array2<double>& TWeights,
                                        NCollection_Array1<double>& TUKnots,
                                        NCollection_Array1<double>& TVKnots,
                                        NCollection_Array1<int>&    TUMults,
                                        NCollection_Array1<int>&    TVMults) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  TPoles   = tabPoles->Array2();
  TWeights = tabWeights->Array2();
  TUKnots  = tabUKnots->Array1();
  TUMults  = tabUMults->Array1();
  TVKnots  = tabVKnots->Array1();
  TVMults  = tabVMults->Array1();
}

double Approx_SweepApproximation::MaxErrorOnSurf() const
{
  int    ii;
  double MaxError = 0, err;
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }

  if (myFunc->IsRational())
  {
    NCollection_Array1<double> Wmin(1, Num1DSS);
    myFunc->GetMinimalWeight(Wmin);
    double Size = myFunc->MaximalSection();
    for (ii = 1; ii <= Num3DSS; ii++)
    {
      err = (Size * MError1d->Value(ii) + MError3d->Value(ii)) / Wmin(ii);
      if (err > MaxError)
        MaxError = err;
    }
  }
  else
  {
    for (ii = 1; ii <= Num3DSS; ii++)
    {
      err = MError3d->Value(ii);
      if (err > MaxError)
        MaxError = err;
    }
  }
  return MaxError;
}

double Approx_SweepApproximation::AverageErrorOnSurf() const
{
  int    ii;
  double MoyError = 0, err;
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }

  if (myFunc->IsRational())
  {
    NCollection_Array1<double> Wmin(1, Num1DSS);
    myFunc->GetMinimalWeight(Wmin);
    double Size = myFunc->MaximalSection();
    for (ii = 1; ii <= Num3DSS; ii++)
    {
      err = (Size * AError1d->Value(ii) + AError3d->Value(ii)) / Wmin(ii);
      MoyError += err;
    }
  }
  else
  {
    for (ii = 1; ii <= Num3DSS; ii++)
    {
      err = AError3d->Value(ii);
      MoyError += err;
    }
  }
  return MoyError / Num3DSS;
}

void Approx_SweepApproximation::Curves2dShape(int& Degree, int& NbPoles, int& NbKnots) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError("Approx_SweepApproximation");
  }
  Degree  = deg2d;
  NbPoles = seqPoles2d(1)->Length();
  NbKnots = tab2dKnots->Length();
}

void Approx_SweepApproximation::Curve2d(const int                     Index,
                                        NCollection_Array1<gp_Pnt2d>& TPoles,
                                        NCollection_Array1<double>&   TKnots,
                                        NCollection_Array1<int>&      TMults) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  if (seqPoles2d.Length() == 0)
  {
    throw Standard_DomainError("Approx_SweepApproximation");
  }
  TPoles = seqPoles2d(Index)->Array1();
  TKnots = tab2dKnots->Array1();
  TMults = tab2dMults->Array1();
}

double Approx_SweepApproximation::Max2dError(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  return tab2dError->Value(Index);
}

double Approx_SweepApproximation::Average2dError(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  return Ave2dError->Value(Index);
}

double Approx_SweepApproximation::TolCurveOnSurf(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone("Approx_SweepApproximation");
  }
  return COnSurfErr->Value(Index);
}

void Approx_SweepApproximation::Dump(Standard_OStream& o) const
{
  o << "Dump of SweepApproximation" << std::endl;
  if (done)
  {
    o << "Error 3d = " << MaxErrorOnSurf() << std::endl;

    if (Num2DSS > 0)
    {
      o << "Error 2d = ";
      for (int ii = 1; ii <= Num2DSS; ii++)
      {
        o << Max2dError(ii);
        if (ii < Num2DSS)
          o << " , " << std::endl;
      }
      std::cout << std::endl;
    }
    o << tabVKnots->Length() - 1 << " Segment(s) of degree " << vdeg << std::endl;
  }
  else
    std::cout << " Not Done " << std::endl;
}
