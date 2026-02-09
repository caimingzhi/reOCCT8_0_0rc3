#pragma once

#include <Graphic3d_TextureSet.hpp>
#include <Graphic3d_TextureSetBits.hpp>

class OpenGl_Texture;

class OpenGl_TextureSet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_TextureSet, Standard_Transient)
public:
  struct TextureSlot
  {
    occ::handle<OpenGl_Texture> Texture;
    Graphic3d_TextureUnit       Unit;

    operator const occ::handle<OpenGl_Texture>&() const { return Texture; }

    operator occ::handle<OpenGl_Texture>&() { return Texture; }

    TextureSlot()
        : Unit(Graphic3d_TextureUnit_0)
    {
    }
  };

  class Iterator : public NCollection_Array1<TextureSlot>::Iterator
  {
  public:
    Iterator() = default;

    Iterator(const occ::handle<OpenGl_TextureSet>& theSet)
    {
      if (!theSet.IsNull())
      {
        NCollection_Array1<TextureSlot>::Iterator::Init(theSet->myTextures);
      }
    }

    const occ::handle<OpenGl_Texture>& Value() const
    {
      return NCollection_Array1<TextureSlot>::Iterator::Value().Texture;
    }

    occ::handle<OpenGl_Texture>& ChangeValue()
    {
      return NCollection_Array1<TextureSlot>::Iterator::ChangeValue().Texture;
    }

    Graphic3d_TextureUnit Unit() const
    {
      return NCollection_Array1<TextureSlot>::Iterator::Value().Unit;
    }

    Graphic3d_TextureUnit& ChangeUnit()
    {
      return NCollection_Array1<TextureSlot>::Iterator::ChangeValue().Unit;
    }
  };

public:
  OpenGl_TextureSet()
      : myTextureSetBits(Graphic3d_TextureSetBits_NONE)
  {
  }

  OpenGl_TextureSet(int theNbTextures)
      : myTextures(0, theNbTextures - 1),
        myTextureSetBits(Graphic3d_TextureSetBits_NONE)
  {
  }

  Standard_EXPORT OpenGl_TextureSet(const occ::handle<OpenGl_Texture>& theTexture);

  int TextureSetBits() const { return myTextureSetBits; }

  int& ChangeTextureSetBits() { return myTextureSetBits; }

  bool IsEmpty() const { return myTextures.IsEmpty(); }

  int Size() const { return myTextures.Size(); }

  int Lower() const { return myTextures.Lower(); }

  int Upper() const { return myTextures.Upper(); }

  const occ::handle<OpenGl_Texture>& First() const { return myTextures.First().Texture; }

  occ::handle<OpenGl_Texture>& ChangeFirst() { return myTextures.ChangeFirst().Texture; }

  Graphic3d_TextureUnit FirstUnit() const { return myTextures.First().Unit; }

  const occ::handle<OpenGl_Texture>& Last() const { return myTextures.Last().Texture; }

  occ::handle<OpenGl_Texture>& ChangeLast() { return myTextures.ChangeLast().Texture; }

  Graphic3d_TextureUnit LastUnit() const { return myTextures.Last().Unit; }

  Graphic3d_TextureUnit& ChangeLastUnit() { return myTextures.ChangeLast().Unit; }

  const occ::handle<OpenGl_Texture>& Value(int theIndex) const
  {
    return myTextures.Value(theIndex).Texture;
  }

  occ::handle<OpenGl_Texture>& ChangeValue(int theIndex)
  {
    return myTextures.ChangeValue(theIndex).Texture;
  }

  Standard_EXPORT bool IsModulate() const;

  Standard_EXPORT bool HasNonPointSprite() const;

  Standard_EXPORT bool HasPointSprite() const;

  void InitZero()
  {
    myTextures.Init(TextureSlot());
    myTextureSetBits = Graphic3d_TextureSetBits_NONE;
  }

protected:
  NCollection_Array1<TextureSlot> myTextures;
  int                             myTextureSetBits;
};
