#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir2d.hpp>
#include <math_FunctionSetWithDerivatives.hpp>
#include <math_Vector.hpp>
class StdFail_UndefinedDerivative;
class BRepAdaptor_Surface;
class BRepApprox_SurfaceTool;
class IntSurf_Quadric;
class IntSurf_QuadricTool;
class math_Matrix;
class gp_Pnt;
class gp_Vec;
class gp_Dir2d;

class BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox : public math_FunctionSetWithDerivatives
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox();

  Standard_EXPORT BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox(
    const BRepAdaptor_Surface& PS,
    const IntSurf_Quadric&     IS);

  Standard_EXPORT BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox(const IntSurf_Quadric& IS);

  void Set(const BRepAdaptor_Surface& PS);

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

  const BRepAdaptor_Surface& PSurface() const;

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

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define IntImp_ZerImpFunc BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox
#define IntImp_ZerImpFunc_hxx <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>

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
