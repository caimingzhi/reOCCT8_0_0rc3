#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <CPnts_MyRootFunction.hpp>
class Adaptor3d_Curve;
class Adaptor2d_Curve2d;

class CPnts_AbscissaPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double Length(const Adaptor3d_Curve& C);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& C);

  Standard_EXPORT static double Length(const Adaptor3d_Curve& C, const double Tol);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& C, const double Tol);

  Standard_EXPORT static double Length(const Adaptor3d_Curve& C, const double U1, const double U2);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& C,
                                       const double             U1,
                                       const double             U2);

  Standard_EXPORT static double Length(const Adaptor3d_Curve& C,
                                       const double           U1,
                                       const double           U2,
                                       const double           Tol);

  Standard_EXPORT static double Length(const Adaptor2d_Curve2d& C,
                                       const double             U1,
                                       const double             U2,
                                       const double             Tol);

  Standard_EXPORT CPnts_AbscissaPoint();

  Standard_EXPORT CPnts_AbscissaPoint(const Adaptor3d_Curve& C,
                                      const double           Abscissa,
                                      const double           U0,
                                      const double           Resolution);

  Standard_EXPORT CPnts_AbscissaPoint(const Adaptor2d_Curve2d& C,
                                      const double             Abscissa,
                                      const double             U0,
                                      const double             Resolution);

  Standard_EXPORT CPnts_AbscissaPoint(const Adaptor3d_Curve& C,
                                      const double           Abscissa,
                                      const double           U0,
                                      const double           Ui,
                                      const double           Resolution);

  Standard_EXPORT CPnts_AbscissaPoint(const Adaptor2d_Curve2d& C,
                                      const double             Abscissa,
                                      const double             U0,
                                      const double             Ui,
                                      const double             Resolution);

  Standard_EXPORT void Init(const Adaptor3d_Curve& C);

  Standard_EXPORT void Init(const Adaptor2d_Curve2d& C);

  Standard_EXPORT void Init(const Adaptor3d_Curve& C, const double Tol);

  Standard_EXPORT void Init(const Adaptor2d_Curve2d& C, const double Tol);

  Standard_EXPORT void Init(const Adaptor3d_Curve& C, const double U1, const double U2);

  Standard_EXPORT void Init(const Adaptor2d_Curve2d& C, const double U1, const double U2);

  Standard_EXPORT void Init(const Adaptor3d_Curve& C,
                            const double           U1,
                            const double           U2,
                            const double           Tol);

  Standard_EXPORT void Init(const Adaptor2d_Curve2d& C,
                            const double             U1,
                            const double             U2,
                            const double             Tol);

  Standard_EXPORT void Perform(const double Abscissa, const double U0, const double Resolution);

  Standard_EXPORT void Perform(const double Abscissa,
                               const double U0,
                               const double Ui,
                               const double Resolution);

  Standard_EXPORT void AdvPerform(const double Abscissa,
                                  const double U0,
                                  const double Ui,
                                  const double Resolution);

  bool IsDone() const;

  double Parameter() const;

  void SetParameter(const double P);

private:
  bool                 myDone;
  double               myL;
  double               myParam;
  double               myUMin;
  double               myUMax;
  CPnts_MyRootFunction myF;
};

#include <StdFail_NotDone.hpp>

inline bool CPnts_AbscissaPoint::IsDone() const
{
  return myDone;
}

inline double CPnts_AbscissaPoint::Parameter() const
{
  StdFail_NotDone_Raise_if(!myDone, "CPnts_AbscissaPoint::Parameter() - no result");
  return myParam;
}

inline void CPnts_AbscissaPoint::SetParameter(const double P)
{
  myParam = P;
  myDone  = true;
}
