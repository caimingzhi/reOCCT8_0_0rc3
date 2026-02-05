#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <FairCurve_BattenLaw.hpp>
#include <FairCurve_DistributionOfEnergy.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt2d.hpp>
#include <math_Vector.hpp>

//! Compute the "Jerk" distribution.
class FairCurve_DistributionOfJerk : public FairCurve_DistributionOfEnergy
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_DistributionOfJerk(
    const int                                         BSplOrder,
    const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
    const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
    const int                                         DerivativeOrder,
    const FairCurve_BattenLaw&                        Law,
    const int                                         NbValAux = 0);

  //! computes the values <F> of the functions for the
  //! variable <X>.
  //! returns True if the computation was done successfully,
  //! False otherwise.
  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

private:
  FairCurve_BattenLaw MyLaw;
};
