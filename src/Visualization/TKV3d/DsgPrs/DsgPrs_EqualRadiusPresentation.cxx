#include <DsgPrs.hpp>
#include <DsgPrs_EqualRadiusPresentation.hpp>
#include <gce_MakeDir.hpp>
#include <Geom_Plane.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_ArrayOfPolylines.hpp>
#include <Graphic3d_Group.hpp>
#include <Precision.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_EqualRadiusPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                         const occ::handle<Prs3d_Drawer>&       aDrawer,
                                         const gp_Pnt&                          FirstCenter,
                                         const gp_Pnt&                          SecondCenter,
                                         const gp_Pnt&                          FirstPoint,
                                         const gp_Pnt&                          SecondPoint,
                                         const occ::handle<Geom_Plane>&         Plane)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  occ::handle<Graphic3d_ArrayOfPolylines> aPrims = new Graphic3d_ArrayOfPolylines(4);
  aPrims->AddVertex(FirstPoint);
  aPrims->AddVertex(FirstCenter);
  aPrims->AddVertex(SecondCenter);
  aPrims->AddVertex(SecondPoint);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  gp_Dir FirstDir  = gce_MakeDir(FirstCenter, FirstPoint),
         SecondDir = gce_MakeDir(SecondCenter, SecondPoint);
  DsgPrs::ComputeSymbol(aPresentation,
                        LA,
                        FirstCenter,
                        FirstPoint,
                        FirstDir.Reversed(),
                        FirstDir,
                        DsgPrs_AS_FIRSTPT_LASTAR);
  DsgPrs::ComputeSymbol(aPresentation,
                        LA,
                        SecondCenter,
                        SecondPoint,
                        SecondDir.Reversed(),
                        SecondDir,
                        DsgPrs_AS_FIRSTPT_LASTAR);

  gp_Pnt Middle((FirstCenter.XYZ() + SecondCenter.XYZ()) * 0.5), aTextPos;
  double SmallDist;

  TCollection_ExtendedString aText("==");

  double Dist = FirstCenter.Distance(SecondCenter);
  if (Dist > Precision::Confusion())
  {
    SmallDist = Dist * 0.05;
    if (SmallDist <= Precision::Confusion())
      SmallDist = Dist;
    gp_Dir LineDir = gce_MakeDir(FirstCenter, SecondCenter);
    gp_Dir OrtDir  = Plane->Pln().Axis().Direction() ^ LineDir;

    gp_Vec OrtVec = gp_Vec(OrtDir) * SmallDist;

    aTextPos = Middle.Translated(OrtVec);
  }
  else
  {
    double Rad = std::max(FirstCenter.Distance(FirstPoint), SecondCenter.Distance(SecondPoint));

    SmallDist = Rad * 0.05;
    if (SmallDist <= Precision::Confusion())
      SmallDist = Rad;

    gp_Vec aVec(SmallDist, SmallDist, SmallDist);

    aTextPos = FirstCenter.Translated(aVec);
  }

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, aTextPos);
}
