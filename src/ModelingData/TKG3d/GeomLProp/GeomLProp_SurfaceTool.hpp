#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class Geom_Surface;
class gp_Pnt;
class gp_Vec;

class GeomLProp_SurfaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the point <P> of parameter <U> and <V> on the
  //! Surface <S>.
  Standard_EXPORT static void Value(const occ::handle<Geom_Surface>& S,
                                    const double                     U,
                                    const double                     V,
                                    gp_Pnt&                          P);

  //! Computes the point <P> and first derivative <D1*> of
  //! parameter <U> and <V> on the Surface <S>.
  Standard_EXPORT static void D1(const occ::handle<Geom_Surface>& S,
                                 const double                     U,
                                 const double                     V,
                                 gp_Pnt&                          P,
                                 gp_Vec&                          D1U,
                                 gp_Vec&                          D1V);

  //! Computes the point <P>, the first derivative <D1*> and second
  //! derivative <D2*> of parameter <U> and <V> on the Surface <S>.
  Standard_EXPORT static void D2(const occ::handle<Geom_Surface>& S,
                                 const double                     U,
                                 const double                     V,
                                 gp_Pnt&                          P,
                                 gp_Vec&                          D1U,
                                 gp_Vec&                          D1V,
                                 gp_Vec&                          D2U,
                                 gp_Vec&                          D2V,
                                 gp_Vec&                          DUV);

  Standard_EXPORT static gp_Vec DN(const occ::handle<Geom_Surface>& S,
                                   const double                     U,
                                   const double                     V,
                                   const int                        IU,
                                   const int                        IV);

  //! returns the order of continuity of the Surface <S>.
  //! returns 1 : first derivative only is computable
  //! returns 2 : first and second derivative only are computable.
  Standard_EXPORT static int Continuity(const occ::handle<Geom_Surface>& S);

  //! returns the bounds of the Surface.
  Standard_EXPORT static void Bounds(const occ::handle<Geom_Surface>& S,
                                     double&                          U1,
                                     double&                          V1,
                                     double&                          U2,
                                     double&                          V2);
};

