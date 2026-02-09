#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;
class TCollection_HAsciiString;

class IGESDimen_NewGeneralNote : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_NewGeneralNote();

  Standard_EXPORT void Init(
    const double                                    width,
    const double                                    height,
    const int                                       justifyCode,
    const gp_XYZ&                                   areaLoc,
    const double                                    areaRotationAngle,
    const gp_XYZ&                                   baseLinePos,
    const double                                    normalInterlineSpace,
    const occ::handle<NCollection_HArray1<int>>&    charDisplays,
    const occ::handle<NCollection_HArray1<double>>& charWidths,
    const occ::handle<NCollection_HArray1<double>>& charHeights,
    const occ::handle<NCollection_HArray1<double>>& interCharSpc,
    const occ::handle<NCollection_HArray1<double>>& interLineSpc,
    const occ::handle<NCollection_HArray1<int>>&    fontStyles,
    const occ::handle<NCollection_HArray1<double>>& charAngles,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>&
                                                                              controlCodeStrings,
    const occ::handle<NCollection_HArray1<int>>&                              nbChars,
    const occ::handle<NCollection_HArray1<double>>&                           boxWidths,
    const occ::handle<NCollection_HArray1<double>>&                           boxHeights,
    const occ::handle<NCollection_HArray1<int>>&                              charSetCodes,
    const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& charSetEntities,
    const occ::handle<NCollection_HArray1<double>>&                           slAngles,
    const occ::handle<NCollection_HArray1<double>>&                           rotAngles,
    const occ::handle<NCollection_HArray1<int>>&                              mirrorFlags,
    const occ::handle<NCollection_HArray1<int>>&                              rotateFlags,
    const occ::handle<NCollection_HArray1<gp_XYZ>>&                           startPoints,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& texts);

  Standard_EXPORT double TextWidth() const;

  Standard_EXPORT double TextHeight() const;

  Standard_EXPORT int JustifyCode() const;

  Standard_EXPORT gp_Pnt AreaLocation() const;

  Standard_EXPORT gp_Pnt TransformedAreaLocation() const;

  Standard_EXPORT double ZDepthAreaLocation() const;

  Standard_EXPORT double AreaRotationAngle() const;

  Standard_EXPORT gp_Pnt BaseLinePosition() const;

  Standard_EXPORT gp_Pnt TransformedBaseLinePosition() const;

  Standard_EXPORT double ZDepthBaseLinePosition() const;

  Standard_EXPORT double NormalInterlineSpace() const;

  Standard_EXPORT int NbStrings() const;

  Standard_EXPORT int CharacterDisplay(const int Index) const;

  Standard_EXPORT bool IsVariable(const int Index) const;

  Standard_EXPORT double CharacterWidth(const int Index) const;

  Standard_EXPORT double CharacterHeight(const int Index) const;

  Standard_EXPORT double InterCharacterSpace(const int Index) const;

  Standard_EXPORT double InterlineSpace(const int Index) const;

  Standard_EXPORT int FontStyle(const int Index) const;

  Standard_EXPORT double CharacterAngle(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ControlCodeString(const int Index) const;

  Standard_EXPORT int NbCharacters(const int Index) const;

  Standard_EXPORT double BoxWidth(const int Index) const;

  Standard_EXPORT double BoxHeight(const int Index) const;

  Standard_EXPORT bool IsCharSetEntity(const int Index) const;

  Standard_EXPORT int CharSetCode(const int Index) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> CharSetEntity(const int Index) const;

  Standard_EXPORT double SlantAngle(const int Index) const;

  Standard_EXPORT double RotationAngle(const int Index) const;

  Standard_EXPORT int MirrorFlag(const int Index) const;

  Standard_EXPORT bool IsMirrored(const int Index) const;

  Standard_EXPORT int RotateFlag(const int Index) const;

  Standard_EXPORT gp_Pnt StartPoint(const int Index) const;

  Standard_EXPORT gp_Pnt TransformedStartPoint(const int Index) const;

  Standard_EXPORT double ZDepthStartPoint(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Text(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_NewGeneralNote, IGESData_IGESEntity)

private:
  double                                                                  theWidth;
  double                                                                  theHeight;
  int                                                                     theJustifyCode;
  gp_XYZ                                                                  theAreaLoc;
  double                                                                  theAreaRotationAngle;
  gp_XYZ                                                                  theBaseLinePos;
  double                                                                  theNormalInterlineSpace;
  occ::handle<NCollection_HArray1<int>>                                   theCharDisplays;
  occ::handle<NCollection_HArray1<double>>                                theCharWidths;
  occ::handle<NCollection_HArray1<double>>                                theCharHeights;
  occ::handle<NCollection_HArray1<double>>                                theInterCharSpaces;
  occ::handle<NCollection_HArray1<double>>                                theInterlineSpaces;
  occ::handle<NCollection_HArray1<int>>                                   theFontStyles;
  occ::handle<NCollection_HArray1<double>>                                theCharAngles;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theControlCodeStrings;
  occ::handle<NCollection_HArray1<int>>                                   theNbChars;
  occ::handle<NCollection_HArray1<double>>                                theBoxWidths;
  occ::handle<NCollection_HArray1<double>>                                theBoxHeights;
  occ::handle<NCollection_HArray1<int>>                                   theCharSetCodes;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>      theCharSetEntities;
  occ::handle<NCollection_HArray1<double>>                                theSlantAngles;
  occ::handle<NCollection_HArray1<double>>                                theRotationAngles;
  occ::handle<NCollection_HArray1<int>>                                   theMirrorFlags;
  occ::handle<NCollection_HArray1<int>>                                   theRotateFlags;
  occ::handle<NCollection_HArray1<gp_XYZ>>                                theStartPoints;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theTexts;
};
