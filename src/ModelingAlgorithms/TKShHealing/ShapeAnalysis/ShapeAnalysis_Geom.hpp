#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
class gp_Pln;
class gp_Trsf;

class ShapeAnalysis_Geom
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool NearestPlane(const NCollection_Array1<gp_Pnt>& Pnts,
                                           gp_Pln&                           aPln,
                                           double&                           Dmax);

  Standard_EXPORT static bool PositionTrsf(const occ::handle<NCollection_HArray2<double>>& coefs,
                                           gp_Trsf&                                        trsf,
                                           const double                                    unit,
                                           const double                                    prec);
};
