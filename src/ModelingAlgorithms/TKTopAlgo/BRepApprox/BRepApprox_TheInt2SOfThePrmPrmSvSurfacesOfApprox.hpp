#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntSurf_PntOn2S.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#include <NCollection_Array1.hpp>
#include <IntImp_ConstIsoparametric.hpp>
class StdFail_NotDone;
class Standard_DomainError;
class Standard_ConstructionError;
class StdFail_UndefinedDerivative;
class BRepAdaptor_Surface;
class BRepApprox_SurfaceTool;
class BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox;
class math_FunctionSetRoot;
class IntSurf_PntOn2S;
class gp_Dir;
class gp_Dir2d;

class BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox(
    const NCollection_Array1<double>& Param,
    const BRepAdaptor_Surface&        S1,
    const BRepAdaptor_Surface&        S2,
    const double                      TolTangency);

  Standard_EXPORT BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox(const BRepAdaptor_Surface& S1,
                                                                   const BRepAdaptor_Surface& S2,
                                                                   const double TolTangency);

  Standard_EXPORT IntImp_ConstIsoparametric Perform(const NCollection_Array1<double>& Param,
                                                    math_FunctionSetRoot&             Rsnld);

  Standard_EXPORT IntImp_ConstIsoparametric Perform(const NCollection_Array1<double>& Param,
                                                    math_FunctionSetRoot&             Rsnld,
                                                    const IntImp_ConstIsoparametric   ChoixIso);

  bool IsDone() const;

  bool IsEmpty() const;

  const IntSurf_PntOn2S& Point() const;

  bool IsTangent() const;

  const gp_Dir& Direction() const;

  const gp_Dir2d& DirectionOnS1() const;

  const gp_Dir2d& DirectionOnS2() const;

  BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox& Function();

  IntSurf_PntOn2S& ChangePoint();

private:
  bool                                                          done;
  bool                                                          empty;
  IntSurf_PntOn2S                                               pint;
  bool                                                          tangent;
  gp_Dir                                                        d3d;
  gp_Dir2d                                                      d2d1;
  gp_Dir2d                                                      d2d2;
  BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox myZerParFunc;
  double                                                        tol;
  double                                                        ua0;
  double                                                        va0;
  double                                                        ua1;
  double                                                        va1;
  double                                                        ub0;
  double                                                        vb0;
  double                                                        ub1;
  double                                                        vb1;
  double                                                        ures1;
  double                                                        ures2;
  double                                                        vres1;
  double                                                        vres2;
};

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define IntImp_TheFunction BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox
#define IntImp_TheFunction_hxx <BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>
#define IntImp_Int2S BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox
#define IntImp_Int2S_hxx <BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox.hpp>

#include <IntImp_Int2S_1.hpp>

#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef IntImp_TheFunction
#undef IntImp_TheFunction_hxx
#undef IntImp_Int2S
#undef IntImp_Int2S_hxx
