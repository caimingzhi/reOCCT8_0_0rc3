#pragma once

#include <Graphic3d_LevelOfTextureAnisotropy.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec4.hpp>
#include <Graphic3d_TextureUnit.hpp>
#include <Graphic3d_TypeOfTextureFilter.hpp>
#include <Graphic3d_TypeOfTextureMode.hpp>
#include <Standard.hpp>
#include <Standard_ShortReal.hpp>
#include <Standard_Type.hpp>
#include <Standard_Transient.hpp>

class Graphic3d_TextureParams : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_TextureParams, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_TextureParams();

  Standard_EXPORT ~Graphic3d_TextureParams() override;

  Graphic3d_TextureUnit TextureUnit() const { return myTextureUnit; }

  void SetTextureUnit(Graphic3d_TextureUnit theUnit) { myTextureUnit = theUnit; }

  bool IsModulate() const { return myToModulate; }

  Standard_EXPORT void SetModulate(const bool theToModulate);

  bool IsRepeat() const { return myToRepeat; }

  Standard_EXPORT void SetRepeat(const bool theToRepeat);

  Graphic3d_TypeOfTextureFilter Filter() const { return myFilter; }

  Standard_EXPORT void SetFilter(const Graphic3d_TypeOfTextureFilter theFilter);

  Graphic3d_LevelOfTextureAnisotropy AnisoFilter() const { return myAnisoLevel; }

  Standard_EXPORT void SetAnisoFilter(const Graphic3d_LevelOfTextureAnisotropy theLevel);

  float Rotation() const { return myRotAngle; }

  Standard_EXPORT void SetRotation(const float theAngleDegrees);

  const NCollection_Vec2<float>& Scale() const { return myScale; }

  Standard_EXPORT void SetScale(const NCollection_Vec2<float> theScale);

  const NCollection_Vec2<float>& Translation() const { return myTranslation; }

  Standard_EXPORT void SetTranslation(const NCollection_Vec2<float> theVec);

  Graphic3d_TypeOfTextureMode GenMode() const { return myGenMode; }

  const NCollection_Vec4<float>& GenPlaneS() const { return myGenPlaneS; }

  const NCollection_Vec4<float>& GenPlaneT() const { return myGenPlaneT; }

  Standard_EXPORT void SetGenMode(const Graphic3d_TypeOfTextureMode theMode,
                                  const NCollection_Vec4<float>     thePlaneS,
                                  const NCollection_Vec4<float>     thePlaneT);

  int BaseLevel() const { return myBaseLevel; }

  int MaxLevel() const { return myMaxLevel; }

  void SetLevelsRange(int theFirstLevel, int theSecondLevel = 0)
  {
    myMaxLevel  = theFirstLevel > theSecondLevel ? theFirstLevel : theSecondLevel;
    myBaseLevel = theFirstLevel > theSecondLevel ? theSecondLevel : theFirstLevel;
  }

  unsigned int SamplerRevision() const { return mySamplerRevision; }

private:
  void updateSamplerRevision() { ++mySamplerRevision; }

private:
  NCollection_Vec4<float>            myGenPlaneS;
  NCollection_Vec4<float>            myGenPlaneT;
  NCollection_Vec2<float>            myScale;
  NCollection_Vec2<float>            myTranslation;
  unsigned int                       mySamplerRevision;
  Graphic3d_TextureUnit              myTextureUnit;
  Graphic3d_TypeOfTextureFilter      myFilter;
  Graphic3d_LevelOfTextureAnisotropy myAnisoLevel;
  Graphic3d_TypeOfTextureMode        myGenMode;
  int                                myBaseLevel;
  int                                myMaxLevel;
  float                              myRotAngle;
  bool                               myToModulate;
  bool                               myToRepeat;
};
