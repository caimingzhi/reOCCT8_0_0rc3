#pragma once


#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <IntImp_ConstIsoparametric.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>

class Adaptor3d_HSurfaceTool;
class math_Matrix;

class IntWalk_TheFunctionOfTheInt2S : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntWalk_TheFunctionOfTheInt2S(const occ::handle<Adaptor3d_Surface>& S1,
                                                const occ::handle<Adaptor3d_Surface>& S2);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  Standard_EXPORT void ComputeParameters(const IntImp_ConstIsoparametric   ChoixIso,
                                         const NCollection_Array1<double>& Param,
                                         math_Vector&                      UVap,
                                         math_Vector&                      BornInf,
                                         math_Vector&                      BornSup,
                                         math_Vector&                      Tolerance);

  //! returns somme des fi*fi
  double Root() const;

  gp_Pnt Point() const;

  Standard_EXPORT bool IsTangent(const math_Vector&          UVap,
                                 NCollection_Array1<double>& Param,
                                 IntImp_ConstIsoparametric&  BestChoix);

  gp_Dir Direction() const;

  gp_Dir2d DirectionOnS1() const;

  gp_Dir2d DirectionOnS2() const;

  const occ::handle<Adaptor3d_Surface>& AuxillarSurface1() const;

  const occ::handle<Adaptor3d_Surface>& AuxillarSurface2() const;

private:
  void*                     surf1;
  void*                     surf2;
  gp_Pnt                    pntsol1;
  gp_Pnt                    pntsol2;
  double                    f[3];
  bool                      compute;
  bool                      tangent;
  double                    tgduv[4];
  gp_Vec                    dpuv[4];
  IntImp_ConstIsoparametric chxIso;
  double                    paramConst;
  double                    ua0;
  double                    va0;
  double                    ua1;
  double                    va1;
  double                    ub0;
  double                    vb0;
  double                    ub1;
  double                    vb1;
  double                    ures1;
  double                    ures2;
  double                    vres1;
  double                    vres2;
};

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define IntImp_ZerParFunc IntWalk_TheFunctionOfTheInt2S
#define IntImp_ZerParFunc_hxx <IntWalk_TheFunctionOfTheInt2S.hpp>

#include <IntImp_ZerParFunc_1.hpp>

#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef IntImp_ZerParFunc
#undef IntImp_ZerParFunc_hxx

