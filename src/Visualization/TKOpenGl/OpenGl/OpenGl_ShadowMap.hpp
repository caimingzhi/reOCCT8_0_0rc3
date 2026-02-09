#pragma once

#include <NCollection_Mat4.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Array1.hpp>
#include <OpenGl_NamedResource.hpp>

class gp_XYZ;
class Graphic3d_Camera;
class Graphic3d_CLight;
class Graphic3d_CView;
class OpenGl_FrameBuffer;
class OpenGl_Texture;

class OpenGl_ShadowMap : public OpenGl_NamedResource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_ShadowMap, OpenGl_NamedResource)
public:
  OpenGl_ShadowMap();

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  Standard_EXPORT size_t EstimatedDataSize() const override;

  Standard_EXPORT ~OpenGl_ShadowMap() override;

  Standard_EXPORT bool IsValid() const;

  const occ::handle<OpenGl_FrameBuffer>& FrameBuffer() const { return myShadowMapFbo; }

  Standard_EXPORT const occ::handle<OpenGl_Texture>& Texture() const;

  const occ::handle<Graphic3d_CLight>& LightSource() const { return myShadowLight; }

  void SetLightSource(const occ::handle<Graphic3d_CLight>& theLight) { myShadowLight = theLight; }

  const occ::handle<Graphic3d_Camera>& Camera() const { return myShadowCamera; }

  const NCollection_Mat4<float>& LightSourceMatrix() const { return myLightMatrix; }

  void SetLightSourceMatrix(const NCollection_Mat4<float>& theMat) { myLightMatrix = theMat; }

  float ShadowMapBias() const { return myShadowMapBias; }

  void SetShadowMapBias(float theBias) { myShadowMapBias = theBias; }

  Standard_EXPORT bool UpdateCamera(const Graphic3d_CView& theView,
                                    const gp_XYZ*          theOrigin = nullptr);

private:
  occ::handle<OpenGl_FrameBuffer> myShadowMapFbo;
  occ::handle<Graphic3d_CLight>   myShadowLight;
  occ::handle<Graphic3d_Camera>   myShadowCamera;
  NCollection_Mat4<float>         myLightMatrix;
  float                           myShadowMapBias;
};

class OpenGl_ShadowMapArray : public Standard_Transient,
                              public NCollection_Array1<occ::handle<OpenGl_ShadowMap>>
{
public:
  OpenGl_ShadowMapArray() = default;

  Standard_EXPORT void Release(OpenGl_Context* theCtx);

  bool IsValid() const { return !IsEmpty() && First()->IsValid(); }

  Standard_EXPORT size_t EstimatedDataSize() const;

public:
  DEFINE_STANDARD_ALLOC
  DEFINE_NCOLLECTION_ALLOC
};
