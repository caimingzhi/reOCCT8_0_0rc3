#include <Precision.hpp>

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen()
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
}

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen(const TheCurve& C,
                                                            const double    TolConf,
                                                            const double    Tol)
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
  Perform(C, TolConf, Tol);
}

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen(const TheCurve&        C,
                                                            const IntRes2d_Domain& D,
                                                            const double           TolConf,
                                                            const double           Tol)
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
  Perform(C, D, TolConf, Tol);
}

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen(const TheCurve& C1,
                                                            const TheCurve& C2,
                                                            const double    TolConf,
                                                            const double    Tol)
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
  Perform(C1, C2, TolConf, Tol);
}

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen(const TheCurve&        C1,
                                                            const IntRes2d_Domain& D1,
                                                            const TheCurve&        C2,
                                                            const double           TolConf,
                                                            const double           Tol)
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
  Perform(C1, D1, C2, TolConf, Tol);
}

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen(const TheCurve&        C1,
                                                            const TheCurve&        C2,
                                                            const IntRes2d_Domain& D2,
                                                            const double           TolConf,
                                                            const double           Tol)
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
  Perform(C1, C2, D2, TolConf, Tol);
}

//----------------------------------------------------------------------
inline IntCurve_IntCurveCurveGen::IntCurve_IntCurveCurveGen(const TheCurve&        C1,
                                                            const IntRes2d_Domain& D1,
                                                            const TheCurve&        C2,
                                                            const IntRes2d_Domain& D2,
                                                            const double           TolConf,
                                                            const double           Tol)
    : param1inf(-Precision::Infinite()),
      param1sup(Precision::Infinite()),
      param2inf(-Precision::Infinite()),
      param2sup(Precision::Infinite())
{
  Perform(C1, D1, C2, D2, TolConf, Tol);
}

//---------------------------------------------------------------------
inline void IntCurve_IntCurveCurveGen::Perform(const TheCurve& C1,
                                               const TheCurve& C2,
                                               const double    TolConf,
                                               const double    Tol)
{
  double TolDomain = Tol;
  if (TolConf > TolDomain)
  {
    TolDomain = TolConf;
  }
  Perform(C1, ComputeDomain(C1, TolDomain), C2, ComputeDomain(C2, TolDomain), TolConf, Tol);
}

//----------------------------------------------------------------------
inline void IntCurve_IntCurveCurveGen::Perform(const TheCurve&        C1,
                                               const IntRes2d_Domain& D1,
                                               const TheCurve&        C2,
                                               const double           TolConf,
                                               const double           Tol)
{
  double TolDomain = Tol;
  if (TolConf > TolDomain)
  {
    TolDomain = TolConf;
  }
  Perform(C1, D1, C2, ComputeDomain(C2, TolDomain), TolConf, Tol);
}

//----------------------------------------------------------------------
inline void IntCurve_IntCurveCurveGen::Perform(const TheCurve&        C1,
                                               const TheCurve&        C2,
                                               const IntRes2d_Domain& D2,
                                               const double           TolConf,
                                               const double           Tol)
{
  double TolDomain = Tol;
  if (TolConf > TolDomain)
  {
    TolDomain = TolConf;
  }
  Perform(C1, ComputeDomain(C1, TolDomain), C2, D2, TolConf, Tol);
}
