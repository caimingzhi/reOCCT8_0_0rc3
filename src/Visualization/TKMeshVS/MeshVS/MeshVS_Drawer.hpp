#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <Quantity_Color.hpp>
#include <Graphic3d_MaterialAspect.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
class Quantity_Color;
class Graphic3d_MaterialAspect;
class TCollection_AsciiString;

//! This class provided the common interface to share between classes
//! big set of constants affecting to object appearance. By default, this class
//! can store integers, doubles, OCC colors, OCC materials. Each of OCC enum members
//! can be stored as integers.
class MeshVS_Drawer : public Standard_Transient
{

public:
  //! This method copies other drawer contents to this.
  Standard_EXPORT virtual void Assign(const occ::handle<MeshVS_Drawer>& aDrawer);

  Standard_EXPORT void SetInteger(const int Key, const int Value);

  Standard_EXPORT void SetDouble(const int Key, const double Value);

  Standard_EXPORT void SetBoolean(const int Key, const bool Value);

  Standard_EXPORT void SetColor(const int Key, const Quantity_Color& Value);

  Standard_EXPORT void SetMaterial(const int Key, const Graphic3d_MaterialAspect& Value);

  Standard_EXPORT void SetAsciiString(const int Key, const TCollection_AsciiString& Value);

  Standard_EXPORT bool GetInteger(const int Key, int& Value) const;

  Standard_EXPORT bool GetDouble(const int Key, double& Value) const;

  Standard_EXPORT bool GetBoolean(const int Key, bool& Value) const;

  Standard_EXPORT bool GetColor(const int Key, Quantity_Color& Value) const;

  Standard_EXPORT bool GetMaterial(const int Key, Graphic3d_MaterialAspect& Value) const;

  Standard_EXPORT bool GetAsciiString(const int Key, TCollection_AsciiString& Value) const;

  Standard_EXPORT bool RemoveInteger(const int Key);

  Standard_EXPORT bool RemoveDouble(const int Key);

  Standard_EXPORT bool RemoveBoolean(const int Key);

  Standard_EXPORT bool RemoveColor(const int Key);

  Standard_EXPORT bool RemoveMaterial(const int Key);

  Standard_EXPORT bool RemoveAsciiString(const int Key);

  DEFINE_STANDARD_RTTIEXT(MeshVS_Drawer, Standard_Transient)

private:
  NCollection_DataMap<int, int>                      myIntegers;
  NCollection_DataMap<int, bool>                     myBooleans;
  NCollection_DataMap<int, double>                   myDoubles;
  NCollection_DataMap<int, Quantity_Color>           myColors;
  NCollection_DataMap<int, Graphic3d_MaterialAspect> myMaterials;
  NCollection_DataMap<int, TCollection_AsciiString>  myAsciiString;
};

