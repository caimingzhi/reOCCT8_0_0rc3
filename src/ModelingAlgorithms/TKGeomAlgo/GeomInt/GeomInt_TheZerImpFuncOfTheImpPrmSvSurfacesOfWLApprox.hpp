#pragma once

#include <Adaptor3d_Surface.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>

class Adaptor3d_HSurfaceTool;
class IntSurf_Quadric;
class IntSurf_QuadricTool;
class math_Matrix;

class GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox();

  Standard_EXPORT GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox(
    const occ::handle<Adaptor3d_Surface>& PS,
    const IntSurf_Quadric&                IS);

  Standard_EXPORT GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox(const IntSurf_Quadric& IS);

  void Set(const occ::handle<Adaptor3d_Surface>& PS);

  void SetImplicitSurface(const IntSurf_Quadric& IS);

  void Set(const double Tolerance);

  Standard_EXPORT int NbVariables() const override;

  Standard_EXPORT int NbEquations() const override;

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

  Standard_EXPORT bool Derivatives(const math_Vector& X, math_Matrix& D) override;

  Standard_EXPORT bool Values(const math_Vector& X, math_Vector& F, math_Matrix& D) override;

  double Root() const;

  double Tolerance() const;

  const gp_Pnt& Point() const;

  Standard_EXPORT bool IsTangent();

  const gp_Vec& Direction3d();

  const gp_Dir2d& Direction2d();

  const occ::handle<Adaptor3d_Surface>& PSurface() const;

  const IntSurf_Quadric& ISurface() const;

private:
  void*    surf;
  void*    func;
  double   u;
  double   v;
  double   tol;
  gp_Pnt   pntsol;
  double   valf;
  bool     computed;
  bool     tangent;
  double   tgdu;
  double   tgdv;
  gp_Vec   gradient;
  bool     derived;
  gp_Vec   d1u;
  gp_Vec   d1v;
  gp_Vec   d3d;
  gp_Dir2d d2d;
};

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define IntImp_ZerImpFunc GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox
#define IntImp_ZerImpFunc_hxx <GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox.hpp>

#include <IntImp_ZerImpFunc_1.hpp>

#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef TheISurface
#undef TheISurface_hxx
#undef TheISurfaceTool
#undef TheISurfaceTool_hxx
#undef IntImp_ZerImpFunc
#undef IntImp_ZerImpFunc_hxx
