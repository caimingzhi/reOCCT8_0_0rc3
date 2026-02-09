#include <DsgPrs_ConcentricPresentation.hpp>
#include <ElCLib.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>

void DsgPrs_ConcentricPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                        const occ::handle<Prs3d_Drawer>&       aDrawer,
                                        const gp_Pnt&                          aCenter,
                                        const double                           aRadius,
                                        const gp_Dir&                          aNorm,
                                        const gp_Pnt&                          aPoint)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();

  gp_Circ      Circ(gp_Ax2(aCenter, aNorm), aRadius);
  const int    nbp   = 50;
  const double dteta = (2. * M_PI) / nbp;

  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(2 * nbp + 6, 4);

  gp_Pnt pt1 = ElCLib::Value(0., Circ);
  aPrims->AddBound(nbp + 1);
  aPrims->AddVertex(pt1);
  double ucur = dteta;
  int    i;
  for (i = 2; i <= nbp; i++, ucur += dteta)
    aPrims->AddVertex(ElCLib::Value(ucur, Circ));
  aPrims->AddVertex(pt1);

  Circ.SetRadius(0.5 * aRadius);
  pt1 = ElCLib::Value(0., Circ);
  aPrims->AddBound(nbp + 1);
  aPrims->AddVertex(pt1);
  ucur = dteta;
  for (i = 2; i <= nbp; i++, ucur += dteta)
    aPrims->AddVertex(ElCLib::Value(ucur, Circ));
  aPrims->AddVertex(pt1);

  gp_Dir vecnorm(aPoint.XYZ() - aCenter.XYZ());
  gp_Vec vec(vecnorm);
  vec.Multiply(aRadius);
  gp_Pnt p1 = aCenter.Translated(vec);
  gp_Pnt p2 = aCenter.Translated(-vec);

  aPrims->AddBound(2);
  aPrims->AddVertex(p1);
  aPrims->AddVertex(p2);

  vec.Cross(aNorm);
  vecnorm.SetCoord(vec.X(), vec.Y(), vec.Z());
  vec.SetXYZ(vecnorm.XYZ());
  vec.Multiply(aRadius);
  p1 = aCenter.Translated(vec);
  p2 = aCenter.Translated(-vec);

  aPrims->AddBound(2);
  aPrims->AddVertex(p1);
  aPrims->AddVertex(p2);

  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);
}
