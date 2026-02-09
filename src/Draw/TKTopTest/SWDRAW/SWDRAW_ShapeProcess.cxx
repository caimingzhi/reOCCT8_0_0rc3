#include <DBRep.hpp>
#include <Draw_Interpretor.hpp>
#include <ShapeProcess.hpp>
#include <ShapeProcess_OperLibrary.hpp>
#include <ShapeProcess_ShapeContext.hpp>
#include <SWDRAW.hpp>
#include <SWDRAW_ShapeProcess.hpp>
#include <TopoDS_Shape.hpp>

static int ApplySequence(Draw_Interpretor& di, int argc, const char** argv)
{
  if (argc < 4)
  {
    di << "Specify result, shape, resource name and prefix (optional)\n";
    return 1;
  }
  const char* arg1 = argv[1];
  const char* arg2 = argv[2];
  const char* arg3 = argv[3];
  const char* arg4 = "";
  if (argc > 4)
    arg4 = argv[4];
  TopoDS_Shape Shape = DBRep::Get(arg2);
  if (Shape.IsNull())
  {
    di << "Shape unknown : " << arg2 << "\n";
    return 1;
  }

  occ::handle<ShapeProcess_ShapeContext> context = new ShapeProcess_ShapeContext(Shape, arg3);
  ShapeProcess::Perform(context, arg4);
  context->PrintStatistics();

  TopoDS_Shape result = context->Result();

  if (result.IsNull())
  {
    di << "No result\n";
  }
  else if (result == Shape)
  {
    di << "Shape not modified\n";
  }
  DBRep::Set(arg1, result);
  return 0;
}

void SWDRAW_ShapeProcess::InitCommands(Draw_Interpretor& theCommands)
{
  static bool initactor = false;
  if (initactor)
  {
    return;
  }
  initactor = true;

  ShapeProcess_OperLibrary::Init();

  const char* g = SWDRAW::GroupName();

  theCommands.Add("SPApply",
                  "SPApply result shape rscfilename [sequence]",
                  __FILE__,
                  ApplySequence,
                  g);
}
