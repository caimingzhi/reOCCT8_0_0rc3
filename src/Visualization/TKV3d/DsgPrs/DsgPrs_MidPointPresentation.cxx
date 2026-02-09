#include <DsgPrs_MidPointPresentation.hpp>
#include <ElCLib.hpp>
#include <gp_Ax2.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_ArrayOfSegments.hpp>
#include <Graphic3d_Group.hpp>
#include <Precision.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_MidPointPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const gp_Ax2&                          theAxe,
                                      const gp_Pnt&                          MidPoint,
                                      const gp_Pnt&                          Position,
                                      const gp_Pnt&                          AttachPoint,
                                      const bool                             first)
{
  double rad = AttachPoint.Distance(MidPoint) / 20.0;

  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  gp_Ax2 ax = theAxe;
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM(ax, rad);

  if (first)
  {

    aPresentation->NewGroup();
    aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

    const double alpha = 2. * M_PI;
    const int    nbp   = 100;
    const double dteta = alpha / (nbp - 1);

    occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(nbp);
    for (int i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta * (i - 1), aCircleM));

    aPrims->AddBound(2);

    aPrims->AddVertex(Position.IsEqual(MidPoint, rad)
                        ? MidPoint
                        : ElCLib::Value(ElCLib::Parameter(aCircleM, Position), aCircleM));

    aPrims->AddVertex(Position);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

    TCollection_ExtendedString aText(" (+)");
    Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, Position);
  }

  if (!AttachPoint.IsEqual(MidPoint, Precision::Confusion()))
  {
    if (!first)
    {
      aPresentation->NewGroup();
      aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
    }

    occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);

    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM, AttachPoint), aCircleM));

    aPrims->AddVertex(AttachPoint);
    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }
}

void DsgPrs_MidPointPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const gp_Ax2&                          theAxe,
                                      const gp_Pnt&                          MidPoint,
                                      const gp_Pnt&                          Position,
                                      const gp_Pnt&                          AttachPoint,
                                      const gp_Pnt&                          Point1,
                                      const gp_Pnt&                          Point2,
                                      const bool                             first)
{
  double rad = AttachPoint.Distance(MidPoint) / 20.0;
  if (rad <= Precision::Confusion())
    rad = Point1.Distance(Point2) / 20.0;

  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  gp_Ax2 ax = theAxe;
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM(ax, rad);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfPrimitives> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(Point1);
  aPrims->AddVertex(Point2);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  if (first)
  {

    const double alpha = 2. * M_PI;
    const int    nbp   = 100;
    const double dteta = alpha / (nbp - 1);

    aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(nbp);
    for (int i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta * (i - 1), aCircleM));

    aPrims->AddBound(2);

    aPrims->AddVertex(Position.IsEqual(MidPoint, rad)
                        ? MidPoint
                        : ElCLib::Value(ElCLib::Parameter(aCircleM, Position), aCircleM));

    aPrims->AddVertex(Position);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

    TCollection_ExtendedString aText(" (+)");
    Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, Position);
  }

  if (!AttachPoint.IsEqual(MidPoint, Precision::Confusion()))
  {

    aPrims = new Graphic3d_ArrayOfSegments(2);
    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM, AttachPoint), aCircleM));
    aPrims->AddVertex(AttachPoint);
    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }
}

