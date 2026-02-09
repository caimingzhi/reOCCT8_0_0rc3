#pragma once

#include <OpenGl_Texture.hpp>

#include <vector>

class OpenGl_HaltonSampler
{
public:
  static unsigned get_num_dimensions() { return 3u; }

public:
  OpenGl_HaltonSampler() { initFaure(); }

  float sample(unsigned theDimension, unsigned theIndex) const
  {
    switch (theDimension)
    {
      case 0:
        return halton2(theIndex);
      case 1:
        return halton3(theIndex);
      case 2:
        return halton5(theIndex);
    }
    return 0.0f;
  }

private:
  void initFaure();

  static unsigned short invert(unsigned short                     theBase,
                               unsigned short                     theDigits,
                               unsigned short                     theIndex,
                               const std::vector<unsigned short>& thePerm)
  {
    unsigned short aResult = 0;
    for (unsigned short i = 0; i < theDigits; ++i)
    {
      aResult = aResult * theBase + thePerm[theIndex % theBase];
      theIndex /= theBase;
    }
    return aResult;
  }

  void initTables(const std::vector<std::vector<unsigned short>>& thePerm)
  {
    for (unsigned short i = 0; i < 243; ++i)
    {
      myPerm3[i] = invert(3, 5, i, thePerm[3]);
    }
    for (unsigned short i = 0; i < 125; ++i)
    {
      myPerm5[i] = invert(5, 3, i, thePerm[5]);
    }
  }

  float halton2(unsigned theIndex) const
  {
    theIndex = (theIndex << 16) | (theIndex >> 16);
    theIndex = ((theIndex & 0x00ff00ff) << 8) | ((theIndex & 0xff00ff00) >> 8);
    theIndex = ((theIndex & 0x0f0f0f0f) << 4) | ((theIndex & 0xf0f0f0f0) >> 4);
    theIndex = ((theIndex & 0x33333333) << 2) | ((theIndex & 0xcccccccc) >> 2);
    theIndex = ((theIndex & 0x55555555) << 1) | ((theIndex & 0xaaaaaaaa) >> 1);

    union Result
    {
      unsigned u;
      float    f;
    } aResult;

    aResult.u = 0x3f800000u | (theIndex >> 9);
    return aResult.f - 1.0f;
  }

  float halton3(unsigned theIndex) const
  {
    return (myPerm3[theIndex % 243u] * 14348907u + myPerm3[(theIndex / 243u) % 243u] * 59049u
            + myPerm3[(theIndex / 59049u) % 243u] * 243u + myPerm3[(theIndex / 14348907u) % 243u])
           * float(0.999999999999999 / 3486784401u);
  }

  float halton5(unsigned theIndex) const
  {
    return (myPerm5[theIndex % 125u] * 1953125u + myPerm5[(theIndex / 125u) % 125u] * 15625u
            + myPerm5[(theIndex / 15625u) % 125u] * 125u + myPerm5[(theIndex / 1953125u) % 125u])
           * float(0.999999999999999 / 244140625u);
  }

private:
  unsigned short myPerm3[243];
  unsigned short myPerm5[125];
};

inline void OpenGl_HaltonSampler::initFaure()
{
  const unsigned                           THE_MAX_BASE = 5u;
  std::vector<std::vector<unsigned short>> aPerms(THE_MAX_BASE + 1);
  for (unsigned k = 1; k <= 3; ++k)
  {
    aPerms[k].resize(k);
    for (unsigned i = 0; i < k; ++i)
    {
      aPerms[k][i] = static_cast<unsigned short>(i);
    }
  }

  for (unsigned aBase = 4; aBase <= THE_MAX_BASE; ++aBase)
  {
    aPerms[aBase].resize(aBase);
    const unsigned b = aBase / 2;
    if (aBase & 1)
    {
      for (unsigned i = 0; i < aBase - 1; ++i)
      {
        aPerms[aBase][i + (i >= b)] = aPerms[aBase - 1][i] + (aPerms[aBase - 1][i] >= b);
      }
      aPerms[aBase][b] = static_cast<unsigned short>(b);
    }
    else
    {
      for (unsigned i = 0; i < b; ++i)
      {
        aPerms[aBase][i]     = 2 * aPerms[b][i];
        aPerms[aBase][b + i] = 2 * aPerms[b][i] + 1;
      }
    }
  }
  initTables(aPerms);
}

#ifndef _Image_PixMapTypedData_Header
  #define _Image_PixMapTypedData_Header

  #include <Image_PixMapData.hpp>

template <typename PixelType_t>
class Image_PixMapTypedData : public Image_PixMapData
{
public:
  Image_PixMapTypedData() = default;

  bool Init(const occ::handle<NCollection_BaseAllocator>& theAlloc,
            size_t                                        theSizeX,
            size_t                                        theSizeY,
            size_t                                        theSizeRowBytes = 0,
            uint8_t*                                      theDataPtr      = nullptr)
  {
    const size_t aSizeBPP = sizeof(PixelType_t);
    return Image_PixMapData::Init(theAlloc,
                                  aSizeBPP,
                                  theSizeX,
                                  theSizeY,
                                  theSizeRowBytes,
                                  theDataPtr);
  }

