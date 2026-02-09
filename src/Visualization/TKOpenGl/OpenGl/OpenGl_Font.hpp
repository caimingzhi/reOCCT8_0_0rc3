#pragma once

#include <OpenGl_Texture.hpp>
#include <OpenGl_Vec.hpp>

#include <Font_Rect.hpp>

#include <NCollection_DataMap.hpp>
#include <NCollection_Vector.hpp>
#include <TCollection_AsciiString.hpp>

class Font_FTFont;

class OpenGl_Font : public OpenGl_Resource
{

public:
  struct Tile
  {
    Font_Rect uv;
    Font_Rect px;
    GLuint    texture;
  };

  struct RectI
  {
    int Left;
    int Right;
    int Top;
    int Bottom;
  };

public:
  Standard_EXPORT OpenGl_Font(const occ::handle<Font_FTFont>& theFont,
                              const TCollection_AsciiString&  theKey = "");

  Standard_EXPORT ~OpenGl_Font() override;

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  Standard_EXPORT size_t EstimatedDataSize() const override;

  inline const TCollection_AsciiString& ResourceKey() const { return myKey; }

  inline const occ::handle<Font_FTFont>& FTFont() const { return myFont; }

  inline bool IsValid() const { return !myTextures.IsEmpty() && myTextures.First()->IsValid(); }

  inline bool WasInitialized() const { return !myTextures.IsEmpty(); }

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theCtx);

  inline float Ascender() const { return myAscender; }

  inline float Descender() const { return myDescender; }

  Standard_EXPORT bool RenderGlyph(const occ::handle<OpenGl_Context>& theCtx,
                                   const char32_t                     theUChar,
                                   Tile&                              theGlyph);

  const occ::handle<OpenGl_Texture>& Texture() const { return myTextures.First(); }

protected:
  bool renderGlyph(const occ::handle<OpenGl_Context>& theCtx, const char32_t theChar);

  bool createTexture(const occ::handle<OpenGl_Context>& theCtx);

protected:
  TCollection_AsciiString  myKey;
  occ::handle<Font_FTFont> myFont;
  float                    myAscender;
  float                    myDescender;
  int                      myTileSizeY;
  int                      myLastTileId;
  RectI                    myLastTilePx;
  int                      myTextureFormat;

  NCollection_Vector<occ::handle<OpenGl_Texture>> myTextures;
  NCollection_Vector<Tile>                        myTiles;

  NCollection_DataMap<char32_t, int> myGlyphMap;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_Font, OpenGl_Resource)
};
