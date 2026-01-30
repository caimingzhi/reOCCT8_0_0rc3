# Source files for GeomHash package
set(OCCT_GeomHash_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_GeomHash_FILES
  # Foundational Hashers
  GeomHash_PointHasher.hpp
  GeomHash_DirectionHasher.hpp
  GeomHash_VectorHasher.hpp
  GeomHash_AxisPlacement.hpp

  # Surface Hashers
  GeomHash_PlaneHasher.hpp
  GeomHash_CylindricalSurfaceHasher.hpp
  GeomHash_ConicalSurfaceHasher.hpp
  GeomHash_SphericalSurfaceHasher.hpp
  GeomHash_ToroidalSurfaceHasher.hpp
  GeomHash_SurfaceOfRevolutionHasher.hpp
  GeomHash_SurfaceOfLinearExtrusionHasher.hpp
  GeomHash_BezierSurfaceHasher.hpp
  GeomHash_BSplineSurfaceHasher.hpp
  GeomHash_RectangularTrimmedSurfaceHasher.hpp
  GeomHash_OffsetSurfaceHasher.hpp
  GeomHash_SurfaceHasher.hpp
  GeomHash_SurfaceHasher.cxx

  # Curve Hashers
  GeomHash_LineHasher.hpp
  GeomHash_CircleHasher.hpp
  GeomHash_EllipseHasher.hpp
  GeomHash_HyperbolaHasher.hpp
  GeomHash_ParabolaHasher.hpp
  GeomHash_BezierCurveHasher.hpp
  GeomHash_BSplineCurveHasher.hpp
  GeomHash_TrimmedCurveHasher.hpp
  GeomHash_OffsetCurveHasher.hpp
  GeomHash_CurveHasher.hpp
  GeomHash_CurveHasher.cxx
)
