#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <Image_Texture.hpp>
#include <Quantity_ColorRGBA.hpp>
#include <Standard_Dump.hpp>

class Graphic3d_Aspects;
class Graphic3d_MaterialAspect;

struct XCAFDoc_VisMaterialCommon
{
  occ::handle<Image_Texture> DiffuseTexture;
  Quantity_Color             AmbientColor;
  Quantity_Color             DiffuseColor;
  Quantity_Color             SpecularColor;
  Quantity_Color             EmissiveColor;
  float                      Shininess;

  float Transparency;

  bool IsDefined;

  XCAFDoc_VisMaterialCommon()
      : AmbientColor(0.1, 0.1, 0.1, Quantity_TOC_RGB),
        DiffuseColor(0.8, 0.8, 0.8, Quantity_TOC_RGB),
        SpecularColor(0.2, 0.2, 0.2, Quantity_TOC_RGB),
        EmissiveColor(0.0, 0.0, 0.0, Quantity_TOC_RGB),
        Shininess(1.0f),
        Transparency(0.0f),
        IsDefined(true)
  {
  }

  bool IsEqual(const XCAFDoc_VisMaterialCommon& theOther) const
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

    return theOther.DiffuseTexture == DiffuseTexture && theOther.AmbientColor == AmbientColor
           && theOther.DiffuseColor == DiffuseColor && theOther.SpecularColor == SpecularColor
           && theOther.EmissiveColor == EmissiveColor && theOther.Shininess == Shininess
           && theOther.Transparency == Transparency;
  }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    OCCT_DUMP_CLASS_BEGIN(theOStream, XCAFDoc_VisMaterialCommon)

    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, DiffuseTexture.get())

    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &AmbientColor)
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &DiffuseColor)
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &SpecularColor)
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &EmissiveColor)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Shininess)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Transparency)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsDefined)
  }
};
