#pragma once


#include <OpenGl_Texture.hpp>
// Copyright (c) 2012 Leonhard Gruenschloss (leonhard@gruenschloss.org)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include <vector>

//! Compute points of the Halton sequence with digit-permutations for different bases.
class OpenGl_HaltonSampler
{
public:
  //! Return the number of supported dimensions.
  static unsigned get_num_dimensions() { return 3u; }

public:
  //! Init the permutation arrays using Faure-permutations.
  OpenGl_HaltonSampler() { initFaure(); }

  //! Return the Halton sample for the given dimension (component) and index.
  //! The client must have called initFaure() at least once before.
  //! dimension must be smaller than the value returned by get_num_dimensions().
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
  //! Init the permutation arrays using Faure-permutations.
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

  //! Special case: radical inverse in base 2, with direct bit reversal.
  float halton2(unsigned theIndex) const
  {
    theIndex = (theIndex << 16) | (theIndex >> 16);
    theIndex = ((theIndex & 0x00ff00ff) << 8) | ((theIndex & 0xff00ff00) >> 8);
    theIndex = ((theIndex & 0x0f0f0f0f) << 4) | ((theIndex & 0xf0f0f0f0) >> 4);
    theIndex = ((theIndex & 0x33333333) << 2) | ((theIndex & 0xcccccccc) >> 2);
    theIndex = ((theIndex & 0x55555555) << 1) | ((theIndex & 0xaaaaaaaa) >> 1);

    // clang-format off
    union Result { unsigned u; float f; } aResult; // Write reversed bits directly into floating-point mantissa.

    // clang-format on
    aResult.u = 0x3f800000u | (theIndex >> 9);
    return aResult.f - 1.0f;
  }

  float halton3(unsigned theIndex) const
  {
    return (myPerm3[theIndex % 243u] * 14348907u + myPerm3[(theIndex / 243u) % 243u] * 59049u
            + myPerm3[(theIndex / 59049u) % 243u] * 243u + myPerm3[(theIndex / 14348907u) % 243u])
           * float(0.999999999999999 / 3486784401u); // Results in [0,1).
  }

  float halton5(unsigned theIndex) const
  {
    return (myPerm5[theIndex % 125u] * 1953125u + myPerm5[(theIndex / 125u) % 125u] * 15625u
            + myPerm5[(theIndex / 15625u) % 125u] * 125u + myPerm5[(theIndex / 1953125u) % 125u])
           * float(0.999999999999999 / 244140625u); // Results in [0,1).
  }

private:
  unsigned short myPerm3[243];
  unsigned short myPerm5[125];
};

