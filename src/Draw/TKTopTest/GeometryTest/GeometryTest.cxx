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
}
