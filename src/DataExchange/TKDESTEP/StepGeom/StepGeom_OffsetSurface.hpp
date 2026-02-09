#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <StepData_Logical.hpp>
#include <StepGeom_Surface.hpp>
class TCollection_HAsciiString;

class StepGeom_OffsetSurface : public StepGeom_Surface
{

public:
  Standard_EXPORT StepGeom_OffsetSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Surface>&         aBasisSurface,
                            const double                                 aDistance,
                            const StepData_Logical                       aSelfIntersect);

  Standard_EXPORT void SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface);

  Standard_EXPORT occ::handle<StepGeom_Surface> BasisSurface() const;

  Standard_EXPORT void SetDistance(const double aDistance);

  Standard_EXPORT double Distance() const;

  Standard_EXPORT void SetSelfIntersect(const StepData_Logical aSelfIntersect);

  Standard_EXPORT StepData_Logical SelfIntersect() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_OffsetSurface, StepGeom_Surface)

private:
  occ::handle<StepGeom_Surface> basisSurface;
  double                        distance;
  StepData_Logical              selfIntersect;
};
