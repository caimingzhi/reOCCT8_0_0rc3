#pragma once

#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec4.hpp>

class Graphic3d_PBRMaterial;

enum Graphic3d_FresnelModel
{
  Graphic3d_FM_SCHLICK    = 0,
  Graphic3d_FM_CONSTANT   = 1,
  Graphic3d_FM_CONDUCTOR  = 2,
  Graphic3d_FM_DIELECTRIC = 3
};

class Graphic3d_Fresnel
{
public:
  Graphic3d_Fresnel()
      : myFresnelType(Graphic3d_FM_CONSTANT)
  {

    myFresnelData = NCollection_Vec3<float>(0.f, 1.f, 0.f);
  }

  static Graphic3d_Fresnel CreateSchlick(const NCollection_Vec3<float>& theSpecularColor)
  {
    return Graphic3d_Fresnel(Graphic3d_FM_SCHLICK, theSpecularColor);
  }

  static Graphic3d_Fresnel CreateConstant(const float theReflection)
  {
    return Graphic3d_Fresnel(Graphic3d_FM_CONSTANT,
                             NCollection_Vec3<float>(0.f, 1.f, theReflection));
  }

  static Graphic3d_Fresnel CreateDielectric(float theRefractionIndex)
  {
    return Graphic3d_Fresnel(Graphic3d_FM_DIELECTRIC,
                             NCollection_Vec3<float>(0.f, theRefractionIndex, 0.f));
  }

  static Graphic3d_Fresnel CreateConductor(float theRefractionIndex, float theAbsorptionIndex)
  {
    return Graphic3d_Fresnel(Graphic3d_FM_CONDUCTOR,
                             NCollection_Vec3<float>(0.f, theRefractionIndex, theAbsorptionIndex));
  }

  Standard_EXPORT static Graphic3d_Fresnel CreateConductor(
    const NCollection_Vec3<float>& theRefractionIndex,
    const NCollection_Vec3<float>& theAbsorptionIndex);

public:
  Standard_EXPORT NCollection_Vec4<float> Serialize() const;

  bool operator==(const Graphic3d_Fresnel& theOther) const
  {
    return myFresnelType == theOther.myFresnelType && myFresnelData == theOther.myFresnelData;
  }

  Graphic3d_FresnelModel FresnelType() const { return myFresnelType; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Graphic3d_Fresnel(Graphic3d_FresnelModel theType, const NCollection_Vec3<float>& theData)
      : myFresnelType(theType),
        myFresnelData(theData)
  {
  }

private:
  Graphic3d_FresnelModel myFresnelType;

  NCollection_Vec3<float> myFresnelData;
};

class Graphic3d_BSDF
{
public:
  NCollection_Vec4<float> Kc;

  NCollection_Vec3<float> Kd;

  NCollection_Vec4<float> Ks;

  NCollection_Vec3<float> Kt;

  NCollection_Vec3<float> Le;

  NCollection_Vec4<float> Absorption;

  Graphic3d_Fresnel FresnelCoat;

  Graphic3d_Fresnel FresnelBase;

public:
  static Standard_EXPORT Graphic3d_BSDF CreateDiffuse(const NCollection_Vec3<float>& theWeight);

  static Standard_EXPORT Graphic3d_BSDF CreateMetallic(const NCollection_Vec3<float>& theWeight,
                                                       const Graphic3d_Fresnel&       theFresnel,
                                                       const float                    theRoughness);

  static Standard_EXPORT Graphic3d_BSDF
    CreateTransparent(const NCollection_Vec3<float>& theWeight,
                      const NCollection_Vec3<float>& theAbsorptionColor,
                      const float                    theAbsorptionCoeff);

  static Standard_EXPORT Graphic3d_BSDF
    CreateGlass(const NCollection_Vec3<float>& theWeight,
                const NCollection_Vec3<float>& theAbsorptionColor,
                const float                    theAbsorptionCoeff,
                const float                    theRefractionIndex);

  static Standard_EXPORT Graphic3d_BSDF
    CreateMetallicRoughness(const Graphic3d_PBRMaterial& thePbr);

public:
  Standard_EXPORT Graphic3d_BSDF();

  Standard_EXPORT void Normalize();

  Standard_EXPORT bool operator==(const Graphic3d_BSDF& theOther) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;
};
