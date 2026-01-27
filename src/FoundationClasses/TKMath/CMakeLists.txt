project(TKMath)

# Eigen library include path
# Note: The eigen variable can be set externally, or defaults to the repository path
if(NOT DEFINED eigen)
  set(eigen "${CMAKE_CURRENT_SOURCE_DIR}/../../../../eigen")
endif()

include_directories(${eigen})

OCCT_INCLUDE_CMAKE_FILE (adm/cmake/occt_toolkit)

# Add the precompiled header
ADD_PRECOMPILED_HEADER(TKMath "TKMath_pch.hxx" FALSE)
