#pragma once


#include <StepGeom_BSplineSurfaceForm.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWBSplineSurfaceForm
{
static constexpr char bssfSurfOfLinearExtrusion[] = (".SURF_OF_LINEAR_EXTRUSION.");
static constexpr char bssfPlaneSurf[]             = (".PLANE_SURF.");
static constexpr char bssfGeneralisedCone[]       = (".GENERALISED_CONE.");
static constexpr char bssfToroidalSurf[]          = (".TOROIDAL_SURF.");
static constexpr char bssfConicalSurf[]           = (".CONICAL_SURF.");
static constexpr char bssfSphericalSurf[]         = (".SPHERICAL_SURF.");
static constexpr char bssfUnspecified[]           = (".UNSPECIFIED.");
static constexpr char bssfRuledSurf[]             = (".RULED_SURF.");
static constexpr char bssfSurfOfRevolution[]      = (".SURF_OF_REVOLUTION.");
static constexpr char bssfCylindricalSurf[]       = (".CYLINDRICAL_SURF.");
static constexpr char bssfQuadricSurf[]           = (".QUADRIC_SURF.");

//! Convert StepGeom_BSplineSurfaceForm to string
//! @param theSourceEnum The StepGeom_BSplineSurfaceForm value to convert
//! @return The corresponding string representation or nullptr if not found
inline const char* ConvertToString(const StepGeom_BSplineSurfaceForm theSourceEnum)
{
  switch (theSourceEnum)
  {
    case StepGeom_bssfSurfOfLinearExtrusion:
      return bssfSurfOfLinearExtrusion;
    case StepGeom_bssfPlaneSurf:
      return bssfPlaneSurf;
    case StepGeom_bssfGeneralisedCone:
      return bssfGeneralisedCone;
    case StepGeom_bssfToroidalSurf:
      return bssfToroidalSurf;
    case StepGeom_bssfConicalSurf:
      return bssfConicalSurf;
    case StepGeom_bssfSphericalSurf:
      return bssfSphericalSurf;
    case StepGeom_bssfUnspecified:
      return bssfUnspecified;
    case StepGeom_bssfRuledSurf:
      return bssfRuledSurf;
    case StepGeom_bssfSurfOfRevolution:
      return bssfSurfOfRevolution;
    case StepGeom_bssfCylindricalSurf:
      return bssfCylindricalSurf;
    case StepGeom_bssfQuadricSurf:
      return bssfQuadricSurf;
  }
  return nullptr;
}

//! Convert string to StepGeom_BSplineSurfaceForm
//! @param theFormString The string to convert
//! @param theResultEnum The corresponding StepGeom_BSplineSurfaceForm value
//! @return true if the conversion was successful, false otherwise
inline bool ConvertToEnum(const char* theFormString, StepGeom_BSplineSurfaceForm& theResultEnum)
{
  if (IsEqual(theFormString, bssfSurfOfLinearExtrusion))
  {
    theResultEnum = StepGeom_bssfSurfOfLinearExtrusion;
  }
  else if (IsEqual(theFormString, bssfPlaneSurf))
  {
    theResultEnum = StepGeom_bssfPlaneSurf;
  }
  else if (IsEqual(theFormString, bssfGeneralisedCone))
  {
    theResultEnum = StepGeom_bssfGeneralisedCone;
  }
  else if (IsEqual(theFormString, bssfToroidalSurf))
  {
    theResultEnum = StepGeom_bssfToroidalSurf;
  }
  else if (IsEqual(theFormString, bssfConicalSurf))
  {
    theResultEnum = StepGeom_bssfConicalSurf;
  }
  else if (IsEqual(theFormString, bssfSphericalSurf))
  {
    theResultEnum = StepGeom_bssfSphericalSurf;
  }
  else if (IsEqual(theFormString, bssfUnspecified))
  {
    theResultEnum = StepGeom_bssfUnspecified;
  }
  else if (IsEqual(theFormString, bssfRuledSurf))
  {
    theResultEnum = StepGeom_bssfRuledSurf;
  }
  else if (IsEqual(theFormString, bssfSurfOfRevolution))
  {
    theResultEnum = StepGeom_bssfSurfOfRevolution;
  }
  else if (IsEqual(theFormString, bssfCylindricalSurf))
  {
    theResultEnum = StepGeom_bssfCylindricalSurf;
  }
  else if (IsEqual(theFormString, bssfQuadricSurf))
  {
    theResultEnum = StepGeom_bssfQuadricSurf;
  }
  else
  {
    return false;
  }
  return true;
}
} // namespace RWStepGeom_RWBSplineSurfaceForm

