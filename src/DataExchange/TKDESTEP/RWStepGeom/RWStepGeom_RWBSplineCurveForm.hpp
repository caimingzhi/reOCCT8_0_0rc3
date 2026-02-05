#pragma once

#include <StepGeom_BSplineCurveForm.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWBSplineCurveForm
{
  static constexpr char bscfEllipticArc[]   = ".ELLIPTIC_ARC.";
  static constexpr char bscfPolylineForm[]  = ".POLYLINE_FORM.";
  static constexpr char bscfParabolicArc[]  = ".PARABOLIC_ARC.";
  static constexpr char bscfCircularArc[]   = ".CIRCULAR_ARC.";
  static constexpr char bscfUnspecified[]   = ".UNSPECIFIED.";
  static constexpr char bscfHyperbolicArc[] = ".HYPERBOLIC_ARC.";

  //! Convert StepGeom_BSplineCurveForm to string
  //! @param theSourceEnum The StepGeom_BSplineCurveForm value to convert
  //! @return The corresponding string representation or nullptr if not found
  inline const char* ConvertToString(const StepGeom_BSplineCurveForm theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepGeom_bscfEllipticArc:
        return bscfEllipticArc;
      case StepGeom_bscfPolylineForm:
        return bscfPolylineForm;
      case StepGeom_bscfParabolicArc:
        return bscfParabolicArc;
      case StepGeom_bscfCircularArc:
        return bscfCircularArc;
      case StepGeom_bscfUnspecified:
        return bscfUnspecified;
      case StepGeom_bscfHyperbolicArc:
        return bscfHyperbolicArc;
    }
    return nullptr;
  }

  //! Convert string to StepGeom_BSplineCurveForm
  //! @param theFormString The string to convert
  //! @param theResultEnum The corresponding StepGeom_BSplineCurveForm value
  //! @return true if the conversion was successful, false otherwise
  inline bool ConvertToEnum(const char* theFormString, StepGeom_BSplineCurveForm& theResultEnum)
  {
    if (IsEqual(theFormString, bscfEllipticArc))
    {
      theResultEnum = StepGeom_bscfEllipticArc;
    }
    else if (IsEqual(theFormString, bscfPolylineForm))
    {
      theResultEnum = StepGeom_bscfPolylineForm;
    }
    else if (IsEqual(theFormString, bscfParabolicArc))
    {
      theResultEnum = StepGeom_bscfParabolicArc;
    }
    else if (IsEqual(theFormString, bscfCircularArc))
    {
      theResultEnum = StepGeom_bscfCircularArc;
    }
    else if (IsEqual(theFormString, bscfUnspecified))
    {
      theResultEnum = StepGeom_bscfUnspecified;
    }
    else if (IsEqual(theFormString, bscfHyperbolicArc))
    {
      theResultEnum = StepGeom_bscfHyperbolicArc;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepGeom_RWBSplineCurveForm
