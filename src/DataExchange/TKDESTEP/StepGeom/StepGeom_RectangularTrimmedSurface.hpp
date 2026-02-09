#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <StepGeom_BoundedSurface.hpp>
class StepGeom_Surface;
class TCollection_HAsciiString;

class StepGeom_RectangularTrimmedSurface : public StepGeom_BoundedSurface
{

public:
  Standard_EXPORT StepGeom_RectangularTrimmedSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Surface>&         aBasisSurface,
                            const double                                 aU1,
                            const double                                 aU2,
                            const double                                 aV1,
                            const double                                 aV2,
                            const bool                                   aUsense,
                            const bool                                   aVsense);

  Standard_EXPORT void SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface);

  Standard_EXPORT occ::handle<StepGeom_Surface> BasisSurface() const;

  Standard_EXPORT void SetU1(const double aU1);

  Standard_EXPORT double U1() const;

  Standard_EXPORT void SetU2(const double aU2);

  Standard_EXPORT double U2() const;

  Standard_EXPORT void SetV1(const double aV1);

  Standard_EXPORT double V1() const;

  Standard_EXPORT void SetV2(const double aV2);

  Standard_EXPORT double V2() const;

  Standard_EXPORT void SetUsense(const bool aUsense);

  Standard_EXPORT bool Usense() const;

  Standard_EXPORT void SetVsense(const bool aVsense);

  Standard_EXPORT bool Vsense() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_RectangularTrimmedSurface, StepGeom_BoundedSurface)

private:
  occ::handle<StepGeom_Surface> basisSurface;
  double                        u1;
  double                        u2;
  double                        v1;
  double                        v2;
  bool                          usense;
  bool                          vsense;
};
