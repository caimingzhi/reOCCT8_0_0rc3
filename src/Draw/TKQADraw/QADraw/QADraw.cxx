#include <QADraw.hpp>

#include <QABugs.hpp>
#include <QADNaming.hpp>

#include <AIS_InteractiveContext.hpp>
#include <Bnd_Box.hpp>
#include <BRepBndLib.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <DBRep.hpp>
#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_PluginMacro.hpp>
#include <OSD_Timer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_XYZ.hpp>

#include <cstdio>

static int QATestExtremaSS(Draw_Interpretor& theInterpretor, int theArgNb, const char** theArgs)
{
  if (theArgNb < 3 || theArgNb > 4)
  {
    std::cerr << "Usage: type help " << theArgs[0] << std::endl;
    return 1;
  }

  TopoDS_Shape aShape = DBRep::Get(theArgs[1]);
  if (aShape.IsNull())
  {
    std::cerr << "Error: " << theArgs[1] << " shape is null\n";
    return 1;
  }

  const double aStep = Draw::Atof(theArgs[2]);
  if (aStep <= 1e-5)
  {
    std::cerr << "Error: Step " << aStep << " is too small\n";
    return 1;
  }

  Extrema_ExtFlag aFlag = Extrema_ExtFlag_MIN;
  if (theArgNb > 3)
  {
    int aVal = Draw::Atoi(theArgs[3]);
    if (aVal > 0)
    {
      aFlag = aVal == 1 ? Extrema_ExtFlag_MAX : Extrema_ExtFlag_MINMAX;
    }
  }

  Bnd_Box aBounds;
  BRepBndLib::Add(aShape, aBounds);

  double aXmin, aYmin, aZmin;
  double aXmax, aYmax, aZmax;
  aBounds.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  const double aScaleFactor = 1.5;
  aXmin *= aScaleFactor;
  aYmin *= aScaleFactor;
  aZmin *= aScaleFactor;
  aXmax *= aScaleFactor;
  aYmax *= aScaleFactor;
  aZmax *= aScaleFactor;

  NCollection_Sequence<TopoDS_Shape> aList;
  NCollection_Sequence<gp_XYZ>       aPoints;
  for (double aX = aXmin + 0.5 * aStep; aX < aXmax; aX += aStep)
  {
    for (double aY = aYmin + 0.5 * aStep; aY < aYmax; aY += aStep)
    {
      aList.Append(BRepBuilderAPI_MakeVertex(gp_Pnt(aX, aY, aZmin)));
      aList.Append(BRepBuilderAPI_MakeVertex(gp_Pnt(aX, aY, aZmax)));

      aPoints.Append(gp_XYZ(aX, aY, aZmin));
      aPoints.Append(gp_XYZ(aX, aY, aZmax));
    }

    for (double aZ = aZmin + 0.5 * aStep; aZ < aZmax; aZ += aStep)
    {
      aList.Append(BRepBuilderAPI_MakeVertex(gp_Pnt(aX, aYmin, aZ)));
      aList.Append(BRepBuilderAPI_MakeVertex(gp_Pnt(aX, aYmax, aZ)));

      aPoints.Append(gp_XYZ(aX, aYmin, aZ));
      aPoints.Append(gp_XYZ(aX, aYmax, aZ));
    }
  }

  for (double aY = aYmin + 0.5 * aStep; aY < aYmax; aY += aStep)
  {
    for (double aZ = aZmin + 0.5 * aStep; aZ < aZmax; aZ += aStep)
    {
      aList.Append(BRepBuilderAPI_MakeVertex(gp_Pnt(aXmin, aY, aZ)));
      aList.Append(BRepBuilderAPI_MakeVertex(gp_Pnt(aXmax, aY, aZ)));

      aPoints.Append(gp_XYZ(aXmin, aY, aZ));
      aPoints.Append(gp_XYZ(aXmax, aY, aZ));
    }
  }

  const int aNbPoints = aList.Length();
  theInterpretor << "Number of sampled points: " << aNbPoints << "\n";

  OSD_Timer aTimer;
  aTimer.Start();

  BRepExtrema_DistShapeShape aTool;
  aTool.SetFlag(aFlag);
  aTool.LoadS1(aShape);
  for (int anIdx = 1; anIdx <= aNbPoints; ++anIdx)
  {
    aTool.LoadS2(aList(anIdx));
    aTool.Perform();
  }

  aTimer.Stop();
  theInterpretor << "Test for gradient descent complete in: " << aTimer.ElapsedTime() << "\n";
  return 0;
}

void QADraw::CommonCommands(Draw_Interpretor& theCommands)
{
  const char* group = "QA_Commands";

  theCommands.Add("QATestExtremaSS",
                  "QATestExtremaSS Shape Step [Flag { MIN = 0 | MAX = 1 | MINMAX = 2 }]",
                  __FILE__,
                  QATestExtremaSS,
                  group);
}

void QADraw::Factory(Draw_Interpretor& theCommands)
{

  QADraw::CommonCommands(theCommands);
  QADraw::TutorialCommands(theCommands);

  QABugs::Commands(theCommands);
  QADNaming::AllCommands(theCommands);
}

DPLUGIN(QADraw)
