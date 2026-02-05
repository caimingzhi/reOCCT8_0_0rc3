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

//! Analyzing tool aimed to work on primitive geometrical objects
class ShapeAnalysis_Geom
{
public:
  DEFINE_STANDARD_ALLOC

  //! Builds a plane out of a set of points in array
  //! Returns in <dmax> the maximal distance between the produced
  //! plane and given points
  Standard_EXPORT static bool NearestPlane(const NCollection_Array1<gp_Pnt>& Pnts,
                                           gp_Pln&                           aPln,
                                           double&                           Dmax);

  //! Builds transformation object out of matrix.
  //! Matrix must be 3 x 4.
  //! Unit is used as multiplier.
  Standard_EXPORT static bool PositionTrsf(const occ::handle<NCollection_HArray2<double>>& coefs,
                                           gp_Trsf&                                        trsf,
                                           const double                                    unit,
                                           const double                                    prec);
};
