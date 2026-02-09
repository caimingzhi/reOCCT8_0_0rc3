#pragma once

#include <Graphic3d_TextureMap.hpp>
#include <NCollection_Array1.hpp>

class Graphic3d_TextureSet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureSet, Standard_Transient)
public:
  class Iterator : public NCollection_Array1<occ::handle<Graphic3d_TextureMap>>::Iterator
  {
  public:
    Iterator() = default;

    Iterator(const occ::handle<Graphic3d_TextureSet>& theSet)
    {
      if (!theSet.IsNull())
      {
        NCollection_Array1<occ::handle<Graphic3d_TextureMap>>::Iterator::Init(theSet->myTextures);
      }
    }
  };

public:
  Graphic3d_TextureSet() = default;

  Graphic3d_TextureSet(int theNbTextures)
      : myTextures(0, theNbTextures - 1)
  {
  }

  Graphic3d_TextureSet(const occ::handle<Graphic3d_TextureMap>& theTexture)
      : myTextures(0, 0)
  {
    myTextures.ChangeFirst() = theTexture;
  }

  bool IsEmpty() const { return myTextures.IsEmpty(); }

  int Size() const { return myTextures.Size(); }

  int Lower() const { return myTextures.Lower(); }

  int Upper() const { return myTextures.Upper(); }

  const occ::handle<Graphic3d_TextureMap>& First() const { return myTextures.First(); }

  void SetFirst(const occ::handle<Graphic3d_TextureMap>& theTexture)
  {
    myTextures.ChangeFirst() = theTexture;
  }

  const occ::handle<Graphic3d_TextureMap>& Value(int theIndex) const
  {
    return myTextures.Value(theIndex);
  }

  void SetValue(int theIndex, const occ::handle<Graphic3d_TextureMap>& theTexture)
  {
    myTextures.SetValue(theIndex, theTexture);
  }

protected:
  NCollection_Array1<occ::handle<Graphic3d_TextureMap>> myTextures;
};
