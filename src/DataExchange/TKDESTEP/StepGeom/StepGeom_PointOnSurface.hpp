#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <StepGeom_Point.hpp>
class StepGeom_Surface;
class TCollection_HAsciiString;

class StepGeom_PointOnSurface : public StepGeom_Point
{

public:
  //! Returns a PointOnSurface
  Standard_EXPORT StepGeom_PointOnSurface();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepGeom_Surface>&         aBasisSurface,
                            const double                                 aPointParameterU,
                            const double                                 aPointParameterV);

  Standard_EXPORT void SetBasisSurface(const occ::handle<StepGeom_Surface>& aBasisSurface);

  Standard_EXPORT occ::handle<StepGeom_Surface> BasisSurface() const;

  Standard_EXPORT void SetPointParameterU(const double aPointParameterU);

  Standard_EXPORT double PointParameterU() const;

  Standard_EXPORT void SetPointParameterV(const double aPointParameterV);

  Standard_EXPORT double PointParameterV() const;

  DEFINE_STANDARD_RTTIEXT(StepGeom_PointOnSurface, StepGeom_Point)

private:
  occ::handle<StepGeom_Surface> basisSurface;
  double                        pointParameterU;
  double                        pointParameterV;
};

