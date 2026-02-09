#include <QABugs.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <AIS_InteractiveContext.hpp>
#include <ViewerTest.hpp>

#include <V3d_View.hpp>
#include <Graphic3d_AspectMarker3d.hpp>

static int OCC281bug(Draw_Interpretor& di, int argc, const char** argv)
{
  occ::handle<AIS_InteractiveContext> aContext = ViewerTest::GetAISContext();
  if (aContext.IsNull())
  {
    std::cerr << "use 'vinit' command before " << argv[0] << "\n";
    return -1;
  }
  if (argc < 4)
  {
    di << "Usage : " << argv[0] << " x y TypeOfMarker(0-12)\n";
    return 1;
  }

  int x, y, TypeOfMarker;
  x            = Draw::Atoi(argv[1]);
  y            = Draw::Atoi(argv[2]);
  TypeOfMarker = Draw::Atoi(argv[3]);
  if (x <= 0)
  {
    di << "Bad value x=" << x << "\n";
    return 1;
  }
  if (y <= 0)
  {
    di << "Bad value y=" << y << "\n";
    return 1;
  }
  if (TypeOfMarker < 0 || TypeOfMarker > 12)
  {
    di << "Bad value TypeOfMarker=" << TypeOfMarker << "\n";
    return 1;
  }
  Aspect_TypeOfMarker AspectTypeOfMarker((Aspect_TypeOfMarker)TypeOfMarker);

  occ::handle<V3d_Viewer> aViewer = ViewerTest::GetViewerFromContext();
  occ::handle<V3d_View>   aView   = ViewerTest::CurrentView();

  aViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
  occ::handle<Graphic3d_AspectMarker3d> GridAsp =
    new Graphic3d_AspectMarker3d(AspectTypeOfMarker, Quantity_NOC_BLUE1, 10.);
  aViewer->SetGridEcho(GridAsp);

  if (aViewer->IsGridActive())
  {
    if (aViewer->GridEcho())
    {
      double X, Y, Z;
      aView->ConvertToGrid(x, y, X, Y, Z);
    }
    else
    {
      di << "NOT aViewer->GridEcho()\n";
      return 1;
    }
  }
  else
  {
    di << "NOT aViewer->IsActive()\n";
    return 1;
  }
  return 0;
}

void QABugs::Commands_6(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";

  theCommands.Add("OCC281", "OCC281 x y TypeOfMarker(0-12)", __FILE__, OCC281bug, group);

  return;
}
