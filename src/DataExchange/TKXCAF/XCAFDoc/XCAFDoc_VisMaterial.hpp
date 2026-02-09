#pragma once

#include <Graphic3d_AlphaMode.hpp>
#include <Graphic3d_TypeOfBackfacingModel.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_VisMaterialCommon.hpp>

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <Image_Texture.hpp>
#include <Quantity_ColorRGBA.hpp>
#include <Standard_Dump.hpp>

struct XCAFDoc_VisMaterialPBR
{
  occ::handle<Image_Texture> BaseColorTexture;

  occ::handle<Image_Texture> MetallicRoughnessTexture;
  occ::handle<Image_Texture> EmissiveTexture;
  occ::handle<Image_Texture> OcclusionTexture;
  occ::handle<Image_Texture> NormalTexture;
  Quantity_ColorRGBA         BaseColor;
  NCollection_Vec3<float>    EmissiveFactor;
  float                      Metallic;
  float                      Roughness;
  float                      RefractionIndex;

  bool IsDefined;

  XCAFDoc_VisMaterialPBR()
      : BaseColor(1.0f, 1.0f, 1.0f, 1.0f),
        EmissiveFactor(0.0f, 0.0f, 0.0f),
        Metallic(1.0f),
        Roughness(1.0f),
        RefractionIndex(1.5f),
        IsDefined(true)
  {
  }

  bool IsEqual(const XCAFDoc_VisMaterialPBR& theOther) const
  {
    if (&theOther == this)
    {
      return true;
    }
    else if (theOther.IsDefined != IsDefined)
    {
      return false;
    }
    else if (!IsDefined)
    {
      return true;
    }

    return theOther.BaseColorTexture == BaseColorTexture
           && theOther.MetallicRoughnessTexture == MetallicRoughnessTexture
           && theOther.EmissiveTexture == EmissiveTexture
           && theOther.OcclusionTexture == OcclusionTexture
           && theOther.NormalTexture == NormalTexture && theOther.BaseColor == BaseColor
           && theOther.EmissiveFactor == EmissiveFactor && theOther.Metallic == Metallic
           && theOther.Roughness == Roughness && theOther.RefractionIndex == RefractionIndex;
  }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    OCCT_DUMP_CLASS_BEGIN(theOStream, XCAFDoc_VisMaterialPBR)

    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, BaseColorTexture.get())
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, MetallicRoughnessTexture.get())
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, EmissiveTexture.get())
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, OcclusionTexture.get())
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, NormalTexture.get())

    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &BaseColor)
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &EmissiveFactor)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Metallic)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Roughness)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, RefractionIndex)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsDefined)
  }
};

class Graphic3d_Aspects;
class Graphic3d_MaterialAspect;

class XCAFDoc_VisMaterial : public TDF_Attribute
{
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_VisMaterial, TDF_Attribute)
public:
  Standard_EXPORT static const Standard_GUID& GetID();

public:
  Standard_EXPORT XCAFDoc_VisMaterial();

  bool IsEmpty() const { return !myPbrMat.IsDefined && !myCommonMat.IsDefined; }

  Standard_EXPORT void FillMaterialAspect(Graphic3d_MaterialAspect& theAspect) const;

  Standard_EXPORT void FillAspect(const occ::handle<Graphic3d_Aspects>& theAspect) const;

  bool HasPbrMaterial() const { return myPbrMat.IsDefined; }

  const XCAFDoc_VisMaterialPBR& PbrMaterial() const { return myPbrMat; }

  Standard_EXPORT void SetPbrMaterial(const XCAFDoc_VisMaterialPBR& theMaterial);

  void UnsetPbrMaterial()
  {
    XCAFDoc_VisMaterialPBR anEmpty;
    anEmpty.IsDefined = false;
    SetPbrMaterial(anEmpty);
  }

  bool HasCommonMaterial() const { return myCommonMat.IsDefined; }

  const XCAFDoc_VisMaterialCommon& CommonMaterial() const { return myCommonMat; }

  Standard_EXPORT void SetCommonMaterial(const XCAFDoc_VisMaterialCommon& theMaterial);

  void UnsetCommonMaterial()
  {
    XCAFDoc_VisMaterialCommon anEmpty;
    anEmpty.IsDefined = false;
    SetCommonMaterial(anEmpty);
  }

  Standard_EXPORT Quantity_ColorRGBA BaseColor() const;

  Graphic3d_AlphaMode AlphaMode() const { return myAlphaMode; }

  float AlphaCutOff() const { return myAlphaCutOff; }

  Standard_EXPORT void SetAlphaMode(Graphic3d_AlphaMode theMode, float theCutOff = 0.5f);

  Graphic3d_TypeOfBackfacingModel FaceCulling() const { return myFaceCulling; }

  Standard_EXPORT void SetFaceCulling(Graphic3d_TypeOfBackfacingModel theFaceCulling);

  Standard_DEPRECATED("Deprecated method, FaceCulling() should be used instead")

  bool IsDoubleSided() const
  {
    return myFaceCulling == Graphic3d_TypeOfBackfacingModel_DoubleSided;
  }

  Standard_DEPRECATED("Deprecated method, SetFaceCulling() should be used "
                      "instead")

  void SetDoubleSided(bool theIsDoubleSided)
  {
    SetFaceCulling(theIsDoubleSided ? Graphic3d_TypeOfBackfacingModel_DoubleSided
                                    : Graphic3d_TypeOfBackfacingModel_Auto);
  }

  const occ::handle<TCollection_HAsciiString>& RawName() const { return myRawName; }

  void SetRawName(const occ::handle<TCollection_HAsciiString>& theName) { myRawName = theName; }

  bool IsEqual(const occ::handle<XCAFDoc_VisMaterial>& theOther) const
  {
    if (theOther.get() == this)
    {
      return true;
    }
    return theOther->myFaceCulling == myFaceCulling && theOther->myAlphaCutOff == myAlphaCutOff
           && theOther->myAlphaMode == myAlphaMode && theOther->myCommonMat.IsEqual(myCommonMat)
           && theOther->myPbrMat.IsEqual(myPbrMat);
  }

  Standard_EXPORT XCAFDoc_VisMaterialCommon ConvertToCommonMaterial();

  Standard_EXPORT XCAFDoc_VisMaterialPBR ConvertToPbrMaterial();

public:
  const Standard_GUID& ID() const override { return GetID(); }

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& theWith) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       theInto,
                             const occ::handle<TDF_RelocationTable>& theRelTable) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  occ::handle<TCollection_HAsciiString> myRawName;
  XCAFDoc_VisMaterialPBR                myPbrMat;
  XCAFDoc_VisMaterialCommon             myCommonMat;

  Graphic3d_AlphaMode             myAlphaMode;
  float                           myAlphaCutOff;
  Graphic3d_TypeOfBackfacingModel myFaceCulling;
};
