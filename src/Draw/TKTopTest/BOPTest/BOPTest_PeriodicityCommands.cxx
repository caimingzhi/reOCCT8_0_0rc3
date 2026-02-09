#include <BOPTest.hpp>

#include <BOPAlgo_MakePeriodic.hpp>

#include <BOPTest_DrawableShape.hpp>
#include <BOPTest_Objects.hpp>

#include <BRep_Builder.hpp>

#include <BRepTest_Objects.hpp>

#include <DBRep.hpp>
#include <Draw.hpp>

#include <TopoDS.hpp>

static int MakePeriodic(Draw_Interpretor&, int, const char**);
static int GetTwins(Draw_Interpretor&, int, const char**);
static int RepeatShape(Draw_Interpretor&, int, const char**);
static int ClearRepetitions(Draw_Interpretor&, int, const char**);

namespace
{
  static BOPAlgo_MakePeriodic& getPeriodicityMaker()
  {
    static BOPAlgo_MakePeriodic ThePeriodicityMaker;
    return ThePeriodicityMaker;
  }
} // namespace

void BOPTest::PeriodicityCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* group = "BOPTest commands";

  theCommands.Add("makeperiodic",
                  "makeperiodic result shape [-x/y/z period [-trim first]]\n"
                  "\t\tMake the shape periodic in the required directions.\n"
                  "\t\tresult        - resulting periodic shape;\n"
                  "\t\t-x/y/z period - option to make the shape periodic in X, Y or Z\n "
                  "\t\t                direction with the given period;\n"
                  "\t\t-trim first   - option to trim the shape to fit the required period,\n"
                  "\t\t                starting the period in first.",
                  __FILE__,
                  MakePeriodic,
                  group);

  theCommands.Add(
    "periodictwins",
    "periodictwins twins shape\n"
    "\t\tReturns the twins for the shape located on the opposite side of the periodic shape.",
    __FILE__,
    GetTwins,
    group);

  theCommands.Add(
    "repeatshape",
    "repeatshape result -x/y/z times\n"
    "\t\tRepeats the periodic shape in periodic directions required number of times.\n"
    "\t\tresult       - resulting shape;\n"
    "\t\t-x/y/z times - direction for repetition and number of repetitions.",
    __FILE__,
    RepeatShape,
    group);

  theCommands.Add("clearrepetitions",
                  "clearrepetitions [result]\n"
                  "\t\tClears all previous repetitions of the periodic shape.",
                  __FILE__,
                  ClearRepetitions,
                  group);
}

int MakePeriodic(Draw_Interpretor& theDI, int theArgc, const char** theArgv)
{
  if (theArgc < 5)
  {
    theDI.PrintHelp(theArgv[0]);
    return 1;
  }

  TopoDS_Shape aShape = DBRep::Get(theArgv[2]);
  if (aShape.IsNull())
  {
    theDI << "Error: " << theArgv[2] << " is a null shape.\n";
    return 1;
  }

  getPeriodicityMaker().Clear();
  getPeriodicityMaker().SetShape(aShape);

  for (int i = 3; i < theArgc;)
  {

    int iDir = i;

    int aDirID = -1;
    if (!strcasecmp(theArgv[i], "-x"))
      aDirID = 0;
    else if (!strcasecmp(theArgv[i], "-y"))
      aDirID = 1;
    else if (!strcasecmp(theArgv[i], "-z"))
      aDirID = 2;
    else
    {
      theDI << theArgv[i] << " - Invalid key\n";
      return 1;
    }

    char cDirName[2];
    Sprintf(cDirName, "%c", theArgv[iDir][1]);

    if (theArgc == (i + 1))
    {
      theDI << "Period for " << cDirName << " direction is not set\n";
      return 1;
    }

    double aPeriod = Draw::Atof(theArgv[++i]);

    getPeriodicityMaker().MakePeriodic(aDirID, true, aPeriod);

    ++i;
    if (theArgc > i + 1)
    {

      if (!strcmp(theArgv[i], "-trim"))
      {
        if (theArgc == (i + 1))
        {
          theDI << "Trim bounds for " << cDirName << " direction are not set\n";
          return 1;
        }
        double aFirst = Draw::Atof(theArgv[++i]);

        getPeriodicityMaker().SetTrimmed(aDirID, false, aFirst);
        ++i;
      }
    }
  }

  getPeriodicityMaker().SetRunParallel(BOPTest_Objects::RunParallel());

  getPeriodicityMaker().Perform();

  BOPTest::ReportAlerts(getPeriodicityMaker().GetReport());

  BRepTest_Objects::SetHistory(getPeriodicityMaker().History());

  if (getPeriodicityMaker().HasErrors())
  {
    return 0;
  }

  const TopoDS_Shape& aResult = getPeriodicityMaker().Shape();
  DBRep::Set(theArgv[1], aResult);

  return 0;
}

