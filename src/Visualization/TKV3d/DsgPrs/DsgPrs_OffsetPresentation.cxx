#include <DsgPrs_OffsetPresentation.hpp>

#include <ElCLib.hpp>
#include <gce_MakeLin.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_ArrayOfPoints.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <Graphic3d_Group.hpp>
#include <Precision.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_OffsetPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                    const occ::handle<Prs3d_Drawer>&       aDrawer,
                                    const TCollection_ExtendedString&      aText,
                                    const gp_Pnt&                          AttachmentPoint1,
                                    const gp_Pnt&                          AttachmentPoint2,
                                    const gp_Dir&                          aDirection,
                                    const gp_Dir&                          aDirection2,
                                    const gp_Pnt&                          OffsetPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Lin L1(AttachmentPoint1, aDirection);
  gp_Lin L2(AttachmentPoint2, aDirection2);
  gp_Pnt Proj1 = ElCLib::Value(ElCLib::Parameter(L1, OffsetPoint), L1);
  gp_Pnt Proj2 = ElCLib::Value(ElCLib::Parameter(L2, OffsetPoint), L2);
  gp_Lin L3, L4;
  bool   DimNulle = false;
  if (!Proj1.IsEqual(Proj2, Precision::Confusion() * 100.))
  {
    L3 = gce_MakeLin(Proj1, Proj2);
  }
  else
  {

    DimNulle = true;
    L3       = gp_Lin(Proj1, aDirection);
    gp_Vec v4(Proj1, OffsetPoint);
    gp_Dir d4(v4);
    L4 = gp_Lin(Proj1, d4);
  }
  double parmin, parmax, parcur;
  parmin      = ElCLib::Parameter(L3, Proj1);
  parmax      = parmin;
  parcur      = ElCLib::Parameter(L3, Proj2);
  double dist = std::abs(parmin - parcur);
  if (parcur < parmin)
    parmin = parcur;
  if (parcur > parmax)
    parmax = parcur;
  parcur      = ElCLib::Parameter(L3, OffsetPoint);
  gp_Pnt offp = ElCLib::Value(parcur, L3);

  bool outside = false;
  if (parcur < parmin)
  {
    parmin  = parcur;
    outside = true;
  }
  if (parcur > parmax)
  {
    parmax  = parcur;
    outside = true;
  }

  gp_Pnt PointMin = ElCLib::Value(parmin, L3);
  gp_Pnt PointMax = ElCLib::Value(parmax, L3);

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(6);
  aPrims->AddVertex(PointMin);
  aPrims->AddVertex(PointMax);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  if (DimNulle)
  {
    Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                      offp,
                      L4.Direction(),
                      LA->ArrowAspect()->Angle(),
                      LA->ArrowAspect()->Length());
    Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                      offp,
                      L4.Direction().Reversed(),
                      LA->ArrowAspect()->Angle(),
                      LA->ArrowAspect()->Length());
  }
  else
  {
    if (dist < (LA->ArrowAspect()->Length() + LA->ArrowAspect()->Length()))
      outside = true;
    gp_Dir arrdir = L3.Direction().Reversed();
    if (outside)
      arrdir.Reverse();

    Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                      Proj1,
                      arrdir,
                      LA->ArrowAspect()->Angle(),
                      LA->ArrowAspect()->Length());

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    Quantity_Color                        aColor = LA->LineAspect()->Aspect()->Color();
    occ::handle<Graphic3d_AspectMarker3d> aMarkerAsp =
      new Graphic3d_AspectMarker3d(Aspect_TOM_O, aColor, 1.0);
    aPresentation->CurrentGroup()->SetPrimitivesAspect(aMarkerAsp);
    occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints = new Graphic3d_ArrayOfPoints(1);
    anArrayOfPoints->AddVertex(Proj2.X(), Proj2.Y(), Proj2.Z());
    aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints);

    aPresentation->NewGroup();

    Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, offp);
  }

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  aPrims->AddVertex(AttachmentPoint1);
  aPrims->AddVertex(Proj1);

  aPrims->AddVertex(AttachmentPoint2);
  aPrims->AddVertex(Proj2);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
}

void DsgPrs_OffsetPresentation::AddAxes(const occ::handle<Prs3d_Presentation>& aPresentation,
                                        const occ::handle<Prs3d_Drawer>&       aDrawer,
                                        const TCollection_ExtendedString&,
                                        const gp_Pnt& AttachmentPoint1,
                                        const gp_Pnt& AttachmentPoint2,
                                        const gp_Dir& aDirection,
                                        const gp_Dir&,
                                        const gp_Pnt& OffsetPoint)
{
  gp_Lin L1(AttachmentPoint1, aDirection);
  gp_Pnt Proj1 = ElCLib::Value(ElCLib::Parameter(L1, OffsetPoint), L1);

  gp_Lin L2(AttachmentPoint2, aDirection);
  gp_Pnt Proj2 = ElCLib::Value(ElCLib::Parameter(L2, OffsetPoint), L2);

  occ::handle<Prs3d_DimensionAspect> LA     = aDrawer->DimensionAspect();
  Quantity_Color                     acolor = LA->LineAspect()->Aspect()->Color();
  Aspect_TypeOfLine                  atype  = LA->LineAspect()->Aspect()->Type();
  double                             awidth = LA->LineAspect()->Aspect()->Width();

  occ::handle<Graphic3d_AspectLine3d> AxeAsp = new Graphic3d_AspectLine3d(acolor, atype, awidth);
  AxeAsp->SetType(Aspect_TOL_DOTDASH);
  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(AxeAsp);

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(AttachmentPoint1);
  aPrims->AddVertex(Proj1);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  aPresentation->NewGroup();

  occ::handle<Graphic3d_AspectLine3d> Axe2Asp = new Graphic3d_AspectLine3d(acolor, atype, awidth);
  Axe2Asp->SetType(Aspect_TOL_DOTDASH);
  Axe2Asp->SetWidth(4.);
  aPresentation->CurrentGroup()->SetPrimitivesAspect(Axe2Asp);

  aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(AttachmentPoint2);
  aPrims->AddVertex(Proj2);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints = new Graphic3d_ArrayOfPoints(1);
  anArrayOfPoints->AddVertex(Proj2.X(), Proj2.Y(), Proj2.Z());

  aPresentation->NewGroup();
  occ::handle<Graphic3d_AspectMarker3d> MarkerAsp = new Graphic3d_AspectMarker3d();
  MarkerAsp->SetType(Aspect_TOM_O);
  MarkerAsp->SetScale(4.);

  MarkerAsp->SetColor(acolor);
  aPresentation->CurrentGroup()->SetPrimitivesAspect(MarkerAsp);
  aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints);

  aPresentation->NewGroup();
  occ::handle<Graphic3d_AspectMarker3d> Marker2Asp = new Graphic3d_AspectMarker3d();
  Marker2Asp->SetType(Aspect_TOM_O);
  Marker2Asp->SetScale(2.);

  Marker2Asp->SetColor(acolor);
  aPresentation->CurrentGroup()->SetPrimitivesAspect(Marker2Asp);
  aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints);
}
