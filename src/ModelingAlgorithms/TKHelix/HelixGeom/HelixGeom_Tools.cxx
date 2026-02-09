

#include <Adaptor3d_Curve.hpp>
#include <AdvApprox_ApproxAFunction.hpp>
#include <AdvApprox_DichoCutting.hpp>
#include <AdvApprox_EvaluatorFunction.hpp>
#include <Geom_BSplineCurve.hpp>
#include <HelixGeom_HelixCurve.hpp>
#include <HelixGeom_Tools.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

class HelixGeom_Tools_Eval : public AdvApprox_EvaluatorFunction
{
public:
  HelixGeom_Tools_Eval(const occ::handle<Adaptor3d_Curve>& theFunc)
      : fonct(theFunc)
  {
  }

  void Evaluate(int*    Dimension,
                double  StartEnd[2],
                double* Parameter,
                int*    DerivativeRequest,
                double* Result,
                int*    ErrorCode) override;

private:
  occ::handle<Adaptor3d_Curve> fonct;
};

void HelixGeom_Tools_Eval::Evaluate(int* Dimension,
                                    double[2],
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

int HelixGeom_Tools::ApprCurve3D(const occ::handle<Adaptor3d_Curve>& theHC,
                                 const double                        theTol,
                                 const GeomAbs_Shape                 theCont,
                                 const int                           theMaxSeg,
                                 const int                           theMaxDeg,
                                 occ::handle<Geom_BSplineCurve>&     theBSpl,
                                 double&                             theMaxError)
{
  bool                                     anIsDone, aHasResult;
  int                                      Num1DSS, Num2DSS, Num3DSS;
  double                                   First, Last;
  occ::handle<NCollection_HArray1<double>> OneDTolNul, TwoDTolNul, ThreeDTol;
  AdvApprox_DichoCutting                   aCutTool;

  Num1DSS   = 0;
  Num2DSS   = 0;
  Num3DSS   = 1;
  ThreeDTol = new NCollection_HArray1<double>(1, Num3DSS);
  ThreeDTol->Init(theTol);

  First = theHC->FirstParameter();
  Last  = theHC->LastParameter();

  HelixGeom_Tools_Eval      ev(theHC);
  AdvApprox_ApproxAFunction aApprox(Num1DSS,
                                    Num2DSS,
                                    Num3DSS,
                                    OneDTolNul,
                                    TwoDTolNul,
                                    ThreeDTol,
                                    First,
                                    Last,
                                    theCont,
                                    theMaxDeg,
                                    theMaxSeg,
                                    ev,
                                    aCutTool);

  anIsDone = aApprox.IsDone();
  if (!anIsDone)
  {
    return 1;
  }

  theMaxError = 0.;

  aHasResult = aApprox.HasResult();
  if (!aHasResult)
  {
    return 2;
  }

  NCollection_Array1<gp_Pnt> Poles(1, aApprox.NbPoles());
  aApprox.Poles(1, Poles);
  occ::handle<NCollection_HArray1<double>> Knots  = aApprox.Knots();
  occ::handle<NCollection_HArray1<int>>    Mults  = aApprox.Multiplicities();
  int                                      Degree = aApprox.Degree();
  theBSpl     = new Geom_BSplineCurve(Poles, Knots->Array1(), Mults->Array1(), Degree);
  theMaxError = aApprox.MaxError(3, 1);

  return 0;
}

int HelixGeom_Tools::ApprHelix(const double                    aT1,
                               const double                    aT2,
                               const double                    aPitch,
                               const double                    aRStart,
                               const double                    aTaperAngle,
                               const bool                      aIsCW,
                               const double                    theTol,
                               occ::handle<Geom_BSplineCurve>& theBSpl,
                               double&                         theMaxError)
{
  int                               iErr, aMaxDegree, aMaxSeg;
  GeomAbs_Shape                     aCont;
  HelixGeom_HelixCurve              aAdaptor;
  occ::handle<HelixGeom_HelixCurve> aHAdaptor;

  aAdaptor.Load(aT1, aT2, aPitch, aRStart, aTaperAngle, aIsCW);
  aHAdaptor = new HelixGeom_HelixCurve(aAdaptor);

  aCont      = GeomAbs_C2;
  aMaxDegree = 8;
  aMaxSeg    = 150;

  iErr = HelixGeom_Tools::ApprCurve3D(aHAdaptor,
                                      theTol,
                                      aCont,
                                      aMaxSeg,
                                      aMaxDegree,
                                      theBSpl,
                                      theMaxError);
  return iErr;
}
