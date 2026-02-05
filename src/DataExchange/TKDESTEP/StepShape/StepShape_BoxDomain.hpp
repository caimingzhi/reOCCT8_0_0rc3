#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepGeom_CartesianPoint;

class StepShape_BoxDomain : public Standard_Transient
{

public:
  //! Returns a BoxDomain
  Standard_EXPORT StepShape_BoxDomain();

  Standard_EXPORT void Init(const occ::handle<StepGeom_CartesianPoint>& aCorner,
                            const double                                aXlength,
                            const double                                aYlength,
                            const double                                aZlength);

  Standard_EXPORT void SetCorner(const occ::handle<StepGeom_CartesianPoint>& aCorner);

  Standard_EXPORT occ::handle<StepGeom_CartesianPoint> Corner() const;

  Standard_EXPORT void SetXlength(const double aXlength);

  Standard_EXPORT double Xlength() const;

  Standard_EXPORT void SetYlength(const double aYlength);

  Standard_EXPORT double Ylength() const;

  Standard_EXPORT void SetZlength(const double aZlength);

  Standard_EXPORT double Zlength() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_BoxDomain, Standard_Transient)

private:
  occ::handle<StepGeom_CartesianPoint> corner;
  double                               xlength;
  double                               ylength;
  double                               zlength;
};
