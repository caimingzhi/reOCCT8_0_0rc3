#include <Approx_Curve3d.hpp>

#include <Adaptor3d_Curve.hpp>
#include <AdvApprox_ApproxAFunction.hpp>
#include <AdvApprox_PrefAndRec.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

class Approx_Curve3d_Eval : public AdvApprox_EvaluatorFunction
{
public:
  Approx_Curve3d_Eval(const occ::handle<Adaptor3d_Curve>& theFunc, double First, double Last)
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
  occ::handle<Adaptor3d_Curve> fonct;
  double                       StartEndSav[2];
};

void Approx_Curve3d_Eval::Evaluate(int*    Dimension,
                                   double  StartEnd[2],
                                   double* Param,
                                   int*    Order,
                                   double* Result,
                                   int*    ErrorCode)
{
  *ErrorCode = 0;
  double par = *Param;

  if (*Dimension != 3)
  {
    *ErrorCode = 1;
  }

  if (StartEnd[0] != StartEndSav[0] || StartEnd[1] != StartEndSav[1])
  {
    fonct          = fonct->Trim(StartEnd[0], StartEnd[1], Precision::PConfusion());
    StartEndSav[0] = StartEnd[0];
    StartEndSav[1] = StartEnd[1];
  }

  gp_Pnt pnt;
  gp_Vec v1, v2;

  switch (*Order)
  {
    case 0:
      pnt       = fonct->Value(par);
      Result[0] = pnt.X();
      Result[1] = pnt.Y();
      Result[2] = pnt.Z();
      break;
    case 1:
      fonct->D1(par, pnt, v1);
      Result[0] = v1.X();
      Result[1] = v1.Y();
      Result[2] = v1.Z();
      break;
    case 2:
      fonct->D2(par, pnt, v1, v2);
      Result[0] = v2.X();
      Result[1] = v2.Y();
      Result[2] = v2.Z();
      break;
    default:
      Result[0] = Result[1] = Result[2] = 0.;
      *ErrorCode                        = 3;
      break;
  }
}

Approx_Curve3d::Approx_Curve3d(const occ::handle<Adaptor3d_Curve>& Curve,
                               const double                        Tol3d,
                               const GeomAbs_Shape                 Order,
                               const int                           MaxSegments,
                               const int                           MaxDegree)
{

  int                                      Num1DSS = 0, Num2DSS = 0, Num3DSS = 1;
  occ::handle<NCollection_HArray1<double>> OneDTolNul, TwoDTolNul;
  occ::handle<NCollection_HArray1<double>> ThreeDTol = new NCollection_HArray1<double>(1, Num3DSS);
  ThreeDTol->Init(Tol3d);

  double First = Curve->FirstParameter();
  double Last  = Curve->LastParameter();

  int                        NbInterv_C2 = Curve->NbIntervals(GeomAbs_C2);
  NCollection_Array1<double> CutPnts_C2(1, NbInterv_C2 + 1);
  Curve->Intervals(CutPnts_C2, GeomAbs_C2);
  int                        NbInterv_C3 = Curve->NbIntervals(GeomAbs_C3);
  NCollection_Array1<double> CutPnts_C3(1, NbInterv_C3 + 1);
  Curve->Intervals(CutPnts_C3, GeomAbs_C3);

  AdvApprox_PrefAndRec CutTool(CutPnts_C2, CutPnts_C3);

  myMaxError = 0;

  Approx_Curve3d_Eval       ev(Curve, First, Last);
  AdvApprox_ApproxAFunction aApprox(Num1DSS,
                                    Num2DSS,
                                    Num3DSS,
                                    OneDTolNul,
                                    TwoDTolNul,
                                    ThreeDTol,
                                    First,
                                    Last,
                                    Order,
                                    MaxDegree,
                                    MaxSegments,
                                    ev,
                                    CutTool);

  myIsDone    = aApprox.IsDone();
  myHasResult = aApprox.HasResult();

  if (myHasResult)
  {
    NCollection_Array1<gp_Pnt> Poles(1, aApprox.NbPoles());
    aApprox.Poles(1, Poles);
    occ::handle<NCollection_HArray1<double>> Knots  = aApprox.Knots();
    occ::handle<NCollection_HArray1<int>>    Mults  = aApprox.Multiplicities();
    int                                      Degree = aApprox.Degree();
    myBSplCurve = new Geom_BSplineCurve(Poles, Knots->Array1(), Mults->Array1(), Degree);
    myMaxError  = aApprox.MaxError(3, 1);
  }
}

occ::handle<Geom_BSplineCurve> Approx_Curve3d::Curve() const
{
  return myBSplCurve;
}

bool Approx_Curve3d::IsDone() const
{
  return myIsDone;
}

bool Approx_Curve3d::HasResult() const
{
  return myHasResult;
}

double Approx_Curve3d::MaxError() const
{
  return myMaxError;
}

void Approx_Curve3d::Dump(Standard_OStream& o) const
{
  o << "******* Dump of ApproxCurve *******" << std::endl;
  o << "*******Degree     " << Curve()->Degree() << std::endl;
  o << "*******NbSegments " << Curve()->NbKnots() - 1 << std::endl;
  o << "*******Error      " << MaxError() << std::endl;
}
