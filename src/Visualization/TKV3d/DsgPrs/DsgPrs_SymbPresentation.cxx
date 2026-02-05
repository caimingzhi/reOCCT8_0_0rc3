#include <DsgPrs_SymbPresentation.hpp>
#include <Geom_CartesianPoint.hpp>
#include <gp_Pnt.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <Prs3d_TextAspect.hpp>
#include <StdPrs_Point.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_SymbPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_Drawer>&       aDrawer,
                                  const TCollection_ExtendedString&      aText,
                                  const gp_Pnt&                          OffsetPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  occ::handle<Prs3d_TextAspect>      TA = LA->TextAspect();
  TA->SetColor(Quantity_NOC_GREEN);
  Prs3d_Text::Draw(aPresentation->CurrentGroup(), TA, aText, OffsetPoint);

  // 2eme groupe : marker
  occ::handle<Geom_CartesianPoint> theP = new Geom_CartesianPoint(OffsetPoint);
  occ::handle<Prs3d_PointAspect>   PA   = aDrawer->PointAspect();
  PA->SetTypeOfMarker(Aspect_TOM_RING2);
  StdPrs_Point::Add(aPresentation, theP, aDrawer);
}
