

#include <StdPrs_HLRShape.hpp>

#include <BRepAdaptor_Curve.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <StdPrs_HLRToolShape.hpp>
#include <StdPrs_DeflectionCurve.hpp>
#include <TopoDS_Shape.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <HLRAlgo_Projector.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdPrs_HLRShape, StdPrs_HLRShapeI)

void StdPrs_HLRShape::ComputeHLR(const occ::handle<Prs3d_Presentation>& thePresentation,
                                 const TopoDS_Shape&                    theShape,
                                 const occ::handle<Prs3d_Drawer>&       theDrawer,
                                 const occ::handle<Graphic3d_Camera>&   theProjector) const
{
  gp_Dir  aBackDir = -theProjector->Direction();
  gp_Dir  aXpers   = theProjector->Up().Crossed(aBackDir);
  gp_Ax3  anAx3(theProjector->Center(), aBackDir, aXpers);
  gp_Trsf aTrsf;
  aTrsf.SetTransformation(anAx3);
  const HLRAlgo_Projector aProj(aTrsf, !theProjector->IsOrthographic(), theProjector->Scale());

  StdPrs_HLRToolShape          aTool(theShape, aProj);
  int                          aNbEdges = aTool.NbEdges();
  int                          anI;
  double                       anU1, anU2;
  BRepAdaptor_Curve            aCurve;
  double                       aDeviation = theDrawer->MaximalChordialDeviation();
  occ::handle<Graphic3d_Group> aGroup     = thePresentation->CurrentGroup();

  aGroup->SetPrimitivesAspect(theDrawer->SeenLineAspect()->Aspect());

  double                       anAngle = theDrawer->DeviationAngle();
  NCollection_Sequence<gp_Pnt> aPoints;
  for (anI = 1; anI <= aNbEdges; ++anI)
  {
    for (aTool.InitVisible(anI); aTool.MoreVisible(); aTool.NextVisible())
    {
      aTool.Visible(aCurve, anU1, anU2);
      StdPrs_DeflectionCurve::Add(thePresentation,
                                  aCurve,
                                  anU1,
                                  anU2,
                                  aDeviation,
                                  aPoints,
                                  anAngle);
    }
  }

  if (theDrawer->DrawHiddenLine())
  {
    aGroup->SetPrimitivesAspect(theDrawer->HiddenLineAspect()->Aspect());

    for (anI = 1; anI <= aNbEdges; ++anI)
    {
      for (aTool.InitHidden(anI); aTool.MoreHidden(); aTool.NextHidden())
      {
        aTool.Hidden(aCurve, anU1, anU2);
        StdPrs_DeflectionCurve::Add(thePresentation,
                                    aCurve,
                                    anU1,
                                    anU2,
                                    aDeviation,
                                    aPoints,
                                    anAngle);
      }
    }
  }
}
