# Source files for Geom2dHash package
set(OCCT_Geom2dHash_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_Geom2dHash_FILES
  # Foundational Hashers
  Geom2dHash_PointHasher.hpp
  Geom2dHash_DirectionHasher.hpp
  Geom2dHash_AxisPlacement.hpp

  # Curve Hashers
  Geom2dHash_LineHasher.hpp
  Geom2dHash_CircleHasher.hpp
  Geom2dHash_EllipseHasher.hpp
  Geom2dHash_HyperbolaHasher.hpp
  Geom2dHash_ParabolaHasher.hpp
  Geom2dHash_BezierCurveHasher.hpp
  Geom2dHash_BSplineCurveHasher.hpp
  Geom2dHash_TrimmedCurveHasher.hpp
  Geom2dHash_OffsetCurveHasher.hpp
  Geom2dHash_CurveHasher.hpp
  Geom2dHash_CurveHasher.cxx
)
