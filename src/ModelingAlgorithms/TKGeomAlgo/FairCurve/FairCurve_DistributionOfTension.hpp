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

class FairCurve_DistributionOfTension : public FairCurve_DistributionOfEnergy
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_DistributionOfTension(
    const int                                         BSplOrder,
    const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
    const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
    const int                                         DerivativeOrder,
    const double                                      LengthSliding,
    const FairCurve_BattenLaw&                        Law,
    const int                                         NbValAux = 0,
    const bool                                        Uniform  = false);

  void SetLengthSliding(const double LengthSliding);

  Standard_EXPORT bool Value(const math_Vector& X, math_Vector& F) override;

private:
  double              MyLengthSliding;
  FairCurve_BattenLaw MyLaw;
  double              MyHeight;
};

inline void FairCurve_DistributionOfTension::SetLengthSliding(const double LengthSliding)
{
  MyLengthSliding = LengthSliding;
}
