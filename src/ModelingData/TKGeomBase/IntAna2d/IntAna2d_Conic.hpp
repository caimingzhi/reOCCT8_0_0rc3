#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class gp_Circ2d;
class gp_Lin2d;
class gp_Parab2d;
class gp_Hypr2d;
class gp_Elips2d;
class gp_XY;
class gp_Ax2d;

class IntAna2d_Conic
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna2d_Conic(const gp_Circ2d& C);

  Standard_EXPORT IntAna2d_Conic(const gp_Lin2d& C);

  Standard_EXPORT IntAna2d_Conic(const gp_Parab2d& C);

  Standard_EXPORT IntAna2d_Conic(const gp_Hypr2d& C);

  Standard_EXPORT IntAna2d_Conic(const gp_Elips2d& C);

  Standard_EXPORT double Value(const double X, const double Y) const;

  Standard_EXPORT gp_XY Grad(const double X, const double Y) const;

  Standard_EXPORT void ValAndGrad(const double X, const double Y, double& Val, gp_XY& Grd) const;

  Standard_EXPORT void Coefficients(double& A,
                                    double& B,
                                    double& C,
                                    double& D,
                                    double& E,
                                    double& F) const;

  Standard_EXPORT void NewCoefficients(double&        A,
                                       double&        B,
                                       double&        C,
                                       double&        D,
                                       double&        E,
                                       double&        F,
                                       const gp_Ax2d& Axis) const;

private:
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
};
