#include <GeomliteTest.hpp>
#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>

void GeomliteTest::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  GeomliteTest::CurveCommands(theCommands);
  GeomliteTest::SurfaceCommands(theCommands);
  GeomliteTest::ApproxCommands(theCommands);
  GeomliteTest::API2dCommands(theCommands);
  GeomliteTest::ModificationCommands(theCommands);

  // define the TCL variable Draw_GEOMETRY
  // char* com = "set Draw_GEOMETRY 1";
  // theCommands.Eval(com);
}
