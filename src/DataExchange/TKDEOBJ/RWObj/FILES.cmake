# Source files for RWObj package
set(OCCT_RWObj_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_RWObj_FILES
  RWObj.cxx
  RWObj.hpp
  RWObj_CafReader.cxx
  RWObj_CafReader.hpp
  RWObj_CafWriter.cxx
  RWObj_CafWriter.hpp

  RWObj_Material.hpp
  RWObj_MtlReader.cxx
  RWObj_MtlReader.hpp
  RWObj_ObjMaterialMap.cxx
  RWObj_ObjMaterialMap.hpp
  RWObj_ObjWriterContext.cxx
  RWObj_ObjWriterContext.hpp

  RWObj_Reader.cxx
  RWObj_Reader.hpp
  RWObj_SubMesh.hpp
  RWObj_SubMeshReason.hpp
  RWObj_Tools.hpp
  RWObj_TriangulationReader.cxx
  RWObj_TriangulationReader.hpp
)
