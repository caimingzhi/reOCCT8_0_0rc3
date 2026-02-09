#pragma once

#include <Image_PixMap.hpp>
#include <Graphic3d_BSDF.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <Quantity_Color.hpp>

class Graphic3d_PBRMaterial
{
public:
  Standard_EXPORT Graphic3d_PBRMaterial();

  Standard_EXPORT Graphic3d_PBRMaterial(const Graphic3d_BSDF& theBSDF);

  float Metallic() const { return myMetallic; }

  Standard_EXPORT void SetMetallic(float theMetallic);

  Standard_EXPORT static float Roughness(float theNormalizedRoughness);

  float Roughness() const { return Roughness(myRoughness); }

  float NormalizedRoughness() const { return myRoughness; }

  Standard_EXPORT void SetRoughness(float theRoughness);

  float IOR() const { return myIOR; }

  Standard_EXPORT void SetIOR(float theIOR);

  const Quantity_ColorRGBA& Color() const { return myColor; }

  Standard_EXPORT void SetColor(const Quantity_ColorRGBA& theColor);

  Standard_EXPORT void SetColor(const Quantity_Color& theColor);

  float Alpha() const { return myColor.Alpha(); };

  Standard_EXPORT void SetAlpha(float theAlpha);

  NCollection_Vec3<float> Emission() const { return myEmission; }

  Standard_EXPORT void SetEmission(const NCollection_Vec3<float>& theEmission);

  Standard_EXPORT void SetBSDF(const Graphic3d_BSDF& theBSDF);

public:
  bool operator==(const Graphic3d_PBRMaterial& theOther) const
  {
    return (myMetallic == theOther.myMetallic) && (myRoughness == theOther.myRoughness)
           && (myIOR == theOther.myIOR) && (myColor == theOther.myColor)
           && (myEmission == theOther.myEmission);
  }

public:
  Standard_EXPORT static void GenerateEnvLUT(const occ::handle<Image_PixMap>& theLUT,
                                             unsigned int theNbIntegralSamples = 1024);

  Standard_EXPORT static float RoughnessFromSpecular(const Quantity_Color& theSpecular,
                                                     const double          theShiness);

  static float MetallicFromSpecular(const Quantity_Color& theSpecular)
  {
    return ((NCollection_Vec3<float>)theSpecular).maxComp();
  }

public:
  static float MinRoughness() { return 0.01f; }

public:
  Standard_EXPORT static float SpecIBLMapSamplesFactor(float theProbability, float theRoughness);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  static float lutGenGeometryFactor(float theCosL, float theCosV, float theRoughness);

  static NCollection_Vec2<float> lutGenHammersley(unsigned int theNumber, unsigned int theCount);

  static float lutGenImportanceSampleCosTheta(float theHammerslayPointComponent,
                                              float theRoughness);

  static NCollection_Vec3<float> lutGenImportanceSample(
    const NCollection_Vec2<float>& theHammerslayPoint,
    float                          theRoughness);

  static NCollection_Vec3<float> lutGenView(float theCosV);

  static NCollection_Vec3<float> lutGenReflect(const NCollection_Vec3<float>& theVector,
                                               const NCollection_Vec3<float>& theAxis);

private:
  Quantity_ColorRGBA      myColor;
  float                   myMetallic;
  float                   myRoughness;
  NCollection_Vec3<float> myEmission;
  float                   myIOR;
};
