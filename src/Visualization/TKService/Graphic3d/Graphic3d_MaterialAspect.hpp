#pragma once

#include <Graphic3d_BSDF.hpp>
#include <Graphic3d_PBRMaterial.hpp>
#include <Graphic3d_NameOfMaterial.hpp>

enum Graphic3d_TypeOfMaterial
{
  Graphic3d_MATERIAL_ASPECT,

  Graphic3d_MATERIAL_PHYSIC
};

#include <Graphic3d_TypeOfReflection.hpp>
#include <TCollection_AsciiString.hpp>
#include <Quantity_Color.hpp>

class Graphic3d_MaterialAspect
{
public:
  DEFINE_STANDARD_ALLOC

  static int NumberOfMaterials() { return Graphic3d_NameOfMaterial_DEFAULT; }

  Standard_EXPORT static const char* MaterialName(const int theRank);

  Standard_EXPORT static Graphic3d_TypeOfMaterial MaterialType(const int theRank);

  Standard_EXPORT static bool MaterialFromName(const char*               theName,
                                               Graphic3d_NameOfMaterial& theMat);

  static Graphic3d_NameOfMaterial MaterialFromName(const char* theName)
  {
    Graphic3d_NameOfMaterial aMat = Graphic3d_NameOfMaterial_DEFAULT;
    MaterialFromName(theName, aMat);
    return aMat;
  }

public:
  Standard_EXPORT Graphic3d_MaterialAspect();

  Standard_EXPORT Graphic3d_MaterialAspect(const Graphic3d_NameOfMaterial theName);

  Graphic3d_NameOfMaterial Name() const { return myMaterialName; }

  Graphic3d_NameOfMaterial RequestedName() const { return myRequestedMaterialName; }

  const TCollection_AsciiString& StringName() const { return myStringName; }

  const char* MaterialName() const { return myStringName.ToCString(); }

  void SetMaterialName(const TCollection_AsciiString& theName)
  {

    myMaterialName = Graphic3d_NameOfMaterial_UserDefined;
    myStringName   = theName;
  }

  void Reset() { init(myRequestedMaterialName); }

  const Quantity_Color& Color() const { return myColors[Graphic3d_TOR_DIFFUSE]; }

  Standard_EXPORT void SetColor(const Quantity_Color& theColor);

  float Transparency() const { return myTransparencyCoef; }

  float Alpha() const { return 1.0f - myTransparencyCoef; }

  Standard_EXPORT void SetTransparency(const float theValue);

  void SetAlpha(float theValue) { SetTransparency(1.0f - theValue); }

  const Quantity_Color& AmbientColor() const { return myColors[Graphic3d_TOR_AMBIENT]; }

  Standard_EXPORT void SetAmbientColor(const Quantity_Color& theColor);

  const Quantity_Color& DiffuseColor() const { return myColors[Graphic3d_TOR_DIFFUSE]; }

  Standard_EXPORT void SetDiffuseColor(const Quantity_Color& theColor);

  const Quantity_Color& SpecularColor() const { return myColors[Graphic3d_TOR_SPECULAR]; }

  Standard_EXPORT void SetSpecularColor(const Quantity_Color& theColor);

  const Quantity_Color& EmissiveColor() const { return myColors[Graphic3d_TOR_EMISSION]; }

  Standard_EXPORT void SetEmissiveColor(const Quantity_Color& theColor);

  float Shininess() const { return myShininess; }

  Standard_EXPORT void SetShininess(const float theValue);

  Standard_EXPORT void IncreaseShine(const float theDelta);

  float RefractionIndex() const { return myRefractionIndex; }

  Standard_EXPORT void SetRefractionIndex(const float theValue);

  const Graphic3d_BSDF& BSDF() const { return myBSDF; }

  void SetBSDF(const Graphic3d_BSDF& theBSDF) { myBSDF = theBSDF; }

  const Graphic3d_PBRMaterial& PBRMaterial() const { return myPBRMaterial; }

  void SetPBRMaterial(const Graphic3d_PBRMaterial& thePBRMaterial)
  {
    myPBRMaterial = thePBRMaterial;
  }

  bool ReflectionMode(const Graphic3d_TypeOfReflection theType) const
  {
    return !myColors[theType].IsEqual(Quantity_NOC_BLACK);
  }

  Graphic3d_TypeOfMaterial MaterialType() const { return myMaterialType; }

  bool MaterialType(const Graphic3d_TypeOfMaterial theType) const
  {
    return myMaterialType == theType;
  }

  Standard_EXPORT void SetMaterialType(const Graphic3d_TypeOfMaterial theType);

  bool IsDifferent(const Graphic3d_MaterialAspect& theOther) const { return !IsEqual(theOther); }

  bool operator!=(const Graphic3d_MaterialAspect& theOther) const { return IsDifferent(theOther); }

  bool IsEqual(const Graphic3d_MaterialAspect& theOther) const
  {
    return myTransparencyCoef == theOther.myTransparencyCoef
           && myRefractionIndex == theOther.myRefractionIndex && myBSDF == theOther.myBSDF
           && myPBRMaterial == theOther.myPBRMaterial && myShininess == theOther.myShininess
           && myColors[Graphic3d_TOR_AMBIENT] == theOther.myColors[Graphic3d_TOR_AMBIENT]
           && myColors[Graphic3d_TOR_DIFFUSE] == theOther.myColors[Graphic3d_TOR_DIFFUSE]
           && myColors[Graphic3d_TOR_SPECULAR] == theOther.myColors[Graphic3d_TOR_SPECULAR]
           && myColors[Graphic3d_TOR_EMISSION] == theOther.myColors[Graphic3d_TOR_EMISSION];
  }

  bool operator==(const Graphic3d_MaterialAspect& theOther) const { return IsEqual(theOther); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Standard_DEPRECATED("Deprecated method, specific material component should be zerroed "
                      "instead")

  void SetReflectionModeOff(const Graphic3d_TypeOfReflection theType)
  {
    if (!ReflectionMode(theType))
    {
      return;
    }

    switch (theType)
    {
      case Graphic3d_TOR_AMBIENT:
        SetAmbientColor(Quantity_NOC_BLACK);
        break;
      case Graphic3d_TOR_DIFFUSE:
        SetDiffuseColor(Quantity_NOC_BLACK);
        break;
      case Graphic3d_TOR_SPECULAR:
        SetSpecularColor(Quantity_NOC_BLACK);
        break;
      case Graphic3d_TOR_EMISSION:
        SetEmissiveColor(Quantity_NOC_BLACK);
        break;
    }
  }

private:
  Standard_EXPORT void init(const Graphic3d_NameOfMaterial theName);

  void setUserMaterial()
  {

    if (myMaterialName != Graphic3d_NameOfMaterial_UserDefined)
    {
      myMaterialName = Graphic3d_NameOfMaterial_UserDefined;
      myStringName   = "UserDefined";
    }
  }

private:
  Graphic3d_BSDF          myBSDF;
  Graphic3d_PBRMaterial   myPBRMaterial;
  TCollection_AsciiString myStringName;
  Quantity_Color          myColors[Graphic3d_TypeOfReflection_NB];
  float                   myTransparencyCoef;
  float                   myRefractionIndex;
  float                   myShininess;

  Graphic3d_TypeOfMaterial myMaterialType;
  Graphic3d_NameOfMaterial myMaterialName;
  Graphic3d_NameOfMaterial myRequestedMaterialName;
};
