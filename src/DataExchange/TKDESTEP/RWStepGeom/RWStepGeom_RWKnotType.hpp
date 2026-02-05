#pragma once

#include <StepGeom_KnotType.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWKnotType
{

  static constexpr char ktUniformKnots[]         = (".UNIFORM_KNOTS.");
  static constexpr char ktQuasiUniformKnots[]    = (".QUASI_UNIFORM_KNOTS.");
  static constexpr char ktPiecewiseBezierKnots[] = (".PIECEWISE_BEZIER_KNOTS.");
  static constexpr char ktUnspecified[]          = (".UNSPECIFIED.");

  //! Convert StepGeom_KnotType to string
  //! @param theSourceEnum The StepGeom_KnotType value to convert
  //! @return The corresponding string representation or nullptr if not found
  inline const char* ConvertToString(const StepGeom_KnotType theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepGeom_ktUniformKnots:
        return ktUniformKnots;
      case StepGeom_ktQuasiUniformKnots:
        return ktQuasiUniformKnots;
      case StepGeom_ktPiecewiseBezierKnots:
        return ktPiecewiseBezierKnots;
      case StepGeom_ktUnspecified:
        return ktUnspecified;
    }
    return nullptr;
  }

  //! Convert string to StepGeom_KnotType
  //! @param theKnotTypeString The string to convert
  //! @param theResultEnum The corresponding StepGeom_KnotType value
  //! @return true if the conversion was successful, false otherwise
  inline bool ConvertToEnum(const char* theKnotTypeString, StepGeom_KnotType& theResultEnum)
  {
    if (IsEqual(theKnotTypeString, ktUniformKnots))
    {
      theResultEnum = StepGeom_ktUniformKnots;
    }
    else if (IsEqual(theKnotTypeString, ktQuasiUniformKnots))
    {
      theResultEnum = StepGeom_ktQuasiUniformKnots;
    }
    else if (IsEqual(theKnotTypeString, ktPiecewiseBezierKnots))
    {
      theResultEnum = StepGeom_ktPiecewiseBezierKnots;
    }
    else if (IsEqual(theKnotTypeString, ktUnspecified))
    {
      theResultEnum = StepGeom_ktUnspecified;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepGeom_RWKnotType
