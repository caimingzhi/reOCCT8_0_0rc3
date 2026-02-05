#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <IntWalk_TheFunctionOfTheInt2S.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <IntImp_ConstIsoparametric.hpp>

class Adaptor3d_HSurfaceTool;
class math_FunctionSetRoot;

class IntWalk_TheInt2S
{
public:
  DEFINE_STANDARD_ALLOC

  //! compute the solution point with the close point
  Standard_EXPORT IntWalk_TheInt2S(const NCollection_Array1<double>&     Param,
                                   const occ::handle<Adaptor3d_Surface>& S1,
                                   const occ::handle<Adaptor3d_Surface>& S2,
                                   const double                          TolTangency);

  //! initialize the parameters to compute the solution point
  //! it 's possible to write to optimize:
  //! IntImp_Int2S inter(S1,S2,Func,TolTangency);
  //! math_FunctionSetRoot rsnld(inter.Function());
  //! while ...{
  //! Param(1)=...
  //! Param(2)=...
  //! param(3)=...
  //! inter.Perform(Param,rsnld);
  //! }
  Standard_EXPORT IntWalk_TheInt2S(const occ::handle<Adaptor3d_Surface>& S1,
                                   const occ::handle<Adaptor3d_Surface>& S2,
                                   const double                          TolTangency);

  //! returns the best constant isoparametric to find
  //! the next intersection's point +stores the solution
  //! point (the solution point is found with the close point
  //! to intersect the isoparametric with the other patch;
  //! the choice of the isoparametic is calculated)
  Standard_EXPORT IntImp_ConstIsoparametric Perform(const NCollection_Array1<double>& Param,
                                                    math_FunctionSetRoot&             Rsnld);

  //! returns the best constant isoparametric to find
  //! the next intersection's point +stores the solution
  //! point (the solution point is found with the close point
  //! to intersect the isoparametric with the other patch;
  //! the choice of the isoparametic is given by ChoixIso)
  Standard_EXPORT IntImp_ConstIsoparametric Perform(const NCollection_Array1<double>& Param,
                                                    math_FunctionSetRoot&             Rsnld,
                                                    const IntImp_ConstIsoparametric   ChoixIso);

  //! Returns TRUE if the creation completed without failure.
  bool IsDone() const;

  //! Returns TRUE when there is no solution to the problem.
  bool IsEmpty() const;

  //! Returns the intersection point.
  const IntSurf_PntOn2S& Point() const;

  //! Returns True if the surfaces are tangent at the
  //! intersection point.
  bool IsTangent() const;

  //! Returns the tangent at the intersection line.
  const gp_Dir& Direction() const;

  //! Returns the tangent at the intersection line in the
  //! parametric space of the first surface.
  const gp_Dir2d& DirectionOnS1() const;

  //! Returns the tangent at the intersection line in the
  //! parametric space of the second surface.
  const gp_Dir2d& DirectionOnS2() const;

  //! return the math function which
  //! is used to compute the intersection
  IntWalk_TheFunctionOfTheInt2S& Function();

  //! return the intersection point which is
  //! enable for changing.
  IntSurf_PntOn2S& ChangePoint();

private:
  bool                          done;
  bool                          empty;
  IntSurf_PntOn2S               pint;
  bool                          tangent;
  gp_Dir                        d3d;
  gp_Dir2d                      d2d1;
  gp_Dir2d                      d2d2;
  IntWalk_TheFunctionOfTheInt2S myZerParFunc;
  double                        tol;
  double                        ua0;
  double                        va0;
  double                        ua1;
  double                        va1;
  double                        ub0;
  double                        vb0;
  double                        ub1;
  double                        vb1;
  double                        ures1;
  double                        ures2;
  double                        vres1;
  double                        vres2;
};

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define IntImp_TheFunction IntWalk_TheFunctionOfTheInt2S
#define IntImp_TheFunction_hxx <IntWalk_TheFunctionOfTheInt2S.hpp>
#define IntImp_Int2S IntWalk_TheInt2S
#define IntImp_Int2S_hxx <IntWalk_TheInt2S.hpp>

#include <IntImp_Int2S_1.hpp>

#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef IntImp_TheFunction
#undef IntImp_TheFunction_hxx
#undef IntImp_Int2S
#undef IntImp_Int2S_hxx
