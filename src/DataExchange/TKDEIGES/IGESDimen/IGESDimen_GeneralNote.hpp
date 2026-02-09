#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESGraph_TextFontDef.hpp>
#include <gp_XYZ.hpp>
#include <TCollection_HAsciiString.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESGraph_TextFontDef;
class gp_Pnt;
class TCollection_HAsciiString;

class IGESDimen_GeneralNote : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_GeneralNote();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<int>>&                                   nbChars,
    const occ::handle<NCollection_HArray1<double>>&                                widths,
    const occ::handle<NCollection_HArray1<double>>&                                heights,
    const occ::handle<NCollection_HArray1<int>>&                                   fontCodes,
    const occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextFontDef>>>&    fonts,
    const occ::handle<NCollection_HArray1<double>>&                                slants,
    const occ::handle<NCollection_HArray1<double>>&                                rotations,
    const occ::handle<NCollection_HArray1<int>>&                                   mirrorFlags,
    const occ::handle<NCollection_HArray1<int>>&                                   rotFlags,
    const occ::handle<NCollection_HArray1<gp_XYZ>>&                                start,
    const occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& texts);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT int NbStrings() const;

  Standard_EXPORT int NbCharacters(const int Index) const;

  Standard_EXPORT double BoxWidth(const int Index) const;

  Standard_EXPORT double BoxHeight(const int Index) const;

  Standard_EXPORT bool IsFontEntity(const int Index) const;

  Standard_EXPORT int FontCode(const int Index) const;

  Standard_EXPORT occ::handle<IGESGraph_TextFontDef> FontEntity(const int Index) const;

  Standard_EXPORT double SlantAngle(const int Index) const;

  Standard_EXPORT double RotationAngle(const int Index) const;

  Standard_EXPORT int MirrorFlag(const int Index) const;

  Standard_EXPORT int RotateFlag(const int Index) const;

  Standard_EXPORT gp_Pnt StartPoint(const int Index) const;

  Standard_EXPORT gp_Pnt TransformedStartPoint(const int Index) const;

  Standard_EXPORT double ZDepthStartPoint(const int Index) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Text(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_GeneralNote, IGESData_IGESEntity)

private:
  occ::handle<NCollection_HArray1<int>>                                   theNbChars;
  occ::handle<NCollection_HArray1<double>>                                theBoxWidths;
  occ::handle<NCollection_HArray1<double>>                                theBoxHeights;
  occ::handle<NCollection_HArray1<int>>                                   theFontCodes;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextFontDef>>>    theFontEntities;
  occ::handle<NCollection_HArray1<double>>                                theSlantAngles;
  occ::handle<NCollection_HArray1<double>>                                theRotationAngles;
  occ::handle<NCollection_HArray1<int>>                                   theMirrorFlags;
  occ::handle<NCollection_HArray1<int>>                                   theRotateFlags;
  occ::handle<NCollection_HArray1<gp_XYZ>>                                theStartPoints;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> theTexts;
};
