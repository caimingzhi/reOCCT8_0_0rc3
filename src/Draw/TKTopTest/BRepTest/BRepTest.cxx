#include <BRepTest.hpp>
#include <DBRep.hpp>

void BRepTest::AllCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  DBRep::BasicCommands(theCommands);
  BRepTest::BasicCommands(theCommands);
  BRepTest::CurveCommands(theCommands);
  BRepTest::Fillet2DCommands(theCommands);
  BRepTest::SurfaceCommands(theCommands);
  BRepTest::FillingCommands(theCommands);
  BRepTest::PrimitiveCommands(theCommands);
  BRepTest::SweepCommands(theCommands);
  BRepTest::TopologyCommands(theCommands);
  BRepTest::FilletCommands(theCommands);
  BRepTest::ChamferCommands(theCommands);
  BRepTest::GPropCommands(theCommands);
  BRepTest::MatCommands(theCommands);
  BRepTest::DraftAngleCommands(theCommands);
  BRepTest::FeatureCommands(theCommands);
  BRepTest::OtherCommands(theCommands);
  BRepTest::ExtremaCommands(theCommands);
  BRepTest::CheckCommands(theCommands);

  BRepTest::ProjectionCommands(theCommands);
  BRepTest::HistoryCommands(theCommands);
  BRepTest::HelixCommands(theCommands);

  const char* com = "set Draw_TOPOLOGY 1";
  theCommands.Eval(com);
}
