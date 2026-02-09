#include <DsgPrs_IdenticPresentation.hpp>
#include <ElCLib.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfPoints.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <Graphic3d_Group.hpp>
#include <Precision.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_IdenticPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const TCollection_ExtendedString&      aText,
                                     const gp_Pnt&                          aPntAttach,
                                     const gp_Pnt&                          aPntOffset)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(aPntAttach);
  aPrims->AddVertex(aPntOffset);
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

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntOffset);
}

void DsgPrs_IdenticPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const TCollection_ExtendedString&      aText,
                                     const gp_Pnt&                          aFAttach,
                                     const gp_Pnt&                          aSAttach,
                                     const gp_Pnt&                          aPntOffset)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(4);

  aPrims->AddVertex(aFAttach);
  aPrims->AddVertex(aSAttach);

  gp_Vec v1(aFAttach, aSAttach);
  gp_Vec v2(aSAttach, aPntOffset);

  aPrims->AddVertex(aPntOffset);
  if (!v1.IsParallel(v2, Precision::Angular()))
  {

    gp_Lin ll(aFAttach, gp_Dir(v1));
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(ll, aPntOffset), ll));
  }
  else
    aPrims->AddVertex(aSAttach);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntOffset);
}

void DsgPrs_IdenticPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const TCollection_ExtendedString&      aText,
                                     const gp_Ax2&                          theAxe,
                                     const gp_Pnt&                          aCenter,
                                     const gp_Pnt&                          aFAttach,
                                     const gp_Pnt&                          aSAttach,
                                     const gp_Pnt&                          aPntOffset)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Ax2 ax = theAxe;
  ax.SetLocation(aCenter);
  double  rad = aCenter.Distance(aFAttach);
  gp_Circ CC(ax, rad);
  double  pFAttach = ElCLib::Parameter(CC, aFAttach);
  double  pSAttach = ElCLib::Parameter(CC, aSAttach);
  double  alpha    = pSAttach - pFAttach;
  if (alpha < 0)
    alpha += 2. * M_PI;
  const int    nb    = (int)(50. * alpha / M_PI);
  const int    nbp   = std::max(4, nb);
  const double dteta = alpha / (nbp - 1);

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims;

  if (std::abs((aPntOffset.Distance(aCenter) - rad)) >= Precision::Confusion())
  {
    aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(2);
    aPrims->AddVertex(aPntOffset);
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(CC, aPntOffset), CC));
    aPrims->AddBound(nbp);
  }
  else
    aPrims = new Graphic3d_ArrayOfPolylines(nbp);

  for (int i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pFAttach + dteta * (i - 1), CC));

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntOffset);
}

void DsgPrs_IdenticPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const TCollection_ExtendedString&      aText,
                                     const gp_Ax2&                          theAxe,
                                     const gp_Pnt&                          aCenter,
                                     const gp_Pnt&                          aFAttach,
                                     const gp_Pnt&                          aSAttach,
                                     const gp_Pnt&                          aPntOffset,
                                     const gp_Pnt&                          aPntOnCirc)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Ax2 ax = theAxe;
  ax.SetLocation(aCenter);
  double  rad = aCenter.Distance(aFAttach);
  gp_Circ CC(ax, rad);
  double  pFAttach = ElCLib::Parameter(CC, aFAttach);
  double  pSAttach = ElCLib::Parameter(CC, aSAttach);
  double  alpha    = pSAttach - pFAttach;
  if (alpha < 0)
    alpha += 2. * M_PI;
  const int    nb    = (int)(50. * alpha / M_PI);
  const int    nbp   = std::max(4, nb);
  const double dteta = alpha / (nbp - 1);

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims;

  if (aPntOffset.Distance(aPntOnCirc) >= Precision::Confusion())
  {
    aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(2);
    aPrims->AddVertex(aPntOffset);
    aPrims->AddVertex(aPntOnCirc);
    aPrims->AddBound(nbp);
  }
  else
    aPrims = new Graphic3d_ArrayOfPolylines(nbp);

  for (int i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pFAttach + dteta * (i - 1), CC));

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntOffset);
}

void DsgPrs_IdenticPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                     const occ::handle<Prs3d_Drawer>&       aDrawer,
                                     const TCollection_ExtendedString&      aText,
                                     const gp_Elips&                        anEllipse,
                                     const gp_Pnt&                          aFAttach,
                                     const gp_Pnt&                          aSAttach,
                                     const gp_Pnt&                          aPntOffset,
                                     const gp_Pnt&                          aPntOnElli)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  double pFAttach = ElCLib::Parameter(anEllipse, aFAttach);
  double pSAttach = ElCLib::Parameter(anEllipse, aSAttach);
  double alpha    = pSAttach - pFAttach;
  if (alpha < 0)
    alpha += 2. * M_PI;
  const int    nb    = (int)(50.0 * alpha / M_PI);
  const int    nbp   = std::max(4, nb);
  const double dteta = alpha / (nbp - 1);

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims;

  if (!aPntOnElli.IsEqual(aPntOffset, Precision::Confusion()))
  {
    aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(2);
    aPrims->AddVertex(aPntOffset);
    aPrims->AddVertex(aPntOnElli);
    aPrims->AddBound(nbp);
  }
  else
    aPrims = new Graphic3d_ArrayOfPolylines(nbp);

  for (int i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pFAttach + dteta * (i - 1), anEllipse));

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aPntOffset);
}
