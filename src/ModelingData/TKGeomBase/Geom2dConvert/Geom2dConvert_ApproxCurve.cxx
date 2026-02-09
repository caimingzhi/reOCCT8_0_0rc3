#include <Geom2dConvert_ApproxCurve.hpp>

#include <Adaptor2d_Curve2d.hpp>
#include <AdvApprox_ApproxAFunction.hpp>
#include <AdvApprox_PrefAndRec.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class Geom2dConvert_ApproxCurve_Eval : public AdvApprox_EvaluatorFunction
{
public:
  Geom2dConvert_ApproxCurve_Eval(const occ::handle<Adaptor2d_Curve2d>& theFunc,
                                 double                                First,
                                 double                                Last)
      : fonct(theFunc)
  {
    StartEndSav[0] = First;
    StartEndSav[1] = Last;
  }

  void Evaluate(int*    Dimension,
                double  StartEnd[2],
                double* Parameter,
                int*    DerivativeRequest,
                double* Result,
                int*    ErrorCode) override;

private:
  occ::handle<Adaptor2d_Curve2d> fonct;
  double                         StartEndSav[2];
};

void Geom2dConvert_ApproxCurve_Eval::Evaluate(int*    Dimension,
                                              double  StartEnd[2],
                                              double* Param,
                                              int*    Order,
                                              double* Result,
                                              int*    ErrorCode)
{
  *ErrorCode = 0;
  double par = *Param;

  if (*Dimension != 2)
  {
    *ErrorCode = 1;
  }

  if (par < StartEnd[0] || par > StartEnd[1])
  {
    *ErrorCode = 2;
  }
  if (StartEnd[0] != StartEndSav[0] || StartEnd[1] != StartEndSav[1])
  {
    fonct          = fonct->Trim(StartEnd[0], StartEnd[1], Precision::PConfusion());
    StartEndSav[0] = StartEnd[0];
    StartEndSav[1] = StartEnd[1];
  }

  gp_Pnt2d pnt;
  gp_Vec2d v1, v2;

  switch (*Order)
  {
    case 0:
      pnt       = fonct->Value(par);
      Result[0] = pnt.X();
      Result[1] = pnt.Y();
      break;
    case 1:
      fonct->D1(par, pnt, v1);
      Result[0] = v1.X();
      Result[1] = v1.Y();
      break;
    case 2:
      fonct->D2(par, pnt, v1, v2);
      Result[0] = v2.X();
      Result[1] = v2.Y();
      break;
    default:
      Result[0] = Result[1] = 0.;
      *ErrorCode            = 3;
      break;
  }
}

Geom2dConvert_ApproxCurve::Geom2dConvert_ApproxCurve(const occ::handle<Geom2d_Curve>& Curve,
                                                     const double                     Tol2d,
                                                     const GeomAbs_Shape              Order,
                                                     const int                        MaxSegments,
                                                     const int                        MaxDegree)
{
  occ::handle<Geom2dAdaptor_Curve> HCurve = new Geom2dAdaptor_Curve(Curve);
  Approximate(HCurve, Tol2d, Order, MaxSegments, MaxDegree);
}

Geom2dConvert_ApproxCurve::Geom2dConvert_ApproxCurve(const occ::handle<Adaptor2d_Curve2d>& Curve,
                                                     const double                          Tol2d,
                                                     const GeomAbs_Shape                   Order,
                                                     const int MaxSegments,
                                                     const int MaxDegree)
{
  Approximate(Curve, Tol2d, Order, MaxSegments, MaxDegree);
}

void Geom2dConvert_ApproxCurve::Approximate(const occ::handle<Adaptor2d_Curve2d>& theCurve,
                                            const double                          theTol2d,
                                            const GeomAbs_Shape                   theOrder,
                                            const int                             theMaxSegments,
                                            const int                             theMaxDegree)
{

  int                                      Num1DSS = 0, Num2DSS = 1, Num3DSS = 0;
  occ::handle<NCollection_HArray1<double>> OneDTolNul, ThreeDTolNul;
  occ::handle<NCollection_HArray1<double>> TwoDTol = new NCollection_HArray1<double>(1, Num2DSS);
  TwoDTol->Init(theTol2d);

  double First = theCurve->FirstParameter();
  double Last  = theCurve->LastParameter();

  int                        NbInterv_C2 = theCurve->NbIntervals(GeomAbs_C2);
  NCollection_Array1<double> CutPnts_C2(1, NbInterv_C2 + 1);
  theCurve->Intervals(CutPnts_C2, GeomAbs_C2);
  int                        NbInterv_C3 = theCurve->NbIntervals(GeomAbs_C3);
  NCollection_Array1<double> CutPnts_C3(1, NbInterv_C3 + 1);
  theCurve->Intervals(CutPnts_C3, GeomAbs_C3);
  AdvApprox_PrefAndRec CutTool(CutPnts_C2, CutPnts_C3);

  myMaxError = 0;

  Geom2dConvert_ApproxCurve_Eval ev(theCurve, First, Last);
  AdvApprox_ApproxAFunction      aApprox(Num1DSS,
                                    Num2DSS,
                                    Num3DSS,
                                    OneDTolNul,
                                    TwoDTol,
                                    ThreeDTolNul,
                                    First,
                                    Last,
                                    theOrder,
                                    theMaxDegree,
                                    theMaxSegments,
                                    ev,
                                    CutTool);

  myIsDone    = aApprox.IsDone();
  myHasResult = aApprox.HasResult();

  if (myHasResult)
  {
    NCollection_Array1<gp_Pnt2d> Poles(1, aApprox.NbPoles());
    aApprox.Poles2d(1, Poles);
    occ::handle<NCollection_HArray1<double>> Knots  = aApprox.Knots();
    occ::handle<NCollection_HArray1<int>>    Mults  = aApprox.Multiplicities();
    int                                      Degree = aApprox.Degree();
    myBSplCurve = new Geom2d_BSplineCurve(Poles, Knots->Array1(), Mults->Array1(), Degree);
    myMaxError  = aApprox.MaxError(2, 1);
  }
}

occ::handle<Geom2d_BSplineCurve> Geom2dConvert_ApproxCurve::Curve() const
{
  return myBSplCurve;
}

bool Geom2dConvert_ApproxCurve::IsDone() const
{
  return myIsDone;
}

bool Geom2dConvert_ApproxCurve::HasResult() const
{
  return myHasResult;
}

double Geom2dConvert_ApproxCurve::MaxError() const
{
  return myMaxError;
}

void Geom2dConvert_ApproxCurve::Dump(Standard_OStream& o) const
{
  o << "******* Dump of ApproxCurve *******" << std::endl;
  o << "******* Error   " << MaxError() << std::endl;
}
