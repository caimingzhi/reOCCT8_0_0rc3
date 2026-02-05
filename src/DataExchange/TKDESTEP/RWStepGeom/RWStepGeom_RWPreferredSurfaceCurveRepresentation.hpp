#pragma once

#include <StepGeom_PreferredSurfaceCurveRepresentation.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWPreferredSurfaceCurveRepresentation
{
  static constexpr char pscrPcurveS2[] = ".PCURVE_S2.";
  static constexpr char pscrPcurveS1[] = ".PCURVE_S1.";
  static constexpr char pscrCurve3d[]  = ".CURVE_3D.";

  //! Convert StepGeom_PreferredSurfaceCurveRepresentation to string
  //! @param theSourceEnum The StepGeom_PreferredSurfaceCurveRepresentation value to convert
  //! @return The corresponding string representation or nullptr if not found
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

  //! Convert string to StepGeom_PreferredSurfaceCurveRepresentation
  //! @param theRepresentationStr The string to convert
  //! @param theResultEnum The corresponding StepGeom_PreferredSurfaceCurveRepresentation value
  //! @return true if the conversion was successful, false otherwise
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
