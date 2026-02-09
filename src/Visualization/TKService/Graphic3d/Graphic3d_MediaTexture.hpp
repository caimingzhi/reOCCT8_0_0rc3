#pragma once

#include <Graphic3d_Texture2D.hpp>

#include <mutex>

class Media_Frame;

class Graphic3d_MediaTexture : public Graphic3d_Texture2D
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_MediaTexture, Graphic3d_Texture2D)
public:
  Standard_EXPORT occ::handle<Image_PixMap> GetImage(
    const occ::handle<Image_SupportedFormats>& theSupported) override;

  const occ::handle<Media_Frame>& Frame() const { return myFrame; }

  void SetFrame(const occ::handle<Media_Frame>& theFrame) { myFrame = theFrame; }

  void GenerateNewId() { generateId(); }

  friend class Graphic3d_MediaTextureSet;

private:
  Standard_EXPORT Graphic3d_MediaTexture(std::mutex& theMutex, int thePlane = -1);

protected:
  std::mutex&                       myMutex;
  occ::handle<Media_Frame>          myFrame;
  int                               myPlane;
  mutable occ::handle<Image_PixMap> myPixMapWrapper;
};
