set(OCCT_GeomGridEval_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_GeomGridEval_FILES
  # Common result structures
  GeomGridEval.hpp
  # Curve evaluators
  GeomGridEval_Line.hpp
  GeomGridEval_Circle.hpp
  GeomGridEval_Circle.cxx
  GeomGridEval_Ellipse.hpp
  GeomGridEval_Ellipse.cxx
  GeomGridEval_Hyperbola.hpp
  GeomGridEval_Hyperbola.cxx
  GeomGridEval_Parabola.hpp
  GeomGridEval_Parabola.cxx
  GeomGridEval_BezierCurve.hpp
  GeomGridEval_BezierCurve.cxx
  GeomGridEval_BSplineCurve.hpp
  GeomGridEval_BSplineCurve.cxx
  GeomGridEval_OtherCurve.hpp
  GeomGridEval_OtherCurve.cxx
  GeomGridEval_OffsetCurve.hpp
  GeomGridEval_OffsetCurve.cxx
  GeomGridEval_Curve.hpp
  GeomGridEval_Curve.cxx
  # Surface evaluators
  GeomGridEval_Plane.hpp
  GeomGridEval_Cylinder.hpp
  GeomGridEval_Cylinder.cxx
  GeomGridEval_Sphere.hpp
  GeomGridEval_Sphere.cxx
  GeomGridEval_Cone.hpp
  GeomGridEval_Cone.cxx
  GeomGridEval_Torus.hpp
  GeomGridEval_Torus.cxx
  GeomGridEval_BezierSurface.hpp
  GeomGridEval_BezierSurface.cxx
  GeomGridEval_OffsetSurface.hpp
  GeomGridEval_OffsetSurface.cxx
  GeomGridEval_BSplineSurface.hpp
  GeomGridEval_BSplineSurface.cxx
  GeomGridEval_OtherSurface.hpp
  GeomGridEval_OtherSurface.cxx
  GeomGridEval_SurfaceOfRevolution.hpp
  GeomGridEval_SurfaceOfRevolution.cxx
  GeomGridEval_SurfaceOfExtrusion.hpp
  GeomGridEval_SurfaceOfExtrusion.cxx
  GeomGridEval_Surface.hpp
  GeomGridEval_Surface.cxx
)
