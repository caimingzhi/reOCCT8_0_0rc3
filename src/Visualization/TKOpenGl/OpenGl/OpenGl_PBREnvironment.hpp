#pragma once

#include <OpenGl_Texture.hpp>
#include <OpenGl_VertexBuffer.hpp>

class OpenGl_PBREnvironment : public OpenGl_NamedResource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_PBREnvironment, OpenGl_NamedResource)
public:
  Standard_EXPORT static occ::handle<OpenGl_PBREnvironment> Create(
    const occ::handle<OpenGl_Context>& theCtx,
    unsigned int                       thePow2Size         = 9,
    unsigned int                       theSpecMapLevelsNum = 6,
    const TCollection_AsciiString&     theId               = "PBREnvironment");

public:
  Standard_EXPORT void Bind(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT void Unbind(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT void Clear(
    const occ::handle<OpenGl_Context>& theCtx,
    const NCollection_Vec3<float>&     theColor = NCollection_Vec3<float>(1.f));

  Standard_EXPORT void Bake(const occ::handle<OpenGl_Context>& theCtx,
                            const occ::handle<OpenGl_Texture>& theEnvMap,
                            bool                               theZIsInverted      = false,
                            bool                               theIsTopDown        = true,
                            size_t                             theDiffMapNbSamples = 1024,
                            size_t                             theSpecMapNbSamples = 256,
                            float                              theProbability      = 0.99f);

  unsigned int SpecMapLevelsNumber() const { return mySpecMapLevelsNumber; }

  unsigned int Pow2Size() const { return myPow2Size; }

  Standard_EXPORT bool SizesAreDifferent(unsigned int thePow2Size,
                                         unsigned int theSpecMapLevelsNumber) const;

  bool IsNeededToBeBound() const { return myIsNeededToBeBound; }

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  size_t EstimatedDataSize() const override
  {
    unsigned int aDiffIBLMapSidePixelsCount = 1 << myPow2Size;
    aDiffIBLMapSidePixelsCount *= aDiffIBLMapSidePixelsCount;
    size_t anEstimatedDataSize = aDiffIBLMapSidePixelsCount;
    for (unsigned int i = 0; i < mySpecMapLevelsNumber; ++i)
    {
      anEstimatedDataSize += aDiffIBLMapSidePixelsCount >> (2 * i);
    }
    anEstimatedDataSize *= 6;
    anEstimatedDataSize *= 3;
    return anEstimatedDataSize;
  }

  bool IsComplete() const { return myIsComplete; }

  Standard_EXPORT ~OpenGl_PBREnvironment() override;

private:
  Standard_EXPORT OpenGl_PBREnvironment(const occ::handle<OpenGl_Context>& theCtx,
                                        unsigned int                       thePowOf2Size      = 9,
                                        unsigned int                   theSpecMapLevelsNumber = 6,
                                        const TCollection_AsciiString& theId = "PBREnvironment");

private:
  enum OpenGl_TypeOfIBLMap
  {
    OpenGl_TypeOfIBLMap_DiffuseSH,
    OpenGl_TypeOfIBLMap_Specular,
    OpenGl_TypeOfIBLMap_DiffuseFallback,
  };

  struct BakingParams
  {
    size_t NbSpecSamples;
    size_t NbDiffSamples;
    int    EnvMapSize;
    float  Probability;
    bool   IsZInverted;
    bool   IsTopDown;

    BakingParams()
        : NbSpecSamples(0),
          NbDiffSamples(0),
          EnvMapSize(1024),
          Probability(1.0f),
          IsZInverted(false),
          IsTopDown(false)
    {
    }
  };

  bool initTextures(const occ::handle<OpenGl_Context>& theCtx);

  bool initFBO(const occ::handle<OpenGl_Context>& theCtx);

  bool initVAO(const occ::handle<OpenGl_Context>& theCtx);

  bool processDiffIBLMap(const occ::handle<OpenGl_Context>& theCtx,
                         const BakingParams*                theDrawParams);

  bool processSpecIBLMap(const occ::handle<OpenGl_Context>& theCtx,
                         const BakingParams*                theDrawParams);

  bool checkFBOComplentess(const occ::handle<OpenGl_Context>& theCtx);

  void bake(const occ::handle<OpenGl_Context>& theCtx,
            const occ::handle<OpenGl_Texture>& theEnvMap,
            bool                               theZIsInverted      = false,
            bool                               theIsTopDown        = true,
            size_t                             theDiffMapNbSamples = 1024,
            size_t                             theSpecMapNbSamples = 256,
            float                              theProbability      = 1.f);

  void clear(const occ::handle<OpenGl_Context>& theCtx,
             const NCollection_Vec3<float>&     theColor = NCollection_Vec3<float>(1.f));

private:
  unsigned int myPow2Size;
  unsigned int mySpecMapLevelsNumber;

  OpenGl_Texture      myIBLMaps[3];
  OpenGl_VertexBuffer myVBO;
  GLuint              myFBO;

  bool myIsComplete;
  bool myIsNeededToBeBound;
  bool myCanRenderFloat;
};
