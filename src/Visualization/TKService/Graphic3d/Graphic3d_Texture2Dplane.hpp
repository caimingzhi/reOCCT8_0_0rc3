#pragma once

#include <Standard.hpp>

enum Graphic3d_NameOfTexturePlane
{
  Graphic3d_NOTP_XY,
  Graphic3d_NOTP_YZ,
  Graphic3d_NOTP_ZX,
  Graphic3d_NOTP_UNKNOWN
};

#include <Graphic3d_Texture2D.hpp>
#include <Graphic3d_NameOfTexture2D.hpp>
class TCollection_AsciiString;

class Graphic3d_Texture2Dplane : public Graphic3d_Texture2D
{

public:
  Standard_EXPORT Graphic3d_Texture2Dplane(const TCollection_AsciiString& theFileName);

  Standard_EXPORT Graphic3d_Texture2Dplane(const Graphic3d_NameOfTexture2D theNOT);

  Standard_EXPORT Graphic3d_Texture2Dplane(const occ::handle<Image_PixMap>& thePixMap);

  Standard_EXPORT void SetPlaneS(const float A, const float B, const float C, const float D);

  Standard_EXPORT void SetPlaneT(const float A, const float B, const float C, const float D);

  Standard_EXPORT void SetPlane(const Graphic3d_NameOfTexturePlane thePlane);

  Standard_EXPORT void SetScaleS(const float theVal);

  Standard_EXPORT void SetScaleT(const float theVal);

  Standard_EXPORT void SetTranslateS(const float theVal);

  Standard_EXPORT void SetTranslateT(const float theVal);

  Standard_EXPORT void SetRotation(const float theVal);

  Standard_EXPORT Graphic3d_NameOfTexturePlane Plane() const;

  Standard_EXPORT void PlaneS(float& A, float& B, float& C, float& D) const;

  Standard_EXPORT void PlaneT(float& A, float& B, float& C, float& D) const;

  Standard_EXPORT void TranslateS(float& theVal) const;

  Standard_EXPORT void TranslateT(float& theVal) const;

  Standard_EXPORT void ScaleS(float& theVal) const;

  Standard_EXPORT void ScaleT(float& theVal) const;

  Standard_EXPORT void Rotation(float& theVal) const;

  DEFINE_STANDARD_RTTIEXT(Graphic3d_Texture2Dplane, Graphic3d_Texture2D)

private:
  Graphic3d_NameOfTexturePlane myPlaneName;
};
