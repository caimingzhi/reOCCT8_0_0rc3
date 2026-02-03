# Source files for BRepClass3d package
set(OCCT_BRepClass3d_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_BRepClass3d_FILES
  BRepClass3d.cxx
  BRepClass3d.hpp
  BRepClass3d_BndBoxTree.hpp
  BRepClass3d_BndBoxTree.cxx

  BRepClass3d_Intersector3d.cxx
  BRepClass3d_Intersector3d.hpp

  BRepClass3d_SClassifier.cxx
  BRepClass3d_SClassifier.hpp
  BRepClass3d_SolidClassifier.cxx
  BRepClass3d_SolidClassifier.hpp
  BRepClass3d_SolidExplorer.cxx
  BRepClass3d_SolidExplorer.hpp
  BRepClass3d_SolidPassiveClassifier.hpp
  BRepClass3d_SolidPassiveClassifier.cxx
)
