#include <DsgPrs_FixPresentation.hpp>

#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfPoints.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>

//=================================================================================================

void DsgPrs_FixPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                 const occ::handle<Prs3d_Drawer>&       aDrawer,
                                 const gp_Pnt&                          aPntAttach,
                                 const gp_Pnt&                          aPntEnd,
                                 const gp_Dir&                          aNormPln,
                                 const double                           symbsize)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(10);

  // Trace du segment de raccordement
  aPrims->AddVertex(aPntAttach);
  aPrims->AddVertex(aPntEnd);

  // trace du symbole 'Fix'
  gp_Vec dirac(aPntAttach, aPntEnd); // vecteur directeur du seg. de raccord
  dirac.Normalize();
  gp_Vec norac = dirac.Crossed(gp_Vec(aNormPln));
  gp_Ax1 ax(aPntEnd, aNormPln);
  norac.Rotate(ax, M_PI / 8); // vecteur normal au seg. de raccord
  norac *= (symbsize / 2);
  gp_Pnt P1 = aPntEnd.Translated(norac);
  gp_Pnt P2 = aPntEnd.Translated(-norac);

  aPrims->AddVertex(P1);
  aPrims->AddVertex(P2);

  // trace des 'dents'
  norac *= 0.8;
  P1 = aPntEnd.Translated(norac);
  P2 = aPntEnd.Translated(-norac);
  dirac *= (symbsize / 2);
  gp_Pnt PF = P1;
  gp_Pnt PL = PF.Translated(dirac);
  PL.Translate(norac);

  aPrims->AddVertex(PF);
  aPrims->AddVertex(PL);

  PF = P2;
  PL = PF.Translated(dirac);
  PL.Translate(norac);

  aPrims->AddVertex(PF);
  aPrims->AddVertex(PL);

  PF.SetXYZ(0.5 * (P1.XYZ() + P2.XYZ()));
  PL = PF.Translated(dirac);
  PL.Translate(norac);

  aPrims->AddVertex(PF);
  aPrims->AddVertex(PL);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
  Quantity_Color                        aColor = LA->LineAspect()->Aspect()->Color();
  occ::handle<Graphic3d_AspectMarker3d> aMarkerAsp =
    new Graphic3d_AspectMarker3d(Aspect_TOM_O, aColor, 1.0);
  aPresentation->CurrentGroup()->SetPrimitivesAspect(aMarkerAsp);
  occ::handle<Graphic3d_ArrayOfPoints> anArrayOfPoints = new Graphic3d_ArrayOfPoints(1);
  anArrayOfPoints->AddVertex(aPntAttach.X(), aPntAttach.Y(), aPntAttach.Z());
  aPresentation->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints);
}
