# Source files for RWGltf package
set(OCCT_RWGltf_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_RWGltf_FILES
  RWGltf_CafReader.cxx
  RWGltf_CafReader.hpp
  RWGltf_CafWriter.cxx
  RWGltf_CafWriter.hpp

  RWGltf_DracoParameters.hpp
  RWGltf_GltfAccessor.hpp
  RWGltf_GltfAccessorCompType.hpp
  RWGltf_GltfAccessorLayout.hpp
  RWGltf_GltfAlphaMode.hpp
  RWGltf_GltfArrayType.hpp
  RWGltf_GltfBufferView.hpp
  RWGltf_GltfBufferViewTarget.hpp
  RWGltf_GltfFace.hpp
  RWGltf_GltfJsonParser.cxx
  RWGltf_GltfJsonParser.hpp
  RWGltf_GltfLatePrimitiveArray.cxx
  RWGltf_GltfLatePrimitiveArray.hpp
  RWGltf_GltfMaterialMap.cxx
  RWGltf_GltfMaterialMap.hpp
  RWGltf_GltfOStreamWriter.hpp
  RWGltf_GltfPrimArrayData.hpp
  RWGltf_GltfPrimitiveMode.hpp
  RWGltf_GltfRootElement.hpp
  RWGltf_GltfSceneNodeMap.hpp
  RWGltf_MaterialCommon.hpp
  RWGltf_MaterialMetallicRoughness.hpp

  RWGltf_TriangulationReader.cxx
  RWGltf_TriangulationReader.hpp
  RWGltf_WriterTrsfFormat.hpp
)
