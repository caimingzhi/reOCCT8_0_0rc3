#pragma once

#include <Graphic3d_MaterialAspect.hpp>
#include <OpenGl_Vec.hpp>

class OpenGl_Context;

struct OpenGl_MaterialCommon
{

  NCollection_Vec4<float> Diffuse;
  NCollection_Vec4<float> Emission;
  NCollection_Vec4<float> SpecularShininess;
  NCollection_Vec4<float> Ambient;

  float Shine() const { return SpecularShininess.a(); }

  float& ChangeShine() { return SpecularShininess.a(); }

  OpenGl_MaterialCommon()
      : Diffuse(1.0f),
        Emission(1.0f),
        SpecularShininess(1.0f, 1.0f, 1.0f, 0.0f),
        Ambient(1.0f)
  {
  }

  void SetColor(const NCollection_Vec3<float>& theColor)
  {

    Ambient.SetValues(theColor * 0.25f, Ambient.a());
    Diffuse.SetValues(theColor, Diffuse.a());
  }
};

struct OpenGl_MaterialPBR
{

  NCollection_Vec4<float> BaseColor;

  NCollection_Vec4<float> EmissionIOR;

  NCollection_Vec4<float> Params;

  float Metallic() const { return Params.b(); }

  float& ChangeMetallic() { return Params.b(); }

  float Roughness() const { return Params.g(); }

  float& ChangeRoughness() { return Params.g(); }

  OpenGl_MaterialPBR()
      : BaseColor(1.0f),
        EmissionIOR(1.0f),
        Params(1.0f, 1.0f, 1.0f, 1.0f)
  {
  }

  void SetColor(const NCollection_Vec3<float>& theColor)
  {
    BaseColor.SetValues(theColor, BaseColor.a());
  }
};

struct OpenGl_Material
{
  OpenGl_MaterialCommon Common[2];
  OpenGl_MaterialPBR    Pbr[2];

  void SetColor(const NCollection_Vec3<float>& theColor)
  {
    Common[0].SetColor(theColor);
    Common[1].SetColor(theColor);
    Pbr[0].SetColor(theColor);
    Pbr[1].SetColor(theColor);
  }

  void Init(const OpenGl_Context&           theCtx,
            const Graphic3d_MaterialAspect& theFront,
            const Quantity_Color&           theFrontColor,
            const Graphic3d_MaterialAspect& theBack,
            const Quantity_Color&           theBackColor);

  bool IsEqual(const OpenGl_Material& theOther) const
  {
    return std::memcmp(this, &theOther, sizeof(OpenGl_Material)) == 0;
  }

  bool operator==(const OpenGl_Material& theOther) { return IsEqual(theOther); }

  bool operator==(const OpenGl_Material& theOther) const { return IsEqual(theOther); }

  bool operator!=(const OpenGl_Material& theOther) { return !IsEqual(theOther); }

  bool operator!=(const OpenGl_Material& theOther) const { return !IsEqual(theOther); }

  const NCollection_Vec4<float>* PackedCommon() const
  {
    return reinterpret_cast<const NCollection_Vec4<float>*>(Common);
  }

  static int NbOfVec4Common() { return 4 * 2; }

  const NCollection_Vec4<float>* PackedPbr() const
  {
    return reinterpret_cast<const NCollection_Vec4<float>*>(Pbr);
  }

  static int NbOfVec4Pbr() { return 3 * 2; }

private:
  void init(const OpenGl_Context&           theCtx,
            const Graphic3d_MaterialAspect& theMat,
            const Quantity_Color&           theColor,
            const int                       theIndex);
};

enum OpenGl_MaterialFlag
{
  OpenGl_MaterialFlag_Front,
  OpenGl_MaterialFlag_Back
};
