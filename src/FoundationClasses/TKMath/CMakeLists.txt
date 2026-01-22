project(TKMath)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../eigen)

OCCT_INCLUDE_CMAKE_FILE (adm/cmake/occt_toolkit)

# Add the precompiled header
ADD_PRECOMPILED_HEADER(TKMath "TKMath_pch.hxx" FALSE)
