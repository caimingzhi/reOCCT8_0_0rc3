#pragma once

#include <NCollection_DataMap.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_AsciiString.hpp>

#include <Graphic3d_ShaderProgram.hpp>
#include <Graphic3d_TextureSetBits.hpp>

#include <OpenGl_Vec.hpp>
#include <OpenGl_NamedResource.hpp>
#include <OpenGl_ShaderObject.hpp>

enum OpenGl_StateVariable
{

  OpenGl_OCC_MODEL_WORLD_MATRIX,
  OpenGl_OCC_WORLD_VIEW_MATRIX,
  OpenGl_OCC_PROJECTION_MATRIX,
  OpenGl_OCC_MODEL_WORLD_MATRIX_INVERSE,
  OpenGl_OCC_WORLD_VIEW_MATRIX_INVERSE,
  OpenGl_OCC_PROJECTION_MATRIX_INVERSE,
  OpenGl_OCC_MODEL_WORLD_MATRIX_TRANSPOSE,
  OpenGl_OCC_WORLD_VIEW_MATRIX_TRANSPOSE,
  OpenGl_OCC_PROJECTION_MATRIX_TRANSPOSE,
  OpenGl_OCC_MODEL_WORLD_MATRIX_INVERSE_TRANSPOSE,
  OpenGl_OCC_WORLD_VIEW_MATRIX_INVERSE_TRANSPOSE,
  OpenGl_OCC_PROJECTION_MATRIX_INVERSE_TRANSPOSE,

  OpenGl_OCC_CLIP_PLANE_EQUATIONS,
  OpenGl_OCC_CLIP_PLANE_CHAINS,
  OpenGl_OCC_CLIP_PLANE_COUNT,

  OpenGl_OCC_LIGHT_SOURCE_COUNT,
  OpenGl_OCC_LIGHT_SOURCE_TYPES,
  OpenGl_OCC_LIGHT_SOURCE_PARAMS,
  OpenGl_OCC_LIGHT_AMBIENT,
  OpenGl_OCC_LIGHT_SHADOWMAP_SIZE_BIAS,
  OpenGl_OCC_LIGHT_SHADOWMAP_SAMPLERS,
  OpenGl_OCC_LIGHT_SHADOWMAP_MATRICES,

  OpenGl_OCCT_TEXTURE_ENABLE,
  OpenGl_OCCT_DISTINGUISH_MODE,
  OpenGl_OCCT_PBR_MATERIAL,
  OpenGl_OCCT_COMMON_MATERIAL,
  OpenGl_OCCT_ALPHA_CUTOFF,
  OpenGl_OCCT_COLOR,

  OpenGl_OCCT_OIT_OUTPUT,
  OpenGl_OCCT_OIT_DEPTH_FACTOR,

  OpenGl_OCCT_TEXTURE_TRSF2D,
  OpenGl_OCCT_POINT_SIZE,

  OpenGl_OCCT_VIEWPORT,
  OpenGl_OCCT_LINE_WIDTH,
  OpenGl_OCCT_LINE_FEATHER,
  OpenGl_OCCT_LINE_STIPPLE_PATTERN,
  OpenGl_OCCT_LINE_STIPPLE_FACTOR,
  OpenGl_OCCT_WIREFRAME_COLOR,
  OpenGl_OCCT_QUAD_MODE_STATE,

  OpenGl_OCCT_ORTHO_SCALE,
  OpenGl_OCCT_SILHOUETTE_THICKNESS,

  OpenGl_OCCT_NB_SPEC_IBL_LEVELS,

  OpenGl_OCCT_NUMBER_OF_STATE_VARIABLES
};

struct OpenGl_SetterInterface
{

  virtual void Set(const occ::handle<OpenGl_Context>&           theCtx,
                   const occ::handle<Graphic3d_ShaderVariable>& theVariable,
                   OpenGl_ShaderProgram*                        theProgram) = 0;

  virtual ~OpenGl_SetterInterface() = default;
};

class OpenGl_VariableSetterSelector
{
public:
  OpenGl_VariableSetterSelector();

