#include <DsgPrs.hpp>
#include <DsgPrs_ParalPresentation.hpp>
#include <ElCLib.hpp>
#include <gce_MakeLin.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_ParalPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                   const occ::handle<Prs3d_Drawer>&       aDrawer,
                                   const TCollection_ExtendedString&      aText,
                                   const gp_Pnt&                          AttachmentPoint1,
                                   const gp_Pnt&                          AttachmentPoint2,
                                   const gp_Dir&                          aDirection,
                                   const gp_Pnt&                          OffsetPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
  gp_Lin L1(AttachmentPoint1, aDirection);
  gp_Lin L2(AttachmentPoint2, aDirection);
  gp_Pnt Proj1 = ElCLib::Value(ElCLib::Parameter(L1, OffsetPoint), L1);
  gp_Pnt Proj2 = ElCLib::Value(ElCLib::Parameter(L2, OffsetPoint), L2);
  gp_Lin L3    = gce_MakeLin(Proj1, Proj2);
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

  // processing of side : 1st group
  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(6);
  aPrims->AddVertex(PointMin);
  aPrims->AddVertex(PointMax);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  if (dist < (LA->ArrowAspect()->Length() + LA->ArrowAspect()->Length()))
    outside = true;
  gp_Dir arrdir = L3.Direction().Reversed();
  if (outside)
    arrdir.Reverse();

  // arrow 1 : 2nd group
  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    Proj1,
                    arrdir,
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  // arrow 2 : 3rd group
  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    Proj2,
                    arrdir.Reversed(),
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  aPresentation->NewGroup();

  // text : 4th group
  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, offp);

  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  // processing of call 1 : 5th group
  aPrims->AddVertex(AttachmentPoint1);
  aPrims->AddVertex(Proj1);

  // processing of call 2 : 6th group
  aPrims->AddVertex(AttachmentPoint2);
  aPrims->AddVertex(Proj2);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
}

//==========================================================================
// function : DsgPrs_ParalPresentation::Add
// purpose  : it is possible to choose the symbol of extremities of the face (arrow, point...)
//==========================================================================
void DsgPrs_ParalPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                   const occ::handle<Prs3d_Drawer>&       aDrawer,
                                   const TCollection_ExtendedString&      aText,
                                   const gp_Pnt&                          AttachmentPoint1,
                                   const gp_Pnt&                          AttachmentPoint2,
                                   const gp_Dir&                          aDirection,
                                   const gp_Pnt&                          OffsetPoint,
                                   const DsgPrs_ArrowSide                 ArrowPrs)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Lin L1(AttachmentPoint1, aDirection);
  gp_Lin L2(AttachmentPoint2, aDirection);
  gp_Pnt Proj1 = ElCLib::Value(ElCLib::Parameter(L1, OffsetPoint), L1);
  gp_Pnt Proj2 = ElCLib::Value(ElCLib::Parameter(L2, OffsetPoint), L2);
  gp_Lin L3    = gce_MakeLin(Proj1, Proj2);
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

  // processing of face
  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(6);
  aPrims->AddVertex(PointMin);
  aPrims->AddVertex(PointMax);

  if (dist < (LA->ArrowAspect()->Length() + LA->ArrowAspect()->Length()))
    outside = true;
  gp_Dir arrdir = L3.Direction().Reversed();
  if (outside)
    arrdir.Reverse();

  // processing of call 1
  aPrims->AddVertex(AttachmentPoint1);
  aPrims->AddVertex(Proj1);

  // processing of call 2
  aPrims->AddVertex(AttachmentPoint2);
  aPrims->AddVertex(Proj2);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  // text
  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, offp);

  // arrows
  DsgPrs::ComputeSymbol(aPresentation, LA, Proj1, Proj2, arrdir, arrdir.Reversed(), ArrowPrs);
}
