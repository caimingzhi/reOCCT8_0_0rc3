#pragma once

#include <Graphic3d_RenderTransparentMethod.hpp>
#include <Graphic3d_LightSet.hpp>
#include <OpenGl_Element.hpp>
#include <OpenGl_Vec.hpp>

class OpenGl_ShadowMapArray;

class OpenGl_StateInterface
{
public:
  Standard_EXPORT OpenGl_StateInterface();

  size_t Index() const { return myIndex; }

  void Update() { ++myIndex; }

protected:
  size_t myIndex;
};

class OpenGl_ProjectionState : public OpenGl_StateInterface
{
public:
  Standard_EXPORT OpenGl_ProjectionState();

  Standard_EXPORT void Set(const NCollection_Mat4<float>& theProjectionMatrix);

  const NCollection_Mat4<float>& ProjectionMatrix() const { return myProjectionMatrix; }

  Standard_EXPORT const NCollection_Mat4<float>& ProjectionMatrixInverse() const;

private:
  NCollection_Mat4<float>         myProjectionMatrix;
  mutable NCollection_Mat4<float> myProjectionMatrixInverse;
  mutable bool                    myInverseNeedUpdate;
};

class OpenGl_ModelWorldState : public OpenGl_StateInterface
{
public:
  Standard_EXPORT OpenGl_ModelWorldState();

  Standard_EXPORT void Set(const NCollection_Mat4<float>& theModelWorldMatrix);

  const NCollection_Mat4<float>& ModelWorldMatrix() const { return myModelWorldMatrix; }

  Standard_EXPORT const NCollection_Mat4<float>& ModelWorldMatrixInverse() const;

private:
  NCollection_Mat4<float>         myModelWorldMatrix;
  mutable NCollection_Mat4<float> myModelWorldMatrixInverse;
  mutable bool                    myInverseNeedUpdate;
};

class OpenGl_WorldViewState : public OpenGl_StateInterface
{
public:
  Standard_EXPORT OpenGl_WorldViewState();

  Standard_EXPORT void Set(const NCollection_Mat4<float>& theWorldViewMatrix);

  const NCollection_Mat4<float>& WorldViewMatrix() const { return myWorldViewMatrix; }

  Standard_EXPORT const NCollection_Mat4<float>& WorldViewMatrixInverse() const;

private:
  NCollection_Mat4<float>         myWorldViewMatrix;
  mutable NCollection_Mat4<float> myWorldViewMatrixInverse;
  mutable bool                    myInverseNeedUpdate;
};

class OpenGl_LightSourceState : public OpenGl_StateInterface
{
public:
  OpenGl_LightSourceState()
      : mySpecIBLMapLevels(0),
        myToCastShadows(true)
  {
  }

  void Set(const occ::handle<Graphic3d_LightSet>& theLightSources)
  {
    myLightSources = theLightSources;
  }

  const occ::handle<Graphic3d_LightSet>& LightSources() const { return myLightSources; }

  int SpecIBLMapLevels() const { return mySpecIBLMapLevels; }

  void SetSpecIBLMapLevels(int theSpecIBLMapLevels) { mySpecIBLMapLevels = theSpecIBLMapLevels; }

  bool HasShadowMaps() const { return myToCastShadows && !myShadowMaps.IsNull(); }

  const occ::handle<OpenGl_ShadowMapArray>& ShadowMaps() const { return myShadowMaps; }

  void SetShadowMaps(const occ::handle<OpenGl_ShadowMapArray>& theMap) { myShadowMaps = theMap; }

  bool ToCastShadows() const { return myToCastShadows; }

  void SetCastShadows(bool theToCast) { myToCastShadows = theToCast; }

private:
  occ::handle<Graphic3d_LightSet> myLightSources;

  int mySpecIBLMapLevels;

  occ::handle<OpenGl_ShadowMapArray> myShadowMaps;
  bool                               myToCastShadows;
};

class OpenGl_ClippingState
{
public:
  Standard_EXPORT OpenGl_ClippingState();

  size_t Index() const { return myIndex; }

  Standard_EXPORT void Update();

  Standard_EXPORT void Revert();

protected:
  size_t                   myIndex;
  size_t                   myNextIndex;
  NCollection_List<size_t> myStateStack;
};

class OpenGl_OitState : public OpenGl_StateInterface
{
public:
  OpenGl_OitState()
      : myOitMode(Graphic3d_RTM_BLEND_UNORDERED),
        myDepthFactor(0.5f)
  {
  }

  void Set(Graphic3d_RenderTransparentMethod theMode, const float theDepthFactor)
  {
    myOitMode     = theMode;
    myDepthFactor = static_cast<float>((std::max)(0.f, (std::min)(1.f, theDepthFactor)));
  }

  Graphic3d_RenderTransparentMethod ActiveMode() const { return myOitMode; }

  float DepthFactor() const { return myDepthFactor; }

private:
  Graphic3d_RenderTransparentMethod myOitMode;

  float myDepthFactor;
};
