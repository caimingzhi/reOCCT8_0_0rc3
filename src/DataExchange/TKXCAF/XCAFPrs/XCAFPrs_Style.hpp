#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <XCAFDoc_VisMaterial.hpp>
#include <Standard_HashUtils.hpp>

class XCAFPrs_Style
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XCAFPrs_Style();

  bool IsEmpty() const
  {
    return !myHasColorSurf && !myHasColorCurv && myMaterial.IsNull() && myIsVisible;
  }

  const occ::handle<XCAFDoc_VisMaterial>& Material() const { return myMaterial; }

  void SetMaterial(const occ::handle<XCAFDoc_VisMaterial>& theMaterial)
  {
    myMaterial = theMaterial;
  }

  bool IsSetColorSurf() const { return myHasColorSurf; }

  const Quantity_Color& GetColorSurf() const { return myColorSurf.GetRGB(); }

  void SetColorSurf(const Quantity_Color& theColor) { SetColorSurf(Quantity_ColorRGBA(theColor)); }

  const Quantity_ColorRGBA& GetColorSurfRGBA() const { return myColorSurf; }

  Standard_EXPORT void SetColorSurf(const Quantity_ColorRGBA& theColor);

  Standard_EXPORT void UnSetColorSurf();

  bool IsSetColorCurv() const { return myHasColorCurv; }

  const Quantity_Color& GetColorCurv() const { return myColorCurv; }

  Standard_EXPORT void SetColorCurv(const Quantity_Color& col);

  Standard_EXPORT void UnSetColorCurv();

  void SetVisibility(const bool theVisibility) { myIsVisible = theVisibility; }

  bool IsVisible() const { return myIsVisible; }

  const occ::handle<Image_Texture>& BaseColorTexture() const
  {
    static const occ::handle<Image_Texture> THE_NULL_TEXTURE;
    if (myMaterial.IsNull())
    {
      return THE_NULL_TEXTURE;
    }
    else if (myMaterial->HasPbrMaterial() && !myMaterial->PbrMaterial().BaseColorTexture.IsNull())
    {
      return myMaterial->PbrMaterial().BaseColorTexture;
    }
    else if (myMaterial->HasCommonMaterial()
             && !myMaterial->CommonMaterial().DiffuseTexture.IsNull())
    {
      return myMaterial->CommonMaterial().DiffuseTexture;
    }
    return THE_NULL_TEXTURE;
  }

  bool IsEqual(const XCAFPrs_Style& theOther) const
  {
    if (myIsVisible != theOther.myIsVisible)
    {
      return false;
    }
    else if (!myIsVisible)
    {
      return true;
    }

    return myHasColorSurf == theOther.myHasColorSurf && myHasColorCurv == theOther.myHasColorCurv
           && myMaterial == theOther.myMaterial
           && (!myHasColorSurf || myColorSurf == theOther.myColorSurf)
           && (!myHasColorCurv || myColorCurv == theOther.myColorCurv);
  }

  bool operator==(const XCAFPrs_Style& theOther) const { return IsEqual(theOther); }

  template <class T>
  friend struct std::hash;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  occ::handle<XCAFDoc_VisMaterial> myMaterial;
  Quantity_ColorRGBA               myColorSurf;
  Quantity_Color                   myColorCurv;
  bool                             myHasColorSurf;
  bool                             myHasColorCurv;
  bool                             myIsVisible;
};

namespace std
{
  template <>
  struct hash<XCAFPrs_Style>
  {
    size_t operator()(const XCAFPrs_Style& theStyle) const
    {
      if (!theStyle.myIsVisible)
      {
        return 1;
      }
      size_t aCombination[3];
      int    aCount = 0;
      if (theStyle.myHasColorSurf)
      {
        aCombination[aCount++] = std::hash<Quantity_ColorRGBA>{}(theStyle.myColorSurf);
      }
      if (theStyle.myHasColorCurv)
      {
        aCombination[aCount++] = std::hash<Quantity_Color>{}(theStyle.myColorCurv);
      }
      if (!theStyle.myMaterial.IsNull())
      {
        aCombination[aCount++] = std::hash<occ::handle<XCAFDoc_VisMaterial>>{}(theStyle.myMaterial);
      }
      return aCount > 0 ? opencascade::hashBytes(aCombination, sizeof(size_t) * aCount) : 0;
    }
  };
} // namespace std