  ~OpenGl_VariableSetterSelector();

  void Set(const occ::handle<OpenGl_Context>&           theCtx,
           const occ::handle<Graphic3d_ShaderVariable>& theVariable,
           OpenGl_ShaderProgram*                        theProgram) const;

private:
  NCollection_DataMap<size_t, OpenGl_SetterInterface*> mySetterList;
};

enum OpenGl_UniformStateType
{
  OpenGl_LIGHT_SOURCES_STATE,
  OpenGl_CLIP_PLANES_STATE,
  OpenGl_MODEL_WORLD_STATE,
  OpenGl_WORLD_VIEW_STATE,
  OpenGl_PROJECTION_STATE,
  OpenGl_MATERIAL_STATE,
  OpenGl_SURF_DETAIL_STATE,
  OpenGL_OIT_STATE,
  OpenGl_UniformStateType_NB
};

class OpenGl_ShaderUniformLocation
{
public:
  static const GLint INVALID_LOCATION = -1;

public:
  OpenGl_ShaderUniformLocation()
      : myLocation(INVALID_LOCATION)
  {
  }

  explicit OpenGl_ShaderUniformLocation(GLint theLocation)
      : myLocation(theLocation)
  {
  }

  bool IsValid() const { return myLocation != INVALID_LOCATION; }

  operator bool() const { return myLocation != INVALID_LOCATION; }

  operator GLint() const { return myLocation; }

private:
  GLint myLocation;
};

class OpenGl_ShaderProgram : public OpenGl_NamedResource
{
  friend class OpenGl_View;
  friend class OpenGl_ShaderManager;
  DEFINE_STANDARD_RTTIEXT(OpenGl_ShaderProgram, OpenGl_NamedResource)
public:
  static const GLuint NO_PROGRAM = 0;

  static const GLint INVALID_LOCATION = -1;

  static const char* PredefinedKeywords[OpenGl_OCCT_NUMBER_OF_STATE_VARIABLES];

  Standard_EXPORT static bool compileShaderVerbose(
    const occ::handle<OpenGl_Context>&      theCtx,
    const occ::handle<OpenGl_ShaderObject>& theShader,
    const TCollection_AsciiString&          theSource,
    bool                                    theToPrintSource = true);

  Standard_EXPORT OpenGl_ShaderProgram(
    const occ::handle<Graphic3d_ShaderProgram>& theProxy = nullptr,
    const TCollection_AsciiString&              theId    = "");

protected:
  static OpenGl_VariableSetterSelector mySetterSelector;

public:
  Standard_EXPORT ~OpenGl_ShaderProgram() override;

