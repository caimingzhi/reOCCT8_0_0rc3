# Source files for AppParCurves package
set(OCCT_AppParCurves_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_AppParCurves_FILES
  AppParCurves.cxx
  AppParCurves.hpp

  AppParCurves_BSpFunction.hpp
  AppParCurves_BSpGradient.hpp
  AppParCurves_Constraint.hpp
  AppParCurves_ConstraintCouple.cxx
  AppParCurves_ConstraintCouple.hpp
  AppParCurves_Function.hpp
  AppParCurves_Gradient.hpp

  AppParCurves_LeastSquare.hpp
  AppParCurves_MultiBSpCurve.cxx
  AppParCurves_MultiBSpCurve.hpp
  AppParCurves_MultiCurve.cxx
  AppParCurves_MultiCurve.hpp
  AppParCurves_MultiPoint.cxx
  AppParCurves_MultiPoint.hpp
  AppParCurves_ResolConstraint.hpp

)
