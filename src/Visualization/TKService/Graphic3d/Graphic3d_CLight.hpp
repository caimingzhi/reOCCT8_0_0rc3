#pragma once

#include <gp_Dir.hpp>

enum Graphic3d_TypeOfLightSource
{
  Graphic3d_TypeOfLightSource_Ambient,
  Graphic3d_TypeOfLightSource_Directional,
  Graphic3d_TypeOfLightSource_Positional,
  Graphic3d_TypeOfLightSource_Spot,

  Graphic3d_TOLS_AMBIENT     = Graphic3d_TypeOfLightSource_Ambient,
  Graphic3d_TOLS_DIRECTIONAL = Graphic3d_TypeOfLightSource_Directional,
  Graphic3d_TOLS_POSITIONAL  = Graphic3d_TypeOfLightSource_Positional,
  Graphic3d_TOLS_SPOT        = Graphic3d_TypeOfLightSource_Spot,

  V3d_AMBIENT     = Graphic3d_TypeOfLightSource_Ambient,
  V3d_DIRECTIONAL = Graphic3d_TypeOfLightSource_Directional,
  V3d_POSITIONAL  = Graphic3d_TypeOfLightSource_Positional,
  V3d_SPOT        = Graphic3d_TypeOfLightSource_Spot
};

enum
{

  Graphic3d_TypeOfLightSource_NB = Graphic3d_TypeOfLightSource_Spot + 1
};

#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_List.hpp>
#include <TCollection_AsciiString.hpp>
#include <Quantity_ColorRGBA.hpp>

class Graphic3d_CLight : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CLight, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_CLight(Graphic3d_TypeOfLightSource theType);

  Standard_EXPORT void CopyFrom(const occ::handle<Graphic3d_CLight>& theLight);

  Graphic3d_TypeOfLightSource Type() const { return myType; }

  const TCollection_AsciiString& Name() const { return myName; }

  void SetName(const TCollection_AsciiString& theName) { myName = theName; }

  const Quantity_Color& Color() const { return myColor.GetRGB(); }

  Standard_EXPORT void SetColor(const Quantity_Color& theColor);

  bool IsEnabled() const { return myIsEnabled; }

  Standard_EXPORT void SetEnabled(bool theIsOn);

  bool ToCastShadows() const { return myToCastShadows; }

  Standard_EXPORT void SetCastShadows(bool theToCast);

  bool IsHeadlight() const { return myIsHeadlight; }

  bool Headlight() const { return myIsHeadlight; }

  Standard_EXPORT void SetHeadlight(bool theValue);

public:
  const gp_Pnt& Position() const { return myPosition; }

  Standard_EXPORT void SetPosition(const gp_Pnt& thePosition);

  void Position(double& theX, double& theY, double& theZ) const
  {
    theX = myPosition.X();
    theY = myPosition.Y();
    theZ = myPosition.Z();
  }

  void SetPosition(double theX, double theY, double theZ) { SetPosition(gp_Pnt(theX, theY, theZ)); }

  float ConstAttenuation() const { return myParams.x(); }

  float LinearAttenuation() const { return myParams.y(); }

  void Attenuation(double& theConstAttenuation, double& theLinearAttenuation) const
  {
    theConstAttenuation  = ConstAttenuation();
    theLinearAttenuation = LinearAttenuation();
  }

  Standard_EXPORT void SetAttenuation(float theConstAttenuation, float theLinearAttenuation);

public:
  gp_Dir Direction() const { return gp_Dir(myDirection.x(), myDirection.y(), myDirection.z()); }

  Standard_EXPORT void SetDirection(const gp_Dir& theDir);

  void Direction(double& theVx, double& theVy, double& theVz) const
  {
    theVx = myDirection.x();
    theVy = myDirection.y();
    theVz = myDirection.z();
  }

  void SetDirection(double theVx, double theVy, double theVz)
  {
    SetDirection(gp_Dir(theVx, theVy, theVz));
  }

  const gp_Pnt& DisplayPosition() const { return myPosition; }

  Standard_EXPORT void SetDisplayPosition(const gp_Pnt& thePosition);

public:
  float Angle() const { return myParams.z(); }

  Standard_EXPORT void SetAngle(float theAngle);

  float Concentration() const { return myParams.w(); }

  Standard_EXPORT void SetConcentration(float theConcentration);

public:
  float Intensity() const { return myIntensity; }

  Standard_EXPORT void SetIntensity(float theValue);

  float Smoothness() const { return mySmoothness; }

  Standard_EXPORT void SetSmoothRadius(float theValue);

  Standard_EXPORT void SetSmoothAngle(float theValue);

  bool HasRange() const { return myDirection.w() != 0.0f; }

  float Range() const { return myDirection.w(); }

  Standard_EXPORT void SetRange(float theValue);

public:
  const TCollection_AsciiString& GetId() const { return myId; }

  const NCollection_Vec4<float>& PackedParams() const { return myParams; }

  const NCollection_Vec4<float>& PackedColor() const { return myColor; }

  const NCollection_Vec4<float>& PackedDirectionRange() const { return myDirection; }

  NCollection_Vec3<float> PackedDirection() const { return myDirection.xyz(); }

  size_t Revision() const { return myRevision; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  float& changeConstAttenuation() { return myParams.x(); }

  float& changeLinearAttenuation() { return myParams.y(); }

  float& changeAngle() { return myParams.z(); }

  float& changeConcentration() { return myParams.w(); }

private:
  void makeId();

  void updateRevisionIf(bool theIsModified)
  {
    if (theIsModified)
    {
      ++myRevision;
    }
  }

private:
  Graphic3d_CLight(const Graphic3d_CLight&)            = delete;
  Graphic3d_CLight& operator=(const Graphic3d_CLight&) = delete;

protected:
  TCollection_AsciiString myId;
  TCollection_AsciiString myName;
  gp_Pnt                  myPosition;
  Quantity_ColorRGBA      myColor;
  NCollection_Vec4<float> myDirection;
  NCollection_Vec4<float> myParams;

  float mySmoothness;

  float                             myIntensity;
  const Graphic3d_TypeOfLightSource myType;
  size_t                            myRevision;
  bool                              myIsHeadlight;
  bool                              myIsEnabled;
  bool                              myToCastShadows;
};
