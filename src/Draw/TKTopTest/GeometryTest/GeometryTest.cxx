#include <GeometryTest.hpp>
#include <GeomliteTest.hpp>
#include <Standard_Boolean.hpp>
#include <Draw_Interpretor.hpp>

void GeometryTest::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  GeomliteTest::AllCommands(theCommands);
  GeometryTest::CurveCommands(theCommands);
  GeometryTest::CurveTanCommands(theCommands);
  GeometryTest::FairCurveCommands(theCommands);
  GeometryTest::SurfaceCommands(theCommands);
  GeometryTest::ConstraintCommands(theCommands);
  GeometryTest::APICommands(theCommands);
  GeometryTest::ContinuityCommands(theCommands);
  GeometryTest::TestProjCommands(theCommands);
  GeometryTest::PolyCommands(theCommands);

  // define the TCL variable Draw_GEOMETRY
  // char* com = "set Draw_GEOMETRY 1";
  // theCommands.Eval(com);
  // char* com2 = "source $env(CASROOT)/src/DrawResources/CURVES.tcl";
  // theCommands.Eval(com2);
  // char* com3 = "source $env(CASROOT)/src/DrawResources/SURFACES.tcl";
  // theCommands.Eval(com3);
}
