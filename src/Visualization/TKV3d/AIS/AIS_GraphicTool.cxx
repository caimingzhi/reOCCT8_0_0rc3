#include <AIS_GraphicTool.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_MaterialAspect.hpp>
#include <Prs3d_DatumAspect.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_IsoAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_PlaneAspect.hpp>
#include <Prs3d_ShadingAspect.hpp>
#include <Quantity_Color.hpp>

static occ::handle<Prs3d_LineAspect> GetLineAspect(const occ::handle<Prs3d_Drawer>& Dr,
                                                   const AIS_TypeOfAttribute        Att)
{
  switch (Att)
  {
    case AIS_TOA_Line:
      return Dr->LineAspect();
    case AIS_TOA_Dimension:
      return Dr->DimensionAspect()->LineAspect();
    case AIS_TOA_Wire:
      return Dr->WireAspect();
    case AIS_TOA_Plane:
      return Dr->PlaneAspect()->EdgesAspect();
    case AIS_TOA_Vector:
      return Dr->VectorAspect();
    case AIS_TOA_UIso:
      return occ::handle<Prs3d_LineAspect>(Dr->UIsoAspect());
    case AIS_TOA_VIso:
      return occ::handle<Prs3d_LineAspect>(Dr->VIsoAspect());
    case AIS_TOA_Free:
      return Dr->FreeBoundaryAspect();
    case AIS_TOA_UnFree:
      return Dr->UnFreeBoundaryAspect();
    case AIS_TOA_Section:
      return Dr->SectionAspect();
    case AIS_TOA_Hidden:
      return Dr->HiddenLineAspect();
    case AIS_TOA_Seen:
      return Dr->SeenLineAspect();
    case AIS_TOA_FaceBoundary:
      return Dr->FaceBoundaryAspect();
    case AIS_TOA_FirstAxis:
      return Dr->DatumAspect()->LineAspect(Prs3d_DatumParts_XAxis);
    case AIS_TOA_SecondAxis:
      return Dr->DatumAspect()->LineAspect(Prs3d_DatumParts_YAxis);
    case AIS_TOA_ThirdAxis:
      return Dr->DatumAspect()->LineAspect(Prs3d_DatumParts_ZAxis);
  }
  occ::handle<Prs3d_LineAspect> bid;
  return bid;
}

Quantity_NameOfColor AIS_GraphicTool::GetLineColor(const occ::handle<Prs3d_Drawer>& Dr,
                                                   const AIS_TypeOfAttribute        Att)
{
  Quantity_Color color;
  GetLineColor(Dr, Att, color);
  return color.Name();
}

void AIS_GraphicTool::GetLineColor(const occ::handle<Prs3d_Drawer>& Dr,
                                   const AIS_TypeOfAttribute        Att,
                                   Quantity_Color&                  aColor)
{
  aColor = GetLineAspect(Dr, Att)->Aspect()->Color();
}

double AIS_GraphicTool::GetLineWidth(const occ::handle<Prs3d_Drawer>& Dr,
                                     const AIS_TypeOfAttribute        Att)
{
  occ::handle<Prs3d_LineAspect> LA = GetLineAspect(Dr, Att);
  return LA->Aspect()->Width();
}

Aspect_TypeOfLine AIS_GraphicTool::GetLineType(const occ::handle<Prs3d_Drawer>& Dr,
                                               const AIS_TypeOfAttribute        Att)
{
  occ::handle<Prs3d_LineAspect> LA = GetLineAspect(Dr, Att);
  return LA->Aspect()->Type();
}

void AIS_GraphicTool::GetLineAtt(const occ::handle<Prs3d_Drawer>& Dr,
                                 const AIS_TypeOfAttribute        Att,
                                 Quantity_NameOfColor&            Col,
                                 double&                          W,
                                 Aspect_TypeOfLine&               TYP)
{
  occ::handle<Prs3d_LineAspect> LA = GetLineAspect(Dr, Att);
  Col                              = LA->Aspect()->Color().Name();
  W                                = LA->Aspect()->Width();
  TYP                              = LA->Aspect()->Type();
}

Quantity_NameOfColor AIS_GraphicTool::GetInteriorColor(const occ::handle<Prs3d_Drawer>& Dr)
{
  Quantity_Color color;
  GetInteriorColor(Dr, color);
  return color.Name();
}

void AIS_GraphicTool::GetInteriorColor(const occ::handle<Prs3d_Drawer>& Dr, Quantity_Color& aColor)
{
  occ::handle<Graphic3d_AspectFillArea3d> AFA = Dr->ShadingAspect()->Aspect();
  aColor                                      = AFA->InteriorColor();
}

Graphic3d_MaterialAspect AIS_GraphicTool::GetMaterial(const occ::handle<Prs3d_Drawer>& Dr)
{
  return Dr->ShadingAspect()->Aspect()->BackMaterial();
}