inline void OpenGl_HaltonSampler::initFaure()
{
  const unsigned                           THE_MAX_BASE = 5u;
  std::vector<std::vector<unsigned short>> aPerms(THE_MAX_BASE + 1);
  for (unsigned k = 1; k <= 3; ++k) // Keep identity permutations for base 1, 2, 3.
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
    if (aBase & 1) // odd
    {
      for (unsigned i = 0; i < aBase - 1; ++i)
      {
        aPerms[aBase][i + (i >= b)] = aPerms[aBase - 1][i] + (aPerms[aBase - 1][i] >= b);
      }
      aPerms[aBase][b] = static_cast<unsigned short>(b);
    }
    else // even
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


// Copyright (c) 2019 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _Image_PixMapTypedData_Header
#define _Image_PixMapTypedData_Header

#include <Image_PixMapData.hpp>

//! Structure to manage image buffer with predefined pixel type.
template <typename PixelType_t>
class Image_PixMapTypedData : public Image_PixMapData
{
public:
  //! Empty constructor.
  Image_PixMapTypedData() = default;

  //! Initializer.
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

  //! Reset all values to specified one.
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

  //! @return data pointer to requested row (first column).
  const PixelType_t* Row(size_t theRow) const
  {
    return (const PixelType_t*)Image_PixMapData::Row(theRow);
  }

  //! @return data pointer to requested row (first column).
  PixelType_t* ChangeRow(size_t theRow)
  {
    return (PixelType_t*)Image_PixMapData::ChangeRow(theRow);
  }

  //! @return data pointer to requested position.
  const PixelType_t& Value(size_t theRow, size_t theCol) const
  {
    return *(const PixelType_t*)Image_PixMapData::Value(theRow, theCol);
  }

  //! @return data pointer to requested position.
  PixelType_t& ChangeValue(size_t theRow, size_t theCol)
  {
    return *(PixelType_t*)Image_PixMapData::ChangeValue(theRow, theCol);
  }
};

#endif // _Image_PixMapTypedData_Header


#include <vector>

class Graphic3d_RenderingParams;

//! Tool object used for sampling screen tiles according to estimated pixel variance (used in path
//! tracing engine). To improve GPU thread coherency, rendering window is split into pixel blocks or
//! tiles. The important feature of this approach is that it is possible to keep the same number of
//! tiles for any screen resolution (e.g. 256 tiles can be used for both 512 x 512 window and 1920 x
//! 1080 window). So, a smaller number of tiles allows to increase interactivity (FPS), but at the
//! cost of higher per-frame variance ('noise'). On the contrary a larger number of tiles decrease
//! interactivity, but leads to lower per-frame variance. Note that the total time needed to produce
//! final final image is the same for both cases.
class OpenGl_TileSampler
{
public:
  //! Creates new tile sampler.
  Standard_EXPORT OpenGl_TileSampler();

  //! Size of individual tile in pixels.
  NCollection_Vec2<int> TileSize() const { return NCollection_Vec2<int>(myTileSize, myTileSize); }

  //! Scale factor for quantization of visual error (float) into signed integer.
  float VarianceScaleFactor() const { return myScaleFactor; }

  //! Returns number of tiles in X dimension.
  int NbTilesX() const { return (int)myTiles.SizeX; }

  //! Returns number of tiles in Y dimension.
  int NbTilesY() const { return (int)myTiles.SizeY; }

  //! Returns total number of tiles in viewport.
  int NbTiles() const { return int(myTiles.SizeX * myTiles.SizeY); }

  //! Returns ray-tracing viewport.
  const NCollection_Vec2<int>& ViewSize() const { return myViewSize; }

  //! Number of tiles within offsets texture.
  NCollection_Vec2<int> NbOffsetTiles(bool theAdaptive) const
  {
    return theAdaptive
             ? NCollection_Vec2<int>((int)myOffsetsShrunk.SizeX, (int)myOffsetsShrunk.SizeY)
             : NCollection_Vec2<int>((int)myOffsets.SizeX, (int)myOffsets.SizeY);
  }

  //! Maximum number of tiles within offsets texture.
  NCollection_Vec2<int> NbOffsetTilesMax() const
  {
    return NbOffsetTiles(true).cwiseMax(NbOffsetTiles(false));
  }

  //! Viewport for rendering using offsets texture.
  NCollection_Vec2<int> OffsetTilesViewport(bool theAdaptive) const
  {
    return NbOffsetTiles(theAdaptive) * myTileSize;
  }

  //! Maximum viewport for rendering using offsets texture.
  NCollection_Vec2<int> OffsetTilesViewportMax() const { return NbOffsetTilesMax() * myTileSize; }

  //! Return maximum number of samples per tile.
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

  //! Specifies size of ray-tracing viewport and recomputes tile size.
  Standard_EXPORT void SetSize(const Graphic3d_RenderingParams& theParams,
                               const NCollection_Vec2<int>&     theSize);

  //! Fetches current error estimation from the GPU and
  //! builds 2D discrete distribution for tile sampling.
  Standard_EXPORT void GrabVarianceMap(const occ::handle<OpenGl_Context>& theContext,
                                       const occ::handle<OpenGl_Texture>& theTexture);

  //! Resets (restart) tile sampler to initial state.
  void Reset() { myLastSample = 0; }

  //! Uploads tile samples to the given OpenGL texture.
  bool UploadSamples(const occ::handle<OpenGl_Context>& theContext,
                     const occ::handle<OpenGl_Texture>& theSamplesTexture,
                     const bool                         theAdaptive)
  {
    return upload(theContext, theSamplesTexture, occ::handle<OpenGl_Texture>(), theAdaptive);
  }

  //! Uploads offsets of sampled tiles to the given OpenGL texture.
  bool UploadOffsets(const occ::handle<OpenGl_Context>& theContext,
                     const occ::handle<OpenGl_Texture>& theOffsetsTexture,
                     const bool                         theAdaptive)
  {
    return upload(theContext, occ::handle<OpenGl_Texture>(), theOffsetsTexture, theAdaptive);
  }

protected:
  //! Returns number of pixels in the given tile.
  int tileArea(int theX, int theY) const
  {
    const int aSizeX = (std::min)(myTileSize, myViewSize.x() - theX * myTileSize);
    const int aSizeY = (std::min)(myTileSize, myViewSize.y() - theY * myTileSize);
    return aSizeX * aSizeY;
  }

  //! Samples tile location according to estimated error.
  Standard_EXPORT NCollection_Vec2<int> nextTileToSample();

  //! Uploads offsets of sampled tiles to the given OpenGL texture.
  Standard_EXPORT bool upload(const occ::handle<OpenGl_Context>& theContext,
                              const occ::handle<OpenGl_Texture>& theSamplesTexture,
                              const occ::handle<OpenGl_Texture>& theOffsetsTexture,
                              const bool                         theAdaptive);

  //! Auxiliary method for dumping 2D image map into stream (e.g. for debugging).
  Standard_EXPORT void dumpMap(std::ostream&                     theStream,
                               const Image_PixMapTypedData<int>& theMap,
                               const char*                       theTitle) const;

protected:
  // clang-format off
  Image_PixMapTypedData<unsigned int>    myTiles;         //!< number of samples per tile (initially all 1)
  Image_PixMapTypedData<unsigned int>    myTileSamples;   //!< number of samples for all pixels within the tile (initially equals to Tile area)
  Image_PixMapTypedData<float>           myVarianceMap;   //!< Estimation of visual error per tile
  Image_PixMapTypedData<int>             myVarianceRaw;   //!< Estimation of visual error per tile (raw data)
  Image_PixMapTypedData<NCollection_Vec2<int>> myOffsets;       //!< 2D array of tiles redirecting to another tile
  Image_PixMapTypedData<NCollection_Vec2<int>> myOffsetsShrunk; //!< 2D array of tiles redirecting to another tile (shrunk)
  std::vector<float>                     myMarginalMap;   //!< Marginal distribution of 2D error map
  OpenGl_HaltonSampler                   mySampler;       //!< Halton sequence generator
  unsigned int                           myLastSample;    //!< Index of generated sample
  float                                  myScaleFactor;   //!< scale factor for quantization of visual error (float) into signed integer
  // clang-format on
  int                   myTileSize; //!< tile size
  NCollection_Vec2<int> myViewSize; //!< ray-tracing viewport
};

