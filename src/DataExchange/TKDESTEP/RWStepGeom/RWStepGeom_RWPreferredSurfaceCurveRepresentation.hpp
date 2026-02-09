#pragma once

#include <StepGeom_PreferredSurfaceCurveRepresentation.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWPreferredSurfaceCurveRepresentation
{
  static constexpr char pscrPcurveS2[] = ".PCURVE_S2.";
  static constexpr char pscrPcurveS1[] = ".PCURVE_S1.";
  static constexpr char pscrCurve3d[]  = ".CURVE_3D.";

  inline const char* ConvertToString(
    const StepGeom_PreferredSurfaceCurveRepresentation theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepGeom_pscrPcurveS2:
        return pscrPcurveS2;
      case StepGeom_pscrPcurveS1:
        return pscrPcurveS1;
      case StepGeom_pscrCurve3d:
        return pscrCurve3d;
    }
    return nullptr;
  }

  inline bool ConvertToEnum(const char*                                   theRepresentationStr,
                            StepGeom_PreferredSurfaceCurveRepresentation& theResultEnum)
  {
    if (IsEqual(theRepresentationStr, pscrPcurveS2))
    {
      theResultEnum = StepGeom_pscrPcurveS2;
    }
    else if (IsEqual(theRepresentationStr, pscrPcurveS1))
    {
      theResultEnum = StepGeom_pscrPcurveS1;
    }
    else if (IsEqual(theRepresentationStr, pscrCurve3d))
    {
      theResultEnum = StepGeom_pscrCurve3d;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepGeom_RWPreferredSurfaceCurveRepresentation