void DsgPrs_MidPointPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const gp_Circ&                         aCircle,
                                      const gp_Pnt&                          MidPoint,
                                      const gp_Pnt&                          Position,
                                      const gp_Pnt&                          AttachPoint,
                                      const gp_Pnt&                          Point1,
                                      const gp_Pnt&                          Point2,
                                      const bool                             first)
{
  double rad = AttachPoint.Distance(MidPoint) / 20.0;
  if (rad <= Precision::Confusion())
    rad = Point1.Distance(Point2) / 20.0;

  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  gp_Ax2 ax = aCircle.Position();
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM(ax, rad);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  const double pf    = ElCLib::Parameter(aCircle, Point1);
  const double pl    = ElCLib::Parameter(aCircle, Point2);
  double       alpha = pl - pf;
  if (alpha < 0)
    alpha += 2. * M_PI;
  const int nb    = (int)(50.0 * alpha / M_PI);
  int       nbp   = std::max(4, nb);
  double    dteta = alpha / (nbp - 1);

  occ::handle<Graphic3d_ArrayOfPrimitives> aPrims = new Graphic3d_ArrayOfPolylines(nbp);
  for (int i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pf + dteta * (i - 1), aCircle));
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  if (first)
  {

    alpha = 2. * M_PI;
    nbp   = 100;
    dteta = alpha / (nbp - 1);

    aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(nbp);
    for (int i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta * (i - 1), aCircleM));

    aPrims->AddBound(2);

    aPrims->AddVertex(Position.IsEqual(MidPoint, rad)
                        ? MidPoint
                        : ElCLib::Value(ElCLib::Parameter(aCircleM, Position), aCircleM));

    aPrims->AddVertex(Position);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

    TCollection_ExtendedString aText(" (+)");
    Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, Position);
  }

  if (!AttachPoint.IsEqual(MidPoint, Precision::Confusion()))
  {

    aPrims = new Graphic3d_ArrayOfSegments(2);

    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM, AttachPoint), aCircleM));

    aPrims->AddVertex(AttachPoint);
    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }
}

void DsgPrs_MidPointPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const gp_Elips&                        aCircle,
                                      const gp_Pnt&                          MidPoint,
                                      const gp_Pnt&                          Position,
                                      const gp_Pnt&                          AttachPoint,
                                      const gp_Pnt&                          Point1,
                                      const gp_Pnt&                          Point2,
                                      const bool                             first)
{
  double rad = AttachPoint.Distance(MidPoint) / 20.0;
  if (rad <= Precision::Confusion())
    rad = Point1.Distance(Point2) / 20.0;

  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  gp_Ax2 ax = aCircle.Position();
  ax.SetLocation(MidPoint);
  gp_Circ aCircleM(ax, rad);

  aPresentation->NewGroup();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  const double pf    = ElCLib::Parameter(aCircle, Point1);
  const double pl    = ElCLib::Parameter(aCircle, Point2);
  double       alpha = pl - pf;
  if (alpha < 0)
    alpha += 2 * M_PI;
  const int nb    = (int)(50.0 * alpha / M_PI);
  int       nbp   = std::max(4, nb);
  double    dteta = alpha / (nbp - 1);

  occ::handle<Graphic3d_ArrayOfPrimitives> aPrims = new Graphic3d_ArrayOfPolylines(nbp);
  for (int i = 1; i <= nbp; i++)
    aPrims->AddVertex(ElCLib::Value(pf + dteta * (i - 1), aCircle));
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  if (first)
  {

    alpha = 2. * M_PI;
    nbp   = 100;
    dteta = alpha / (nbp - 1);

    aPrims = new Graphic3d_ArrayOfPolylines(nbp + 2, 2);
    aPrims->AddBound(nbp);
    for (int i = 1; i <= nbp; i++)
      aPrims->AddVertex(ElCLib::Value(dteta * (i - 1), aCircleM));

    aPrims->AddBound(2);

    aPrims->AddVertex(Position.IsEqual(MidPoint, rad)
                        ? MidPoint
                        : ElCLib::Value(ElCLib::Parameter(aCircleM, Position), aCircleM));

    aPrims->AddVertex(Position);

    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

    TCollection_ExtendedString aText(" (+)");
    Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, Position);
  }

  if (!AttachPoint.IsEqual(MidPoint, Precision::Confusion()))
  {

    aPrims = new Graphic3d_ArrayOfSegments(2);

    aPrims->AddVertex(ElCLib::Value(ElCLib::Parameter(aCircleM, AttachPoint), aCircleM));

    aPrims->AddVertex(AttachPoint);
    aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
  }
}
