# Source files for Shaders package
set(OCCT_Shaders_FILES_LOCATION "${CMAKE_CURRENT_LIST_DIR}")

set(OCCT_Shaders_FILES
  Shaders_Declarations_glsl.hpp
  Shaders_DeclarationsImpl_glsl.hpp
  Shaders_LightShadow_glsl.hpp
  Shaders_Display_fs.hpp
  Shaders_PBRCookTorrance_glsl.hpp
  Shaders_PBRDirectionalLight_glsl.hpp
  Shaders_PBRDistribution_glsl.hpp
  Shaders_PBREnvBaking_fs.hpp
  Shaders_PBREnvBaking_vs.hpp
  Shaders_PBRFresnel_glsl.hpp
  Shaders_PBRGeometry_glsl.hpp
  Shaders_PBRIllumination_glsl.hpp
  Shaders_PBRPointLight_glsl.hpp
  Shaders_PBRSpotLight_glsl.hpp
  Shaders_PhongDirectionalLight_glsl.hpp
  Shaders_PhongPointLight_glsl.hpp
  Shaders_PhongSpotLight_glsl.hpp
  Shaders_PointLightAttenuation_glsl.hpp
  Shaders_RaytraceBase_fs.hpp
  Shaders_RaytraceRender_fs.hpp
  Shaders_PathtraceBase_fs.hpp
  Shaders_RaytraceBase_vs.hpp
  Shaders_RaytraceSmooth_fs.hpp
  Shaders_TangentSpaceNormal_glsl.hpp
  Shaders_SkydomBackground_fs.hpp
)