int GetTwins(Draw_Interpretor& theDI, int theArgc, const char** theArgv)
{
  if (theArgc != 3)
  {
    theDI.PrintHelp(theArgv[0]);
    return 1;
  }

  TopoDS_Shape aShape = DBRep::Get(theArgv[2]);
  if (aShape.IsNull())
  {
    theDI << "Error: " << theArgv[2] << " is a null shape.\n";
    return 1;
  }

  const NCollection_List<TopoDS_Shape>& aTwins = getPeriodicityMaker().GetTwins(aShape);

  TopoDS_Shape aCTwins;
  if (aTwins.IsEmpty())
    theDI << "No twins for the shape.\n";
  else if (aTwins.Extent() == 1)
    aCTwins = aTwins.First();
  else
  {
    BRep_Builder().MakeCompound(TopoDS::Compound(aCTwins));
    for (NCollection_List<TopoDS_Shape>::Iterator it(aTwins); it.More(); it.Next())
      BRep_Builder().Add(aCTwins, it.Value());
  }

  DBRep::Set(theArgv[1], aCTwins);

  return 0;
}

int RepeatShape(Draw_Interpretor& theDI, int theArgc, const char** theArgv)
{
  if (theArgc < 4)
  {
    theDI.PrintHelp(theArgv[0]);
    return 1;
  }

  for (int i = 2; i < theArgc; ++i)
  {
    int aDirID = -1;
    if (!strcasecmp(theArgv[i], "-x"))
      aDirID = 0;
    else if (!strcasecmp(theArgv[i], "-y"))
      aDirID = 1;
    else if (!strcasecmp(theArgv[i], "-z"))
      aDirID = 2;
    else
    {
      theDI << theArgv[i] << " - Invalid key\n";
      return 1;
    }

    char cDirName[2];
    Sprintf(cDirName, "%c", theArgv[i][1]);

    int aTimes = 0;
    if (theArgc > i + 1)
      aTimes = Draw::Atoi(theArgv[++i]);

    if (aTimes == 0)
    {
      theDI << "Number of repetitions for " << cDirName << " direction is not set\n";
      return 1;
    }

    getPeriodicityMaker().RepeatShape(aDirID, aTimes);
  }

  BOPTest::ReportAlerts(getPeriodicityMaker().GetReport());

  BRepTest_Objects::SetHistory(getPeriodicityMaker().History());

  if (getPeriodicityMaker().HasErrors())
  {
    return 0;
  }

  const TopoDS_Shape& aResult = getPeriodicityMaker().RepeatedShape();
  DBRep::Set(theArgv[1], aResult);

  return 0;
}

int ClearRepetitions(Draw_Interpretor&, int theArgc, const char** theArgv)
{

  getPeriodicityMaker().ClearRepetitions();

  BRepTest_Objects::SetHistory(getPeriodicityMaker().History());

  if (theArgc > 1)
  {
    DBRep::Set(theArgv[1], getPeriodicityMaker().Shape());
  }

  return 0;
}
