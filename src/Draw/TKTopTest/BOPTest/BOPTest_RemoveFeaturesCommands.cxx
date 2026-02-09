#include <BOPTest.hpp>

#include <BOPTest_DrawableShape.hpp>
#include <BOPTest_Objects.hpp>

#include <BRep_Builder.hpp>

#include <BRepAlgoAPI_Defeaturing.hpp>

#include <BRepTest_Objects.hpp>

#include <DBRep.hpp>
#include <Draw_ProgressIndicator.hpp>

static int RemoveFeatures(Draw_Interpretor&, int, const char**);

void BOPTest::RemoveFeaturesCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  const char* group = "BOPTest commands";

  theCommands.Add("removefeatures",
                  "removefeatures result shape f1 f2 ... [-parallel]\n"
                  "\t\tRemoves user-defined features (faces) from the shape.\n"
                  "\t\tresult   - result of the operation;\n"
                  "\t\tshape    - the shape to remove the features from;\n"
                  "\t\tf1, f2   - features to remove from the shape;\n"
                  "\t\tparallel - enables the parallel processing mode.",
                  __FILE__,
                  RemoveFeatures,
                  group);
}

int RemoveFeatures(Draw_Interpretor& theDI, int theArgc, const char** theArgv)
{
  if (theArgc < 4)
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

  BRepAlgoAPI_Defeaturing aRF;
  aRF.SetShape(aShape);

  for (int i = 3; i < theArgc; ++i)
  {
    TopoDS_Shape aF = DBRep::Get(theArgv[i]);
    if (aF.IsNull())
    {
      if (!strcmp(theArgv[i], "-parallel"))
      {

        aRF.SetRunParallel(true);
      }
      else
        theDI << "Warning: " << theArgv[i] << " is a null shape. Skip it.\n";

      continue;
    }

    aRF.AddFaceToRemove(aF);
  }

  aRF.SetToFillHistory(BRepTest_Objects::IsHistoryNeeded());
  occ::handle<Draw_ProgressIndicator> aProgress = new Draw_ProgressIndicator(theDI, 1);

  aRF.Build(aProgress->Start());

  BOPTest::ReportAlerts(aRF.GetReport());

  if (BRepTest_Objects::IsHistoryNeeded())
    BRepTest_Objects::SetHistory(aRF.History());

  if (aRF.HasErrors())
    return 0;

  const TopoDS_Shape& aResult = aRF.Shape();
  DBRep::Set(theArgv[1], aResult);

  return 0;
}
