#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <math_MultipleVarFunctionWithHessian.hpp>
#include <Standard_Real.hpp>
class math_Matrix;
class gp_Pnt2d;

class FairCurve_Energy : public math_MultipleVarFunctionWithHessian
{
public:
  DEFINE_STANDARD_ALLOC

  int NbVariables() const override;

  Standard_EXPORT bool Value(const math_Vector& X, double& E) override;

  Standard_EXPORT bool Gradient(const math_Vector& X, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X, double& E, math_Vector& G) override;

  Standard_EXPORT bool Values(const math_Vector& X,
                              double&            E,
                              math_Vector&       G,
                              math_Matrix&       H) override;

  Standard_EXPORT virtual bool Variable(math_Vector& X) const;

  const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles() const;

protected:
  Standard_EXPORT FairCurve_Energy(const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
                                   const int                                         ConstrOrder1,
                                   const int                                         ConstrOrder2,
                                   const bool   WithAuxValue = false,
                                   const double Angle1       = 0,
                                   const double Angle2       = 0,
                                   const int    Degree       = 2,
                                   const double Curvature1   = 0,
                                   const double Curvature2   = 0);

  Standard_EXPORT void Gradient1(const math_Vector& TheVector, math_Vector& G);

  Standard_EXPORT void Hessian1(const math_Vector& TheVector, math_Matrix& H);

  Standard_EXPORT virtual void ComputePoles(const math_Vector& X);

  int Indice(const int i, const int j) const;

  Standard_EXPORT void ComputePolesG1(const int       Side,
                                      const double    Lambda,
                                      const gp_Pnt2d& P1,
                                      gp_Pnt2d&       P2) const;

  Standard_EXPORT void ComputePolesG2(const int       Side,
                                      const double    Lambda,
                                      const double    Rho,
                                      const gp_Pnt2d& P1,
                                      gp_Pnt2d&       P2) const;

  Standard_EXPORT virtual bool Compute(const int DerivativeOrder, math_Vector& Result) = 0;

  occ::handle<NCollection_HArray1<gp_Pnt2d>> MyPoles;
  int                                        MyContrOrder1;
  int                                        MyContrOrder2;
  bool                                       MyWithAuxValue;
  int                                        MyNbVar;

private:
  int                       MyNbValues;
  NCollection_Array1<gp_XY> MyLinearForm;
  NCollection_Array1<gp_XY> MyQuadForm;
  math_Vector               MyGradient;
  math_Vector               MyHessian;
};

inline int FairCurve_Energy::NbVariables() const
{
  return MyNbVar;
}

inline const occ::handle<NCollection_HArray1<gp_Pnt2d>>& FairCurve_Energy::Poles() const
{
  return MyPoles;
}

inline int FairCurve_Energy::Indice(const int i, const int j) const
{
  return MyNbValues + j + i * (i - 1) / 2;
}
