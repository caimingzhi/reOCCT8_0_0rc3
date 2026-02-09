

#include <Graphic3d_TextureParams.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_TextureParams, Standard_Transient)

Graphic3d_TextureParams::Graphic3d_TextureParams()
    : myGenPlaneS(0.0f, 0.0f, 0.0f, 0.0f),
      myGenPlaneT(0.0f, 0.0f, 0.0f, 0.0f),
      myScale(1.0f, 1.0f),
      myTranslation(0.0f, 0.0f),
      mySamplerRevision(0),
      myTextureUnit(Graphic3d_TextureUnit_BaseColor),
      myFilter(Graphic3d_TOTF_NEAREST),
      myAnisoLevel(Graphic3d_LOTA_OFF),
      myGenMode(Graphic3d_TOTM_MANUAL),
      myBaseLevel(0),
      myMaxLevel(1000),
      myRotAngle(0.0f),
      myToModulate(false),
      myToRepeat(false)
{
}

Graphic3d_TextureParams::~Graphic3d_TextureParams() = default;

void Graphic3d_TextureParams::SetModulate(const bool theToModulate)
{
  myToModulate = theToModulate;
}

void Graphic3d_TextureParams::SetRepeat(const bool theToRepeat)
{
  if (myToRepeat != theToRepeat)
  {
    myToRepeat = theToRepeat;
    updateSamplerRevision();
  }
}

void Graphic3d_TextureParams::SetFilter(const Graphic3d_TypeOfTextureFilter theFilter)
{
  if (myFilter != theFilter)
  {
    myFilter = theFilter;
    updateSamplerRevision();
  }
}

void Graphic3d_TextureParams::SetAnisoFilter(const Graphic3d_LevelOfTextureAnisotropy theLevel)
{
  if (myAnisoLevel != theLevel)
  {
    myAnisoLevel = theLevel;
    updateSamplerRevision();
  }
}

void Graphic3d_TextureParams::SetRotation(const float theAngleDegrees)
{
  myRotAngle = theAngleDegrees;
}

void Graphic3d_TextureParams::SetScale(const NCollection_Vec2<float> theScale)
{
  myScale = theScale;
}

void Graphic3d_TextureParams::SetTranslation(const NCollection_Vec2<float> theVec)
{
  myTranslation = theVec;
}

void Graphic3d_TextureParams::SetGenMode(const Graphic3d_TypeOfTextureMode theMode,
                                         const NCollection_Vec4<float>     thePlaneS,
                                         const NCollection_Vec4<float>     thePlaneT)
{
  myGenMode   = theMode;
  myGenPlaneS = thePlaneS;
  myGenPlaneT = thePlaneT;
}
