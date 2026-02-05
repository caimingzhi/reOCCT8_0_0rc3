#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <IGESGraph_TextFontDef.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_TextDisplayTemplate, IGESData_IGESEntity)

IGESGraph_TextDisplayTemplate::IGESGraph_TextDisplayTemplate() = default;

void IGESGraph_TextDisplayTemplate::Init(const double                              aWidth,
                                         const double                              aHeight,
                                         const int                                 aFontCode,
                                         const occ::handle<IGESGraph_TextFontDef>& aFontEntity,
                                         const double                              aSlantAngle,
                                         const double                              aRotationAngle,
                                         const int                                 aMirrorFlag,
                                         const int                                 aRotationFlag,
                                         const gp_XYZ&                             aCorner)
{
  theBoxWidth      = aWidth;
  theBoxHeight     = aHeight;
  theFontCode      = aFontCode;
  theFontEntity    = aFontEntity;
  theSlantAngle    = aSlantAngle;
  theRotationAngle = aRotationAngle;
  theMirrorFlag    = aMirrorFlag;
  theRotateFlag    = aRotationFlag;
  theCorner        = aCorner;
  InitTypeAndForm(312, FormNumber()); // FormNumber 0-1 : Incremental status
}

void IGESGraph_TextDisplayTemplate::SetIncremental(const bool F)
{
  InitTypeAndForm(312, (F ? 1 : 0));
}

double IGESGraph_TextDisplayTemplate::BoxWidth() const
{
  return theBoxWidth;
}

double IGESGraph_TextDisplayTemplate::BoxHeight() const
{
  return theBoxHeight;
}

bool IGESGraph_TextDisplayTemplate::IsFontEntity() const
{
  return (!theFontEntity.IsNull());
}

int IGESGraph_TextDisplayTemplate::FontCode() const
{
  return theFontCode;
}

occ::handle<IGESGraph_TextFontDef> IGESGraph_TextDisplayTemplate::FontEntity() const
{
  return theFontEntity;
}

double IGESGraph_TextDisplayTemplate::SlantAngle() const
{
  return theSlantAngle;
}

double IGESGraph_TextDisplayTemplate::RotationAngle() const
{
  return theRotationAngle;
}

int IGESGraph_TextDisplayTemplate::MirrorFlag() const
{
  return theMirrorFlag;
}

int IGESGraph_TextDisplayTemplate::RotateFlag() const
{
  return theRotateFlag;
}

bool IGESGraph_TextDisplayTemplate::IsIncremental() const
{
  return (FormNumber() == 1);
}

gp_Pnt IGESGraph_TextDisplayTemplate::StartingCorner() const
{
  return (gp_Pnt(theCorner));
}

gp_Pnt IGESGraph_TextDisplayTemplate::TransformedStartingCorner() const
{
  gp_XYZ TempXYZ = theCorner;
  if (HasTransf())
    Location().Transforms(TempXYZ);
  return (gp_Pnt(TempXYZ));
}
