#pragma once

#include <Graphic3d_TextureParams.hpp>
#include <OpenGl_Resource.hpp>

class OpenGl_Texture;

class OpenGl_Sampler : public OpenGl_Resource
{
  friend class OpenGl_Context;
  friend class OpenGl_Texture;
  friend class OpenGl_Text;
  DEFINE_STANDARD_RTTIEXT(OpenGl_Sampler, OpenGl_Resource)
public:
  static const unsigned int NO_SAMPLER = 0;

public:
  Standard_EXPORT OpenGl_Sampler(const occ::handle<Graphic3d_TextureParams>& theParams);

  Standard_EXPORT ~OpenGl_Sampler() override;

  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  size_t EstimatedDataSize() const override { return 0; }

  Standard_EXPORT bool Create(const occ::handle<OpenGl_Context>& theContext);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theContext,
                            const OpenGl_Texture&              theTexture);

  bool IsValid() const { return isValidSampler(); }

  void Bind(const occ::handle<OpenGl_Context>& theCtx) { Bind(theCtx, myParams->TextureUnit()); }

  void Unbind(const occ::handle<OpenGl_Context>& theCtx)
  {
    Unbind(theCtx, myParams->TextureUnit());
  }

  Standard_EXPORT void Bind(const occ::handle<OpenGl_Context>& theCtx,
                            const Graphic3d_TextureUnit        theUnit);

  Standard_EXPORT void Unbind(const occ::handle<OpenGl_Context>& theCtx,
                              const Graphic3d_TextureUnit        theUnit);

  void SetParameter(const occ::handle<OpenGl_Context>& theCtx,
                    unsigned int                       theTarget,
                    unsigned int                       theParam,
                    int                                theValue)
  {
    setParameter(theCtx, this, theTarget, theParam, theValue);
  }

  unsigned int SamplerID() const { return mySamplerID; }

  bool IsImmutable() const { return myIsImmutable; }

  void SetImmutable() { myIsImmutable = true; }

  const occ::handle<Graphic3d_TextureParams>& Parameters() { return myParams; }

  Standard_EXPORT void SetParameters(const occ::handle<Graphic3d_TextureParams>& theParams);

  bool ToUpdateParameters() const { return mySamplerRevision != myParams->SamplerRevision(); }

protected:
  bool isValidSampler() const { return mySamplerID != NO_SAMPLER; }

  Standard_EXPORT static void setParameter(const occ::handle<OpenGl_Context>& theContext,
                                           OpenGl_Sampler*                    theSampler,
                                           unsigned int                       theTarget,
                                           unsigned int                       theParam,
                                           int                                theValue);

  Standard_EXPORT static void applySamplerParams(
    const occ::handle<OpenGl_Context>&          theCtx,
    const occ::handle<Graphic3d_TextureParams>& theParams,
    OpenGl_Sampler*                             theSampler,
    const unsigned int                          theTarget,
    const int                                   theMaxMipLevel);

  Standard_EXPORT static void applyGlobalTextureParams(
    const occ::handle<OpenGl_Context>&          theCtx,
    const OpenGl_Texture&                       theTexture,
    const occ::handle<Graphic3d_TextureParams>& theParams);

  Standard_EXPORT static void resetGlobalTextureParams(
    const occ::handle<OpenGl_Context>&          theCtx,
    const OpenGl_Texture&                       theTexture,
    const occ::handle<Graphic3d_TextureParams>& theParams);

protected:
  occ::handle<Graphic3d_TextureParams> myParams;

  unsigned int mySamplerRevision;
  unsigned int mySamplerID;
  bool         myIsImmutable;
};
