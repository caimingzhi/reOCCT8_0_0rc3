#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESGraph_TextFontDef;
class gp_Pnt;

class IGESGraph_TextDisplayTemplate : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGraph_TextDisplayTemplate();

  Standard_EXPORT void Init(const double                              aWidth,
                            const double                              aHeight,
                            const int                                 aFontCode,
                            const occ::handle<IGESGraph_TextFontDef>& aFontEntity,
                            const double                              aSlantAngle,
                            const double                              aRotationAngle,
                            const int                                 aMirrorFlag,
                            const int                                 aRotationFlag,
                            const gp_XYZ&                             aCorner);

  Standard_EXPORT void SetIncremental(const bool mode);

  Standard_EXPORT bool IsIncremental() const;

  Standard_EXPORT double BoxWidth() const;

  Standard_EXPORT double BoxHeight() const;

  Standard_EXPORT bool IsFontEntity() const;

  Standard_EXPORT int FontCode() const;

  Standard_EXPORT occ::handle<IGESGraph_TextFontDef> FontEntity() const;

  Standard_EXPORT double SlantAngle() const;

  Standard_EXPORT double RotationAngle() const;

  Standard_EXPORT int MirrorFlag() const;

  Standard_EXPORT int RotateFlag() const;

  Standard_EXPORT gp_Pnt StartingCorner() const;

  Standard_EXPORT gp_Pnt TransformedStartingCorner() const;

  DEFINE_STANDARD_RTTIEXT(IGESGraph_TextDisplayTemplate, IGESData_IGESEntity)

private:
  double                             theBoxWidth;
  double                             theBoxHeight;
  int                                theFontCode;
  occ::handle<IGESGraph_TextFontDef> theFontEntity;
  double                             theSlantAngle;
  double                             theRotationAngle;
  int                                theMirrorFlag;
  int                                theRotateFlag;
  gp_XYZ                             theCorner;
};
