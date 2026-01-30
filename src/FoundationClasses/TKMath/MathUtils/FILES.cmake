# Source files for MathUtils package
set(OCCT_MathUtils_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_MathUtils_FILES
  # Types and configuration
  MathUtils_Types.hpp
  MathUtils_Config.hpp
  MathUtils_Domain.hpp
  # Core utilities
  MathUtils_Core.hpp
  MathUtils_Convergence.hpp
  MathUtils_Poly.hpp
  MathUtils_Bracket.hpp
  MathUtils_Gauss.hpp
  MathUtils_Deriv.hpp
  MathUtils_LineSearch.hpp
  MathUtils_GaussKronrodWeights.hpp
  MathUtils_GaussKronrodWeights.cxx
  # Functors
  MathUtils_FunctorScalar.hpp
  MathUtils_FunctorVector.hpp
  # Documentation
  README.md
)
