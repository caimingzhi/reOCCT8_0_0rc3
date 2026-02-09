#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <FairCurve_BattenLaw.hpp>
#include <FairCurve_DistributionOfTension.hpp>
#include <FairCurve_DistributionOfSagging.hpp>
#include <FairCurve_DistributionOfJerk.hpp>
#include <FairCurve_AnalysisCode.hpp>
#include <FairCurve_Energy.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt2d.hpp>
#include <math_Vector.hpp>

#ifdef Status
  #undef Status
#endif

class FairCurve_EnergyOfMVC : public FairCurve_Energy
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT FairCurve_EnergyOfMVC(const int                                         BSplOrder,
                                        const occ::handle<NCollection_HArray1<double>>&   FlatKnots,
                                        const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
                                        const int                  ContrOrder1,
                                        const int                  ContrOrder2,
                                        const FairCurve_BattenLaw& Law,
                                        const double               PhysicalRatio,
                                        const double               LengthSliding,
                                        const bool                 FreeSliding = true,
                                        const double               Angle1      = 0,
                                        const double               Angle2      = 0,
                                        const double               Curvature1  = 0,
                                        const double               Curvature2  = 0);

  double LengthSliding() const;

  FairCurve_AnalysisCode Status() const;

  Standard_EXPORT bool Variable(math_Vector& X) const override;

protected:
  Standard_EXPORT void ComputePoles(const math_Vector& X) override;

  Standard_EXPORT bool Compute(const int DerivativeOrder, math_Vector& Result) override;

private:
  double                          MyLengthSliding;
  double                          OriginalSliding;
  FairCurve_BattenLaw             MyBattenLaw;
  double                          MyPhysicalRatio;
  FairCurve_DistributionOfTension MyTension;
  FairCurve_DistributionOfSagging MySagging;
  FairCurve_DistributionOfJerk    MyJerk;
  FairCurve_AnalysisCode          MyStatus;
};

inline double FairCurve_EnergyOfMVC::LengthSliding() const
{
  return MyLengthSliding;
}

inline FairCurve_AnalysisCode FairCurve_EnergyOfMVC::Status() const
{
  return MyStatus;
}
