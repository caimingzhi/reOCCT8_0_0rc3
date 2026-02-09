#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <IntPatch_Polygo.hpp>
#include <Standard_Integer.hpp>
class Bnd_Box2d;
class gp_Pnt2d;

class IntPatch_PolyArc : public IntPatch_Polygo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_PolyArc(const occ::handle<Adaptor2d_Curve2d>& A,
                                   const int                             NbSample,
                                   const double                          Pfirst,
                                   const double                          Plast,
                                   const Bnd_Box2d&                      BoxOtherPolygon);

  Standard_EXPORT bool Closed() const override;

  Standard_EXPORT int NbPoints() const override;

  Standard_EXPORT gp_Pnt2d Point(const int Index) const override;

  Standard_EXPORT double Parameter(const int Index) const;

  Standard_EXPORT void SetOffset(const double OffsetX, const double OffsetY);

private:
  NCollection_Array1<gp_Pnt2d> brise;
  NCollection_Array1<double>   param;
  double                       offsetx;
  double                       offsety;
  bool                         ferme;
};