  Standard_EXPORT bool Create(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  size_t EstimatedDataSize() const override { return 0; }

  Standard_EXPORT bool AttachShader(const occ::handle<OpenGl_Context>&      theCtx,
                                    const occ::handle<OpenGl_ShaderObject>& theShader);

  Standard_EXPORT bool DetachShader(const occ::handle<OpenGl_Context>&      theCtx,
                                    const occ::handle<OpenGl_ShaderObject>& theShader);

  Standard_EXPORT bool Initialize(
    const occ::handle<OpenGl_Context>&                               theCtx,
    const NCollection_Sequence<occ::handle<Graphic3d_ShaderObject>>& theShaders);

  Standard_EXPORT bool Link(const occ::handle<OpenGl_Context>& theCtx, bool theIsVerbose = true);

  Standard_EXPORT bool FetchInfoLog(const occ::handle<OpenGl_Context>& theCtx,
                                    TCollection_AsciiString&           theLog);

  Standard_EXPORT bool ApplyVariables(const occ::handle<OpenGl_Context>& theCtx);

  const occ::handle<Graphic3d_ShaderProgram>& Proxy() const { return myProxy; }

  inline bool IsValid() const { return myProgramID != NO_PROGRAM; }

  inline GLuint ProgramId() const { return myProgramID; }

public:
  bool HasTessellationStage() const { return myHasTessShader; }

  int NbLightsMax() const { return myNbLightsMax; }

  int NbShadowMaps() const { return myNbShadowMaps; }

  int NbClipPlanesMax() const { return myNbClipPlanesMax; }

  int NbFragmentOutputs() const { return myNbFragOutputs; }

  bool HasAlphaTest() const { return myHasAlphaTest; }

  Graphic3d_RenderTransparentMethod OitOutput() const { return myOitOutput; }

  int TextureSetBits() const { return myTextureSetBits; }

private:
  size_t ActiveState(const OpenGl_UniformStateType theType) const
  {
    return theType < OpenGl_UniformStateType_NB ? myCurrentState[theType] : 0;
  }

  void UpdateState(const OpenGl_UniformStateType theType, const size_t theIndex)
  {
    if (theType < OpenGl_UniformStateType_NB)
    {
      myCurrentState[theType] = theIndex;
    }
  }

public:
  Standard_EXPORT OpenGl_ShaderUniformLocation
    GetUniformLocation(const occ::handle<OpenGl_Context>& theCtx, const GLchar* theName) const;

  Standard_EXPORT GLint GetAttributeLocation(const occ::handle<OpenGl_Context>& theCtx,
                                             const GLchar*                      theName) const;

  const OpenGl_ShaderUniformLocation& GetStateLocation(OpenGl_StateVariable theVariable) const
  {
    return myStateLocations[theVariable];
  }

public:
  template <typename ValueType>
  bool GetUniform(const occ::handle<OpenGl_Context>& theCtx,
                  const GLchar*                      theName,
                  ValueType&                         theValue) const
  {
    return GetUniform(theCtx, GetUniformLocation(theCtx, theName), theValue);
  }

  Standard_EXPORT bool GetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  NCollection_Vec4<int>&             theValue) const;

  Standard_EXPORT bool GetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  NCollection_Vec4<float>&           theValue) const;

public:
  template <typename ValueType>
  bool GetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                    const GLchar*                      theName,
                    ValueType&                         theValue) const
  {
    return GetAttribute(theCtx, GetAttributeLocation(theCtx, theName), theValue);
  }

  Standard_EXPORT bool GetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                    GLint                              theIndex,
                                    NCollection_Vec4<int>&             theValue) const;

  Standard_EXPORT bool GetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                    GLint                              theIndex,
                                    NCollection_Vec4<float>&           theValue) const;

public:
  Standard_EXPORT bool SetAttributeName(const occ::handle<OpenGl_Context>& theCtx,
                                        GLint                              theIndex,
                                        const GLchar*                      theName);

  template <typename ValueType>
  bool SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                    const GLchar*                      theName,
                    const ValueType&                   theValue)
  {
    return SetAttribute(theCtx, GetAttributeLocation(theCtx, theName), theValue);
  }

  Standard_EXPORT bool SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                    GLint                              theIndex,
                                    GLfloat                            theValue);

  Standard_EXPORT bool SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                    GLint                              theIndex,
                                    const NCollection_Vec2<float>&     theValue);

  Standard_EXPORT bool SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                    GLint                              theIndex,
                                    const NCollection_Vec3<float>&     theValue);

  Standard_EXPORT bool SetAttribute(const occ::handle<OpenGl_Context>& theCtx,
                                    GLint                              theIndex,
                                    const NCollection_Vec4<float>&     theValue);

public:
  template <typename ValueType>
  bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                  const GLchar*                      theName,
                  const ValueType&                   theValue)
  {
    return SetUniform(theCtx, GetUniformLocation(theCtx, theName), theValue);
  }

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLint                              theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Vec2<int>&       theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Vec3<int>&       theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Vec4<int>&       theValue);

public:
  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>&    theCtx,
                                  GLint                                 theLocation,
                                  const NCollection_Vec2<unsigned int>& theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>&    theCtx,
                                  const GLchar*                         theName,
                                  const GLsizei                         theCount,
                                  const NCollection_Vec2<unsigned int>* theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>&    theCtx,
                                  GLint                                 theLocation,
                                  const GLsizei                         theCount,
                                  const NCollection_Vec2<unsigned int>* theValue);

