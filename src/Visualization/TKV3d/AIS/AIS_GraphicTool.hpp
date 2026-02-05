#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Drawer.hpp>

enum AIS_TypeOfAttribute
{
  AIS_TOA_Line,
  AIS_TOA_Dimension,
  AIS_TOA_Wire,
  AIS_TOA_Plane,
  AIS_TOA_Vector,
  AIS_TOA_UIso,
  AIS_TOA_VIso,
  AIS_TOA_Free,
  AIS_TOA_UnFree,
  AIS_TOA_Section,
  AIS_TOA_Hidden,
  AIS_TOA_Seen,
  AIS_TOA_FaceBoundary,
  AIS_TOA_FirstAxis,
  AIS_TOA_SecondAxis,
  AIS_TOA_ThirdAxis
};

#include <Standard_Real.hpp>
#include <Aspect_TypeOfLine.hpp>
class Quantity_Color;
class Graphic3d_MaterialAspect;

class AIS_GraphicTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static Quantity_NameOfColor GetLineColor(
    const occ::handle<Prs3d_Drawer>& aDrawer,
    const AIS_TypeOfAttribute        TheTypeOfAttributes);

  Standard_EXPORT static void GetLineColor(const occ::handle<Prs3d_Drawer>& aDrawer,
                                           const AIS_TypeOfAttribute        TheTypeOfAttributes,
                                           Quantity_Color&                  TheLineColor);

  Standard_EXPORT static double GetLineWidth(const occ::handle<Prs3d_Drawer>& aDrawer,
                                             const AIS_TypeOfAttribute        TheTypeOfAttributes);

  Standard_EXPORT static Aspect_TypeOfLine GetLineType(
    const occ::handle<Prs3d_Drawer>& aDrawer,
    const AIS_TypeOfAttribute        TheTypeOfAttributes);

  Standard_EXPORT static void GetLineAtt(const occ::handle<Prs3d_Drawer>& aDrawer,
                                         const AIS_TypeOfAttribute        TheTypeOfAttributes,
                                         Quantity_NameOfColor&            aCol,
                                         double&                          aWidth,
                                         Aspect_TypeOfLine&               aTyp);

  Standard_EXPORT static Quantity_NameOfColor GetInteriorColor(
    const occ::handle<Prs3d_Drawer>& aDrawer);

  Standard_EXPORT static void GetInteriorColor(const occ::handle<Prs3d_Drawer>& aDrawer,
                                               Quantity_Color&                  aColor);

  Standard_EXPORT static Graphic3d_MaterialAspect GetMaterial(
    const occ::handle<Prs3d_Drawer>& aDrawer);
};