  void Init(const PixelType_t& theValue)
  {
    for (size_t aRowIter = 0; aRowIter < SizeY; ++aRowIter)
    {
      for (size_t aColIter = 0; aColIter < SizeX; ++aColIter)
      {
        ChangeValue(aRowIter, aColIter) = theValue;
      }
    }
  }

  const PixelType_t* Row(size_t theRow) const
  {
    return (const PixelType_t*)Image_PixMapData::Row(theRow);
  }

  PixelType_t* ChangeRow(size_t theRow)
  {
    return (PixelType_t*)Image_PixMapData::ChangeRow(theRow);
  }

  const PixelType_t& Value(size_t theRow, size_t theCol) const
  {
    return *(const PixelType_t*)Image_PixMapData::Value(theRow, theCol);
  }

  PixelType_t& ChangeValue(size_t theRow, size_t theCol)
  {
    return *(PixelType_t*)Image_PixMapData::ChangeValue(theRow, theCol);
  }
};

#endif

#include <vector>

class Graphic3d_RenderingParams;

class OpenGl_TileSampler
{
public:
  Standard_EXPORT OpenGl_TileSampler();

  NCollection_Vec2<int> TileSize() const { return NCollection_Vec2<int>(myTileSize, myTileSize); }

  float VarianceScaleFactor() const { return myScaleFactor; }

  int NbTilesX() const { return (int)myTiles.SizeX; }

  int NbTilesY() const { return (int)myTiles.SizeY; }

  int NbTiles() const { return int(myTiles.SizeX * myTiles.SizeY); }

  const NCollection_Vec2<int>& ViewSize() const { return myViewSize; }

  NCollection_Vec2<int> NbOffsetTiles(bool theAdaptive) const
  {
    return theAdaptive
             ? NCollection_Vec2<int>((int)myOffsetsShrunk.SizeX, (int)myOffsetsShrunk.SizeY)
             : NCollection_Vec2<int>((int)myOffsets.SizeX, (int)myOffsets.SizeY);
  }

  NCollection_Vec2<int> NbOffsetTilesMax() const
  {
    return NbOffsetTiles(true).cwiseMax(NbOffsetTiles(false));
  }

  NCollection_Vec2<int> OffsetTilesViewport(bool theAdaptive) const
  {
    return NbOffsetTiles(theAdaptive) * myTileSize;
  }

  NCollection_Vec2<int> OffsetTilesViewportMax() const { return NbOffsetTilesMax() * myTileSize; }

  int MaxTileSamples() const
  {
    int aNbSamples = 0;
    for (size_t aRowIter = 0; aRowIter < myTiles.SizeY; ++aRowIter)
    {
      for (size_t aColIter = 0; aColIter < myTiles.SizeX; ++aColIter)
      {
        aNbSamples = (std::max)(aNbSamples, static_cast<int>(myTiles.Value(aRowIter, aColIter)));
      }
    }
    return aNbSamples;
  }

  Standard_EXPORT void SetSize(const Graphic3d_RenderingParams& theParams,
                               const NCollection_Vec2<int>&     theSize);

  Standard_EXPORT void GrabVarianceMap(const occ::handle<OpenGl_Context>& theContext,
                                       const occ::handle<OpenGl_Texture>& theTexture);

  void Reset() { myLastSample = 0; }

  bool UploadSamples(const occ::handle<OpenGl_Context>& theContext,
                     const occ::handle<OpenGl_Texture>& theSamplesTexture,
                     const bool                         theAdaptive)
  {
    return upload(theContext, theSamplesTexture, occ::handle<OpenGl_Texture>(), theAdaptive);
  }

  bool UploadOffsets(const occ::handle<OpenGl_Context>& theContext,
                     const occ::handle<OpenGl_Texture>& theOffsetsTexture,
                     const bool                         theAdaptive)
  {
    return upload(theContext, occ::handle<OpenGl_Texture>(), theOffsetsTexture, theAdaptive);
  }

protected:
  int tileArea(int theX, int theY) const
  {
    const int aSizeX = (std::min)(myTileSize, myViewSize.x() - theX * myTileSize);
    const int aSizeY = (std::min)(myTileSize, myViewSize.y() - theY * myTileSize);
    return aSizeX * aSizeY;
  }

  Standard_EXPORT NCollection_Vec2<int> nextTileToSample();

  Standard_EXPORT bool upload(const occ::handle<OpenGl_Context>& theContext,
                              const occ::handle<OpenGl_Texture>& theSamplesTexture,
                              const occ::handle<OpenGl_Texture>& theOffsetsTexture,
                              const bool                         theAdaptive);

  Standard_EXPORT void dumpMap(std::ostream&                     theStream,
                               const Image_PixMapTypedData<int>& theMap,
                               const char*                       theTitle) const;

protected:
  Image_PixMapTypedData<unsigned int>          myTiles;
  Image_PixMapTypedData<unsigned int>          myTileSamples;
  Image_PixMapTypedData<float>                 myVarianceMap;
  Image_PixMapTypedData<int>                   myVarianceRaw;
  Image_PixMapTypedData<NCollection_Vec2<int>> myOffsets;
  Image_PixMapTypedData<NCollection_Vec2<int>> myOffsetsShrunk;
  std::vector<float>                           myMarginalMap;
  OpenGl_HaltonSampler                         mySampler;
  unsigned int                                 myLastSample;
  float                                        myScaleFactor;

  int                   myTileSize;
  NCollection_Vec2<int> myViewSize;
};
