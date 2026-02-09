#pragma once

#include <Graphic3d_RenderTransparentMethod.hpp>
#include <Graphic3d_ShaderAttribute.hpp>
#include <Graphic3d_ShaderObject.hpp>
#include <Graphic3d_ShaderVariable.hpp>
#include <Graphic3d_TextureParams.hpp>
#include <NCollection_Sequence.hpp>

class Graphic3d_ShaderProgram : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ShaderProgram, Standard_Transient)
public:
  static const int THE_MAX_LIGHTS_DEFAULT = 8;

  static const int THE_MAX_CLIP_PLANES_DEFAULT = 8;

  static const int THE_NB_FRAG_OUTPUTS = 1;

public:
  Standard_EXPORT Graphic3d_ShaderProgram();

  Standard_EXPORT ~Graphic3d_ShaderProgram() override;

  Standard_EXPORT virtual bool IsDone() const;

  const TCollection_AsciiString& GetId() const { return myID; }

  void SetId(const TCollection_AsciiString& theId) { myID = theId; }

  const TCollection_AsciiString& Header() const { return myHeader; }

  void SetHeader(const TCollection_AsciiString& theHeader) { myHeader = theHeader; }

  void AppendToHeader(const TCollection_AsciiString& theHeaderLine)
  {
    if (!myHeader.IsEmpty())
    {
      myHeader += "\n";
    }
    myHeader += theHeaderLine;
  }

  int NbLightsMax() const { return myNbLightsMax; }

  void SetNbLightsMax(int theNbLights) { myNbLightsMax = theNbLights; }

  int NbShadowMaps() const { return myNbShadowMaps; }

  void SetNbShadowMaps(int theNbMaps) { myNbShadowMaps = theNbMaps; }

  int NbClipPlanesMax() const { return myNbClipPlanesMax; }

  void SetNbClipPlanesMax(int theNbPlanes) { myNbClipPlanesMax = theNbPlanes; }

  Standard_EXPORT bool AttachShader(const occ::handle<Graphic3d_ShaderObject>& theShader);

  Standard_EXPORT bool DetachShader(const occ::handle<Graphic3d_ShaderObject>& theShader);

  const NCollection_Sequence<occ::handle<Graphic3d_ShaderObject>>& ShaderObjects() const
  {
    return myShaderObjects;
  }

  const NCollection_Sequence<occ::handle<Graphic3d_ShaderVariable>>& Variables() const
  {
    return myVariables;
  }

  const NCollection_Sequence<occ::handle<Graphic3d_ShaderAttribute>>& VertexAttributes() const
  {
    return myAttributes;
  }

  Standard_EXPORT void SetVertexAttributes(
    const NCollection_Sequence<occ::handle<Graphic3d_ShaderAttribute>>& theAttributes);

  int NbFragmentOutputs() const { return myNbFragOutputs; }

  void SetNbFragmentOutputs(const int theNbOutputs) { myNbFragOutputs = theNbOutputs; }

  bool HasAlphaTest() const { return myHasAlphaTest; }

  void SetAlphaTest(bool theAlphaTest) { myHasAlphaTest = theAlphaTest; }

  bool HasDefaultSampler() const { return myHasDefSampler; }

  void SetDefaultSampler(bool theHasDefSampler) { myHasDefSampler = theHasDefSampler; }

  Graphic3d_RenderTransparentMethod OitOutput() const { return myOitOutput; }

  void SetOitOutput(Graphic3d_RenderTransparentMethod theOutput) { myOitOutput = theOutput; }

  bool IsPBR() const { return myIsPBR; }

  void SetPBR(bool theIsPBR) { myIsPBR = theIsPBR; }

  int TextureSetBits() const { return myTextureSetBits; }

  void SetTextureSetBits(int theBits) { myTextureSetBits = theBits; }

  template <class T>
  bool PushVariable(const TCollection_AsciiString& theName, const T& theValue);

  Standard_EXPORT void ClearVariables();

  bool PushVariableFloat(const TCollection_AsciiString& theName, const float theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableVec2(const TCollection_AsciiString& theName,
                        const NCollection_Vec2<float>& theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableVec3(const TCollection_AsciiString& theName,
                        const NCollection_Vec3<float>& theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableVec4(const TCollection_AsciiString& theName,
                        const NCollection_Vec4<float>& theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableInt(const TCollection_AsciiString& theName, const int theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableVec2i(const TCollection_AsciiString& theName,
                         const NCollection_Vec2<int>&   theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableVec3i(const TCollection_AsciiString& theName,
                         const NCollection_Vec3<int>&   theValue)
  {
    return PushVariable(theName, theValue);
  }

  bool PushVariableVec4i(const TCollection_AsciiString& theName,
                         const NCollection_Vec4<int>&   theValue)
  {
    return PushVariable(theName, theValue);
  }

public:
  Standard_EXPORT static const TCollection_AsciiString& ShadersFolder();

private:
  TCollection_AsciiString                                      myID;
  NCollection_Sequence<occ::handle<Graphic3d_ShaderObject>>    myShaderObjects;
  NCollection_Sequence<occ::handle<Graphic3d_ShaderVariable>>  myVariables;
  NCollection_Sequence<occ::handle<Graphic3d_ShaderAttribute>> myAttributes;

  TCollection_AsciiString           myHeader;
  int                               myNbLightsMax;
  int                               myNbShadowMaps;
  int                               myNbClipPlanesMax;
  int                               myNbFragOutputs;
  int                               myTextureSetBits;
  Graphic3d_RenderTransparentMethod myOitOutput;
  bool                              myHasDefSampler;
  bool                              myHasAlphaTest;
  bool                              myIsPBR;
};

template <class T>
inline bool Graphic3d_ShaderProgram::PushVariable(const TCollection_AsciiString& theName,
                                                  const T&                       theValue)
{
  occ::handle<Graphic3d_ShaderVariable> aVariable =
    Graphic3d_ShaderVariable::Create(theName, theValue);
  if (aVariable.IsNull() || !aVariable->IsDone())
  {
    return false;
  }

  myVariables.Append(aVariable);
  return true;
}