public:
  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLfloat                            theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Vec2<float>&     theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Vec3<float>&     theValue);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Vec4<float>&     theValue);

public:
  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Mat3<float>*     theData);

  bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                  const GLchar*                      theName,
                  const NCollection_Mat4<float>&     theValue,
                  GLboolean                          theTranspose = GL_FALSE)
  {
    return SetUniform(theCtx, GetUniformLocation(theCtx, theName), theValue, theTranspose);
  }

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const NCollection_Mat4<float>&     theValue,
                                  GLboolean                          theTranspose = GL_FALSE);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Mat4<float>*     theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const float*                       theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Vec2<float>*     theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Vec3<float>*     theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Vec4<float>*     theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const int*                         theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Vec2<int>*       theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Vec3<int>*       theData);

  Standard_EXPORT bool SetUniform(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  GLuint                             theCount,
                                  const NCollection_Vec4<int>*       theData);

public:
  bool SetSampler(const occ::handle<OpenGl_Context>& theCtx,
                  const GLchar*                      theName,
                  const Graphic3d_TextureUnit        theTextureUnit)
  {
    return SetSampler(theCtx, GetUniformLocation(theCtx, theName), theTextureUnit);
  }

  Standard_EXPORT bool SetSampler(const occ::handle<OpenGl_Context>& theCtx,
                                  GLint                              theLocation,
                                  const Graphic3d_TextureUnit        theTextureUnit);

public:
  Standard_EXPORT bool UpdateDebugDump(const occ::handle<OpenGl_Context>& theCtx,
                                       const TCollection_AsciiString&     theFolder     = "",
                                       bool                               theToBeautify = false,
                                       bool                               theToReset    = false);

protected:
  bool Share() { return ++myShareCount == 1; }

  bool UnShare() { return --myShareCount == 0; }

  Standard_EXPORT bool link(const occ::handle<OpenGl_Context>& theCtx);

protected:
  GLuint                                                 myProgramID;
  NCollection_Sequence<occ::handle<OpenGl_ShaderObject>> myShaderObjects;

  occ::handle<Graphic3d_ShaderProgram> myProxy;
  int                                  myShareCount;
  int                                  myNbLightsMax;
  int                                  myNbShadowMaps;
  int                                  myNbClipPlanesMax;
  int                                  myNbFragOutputs;
  int                                  myTextureSetBits;
  Graphic3d_RenderTransparentMethod    myOitOutput;
  bool                                 myHasAlphaTest;
  bool                                 myHasTessShader;

protected:
  size_t myCurrentState[OpenGl_UniformStateType_NB];

  OpenGl_ShaderUniformLocation myStateLocations[OpenGl_OCCT_NUMBER_OF_STATE_VARIABLES];
};

template <class T>
struct OpenGl_VariableSetter : public OpenGl_SetterInterface
{
  void Set(const occ::handle<OpenGl_Context>&           theCtx,
           const occ::handle<Graphic3d_ShaderVariable>& theVariable,
           OpenGl_ShaderProgram*                        theProgram) override
  {
    theProgram->SetUniform(theCtx, theVariable->Name().ToCString(), theVariable->Value()->As<T>());
  }
};

namespace OpenGl_HashMapInitializer
{
  template <class K, class V>
  struct MapListOfType
  {
    NCollection_DataMap<K, V> myDictionary;

    MapListOfType(K theKey, V theValue) { myDictionary.Bind(theKey, theValue); }

    MapListOfType& operator()(K theKey, V theValue)
    {
      myDictionary.Bind(theKey, theValue);
      return *this;
    }

    operator const NCollection_DataMap<K, V>&() const { return myDictionary; }
  };

  template <class K, class V>
  MapListOfType<K, V> CreateListOf(K theKey, V theValue)
  {
    return MapListOfType<K, V>(theKey, theValue);
  }
} // namespace OpenGl_HashMapInitializer
